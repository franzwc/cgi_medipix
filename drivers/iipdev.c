/*DEVICE DRIVER FILE
--------------------------------------------------------------------------------
--!@brief DEVICE DRIVER DO IIPDEV
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! DRIVER DO DISPOSITIVO IIPDEV PARA UCLINUX
--!
--! DETAILS:      
--!
--!- Project Name: iipdev               
--!- Module Name: iipdev.c
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

#define IIP_TX_BASE	0x028101A0
#define IIP_TX_SIZE	0x10
#define BUF_SIZE	333
#define PACKET_SIZE	188
#define DEVICE_NAME	"iipdev"
#define DEVICE_MAJOR	241
#define DEVICE_MINOR	0

#define RXDATA_OFFSET	0
#define TXDATA_OFFSET	1
#define STATUS_OFFSET	2
#define CONTROL_OFFSET	3
#define IRQR_OFFSET	2
#define IRQR_MASK	0x80000000
#define IRQR_SHIFT	31
#define BUSY_OFFSET	2
#define BUSY_MASK	0x40000000
#define BUSY_SHIFT	30
#define RDEN_OFFSET	3
#define RDEN_MASK	0x80000000
#define RDEN_SHIFT	31
#define RRDY_OFFSET	3
#define RRDY_MASK	0x40000000
#define RRDY_SHIFT	30
#define WREN_OFFSET	3
#define WREN_MASK	0x20000000
#define WREN_SHIFT	29
#define WRDY_OFFSET	3
#define WRDY_MASK	0x10000000
#define WRDY_SHIFT	28
#define INFO_OFFSET	3
#define INFO_MASK	0x00FF0000
#define INFO_SHIFT	16
#define ADDR_OFFSET	3
#define ADDR_MASK	0x000000FF
#define ADDR_SHIFT	0

#define	IIP_TR_EN	49
#define	CTS_NX_EN	50
#define	IIP_ST_EN	51
#define	CTS_CR_EN	256
#define	SFN_NX_EN	257
#define	SFN_CR_EN	258
#define	READ_BLOCK	259
#define	READ_NO_BLOCK	260
#define	WRITE_BLOCK	261
#define	WRITE_NO_BLOCK	262
#define DEV_IO_ON	263
#define DEV_IO_OFF	264

#define SET_EWBS	265
#define GET_EWBS	266

#define DEBUG



/* Prototypes */
static int set_ewbs(int arg0);
static int gen_iip(unsigned char *dest, unsigned char *cts_cr, unsigned char *cts_nx, unsigned char *sfn_cr, unsigned char *sfn_nx);
static void write_to_dev(unsigned int DEV, const unsigned char *buf, unsigned char id, size_t count);
static void iip_tsklt(void);
static int iip_open(struct inode *inode, struct file *file);
static int iip_release(struct inode *inode, struct file *file);
static loff_t iip_llseek(struct file *file, loff_t offset, int orig);
static int iip_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t iip_read(struct file *file, char __user *buf, size_t count, loff_t *ppos);
static ssize_t iip_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
static int __init iip_init(void);
static void __exit iip_cleanup(void);

/* Per-Device structure */
static struct iip_dev {
	struct cdev cdev;		/* Character device struct */
	struct tasklet_struct tsklt;	/* Tasklet struct */
} *iip_devp;

/* File Operations struct */
static struct file_operations iip_fops = {
	.owner =	THIS_MODULE,	/* Owner */
	.open =		iip_open,    	/* Open method */
	.release =	iip_release, 	/* Release method */
	.read =		iip_read,    	/* Read method */
	.write =	iip_write,   	/* Write method */
	.llseek =	iip_llseek,  	/* Seek method */
	.ioctl =	iip_ioctl   	/* Ioctl method */
};

/* Alloted device Number */
static dev_t iip_dev_number = MKDEV(DEVICE_MAJOR, DEVICE_MINOR);
/* Number of minors handled by major */
static int iip_dev_count = 1;
/* Access control */
static int iip_is_open = 0;
/* Tie with the device model */
static struct class *iip_class;	

static int flag_firt_time = 0;

static int flag_ewbs = 0;

/* Device data */
static int current_pointer;
static int iip_rd_mode;
static int iip_wr_mode;
static int iip_src_dest;
static int iip_dev_io;
static unsigned char *iip_tr_rd_buf;
static unsigned char *iip_tr_wr_buf;
static unsigned char *iip_st_rd_buf;
static unsigned char *iip_st_wr_buf;
static unsigned char *cts_cr_rd_buf;
static unsigned char *cts_cr_wr_buf;
static unsigned char *cts_nx_rd_buf;
static unsigned char *cts_nx_wr_buf;
static unsigned char *sfn_nx_rd_buf;
static unsigned char *sfn_nx_wr_buf;
static unsigned char *sfn_cr_rd_buf;
static unsigned char *sfn_cr_wr_buf;
static unsigned char renewal_flag[29];

/* Write to Device*/
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
	control |= id << INFO_SHIFT; /* Set info field */
	IOWR(DEV, CONTROL_OFFSET, control); /* Apply */
	status = IORD(DEV, STATUS_OFFSET); /* Read status register */
	status |= IRQR_MASK; /* Set IRQR flag */
	IOWR(DEV, STATUS_OFFSET, status); /* Apply */
    flag_firt_time |= 1;
#ifdef DEBUG
	printk(KERN_ALERT "IIPDEV: write_to_dev\n");
#endif
}

/* Tasklet */
static void
iip_tsklt(void)
{
	unsigned char *rd_buf;
	unsigned char *wr_buf;

	/* Loop through iip_src_dest */
	switch (iip_src_dest) {
		/* IIP_TR */
		case IIP_TR_EN:
			rd_buf = iip_tr_rd_buf;
			wr_buf = iip_tr_wr_buf;
			break;

		/* IIP_ST */
		case IIP_ST_EN:
			rd_buf = iip_st_rd_buf;
			wr_buf = iip_st_wr_buf;
			break;

		/* CTS_CR */
		case CTS_CR_EN:
			rd_buf = cts_cr_rd_buf;
			wr_buf = cts_cr_wr_buf;
			break;

		/* CTS_NX */
		case CTS_NX_EN:
			rd_buf = cts_nx_rd_buf;
			wr_buf = cts_nx_wr_buf;
			break;

		/* SFN_CR */
		case SFN_CR_EN:
			rd_buf = sfn_cr_rd_buf;
			wr_buf = sfn_cr_wr_buf;
			break;

		/* SFN_NX */
		case SFN_NX_EN:
			rd_buf = sfn_nx_rd_buf;
			wr_buf = sfn_nx_wr_buf;
			break;

		/* Error */
		default:
			return;		
	}

	/* Write to buffer */
	memcpy(rd_buf, wr_buf, BUF_SIZE);
	
	/* Update IIP */
	gen_iip(iip_tr_wr_buf, cts_cr_rd_buf, cts_nx_rd_buf, sfn_cr_rd_buf, sfn_nx_rd_buf);
	memcpy(iip_tr_rd_buf, iip_tr_wr_buf, BUF_SIZE);
	gen_iip(iip_st_wr_buf, cts_nx_rd_buf, cts_nx_rd_buf, sfn_nx_rd_buf, sfn_nx_rd_buf);
	memcpy(iip_st_rd_buf, iip_st_wr_buf, BUF_SIZE);

	/* Write to output device */
	if (iip_dev_io == DEV_IO_ON) {
		write_to_dev(IIP_TX_BASE, iip_tr_rd_buf, IIP_TR_EN, PACKET_SIZE);
		write_to_dev(IIP_TX_BASE, cts_nx_rd_buf, CTS_NX_EN, PACKET_SIZE);	
		write_to_dev(IIP_TX_BASE, iip_st_rd_buf, IIP_ST_EN, PACKET_SIZE);
	}

#ifdef DEBUG
	printk(KERN_ALERT "IIPDEV: tasklet\n");
#endif
}

/* Open Handler */
static int 
iip_open(struct inode *inode, struct file *file)
{
	if (iip_is_open) {
#ifdef DEBUG
		printk(KERN_ALERT "IIPDEV: device busy\n");
#endif
		return -EBUSY;
	}

	++iip_is_open;
	try_module_get(THIS_MODULE);		

#ifdef DEBUG
	printk(KERN_ALERT "IIPDEV: open\n");
#endif
	return 0;
}

/* Release/Close Handler */
static int 
iip_release(struct inode *inode, struct file *file)
{	
	--iip_is_open;			
	module_put(THIS_MODULE);

	/* Reset file pointer */
	current_pointer = 0;

#ifdef DEBUG
	printk(KERN_ALERT "IIPDEV: release\n");
#endif
	return 0;
}

/* Seek Handler */
static loff_t
iip_llseek(struct file *file, loff_t offset, int orig)
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
	printk(KERN_ALERT "IIPDEV: llseek [%d]\n", pointer);
#endif
	return pointer;
}

/* I/O Control Handler */
static int 
iip_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	
	int ewbs = 0;
	int *temp;
	/* Loop through I/O control commands */
	switch (cmd) {
		/* Blocking Read */
		case READ_BLOCK:
			iip_rd_mode = READ_BLOCK;
			break;

		/* Non-Blocking Read */
		case READ_NO_BLOCK:
			iip_rd_mode = READ_NO_BLOCK;
			break;

		/* Blocking Write */
		case WRITE_BLOCK:
			iip_wr_mode = WRITE_BLOCK;
			break;

		/* Non-Blocking Write */
		case WRITE_NO_BLOCK:
			iip_wr_mode = WRITE_NO_BLOCK;
			break;

		/* IIP Transitional Enable */
		case IIP_TR_EN:
			iip_src_dest = IIP_TR_EN;
			break;

		/* IIP Stable Enable */
		case IIP_ST_EN:
			iip_src_dest = IIP_ST_EN;
			break;

		/* CTS Current Enable */
		case CTS_CR_EN:
			iip_src_dest = CTS_CR_EN;
			break;

		/* CTS Next Enable */
		case CTS_NX_EN:
			iip_src_dest = CTS_NX_EN;
			break;

		/* SFN Current Enable */
		case SFN_CR_EN:
			iip_src_dest = SFN_CR_EN;
			break;

		/* SFN Next Enable */
		case SFN_NX_EN:
			iip_src_dest = SFN_NX_EN;
			break;

		/* Output Enable */
		case DEV_IO_ON:
			iip_dev_io = DEV_IO_ON;
			break;

		/* Output Enable */
		case DEV_IO_OFF:                           
			iip_dev_io = DEV_IO_OFF;
			break;
			
		case SET_EWBS_FLAG:
			/* Receive a pointer to a message (in user space) and set that
			 * to be the device's message. Get the parameter given to 
			 * ioctl by the process
			 */
			 
			temp = (int *)arg;
			get_user(ewbs,temp);
			if(ewbs == 1)
				flag_ewbs = 1;
			else
				flag_ewbs = 0;
			
			set_ewbs(flag_ewbs);
			
			break;
		case GET_EWBS_FLAG:
			put_user(flag_ewbs, (int __user *)arg);			
			printk(KERN_DEBUG " Flag EWBS = %d\n",flag_ewbs);
			break;
		/* Error */
		default:
			return -EIO;		
	}

	/* Reset file pointer */
	current_pointer = 0;
#ifdef DEBUG
	printk(KERN_ALERT "IIPDEV: ioctl [%u]\n", cmd);
#endif
	return 0;
}

/* Read Handler */
static ssize_t
iip_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	int remaining_size;
	int transfer_size;
	unsigned char *rd_buf;

	/* Loop through iip_src_dest */
	switch (iip_src_dest) {
		/* IIP_TR */
		case IIP_TR_EN:
			rd_buf = iip_tr_rd_buf;
			break;

		/* IIP_ST */
		case IIP_ST_EN:
			rd_buf = iip_st_rd_buf;
			break;

		/* CTS_CR */
		case CTS_CR_EN:
			rd_buf = cts_cr_rd_buf;
			break;

		/* CTS_NX */
		case CTS_NX_EN:
			rd_buf = cts_nx_rd_buf;
			break;

		/* SFN_CR */
		case SFN_CR_EN:
			rd_buf = sfn_cr_rd_buf;
			break;

		/* SFN_NX */
		case SFN_NX_EN:
			rd_buf = sfn_nx_rd_buf;
			break;

		/* Error */
		default:
			return -EIO;		
	}

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
	if (copy_to_user(buf /* to */, rd_buf + current_pointer /* from */, transfer_size)) {
		return -EFAULT;
	} else {
		/* Increase the position in the open file */
		current_pointer += transfer_size;
#ifdef DEBUG
		printk(KERN_ALERT "IIPDEV: read\n");
#endif
		return transfer_size;
	}
}

/* Write Handler */
static ssize_t
iip_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	int remaining_bytes;
	unsigned char *wr_buf;

	/* Loop through iip_src_dest */
	switch (iip_src_dest) {
		/* IIP_TR */
		case IIP_TR_EN:
			wr_buf = iip_tr_wr_buf;
			break;

		/* IIP_ST */
		case IIP_ST_EN:
			wr_buf = iip_st_wr_buf;
			break;

		/* CTS_CR */
		case CTS_CR_EN:
			wr_buf = cts_cr_wr_buf;
			break;

		/* CTS_NX */
		case CTS_NX_EN:
			/* Set last next values to current */
			memcpy(cts_cr_rd_buf, cts_nx_rd_buf, BUF_SIZE);
			memcpy(cts_cr_wr_buf, cts_nx_rd_buf, BUF_SIZE);
			wr_buf = cts_nx_wr_buf;
			break;

		/* SFN_CR */
		case SFN_CR_EN:
			wr_buf = sfn_cr_wr_buf;
			break;

		/* SFN_NX */
		case SFN_NX_EN:
			/* Set last next values to current */
			memcpy(sfn_cr_rd_buf, sfn_nx_rd_buf, BUF_SIZE);
			memcpy(sfn_cr_wr_buf, sfn_nx_rd_buf, BUF_SIZE);
			wr_buf = sfn_nx_wr_buf;
			break;

		/* Error */
		default:
			return -EIO;		
	}

	/* Number of writable bytes */
	remaining_bytes = BUF_SIZE - current_pointer;

	if (count > remaining_bytes) {
		/* Can't write beyond the end of the device */
		return -EIO;
	}

	/* Copy data from userspace */
	if (copy_from_user(wr_buf + current_pointer /* to */, buf /* from */, count)) {
		return -EFAULT;
	} else {
		/* Increase the position in the open file */
		current_pointer += count;
		/* Handle data */
		tasklet_schedule(&iip_devp->tsklt);
#ifdef DEBUG
		printk(KERN_ALERT "IIPDEV: write\n");	
#endif	
		return count;
	}
}

/* Driver Initialization */
static int __init 
iip_init(void)
{
	int ret;

	/* Request allocation of device major number */
	if (register_chrdev_region(iip_dev_number, iip_dev_count, DEVICE_NAME)) {
		printk(KERN_ERR "Can't register device\n"); 
		return -ENODEV;
    	}

	/* Populate sysfs entries */  
	iip_class = class_create(THIS_MODULE, DEVICE_NAME);

	/* Allocate memory for the per-device structure */
	iip_devp = (struct iip_dev*) kmalloc(sizeof (struct iip_dev), GFP_KERNEL);
	if (!iip_devp) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}

	/* Allocate memory for the device buffers */
	iip_tr_rd_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!iip_tr_rd_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	iip_tr_wr_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!iip_tr_wr_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	iip_st_rd_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!iip_st_rd_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	iip_st_wr_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!iip_st_wr_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	cts_cr_rd_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!cts_cr_rd_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	cts_cr_wr_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!cts_cr_wr_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	cts_nx_rd_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!cts_nx_rd_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	cts_nx_wr_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!cts_nx_wr_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	sfn_cr_rd_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!sfn_cr_rd_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	sfn_cr_wr_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!sfn_cr_wr_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	sfn_nx_rd_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!sfn_nx_rd_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	sfn_nx_wr_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!sfn_nx_wr_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}

	/* Request I/O regions */
	if (!request_region(IIP_TX_BASE, IIP_TX_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "IIP: I/O port 0x%x is not free.\n", IIP_TX_BASE);
		return -EIO;
	}
	
	/* Connect the file operations with the cdev */
	cdev_init(&iip_devp->cdev, &iip_fops);
	iip_devp->cdev.owner = THIS_MODULE;

	ret = cdev_add(/* cdev structure for the device */ &iip_devp->cdev, 
			/* first device number for which this device is responsible */ iip_dev_number, 
			/* number of consecutive minor numbers corresponding to this device */ iip_dev_count);

	if (ret) {
		printk(KERN_ERR "Bad cdev\n");
		return ret;
	}

	/* Tie with the device model */
	device_create(iip_class, NULL, iip_dev_number, NULL, DEVICE_NAME);

	/* Initialize tasklet */
	tasklet_init(&iip_devp->tsklt, iip_tsklt, NULL);

	/* Initialize defaults */
	current_pointer = 0;
	iip_src_dest = CTS_NX_EN;
	iip_dev_io = DEV_IO_ON;
	iip_rd_mode = READ_BLOCK;
	iip_wr_mode = WRITE_BLOCK;
	memset(iip_tr_rd_buf, 0xFF, BUF_SIZE);
	memset(iip_tr_wr_buf, 0xFF, BUF_SIZE);
	memset(iip_st_rd_buf, 0xFF, BUF_SIZE);
	memset(iip_st_wr_buf, 0xFF, BUF_SIZE);
	memset(cts_cr_rd_buf, 0xFF, BUF_SIZE);
	memset(cts_cr_wr_buf, 0xFF, BUF_SIZE);
	memset(cts_nx_rd_buf, 0xFF, BUF_SIZE);
	memset(cts_nx_wr_buf, 0xFF, BUF_SIZE);
	memset(sfn_cr_rd_buf, 0xFF, BUF_SIZE);
	memset(sfn_cr_wr_buf, 0xFF, BUF_SIZE);
	memset(sfn_nx_rd_buf, 0xFF, BUF_SIZE);
	memset(sfn_nx_wr_buf, 0xFF, BUF_SIZE);
	memset(renewal_flag, 0x1, 29);
	sfn_cr_rd_buf[0] = 0;
	sfn_cr_wr_buf[0] = 0;
	sfn_nx_rd_buf[0] = 0;
	sfn_nx_wr_buf[0] = 0;

	/* Initialize hardware */
	IOWR(IIP_TX_BASE, STATUS_OFFSET, 0x0);
	IOWR(IIP_TX_BASE, CONTROL_OFFSET, 0x0);

	/* All Done! */
	printk(KERN_ALERT "IIPDEV Driver Initialized\n");
	return 0;
}

/* Driver Exit */
static void __exit
iip_cleanup(void)
{
	cdev_del(&iip_devp->cdev);
	unregister_chrdev_region(iip_dev_number, iip_dev_count);
	device_destroy(iip_class, iip_dev_number);
	class_destroy(iip_class);
	release_region(IIP_TX_BASE, IIP_TX_SIZE);
	kfree(iip_devp);
	kfree(iip_tr_rd_buf);
	kfree(iip_tr_wr_buf);
	kfree(iip_st_rd_buf);
	kfree(iip_st_wr_buf);
	kfree(cts_cr_rd_buf);
	kfree(cts_cr_wr_buf);
	kfree(cts_nx_rd_buf);
	kfree(cts_nx_wr_buf);
	kfree(sfn_cr_rd_buf);
	kfree(sfn_cr_wr_buf);
	kfree(sfn_nx_rd_buf);
	kfree(sfn_nx_wr_buf);

	return;
}

/* IIP */
static int 
gen_iip(unsigned char *dest, unsigned char *cts_cr, unsigned char *cts_nx, unsigned char *sfn_cr, unsigned char *sfn_nx)
{
	//FIXME: Unsafe code section
	unsigned char IIP[188];
	int nTXAtivos; //Número de Transmissores ativos na Rede SFN
	int nTXSistema; //Número de Transmissores do Sistema da Rede SFN
	int ContTx; //Contador
	int i = 0; //Contador
	unsigned char atualiza_renewal;
	int achou;
	int j = 0; //Contador
	int eq_id;
	unsigned char byte_eight = 0x3C;
	/*
	printk(KERN_ALERT "IIPDEV: layout INICIO -\n");
	for(i=0;i<BUF_SIZE;i++){
		
		printk(KERN_ALERT "%x ", sfn_nx[i]);
		
		if(i%33==0)
			printk(KERN_ALERT "\n");
	}
	printk(KERN_ALERT "\n IIPDEV: layout FIM -\n");
	*/
	
	memset(IIP, 0xFF, PACKET_SIZE);

	//Byte de Sincronismo
	IIP[0]=0x47;
	//  Transport_error_indicator + payload_start_indicator + transport_priority + 1ª parte do PID(5 bits)                PID IIP= 0x1FF0(13bits)
	IIP[1]=0x5F;
	//2ª parte do PID(8 bits)
	IIP[2]=0xF0;
	//Scrambling_mode + No adaption_field +
	IIP[3]=0x10;

	//IIP Packet pointer
	IIP[4]=0x00;
	IIP[5]=0x00;

	//TMCC_syncronization_word ='0'
	//AC_data_effective_position ='1'
	//Reserved = "11"eq_id
	//IN_COUNT_DOWN_MT ='1111'  0111 1111
	IIP[6]=0x7F;

	//Modo Atual(Interface Web) - 2 bits
	//Guard Interval(Interface Web) - 2 bits

	IIP[7]=((cts_cr[1]&0x03)<<6)^((cts_cr[2]&0x03)<<4)^((cts_cr[1]&0x03)<<2)^((cts_cr[2]&0x03));

	//System identifier - tabela 3-24= "00"
	//count_down_index='1111'(default)
	//flag_alert_broadcast='0'
	//Partial reception flag(Interface Web)
	if(flag_ewbs == 1)
		byte_eight = 0x3E;
	else
		byte_eight = 0x3C;
	
	IIP[8] = seven_eight ^ (cts_cr[72]&0x01);

	//***********************************************************************
	//-----------------------------------------------------------------------
	//                        Parâmetros Atuais
	//-----------------------------------------------------------------------
	//***********************************************************************

	//ModulacaoContTx A            - 3 bits
	//Code Rate A            - 3 bits
	//Time Interleaving A    - 2 bits (3 bits)
	IIP[9] = ((cts_cr[4]&0x07)<<5)^((cts_cr[5]&0x07)<<2)^((cts_cr[6]&0x06)>>1); //--Ok

	//Time Interleaving   A  - 1 bit - Continuacao (3 bits)
	//Number of Segments  A  - 4 bits
	//Modulacao B            - 3 bits
	IIP[10]= ((cts_cr[6]&0x01)<<7)^((cts_cr[3]&0x0F)<<3)^((cts_cr[8]&0x07));  //--Ok

	//Code Rate B            - 3 bits
	//Time Interleaving B    - 3 bits (3 bits)
	//Number of Segments  B  - 2 birs (4 birs)
	IIP[11]= ((cts_cr[9]&0x07)<<5)^((cts_cr[10]&0x07)<<2)^((cts_cr[7]&0x0F)>>2); //--Ok

	//Number of Segments  B  - 2 birs (4 birs)
	//Modulacao C            - 3 bits
	//Code Rate C            - 3 bits
	IIP[12]= ((cts_cr[7]&0x03)<<6)^((cts_cr[12]&0x07)<<3)^((cts_cr[13]&0x07));  // -- Ok

	//Time Interleaving   C  - 3 birs
	//Number of Segments  C  - 4 birs
	//Recepcao Parcial       - 1 bit
	IIP[13]= ((cts_cr[14]&0x07)<<5)^((cts_cr[11]&0x0F)<<1)^((cts_cr[72]&0x01));

	//***********************************************************************
	//-----------------------------------------------------------------------
	//                        Próximos Parâmetros
	//-----------------------------------------------------------------------
	//***********************************************************************

	//Modulacao A            - 3 bits
	//Code Rate A            - 3 bits
	//Time Interleaving A    - 2 bits (3 bits)
	IIP[14] = ((cts_nx[4]&0x07)<<5)^((cts_nx[5]&0x07)<<2)^((cts_nx[6]&0x06)>>1);

	//Time Interleaving   A  - 1 bit - Continuacao (3 bits)
	//Number of Segments  A  - 4 bits
	//Modulacao B            - 3 bits
	IIP[15]= ((cts_nx[6]&0x01)<<7)^((cts_nx[3]&0x0F)<<3)^((cts_nx[8]&0x07));

	//Code Rate B            - 3 bits
	//Time Interleaving B    - 3 bits (3 bits)
	//Number of Segments  B  - 2 bits (4 birs)
	IIP[16]= ((cts_nx[9]&0x07)<<5)^((cts_nx[10]&0x07)<<2)^((cts_nx[7]&0x0F)>>2);

	//Number of Segments  B  - 2 birs (4 birs)
	//Modulacao C            - 3 bits
	//Code Rate C            - 3 bits
	IIP[17]= ((cts_nx[7]&0x03)<<6)^((cts_nx[12]&0x07)<<3)^((cts_nx[13]&0x07));

	//Time Interleaving   C  - 3 bits
	//Number of Segments  C  - 4 bits
	//Phase Shift correction of CP='1'(3 bits)
	IIP[18]= ((cts_nx[14]&0x07)<<5)^((cts_nx[11]&0x0F)<<1)^0x01;


	//Phase Shift correction of CP='11'(3 bits) + TMCC_reserved(12 bits)
	IIP[19] =0xFF;


	//TMCC_reserved(continuação - 6 bits)+ "11" (reservado - 10 bits)
	IIP[20]=0xFF;//"11";--reserved - 10 bits



	//  Reservado - 8 bits - Continuação
	IIP[21]= 0xFF;

	//**************
	// CRC TMCC -
	//**************          --
	//Será calculado em VHDL no Mux
	IIP[22] = 0x00;
	IIP[23] = 0x00;
	IIP[24] = 0x00;
	IIP[25] = 0x00;





	//********************************************************************************************
	//---------------------------------------------------------------------------------------------
	//        -- SFN - Single Frequency Network - INÍCIO.
	//---------------------------------------------------------------------------------------------
	//*********************************************************************************************
	//---------------------------------------------------------------------------------------------


	//  Branch -> NSI é < 159 bytes. Todos bytes serão '00'.

	// IIP Branch Number
	IIP[26]=0x00;

	//LAST IIP Branch Number
	IIP[27]=0x00;

	//Network Synchronization Info Length : deve ser <=159. Se 0, sem info de SFN
	IIP[28]=0x00;

	//Synchronization ID  - se =0x00, tem SFN Info, se 0xFF, não tem SFN info
	IIP[29]=0xFF;

	//Numero de Transmissores
	if (sfn_nx[0]==0x00)//Verifica se a Rede SFN está Habilitada
		nTXAtivos=0;	
        else
		nTXAtivos=(int)sfn_nx[6];
	
	nTXSistema=(int)sfn_nx[7];





	if (nTXAtivos>=1)
	{
	//Network Synchronization Info Length : deve ser <=159. Se 0, sem info de SFN
	IIP[28]= (char)(8+4+(5*nTXAtivos));

	// synchronization_id
	IIP[29]=0x00; //-- Se 0x00, IIP carrega NSI. Se 0xFF, IIP não carrega NSI.

	// synchronization_time_stamp. Diferença entre head do multiplex frame e o último 1 pps.
	//O Valor em tempo real do Time Stamo é gerado pelo mux
	IIP[30]=0x00;
	IIP[31]=0x00;
	IIP[32]=0x00;

	// maximum_delay - Máximo atraso na rede.

	atualiza_renewal=0x00;
	if   (!((sfn_cr[3]==sfn_nx[3])&&(sfn_cr[4]==sfn_nx[4])&&(sfn_cr[5]==sfn_nx[5])))
	{

	    atualiza_renewal=0x01;
	}
	IIP[33]=sfn_nx[3];
	IIP[34]=sfn_nx[4];
	IIP[35]=sfn_nx[5];

	// equipament_loop_length ---------- Cada estação usa 5 bytes.
	IIP[36]=(char)(5*nTXAtivos); // Cada estação usa 5 bytes.

	ContTx=0;


	for (i=0;i<nTXSistema;i++)
	{

	    //Se o Equipment ID for 0 quer dizer q não existe a Estação
	    //if (!((sfn_nx[15+i*11]==0)&&(sfn_nx[16+i*11]==0)&&(sfn_nx[17+i*11]==0)))
	    //{

	    if (sfn_nx[24+i*11]==0x01)
	    {

		eq_id=(int)sfn_nx[17+i*11];
		//No Vetor SFN cada estacao ocupa  10 bytes
		//Na IIP cada estacao ocupa  5 bytes
		//Equipment ID

		achou=0;
		j=0;
		while ((j<29)&& (achou==0))

		{

		    if ((sfn_nx[15+i*11]==sfn_cr[15+j*11])&&(sfn_nx[16+i*11]==sfn_cr[16+j*11])&&(sfn_nx[17+i*11]==sfn_cr[17+j*11]))
		    {
		        achou=1;
		    }
		    else
		    {
		        j++;
		    }//if ((sfn_nx[15+i*11]==*sfn_cr[15+j*11])&&(sfn_nx[16+i*11]==*sfn_cr[15+j*11])&&(sfn_nx[17+i*11]==*sfn_cr[15+j*11]))

		}//while ((j<29)&& (achou==0))

		if (achou==1)
		{

		    if (atualiza_renewal==0x01)
		    {
		        renewal_flag[eq_id-1]=renewal_flag[eq_id-1]^0x01;
		    }
		    else
		    {

		        //Static Delay Flag
		        if (!(sfn_nx[18+i*11]==sfn_cr[18+j*11]))
		        {
		            renewal_flag[eq_id-1]=renewal_flag[eq_id-1]^0x01;
		        }//Polaridade
		        else if (!(sfn_nx[19+i*11]==sfn_cr[19+j*11]))
		        {
		            renewal_flag[eq_id-1]=renewal_flag[eq_id-1]^0x01;
		        }//Time OffSet
		        else if (!((sfn_nx[21+i*11]==sfn_cr[21+j*11])&&(sfn_nx[22+i*11]==sfn_cr[22+j*11])&&(sfn_nx[23+i*11]==sfn_cr[23+j*11])))
		        {
		            renewal_flag[eq_id-1]=renewal_flag[eq_id-1]^0x01;
		        }

		    }//if (atualiza_renewal==0x01)
		}
		else //if (achou==1)
		{
		    renewal_flag[eq_id-1]=0x01;
		}//if (achou==1)




		IIP[37+(ContTx*5)+0]  =((sfn_nx[16+i*11]&0x0F)<<4)^((sfn_nx[17+i*11]&0xF0)>>4);



		//                       Equipment ID                          Renewal                  Static delay Flag      Reservado       Polaridade
		IIP[37+(ContTx*5)+1]= ((sfn_nx[17+i*11]&0x0F)<<4)^(((renewal_flag[eq_id-1]&01)<<3))^((sfn_nx[18+i*11]&01)<<2) ^    0x02  ^   (sfn_nx[19+i*11]&01);

		//Time Offset
		IIP[37+(ContTx*5)+2] = sfn_nx[21+i*11];
		IIP[37+(ContTx*5)+3] = sfn_nx[22+i*11];
		IIP[37+(ContTx*5)+4] = sfn_nx[23+i*11];
		ContTx++;
	    }//if (SFN[25+i*11]==0x01)
	    //}//if (!((sfn_nx[15+i*11]==0)&&(sfn_nx[16+i*11]==0)&&(sfn_nx[17+i*11]==0)))
	}// for(i=0;i<nprogramas;i++)
	}

	memcpy(dest, IIP, 188);
	return 0;
}


static int set_ewbs(int arg0)
{
	if(arg0)
		flags_ewbs = 1;
	else
		flags_ewbs = 0;
	
	gen_iip(iip_tr_wr_buf, cts_cr_rd_buf, cts_nx_rd_buf, sfn_cr_rd_buf, sfn_nx_rd_buf);
	memcpy(iip_tr_rd_buf, iip_tr_wr_buf, BUF_SIZE);
	gen_iip(iip_st_wr_buf, cts_nx_rd_buf, cts_nx_rd_buf, sfn_nx_rd_buf, sfn_nx_rd_buf);
	memcpy(iip_st_rd_buf, iip_st_wr_buf, BUF_SIZE);

	printk(KERN_DEBUG "SET EWBS");
	/* Write to output device */
	if (iip_dev_io == DEV_IO_ON) {
		printk(KERN_DEBUG "Trying to write iip into device\n");
		write_to_dev(IIP_TX_BASE, iip_tr_rd_buf, IIP_TR_EN, PACKET_SIZE);
		write_to_dev(IIP_TX_BASE, cts_nx_rd_buf, CTS_NX_EN, PACKET_SIZE);	
		write_to_dev(IIP_TX_BASE, iip_st_rd_buf, IIP_ST_EN, PACKET_SIZE);
	}	
	
	return flag_ewbs;
}


module_init(iip_init);
module_exit(iip_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Franz Wagner");
