/*DEVICE DRIVER FILE
        --------------------------------------------------------------------------------
        --!@brief DEVICE DRIVER DO RXTABLEDEV
        --------------------------------------------------------------------------------                                                                      
        --! DESCRIPTION:
        --!
        --! DRIVER DO DISPOSITIVO RXTABLEDEV PARA UCLINUX
        --!
        --! DETAILS:      
        --!
        --!- Project Name: rxtabledev    
        --!- Module Name: rxtabledev.c
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

#define TABLE_RX_BASE		0x02810170
#define TABLE_RX_SIZE		0x10
#define TABLE_RX_IRQ		7
#define BUF_SIZE		192
#define PACKET_SIZE		188
#define DEVICE_NAME		"rxtabledev"
#define DEVICE_MAJOR		245
#define DEVICE_MINOR		0

#define RXDATA_OFFSET		0
#define TXDATA_OFFSET		1
#define STATUS_OFFSET		2
#define CONTROL_OFFSET		3
#define IRQR_OFFSET		2
#define IRQR_MASK		0x80000000
#define IRQR_SHIFT		31
#define BUSY_OFFSET		2
#define BUSY_MASK		0x40000000
#define BUSY_SHIFT		30
#define RDEN_OFFSET		3
#define RDEN_MASK		0x80000000
#define RDEN_SHIFT		31
#define RRDY_OFFSET		3
#define RRDY_MASK		0x40000000
#define RRDY_SHIFT		30
#define WREN_OFFSET		3
#define WREN_MASK		0x20000000
#define WREN_SHIFT		29
#define WRDY_OFFSET		3
#define WRDY_MASK		0x10000000
#define WRDY_SHIFT		28
#define INFO_OFFSET		3
#define INFO_MASK		0x00FF0000
#define INFO_SHIFT		16
#define ADDR_OFFSET		3
#define ADDR_MASK		0x000000FF
#define ADDR_SHIFT		0

#define	IIP_TR_EN		49
#define	CTS_NX_EN		50
#define	IIP_ST_EN		51
#define	SFN_EN			257
#define	CTS_CR_EN		258
#define	READ_BLOCK		259
#define	READ_NO_BLOCK		260
#define	WRITE_BLOCK		261
#define	WRITE_NO_BLOCK		262
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
static irqreturn_t table_interrupt(int irq, void *dev_id);
static unsigned int read_from_dev(unsigned int DEV, unsigned char *buf, size_t count);
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
	wait_queue_head_t queue;	/* Wait queue */
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
static struct class *rxtable_class;	

/* Device data */
static int current_pointer;
static int table_rd_mode;
static int table_wr_mode;
static int table_dev_io;
static int table_rd_flag;
static int table_wr_flag;
static unsigned char *table_rd_buf;
static unsigned char *table_wr_buf;

/* Read from Device */
static unsigned int
read_from_dev(unsigned int DEV, unsigned char *buf, size_t count)
{	
	unsigned int rxdata;
	unsigned int status;
	unsigned int control;
	unsigned int info;
	unsigned int addr;
	unsigned int busy;
	unsigned int rrdy;

	/* Read operations */
	for (addr = 0; addr < (count / 4); addr++) {
		/* Control */
		control = IORD(DEV, CONTROL_OFFSET); /* Read control register */
		info = (control & INFO_MASK) >> INFO_SHIFT; /* Get info field */
		buf[BUF_SIZE - 1] = info; /* Store info field */
		control &= ~ADDR_MASK; /* Reset address */
		control += addr; /* Set read address */
		IOWR(DEV, CONTROL_OFFSET, control); /* Apply read address */
		control |= RDEN_MASK; /* Set RDEN flag */
		IOWR(DEV, CONTROL_OFFSET, control); /* Apply RDEN flag */

		/* Wait for read operation to complete */
		do {
			control = IORD(DEV, CONTROL_OFFSET); /* Read control register */
			rrdy = (control & RRDY_MASK) >> RRDY_SHIFT; /* Get RRDY flag */
		} while (!rrdy);

		/* RXDATA */
		rxdata = IORD(DEV, RXDATA_OFFSET); /* Read data */
		/* Store data */
		buf[4 * addr] =  (rxdata & 0xFF000000) >> 24;
		buf[(4 * addr) + 1] = (rxdata & 0x00FF0000) >> 16; 
		buf[(4 * addr) + 2] =  (rxdata & 0x0000FF00) >> 8; 
		buf[(4 * addr) + 3] = rxdata & 0x000000FF; 		
        
		control &= ~RDEN_MASK; /* Clear RDEN flag */
		control &= ~RRDY_MASK; /* Clear RRDY flag */
		IOWR(DEV, CONTROL_OFFSET, control); /* Apply */        
	}
   
#ifdef DEBUG
	printk(KERN_ALERT "RXTABLEDEV: read_from_dev [%08X_%02u]\n", 
		(buf[0] << 24) |
		(buf[1] << 16) |
		(buf[2] << 8) |
		buf[3],
		info);
#endif
	return info;
}

/* ISR */
static irqreturn_t
table_interrupt(int irq, void *dev_id)
{
	unsigned int status;

	status = IORD(TABLE_RX_BASE, STATUS_OFFSET); /* Read status register */
	status &= ~IRQR_MASK; /* Clear IRQR flag */
	IOWR(TABLE_RX_BASE, STATUS_OFFSET, status); /* Apply */

	/* Handle data */
	tasklet_schedule(&table_devp->tsklt);
	
	/* All Done! */
	return IRQ_HANDLED;
}

/* Bottom Half Tasklet */
static void
table_tsklt(void)
{
	/* Read from input device */
	if (table_dev_io == DEV_IO_ON) {
		read_from_dev(TABLE_RX_BASE, table_rd_buf, PACKET_SIZE);
	}
	
	/* New data available */
	table_rd_flag = 1;

	/* Wake up waiting process */
	if (table_rd_mode == READ_BLOCK) {
		wake_up_interruptible(&table_devp->queue);
	}	

#ifdef DEBUG
	//printk(KERN_ALERT "RXTABLEDEV: bottom half\n");
#endif
}

/* Open Handler */
static int
table_open(struct inode *inode, struct file *file)
{
	if (table_is_open) {
#ifdef DEBUG
		printk(KERN_ALERT "RXTABLEDEV: device busy\n");
#endif
		return -EBUSY;
	}

	++table_is_open;
	try_module_get(THIS_MODULE);		

#ifdef DEBUG
	//printk(KERN_ALERT "RXTABLEDEV: open\n");
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
	//printk(KERN_ALERT "RXTABLEDEV: release\n");
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
	//printk(KERN_ALERT "RXTABLEDEV: llseek [%d]\n", pointer);
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

		/* Error */
		default:
			return -EIO;		
	}

	/* Reset file pointer */
	current_pointer = 0;
#ifdef DEBUG
	//printk(KERN_ALERT "RXTABLEDEV: ioctl [%u]\n", cmd);
#endif
	return 0;
}

/* Read Handler */
static ssize_t
table_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	int remaining_size;
	int transfer_size;
	unsigned int status;
		
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

	/* Wait for data availability */
	if (table_rd_mode == READ_BLOCK) {
		wait_event_interruptible(table_devp->queue, table_rd_flag != 0);
	}
	table_rd_flag = 0;

	/* Copy data to userspace */
	if (copy_to_user(buf /* to */, table_rd_buf + current_pointer /* from */, transfer_size)) {

		status = IORD(TABLE_RX_BASE, STATUS_OFFSET); /* Read status register */
		status &= ~BUSY_MASK; /* Clear BUSY flag */
		IOWR(TABLE_RX_BASE, STATUS_OFFSET, status); /* Apply */

		return -EFAULT;
	} else {
		/* Increase the position in the open file */
		current_pointer += transfer_size;

		status = IORD(TABLE_RX_BASE, STATUS_OFFSET); /* Read status register */
		status &= ~BUSY_MASK; /* Clear BUSY flag */
		IOWR(TABLE_RX_BASE, STATUS_OFFSET, status); /* Apply */
#ifdef DEBUG
		printk(KERN_ALERT "RXTABLEDEV: read [busy = 0]\n");
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
		memcpy(table_rd_buf, table_wr_buf, BUF_SIZE);
#ifdef DEBUG
		printk(KERN_ALERT "RXTABLEDEV: write\n");	
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
	rxtable_class = class_create(THIS_MODULE, DEVICE_NAME);

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
	
	/* Request I/O regions */
	if (!request_region(TABLE_RX_BASE, TABLE_RX_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "RXTABLEDEV: I/O port 0x%x is not free.\n", TABLE_RX_BASE);
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
	device_create(rxtable_class, NULL, table_dev_number, NULL, DEVICE_NAME);

	/* Request IRQ and register ISR */
	if (request_irq(TABLE_RX_IRQ, table_interrupt, IRQF_DISABLED | IRQF_TRIGGER_RISING, DEVICE_NAME, NULL)) {
		printk(KERN_ERR "Bad request_irq\n"); 
		return -EIO;
	}

	/* Initialize tasklet */
	tasklet_init(&table_devp->tsklt, table_tsklt, NULL);

	/* Initialize wait queue */
	init_waitqueue_head(&table_devp->queue);

	/* Initialize defaults */
	current_pointer = 0;
	table_rd_mode = READ_BLOCK;
	table_wr_mode = WRITE_BLOCK;
	table_dev_io = DEV_IO_ON;
	table_rd_flag = 0;
	table_wr_flag = 0;
	memset(table_rd_buf, 0xFF, BUF_SIZE);
	memset(table_wr_buf, 0xFF, BUF_SIZE);

	/* Initialize hardware */
	IOWR(TABLE_RX_BASE, STATUS_OFFSET, 0x0);
	IOWR(TABLE_RX_BASE, CONTROL_OFFSET, 0x0);

	/* All Done! */
	printk(KERN_ALERT "RXTABLEDEV Driver Initialized\n");
	return 0;
}

/* Driver Exit */
static void __exit
table_cleanup(void)
{
	disable_irq(TABLE_RX_IRQ);
	free_irq(TABLE_RX_IRQ, NULL);
	cdev_del(&table_devp->cdev);
	unregister_chrdev_region(table_dev_number, table_dev_count);
	device_destroy(rxtable_class, table_dev_number);
	class_destroy(rxtable_class);
	release_region(TABLE_RX_BASE, TABLE_RX_SIZE);
	kfree(table_devp);
	kfree(table_rd_buf);
	kfree(table_wr_buf);

	return;
}

module_init(table_init);
module_exit(table_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Franz Wagner");

