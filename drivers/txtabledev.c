/*DEVICE DRIVER FILE
--------------------------------------------------------------------------------
--!@brief DEVICE DRIVER DO TXTABLEDEV
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! DRIVER DO DISPOSITIVO TXTABLEDEV PARA UCLINUX
--!
--! DETAILS:      
--!
--!- Project Name: txtabledev
--!- Module Name: txtabledev.c
--!- Tools: jedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
--!- Create Date: 22/01/2014     
--!- Version: 1.0.0 (jan/2014) 
--------------------------------------------------------------------------------
-- LNLS - DET - 2014
--------------------------------------------------------------------------------
Header*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/gfp.h>
#include <linux/kdev_t.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define IORD(address,offset)		(*(volatile unsigned *)(((address)|0x80000000)+4*(offset)))
#define IOWR(address,offset,value)	(*(volatile unsigned *)(((address)|0x80000000)+4*(offset)))=(value)

#define TABLE_TX_BASE		0x08000000
#define TABLE_TX_SIZE		0x10
#define BUF_SIZE			192
#define PACKET_SIZE			188
#define DEVICE_NAME			"txtabledev"
#define DEVICE_MAJOR		244
#define DEVICE_MINOR		0

#define RXDATA_OFFSET		0
#define TXDATA_OFFSET		1
#define STATUS_OFFSET		2
#define CONTROL_OFFSET		3
#define IRQR_OFFSET			2
#define IRQR_MASK			0x80000000
#define IRQR_SHIFT			31
#define BUSY_OFFSET			2
#define BUSY_MASK			0x40000000
#define BUSY_SHIFT			30
#define RDEN_OFFSET			3
#define RDEN_MASK			0x80000000
#define RDEN_SHIFT			31
#define RRDY_OFFSET			3
#define RRDY_MASK			0x40000000
#define RRDY_SHIFT			30
#define WREN_OFFSET			3
#define WREN_MASK			0x20000000
#define WREN_SHIFT			29
#define WRDY_OFFSET			3
#define WRDY_MASK			0x10000000
#define WRDY_SHIFT			28
#define INFO_OFFSET			3
#define INFO_MASK			0x00FF0000
#define INFO_SHIFT			16
#define ADDR_OFFSET			3
#define ADDR_MASK			0x000000FF
#define ADDR_SHIFT			0

#define	IIP_TR_EN		49
#define	CTS_NX_EN		50
#define	IIP_ST_EN		51
#define	SFN_EN			257
#define	CTS_CR_EN		258
#define	READ_BLOCK		259
#define	READ_NO_BLOCK	260
#define	WRITE_BLOCK		261
#define	WRITE_NO_BLOCK	262
#define DEV_IO_ON		263
#define DEV_IO_OFF		264
#define ASI_BYTE		265
#define ASI_PACKET		266
#define TEST_OFF		267
#define TEST_NULL		268
#define TEST_PN9		269
#define TEST_PN15		270
#define TEST_PN23		271
#define TEST_PN_RND		272
#define	CMUX_IFX		273
#define	CMUX_MUX		274
#define	CLEARVN_H		275
#define	CLEARVN_L		276
#define CPID_IO_ON		277
#define CPID_IO_OFF		278

#define DEBUG

/* Prototypes */
static void write_to_dev(unsigned int DEV, const unsigned char *buf, unsigned char id, size_t count);
static void table_tsklt(void);
static int table_open(struct inode *inode, struct file *file);
static int table_release(struct inode *inode, struct file *file);
static loff_t table_llseek(struct file *file, loff_t offset, int orig);
static int table_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t table_read(struct file *file, char __user *buf, size_t count, loff_t *ppos);
static ssize_t table_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
static int __init table_init(void);
static void __exit table_cleanup(void);

/* Per-Device structure */
static struct table_dev {
	struct cdev cdev;		/* Character device struct */
	struct tasklet_struct tsklt;	/* Tasklet struct */
} *table_devp;

/* File Operations struct */
static struct file_operations table_fops = {
	.owner =	THIS_MODULE,	/* Owner */
	.open =		table_open,    	/* Open method */
	.release =	table_release, 	/* Release method */
	.read =		table_read,    	/* Read method */
	.write =	table_write,   	/* Write method */
	.llseek =	table_llseek,  	/* Seek method */
	.ioctl =	table_ioctl   	/* Ioctl method */
};

/* Alloted device Number */
static dev_t table_dev_number = MKDEV(DEVICE_MAJOR, DEVICE_MINOR);
/* Number of minors handled by major */
static int table_dev_count = 1;
/* Access control */
static int table_is_open = 0;
/* Tie with the device model */
static struct class *txtable_class;	

/* Device data */
static int current_pointer;
static int table_rd_mode;
static int table_wr_mode;
static int table_cpid_io;
static int table_dev_io;
static unsigned char *table_rd_buf;
static unsigned char *table_wr_buf;
static unsigned char *table_cpid_buf;
/* NULL Packet */
static unsigned char null_packet[192] = {
	0x47, 0x1F, 0xFF, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0A
};

/* Write to Device */
static void
write_to_dev(unsigned int DEV, const unsigned char *buf, unsigned char id, size_t count)
{	
	unsigned int txdata;
	unsigned int status;
	unsigned int control;
	unsigned int addr;
	unsigned int busy;
	unsigned int wrdy;

	/* Wait for device availability */
	do {
		status = IORD(DEV, STATUS_OFFSET); /* Read status register */
		busy = (status & BUSY_MASK) >> BUSY_SHIFT; /* Get BUSY flag */
	} while (busy);

	/* Write operations */
	for (addr = 0; addr < (count / 4); addr++) {
		/* TXDATA */
		txdata = 
			buf[4 * addr] << 24 |
			buf[(4 * addr) + 1] << 16 | 
			buf[(4 * addr) + 2] << 8 | 
			buf[(4 * addr) + 3];
		IOWR(DEV, TXDATA_OFFSET, txdata); /* Apply data */

		/* Control */
		control = IORD(DEV, CONTROL_OFFSET); /* Read control register */
		control &= ~ADDR_MASK; /* Reset address */
		control += addr; /* Set write address */
		IOWR(DEV, CONTROL_OFFSET, control); /* Apply write address */
		control |= WREN_MASK; /* Set WREN flag */
		IOWR(DEV, CONTROL_OFFSET, control); /* Apply WREN flag */

		/* Wait for write operation to complete */
		do {
			control = IORD(DEV, CONTROL_OFFSET); /* Read control register */
			wrdy = (control & WRDY_MASK) >> WRDY_SHIFT; /* Get WRDY flag */
		} while (!wrdy);
        
		control &= ~WREN_MASK; /* Clear WREN flag */
		control &= ~WRDY_MASK; /* Clear WRDY flag */
		IOWR(DEV, CONTROL_OFFSET, control); /* Apply */      
	}

	/* New data available */
	control &= ~INFO_MASK; /* Reset info */
	control |= buf[BUF_SIZE - 1] << INFO_SHIFT; /* Set info field */
	IOWR(DEV, CONTROL_OFFSET, control); /* Apply */
	status = IORD(DEV, STATUS_OFFSET); /* Read status register */
	status |= IRQR_MASK; /* Set IRQR flag */
	IOWR(DEV, STATUS_OFFSET, status); /* Apply */
   
#ifdef DEBUG
	printk(KERN_ALERT "TXTABLEDEV: write_to_dev [%02X]\n", buf[2]);
#endif
}

/* Tasklet */
static void
table_tsklt(void)
{
	int i;
	int table_id;
	int buffer_pointer;

	/* Write to buffer */
	memcpy(table_rd_buf, table_wr_buf, BUF_SIZE);

	/* Check for Control PID */
	if (table_rd_buf[0] == 0x47 && table_rd_buf[1] == 0x40 && table_rd_buf[2] == 0x03) {
		table_id = table_rd_buf[5]; /* byte 6 */
		/* Old CPID */
		if (!table_id) {
			buffer_pointer = 0;
			memset(table_cpid_buf, 0x0, PACKET_SIZE * 16);			
		}
		/* New CPID */
		if (table_id < 159 && table_id > 149) { /* New Table ID 150~158 */
			buffer_pointer = table_id - 150;
		}
		memcpy(table_cpid_buf + (buffer_pointer * PACKET_SIZE), table_rd_buf, PACKET_SIZE);
	}

	/* Write to output device */
	if (table_dev_io == DEV_IO_ON) {
		if (table_cpid_io == CPID_IO_ON) { /* May also write Control PIDs */
			for (i = 0; i < 9; i++) {
				if (table_cpid_buf[i * PACKET_SIZE])
					write_to_dev(TABLE_TX_BASE, table_cpid_buf + (i * PACKET_SIZE), 0x0, PACKET_SIZE);
			}
		}
		write_to_dev(TABLE_TX_BASE, table_rd_buf, 0x0, PACKET_SIZE); /* Packet write */
		/* write_to_dev(TABLE_TX_BASE, null_packet, 0x0, PACKET_SIZE); */
	}

#ifdef DEBUG
	printk(KERN_ALERT "TXTABLEDEV: tasklet\n");
#endif
}

/* Open Handler */
static int 
table_open(struct inode *inode, struct file *file)
{
	if (table_is_open) {
#ifdef DEBUG
		printk(KERN_ALERT "TABLEDEV: device busy\n");
#endif
		return -EBUSY;
	}

	++table_is_open;
	try_module_get(THIS_MODULE);		

#ifdef DEBUG
	printk(KERN_ALERT "TXTABLEDEV: open\n");
#endif
	return 0;
}

/* Release/Close Handler */
static int 
table_release(struct inode *inode, struct file *file)
{	
	--table_is_open;			
	module_put(THIS_MODULE);

	/* Reset file pointer */
	current_pointer = 0;

#ifdef DEBUG
	printk(KERN_ALERT "TXTABLEDEV: release\n");
#endif
	return 0;
}

/* Seek Handler */
static loff_t
table_llseek(struct file *file, loff_t offset, int orig)
{
	int pointer;

	/* Seek switch */
	switch (orig) {
		/* SEEK_SET */
		case 0:
			pointer = offset;
			break;

		/* SEEK_CUR */
		case 1: 
			pointer = current_pointer + offset;
			break;

		/* SEEK_END */
		case 2:
			pointer = BUF_SIZE + offset;
			break;

		/* Error */
		default: 
		return -EINVAL;
	}

	/* Can't write beyond the device */
	if (pointer < 0 || pointer > BUF_SIZE) {
		return -EINVAL;
	}

	current_pointer = pointer;
#ifdef DEBUG
	printk(KERN_ALERT "TXTABLEDEV: llseek [%d]\n", pointer);
#endif
	return pointer;
}

/* I/O Control Handler */
static int 
table_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	/* Loop through I/O control commands */
	switch (cmd) {
		/* Blocking Read */
		case READ_BLOCK:
			table_rd_mode = READ_BLOCK;
			break;

		/* Non-Blocking Read */
		case READ_NO_BLOCK:
			table_rd_mode = READ_NO_BLOCK;
			break;

		/* Blocking Write */
		case WRITE_BLOCK:
			table_wr_mode = WRITE_BLOCK;
			break;

		/* Non-Blocking Write */
		case WRITE_NO_BLOCK:
			table_wr_mode = WRITE_NO_BLOCK;
			break;

		/* Output Enable */
		case DEV_IO_ON:
			table_dev_io = DEV_IO_ON;
			break;

		/* Output Enable */
		case DEV_IO_OFF:
			table_dev_io = DEV_IO_OFF;
			break;

		/* Control PID Enable */
		case CPID_IO_ON:
			table_cpid_io = CPID_IO_ON;
			break;

		/* Control PID Enable */
		case CPID_IO_OFF:
			table_cpid_io = CPID_IO_OFF;
			break;

		/* Error */
		default:
			return -EIO;		
	}

	/* Reset file pointer */
	current_pointer = 0;
#ifdef DEBUG
	printk(KERN_ALERT "TXTABLEDEV: ioctl [%u]\n", cmd);
#endif
	return 0;
}

/* Read Handler */
static ssize_t
table_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	int remaining_size;
	int transfer_size;
		
	remaining_size = BUF_SIZE - current_pointer; /* Bytes left to transfer */
	if (!remaining_size) { /* Reached EOF */
		return 0;
	}	

	/* Size of this transfer */
	if (count > remaining_size) {
		transfer_size = remaining_size; 	
	} else {
		transfer_size = count;
	}

	/* Copy data to userspace */
	if (copy_to_user(buf /* to */, table_rd_buf + current_pointer /* from */, transfer_size)) {
		return -EFAULT;
	} else {
		/* Increase the position in the open file */
		current_pointer += transfer_size;
#ifdef DEBUG
		printk(KERN_ALERT "TXTABLEDEV: read\n");
#endif
		return transfer_size;
	}
}

/* Write Handler */
static ssize_t
table_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	int remaining_bytes;

	/* Number of writable bytes */
	remaining_bytes = BUF_SIZE - current_pointer;

	if (count > remaining_bytes) {
		/* Can't write beyond the end of the device */
		return -EIO;
	}

	/* Copy data from userspace */
	if (copy_from_user(table_wr_buf + current_pointer /* to */, buf /* from */, count)) {
		return -EFAULT;
	} else {
		/* Increase the position in the open file */
		current_pointer += count;
		/* Handle data */
		tasklet_schedule(&table_devp->tsklt);
#ifdef DEBUG
		printk(KERN_ALERT "TXTABLEDEV: write\n");	
#endif	
		return count;
	}
}

/* Driver Initialization */
static int __init 
table_init(void)
{
	int ret;

	/* Request allocation of device major number */
	if (register_chrdev_region(table_dev_number, table_dev_count, DEVICE_NAME)) {
		printk(KERN_ERR "Can't register device\n"); 
		return -ENODEV;
    	}

	/* Populate sysfs entries */  
	txtable_class = class_create(THIS_MODULE, DEVICE_NAME);

	/* Allocate memory for the per-device structure */
	table_devp = (struct table_dev*) kmalloc(sizeof (struct table_dev), GFP_KERNEL);
	if (!table_devp) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}

	/* Allocate memory for the device buffers */
	table_rd_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!table_rd_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	table_wr_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!table_wr_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	table_cpid_buf = (unsigned char*) kmalloc(PACKET_SIZE * 16, GFP_KERNEL);
	if (!table_cpid_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	
	/* Request I/O regions */
	if (!request_region(TABLE_TX_BASE, TABLE_TX_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "TXTABLEDEV: I/O port 0x%x is not free.\n", TABLE_TX_BASE);
		return -EIO;
	}
	
	/* Connect the file operations with the cdev */
	cdev_init(&table_devp->cdev, &table_fops);
	table_devp->cdev.owner = THIS_MODULE;

	ret = cdev_add(/* cdev structure for the device */ &table_devp->cdev, 
			/* first device number for which this device is responsible */ table_dev_number, 
			/* number of consecutive minor numbers corresponding to this device */ table_dev_count);

	if (ret) {
		printk(KERN_ERR "Bad cdev\n");
		return ret;
	}

	/* Tie with the device model */
	device_create(txtable_class, NULL, table_dev_number, NULL, DEVICE_NAME);

	/* Initialize tasklet */
	tasklet_init(&table_devp->tsklt, table_tsklt, NULL);

	/* Initialize defaults */
	current_pointer = 0;
	table_rd_mode = READ_BLOCK;
	table_wr_mode = WRITE_BLOCK;
	table_cpid_io = CPID_IO_OFF;
	table_dev_io = DEV_IO_ON;
	memset(table_rd_buf, 0xFF, BUF_SIZE);
	memset(table_wr_buf, 0xFF, BUF_SIZE);
	memset(table_cpid_buf, 0x0, BUF_SIZE);

	/* Initialize hardware */
	IOWR(TABLE_TX_BASE, STATUS_OFFSET, 0x0);
	IOWR(TABLE_TX_BASE, CONTROL_OFFSET, 0x0);

	/* All Done! */
	printk(KERN_ALERT "TXTABLEDEV Driver Initialized\n");
	return 0;
}

/* Driver Exit */
static void __exit
table_cleanup(void)
{
	cdev_del(&table_devp->cdev);
	unregister_chrdev_region(table_dev_number, table_dev_count);
	device_destroy(txtable_class, table_dev_number);
	class_destroy(txtable_class);
	release_region(TABLE_TX_BASE, TABLE_TX_SIZE);
	kfree(table_devp);
	kfree(table_rd_buf);
	kfree(table_wr_buf);

	return;
}

module_init(table_init);
module_exit(table_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Franz Wagner");

