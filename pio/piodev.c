/* Alarm Device Driver */
/* 11/2009 */

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

/* physical address of the devices */
#define ALARMDEV_1 			0x08000010
#define ALARMDEV_RESET 		0x088100a0
#define DEVICE_SIZE			0x0F

#define BUF_SIZE			1 // buffer ASI = 1~32, buffer layer = 33
#define DEVICE_NAME			"piodev"
#define DEVICE_MAJOR 		243
#define DEVICE_MINOR		0

#define	READ_BLOCK			259
#define	READ_NO_BLOCK		260
#define	WRITE_BLOCK			261
#define	WRITE_NO_BLOCK		262
#define DEV_IO_ON			263
#define DEV_IO_OFF			264
#define ASI_BYTE			265
#define ASI_PACKET			266
#define TEST_OFF			267
#define TEST_NULL			268
#define TEST_PN9			269
#define TEST_PN15			270
#define TEST_PN23			271
#define TEST_PN_RND			272
#define	CMUX_IFX			273
#define	CMUX_MUX			274
#define	CLEARVN_H			275
#define	CLEARVN_L			276
#define RESET_ALARM 		280

#define DEBUG

/* Prototypes */
static int alarm_open(struct inode *inode, struct file *file);
static int alarm_release(struct inode *inode, struct file *file);
static loff_t alarm_llseek(struct file *file, loff_t offset, int orig);
static int alarm_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t alarm_read(struct file *file, char __user *buf, size_t count, loff_t *ppos);
static ssize_t alarm_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
static int __init alarm_init(void);
static void __exit alarm_cleanup(void);

/* Per-Device structure */
static struct alarm_dev {
	struct cdev cdev;		/* Character device struct */
} *alarm_devp;

/* File Operations struct */
static struct file_operations alarm_fops = {
	.owner =	THIS_MODULE,	/* Owner */
	.open =		alarm_open,    	/* Open method */
	.release =	alarm_release, 	/* Release method */
	.read =		alarm_read,    	/* Read method */
	.write =	alarm_write,   	/* Write method */
	.llseek =	alarm_llseek,  	/* Seek method */
	.ioctl =	alarm_ioctl   	/* Ioctl method */
};

/* Alloted device Number */
static dev_t alarm_dev_number = MKDEV(DEVICE_MAJOR, DEVICE_MINOR);
/* Number of minors handled by major */
static int alarm_dev_count = 1;
/* Access control */
static int alarm_is_open = 0;
/* Tie with the device model */
static struct class *alarm_class;	

/* Device data */
static int current_pointer;
static unsigned char *alarm_rd_buf;
static unsigned char *alarm_wr_buf;

/* Open Handler */
static int 
alarm_open(struct inode *inode, struct file *file)
{
	if (alarm_is_open) {

#ifdef DEBUG
		printk(KERN_ALERT "PIODEV: device busy\n");
#endif

		return -EBUSY;
	}

	++alarm_is_open;
	try_module_get(THIS_MODULE);		

#ifdef DEBUG
	printk(KERN_ALERT "PIODEV: open\n");
#endif

	return 0;
}

/* Release/Close Handler */
static int 
alarm_release(struct inode *inode, struct file *file)
{	
	--alarm_is_open;			
	module_put(THIS_MODULE);

	/* Reset file pointer */
	current_pointer = 0;

#ifdef DEBUG
	printk(KERN_ALERT "PIODEV: release\n");
#endif

	return 0;
}

/* Seek Handler */
static loff_t
alarm_llseek(struct file *file, loff_t offset, int orig)
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
	printk(KERN_ALERT "PIODEV: llseek [%d]\n", pointer);
#endif

	return pointer;
}

/* I/O Control Handler */
static int 
alarm_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	/* Loop through I/O control commands */
	switch (cmd) {

		/* RESET ALARM */
		case RESET_ALARM:
			//IOWR(ALARMDEV_RESET, 0, 0xFF);
			//IOWR(ALARMDEV_RESET, 0, 0x0);
#ifdef DEBUG
			printk(KERN_ALERT "PIODEV: alarmdev RESET\n");
#endif
		break;

		/* Error */
		default:
			return -EIO;		
	}

	/* Reset file pointer */
	current_pointer = 0;

#ifdef DEBUG
	printk(KERN_ALERT "PIODEV: ioctl [%u]\n", cmd);
#endif

	return 0;
}

/* Read Handler */
static ssize_t
alarm_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	int remaining_size;
	int transfer_size;
	int i=0;
	unsigned int reg;

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
	        
    reg = IORD(ALARMDEV_1, 0);
    alarm_rd_buf[i] = reg & 0xFF;

	/* Copy data to userspace */
	if (copy_to_user(buf /* to */, alarm_rd_buf + current_pointer /* from */, transfer_size)) {
		return -EFAULT;
	} else {
		/* Increase the position in the open file */
		current_pointer += transfer_size;

#ifdef DEBUG
		printk(KERN_ALERT "PIODEV: read\n");
#endif

		return transfer_size;
	}
}

/* Write Handler */
static ssize_t
alarm_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	int remaining_bytes;

	/* Number of writable bytes */
	remaining_bytes = BUF_SIZE - current_pointer;

	if (count > remaining_bytes) {
		/* Can't write beyond the end of the device */
		return -EIO;
	}

	/* Copy data from userspace */
	if (copy_from_user(alarm_wr_buf + current_pointer /* to */, buf /* from */, count)) {
		return -EFAULT;
	} else {
		/* Increase the position in the open file */
		current_pointer += count;
		
		//FIXME: added only for compatibility purposes

#ifdef DEBUG
		printk(KERN_ALERT "PIODEV: write\n");	
#endif	
		return count;
	}
}

/* Driver Initialization */
static int __init 
alarm_init(void)
{
	int ret;
	unsigned int reg;
int i=0;

	/* Request allocation of device major number */
	if (register_chrdev_region(alarm_dev_number, alarm_dev_count, DEVICE_NAME)) {
		printk(KERN_ERR "Can't register device\n"); 
		return -ENODEV;
    	}

	/* Populate sysfs entries */  
	alarm_class = class_create(THIS_MODULE, DEVICE_NAME);

	/* Allocate memory for the per-device structure */
	alarm_devp = (struct alarm_dev*) kmalloc(sizeof (struct alarm_dev), GFP_KERNEL);
	if (!alarm_devp) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}

	/* Allocate memory for the device buffers */
	alarm_rd_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!alarm_rd_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	alarm_wr_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!alarm_wr_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	
	/* request mem region */
	if (!request_region(ALARMDEV_1, DEVICE_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "PIODEV: I/O port 0x%x is not free.\n", ALARMDEV_1);
		return -EIO;
	}
	
	if (!request_region(ALARMDEV_RESET, DEVICE_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "PIODEV: I/O (alarmdev RESET) is not free \n");
		return -EIO;
	}
	
	/* Connect the file operations with the cdev */
	cdev_init(&alarm_devp->cdev, &alarm_fops);
	alarm_devp->cdev.owner = THIS_MODULE;

	ret = cdev_add(/* cdev structure for the device */ &alarm_devp->cdev, 
			/* first device number for which this device is responsible */ alarm_dev_number, 
			/* number of consecutive minor numbers corresponding to this device */ alarm_dev_count);

	if (ret) {
		printk(KERN_ERR "Bad cdev\n");
		return ret;
	}

	/* Tie with the device model */
	device_create(alarm_class, NULL, alarm_dev_number, NULL, DEVICE_NAME);

	/* Initialize defaults */
	current_pointer = 0;
	memset(alarm_rd_buf, 0x00, BUF_SIZE);
	memset(alarm_wr_buf, 0x00, BUF_SIZE);
        
    reg = IORD(ALARMDEV_1, 0);
    alarm_rd_buf[i] = reg & 0xFF;        

	/* All Done! */
	printk(KERN_ALERT "PIODEV Driver Initialized\n");
	return 0;
}

/* Driver Exit */
static void __exit
alarm_cleanup(void)
{
	cdev_del(&alarm_devp->cdev);
	unregister_chrdev_region(alarm_dev_number, alarm_dev_count);
	device_destroy(alarm_class, alarm_dev_number);
	class_destroy(alarm_class);

	release_region(ALARMDEV_1, DEVICE_SIZE);
	release_region(ALARMDEV_RESET, DEVICE_SIZE);
	
	kfree(alarm_devp);
	kfree(alarm_rd_buf);
	kfree(alarm_wr_buf);

	return;
}

module_init(alarm_init);
module_exit(alarm_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("FRANZ WAGNER");
