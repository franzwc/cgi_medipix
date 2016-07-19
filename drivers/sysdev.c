/*DEVICE DRIVER FILE
--------------------------------------------------------------------------------
--!@brief DEVICE DRIVER DO SYSDEV
--------------------------------------------------------------------------------                                                                      
--! DESCRIPTION:
--!
--! DRIVER DO DISPOSITIVO SYSDEV PARA UCLINUX
--!
--! DETAILS:      
--!
--!- Project Name: sysdev           
--!- Module Name: sysdev.c
--!- Tools: jedit 
--!- Author: Franz Wagner
--!- Company: LABORATORIO NACIONAL DE LUZ SINCROTRON - GRUPO DETECTORES
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

#define ENABLE1_BASE		0x02810080
#define ENABLE1_SIZE		0x10
#define ENABLE2_BASE		0x02810090
#define ENABLE2_SIZE		0x10
#define TEST_SIGNAL_BASE	0x02810140
#define TEST_SIGNAL_SIZE	0x10

#define TUNER_BASE	0x02810200
#define TUNER_SIZE	0x10

#define CTABLE_BASE	0x02810210
#define CTABLE_SIZE	0x10

#define ASI_OUT1_BASE	0x02810220
#define ASI_OUT1_SIZE	0x10

#define ASI_OUT2_BASE	0x02810230
#define ASI_OUT2_SIZE	0x10

#define LNB_VOLTAGE_BASE	0x02810240
#define LNB_VOLTAGE_SIZE	0x10


#define ASI_OUTPUT_MODE_BASE	0x02810150
#define ASI_OUTPUT_MODE_SIZE	0x10

#define VIRTUAL_CHANNEL_OUTPUT1	0x02810250
#define VIRTUAL_CHANNEL_OUTPUT1	0x0281025F
#define VIRTUAL_CHANNEL_SIZE	0x10

#define CMUX_BASE		0x028101C0
#define CMUX_SIZE		0x10

#define CPID_BASE		0x028101E0
#define CPID_SIZE		0x10

//#define CTABLE_BASE		0x028101D0
//#define CTABLE_SIZE		0x10
#define CLEARVN_BASE		0x028101D0
#define CLEARVN_SIZE		0x10
//#define CLEARCP_BASE		0x028101D0
//#define CLEARCP_SIZE		0x10

#define SW_BASE			0x028101F0
#define SW_SIZE			0x10

#define BUF_SIZE		24
#define DEVICE_NAME		"sysdev"
#define DEVICE_MAJOR	242
#define DEVICE_MINOR	0

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
#define	CLEARCP_H		290
#define	CLEARCP_L		291
#define	CPID_MUX		292
#define	CPID_IFX		293
#define	CTABLE_MUX		294
#define	CTABLE_IFX		295
#define	SW_SAC			296
#define	SW_PRI			297
#define	SW_SEC			298

#define TUNER_OFF		300
#define TUNER_ASI7		301
#define TUNER_ASI8		302

#define ASI1_OUT_BTS            303 // 00
#define ASI1_OUT_BTSCOMP        304 // 01
#define ASI1_OUT_BTSDECOMP      305 // 10
#define ASI1_OUT_SAT	        306 // 11
								

#define ASI2_OUT_BTS            307 // 00
#define ASI2_OUT_BTSCOMP        308 // 01
#define ASI2_OUT_BTSDECOMP      309 // 10
#define ASI2_OUT_SAT	        310 // 11

#define LNB_VOLT_13V	        311
#define LNB_VOLT_18V	        312

#define VCHANNEL_OUTPUT1	313
#define VCHANNEL_OUTPUT2	314

#define DEBUG

/* Prototypes */
static int sys_open(struct inode *inode, struct file *file);
static int sys_release(struct inode *inode, struct file *file);
static loff_t sys_llseek(struct file *file, loff_t offset, int orig);
static int sys_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg);
static ssize_t sys_read(struct file *file, char __user *buf, size_t count, loff_t *ppos);
static ssize_t sys_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
static int __init sys_init(void);
static void __exit sys_cleanup(void);

/* Per-Device structure */
static struct sys_dev {
	struct cdev cdev;		/* Character device struct */
} *sys_devp;

/* File Operations struct */
static struct file_operations sys_fops = {
	.owner =	THIS_MODULE,	/* Owner */
	.open =		sys_open,    	/* Open method */
	.release =	sys_release, 	/* Release method */
	.read =		sys_read,    	/* Read method */
	.write =	sys_write,   	/* Write method */
	.llseek =	sys_llseek,  	/* Seek method */
	.ioctl =	sys_ioctl   	/* Ioctl method */
};

/* Alloted device Number */
static dev_t sys_dev_number = MKDEV(DEVICE_MAJOR, DEVICE_MINOR);
/* Number of minors handled by major */
static int sys_dev_count = 1;
/* Access control */
static int sys_is_open = 0;
/* Tie with the device model */
static struct class *sys_class;	

/* Device data */
static int current_pointer;
static int sys_rd_mode;
static int sys_wr_mode;
static int sys_dev_out;
static int sys_asi_mode;
static int sys_test_signal;
static unsigned char *sys_rd_buf;
static unsigned char *sys_wr_buf;

/* Open Handler */
static int 
sys_open(struct inode *inode, struct file *file)
{
	if (sys_is_open) {
#ifdef DEBUG
		printk(KERN_ALERT "SYSDEV: device busy\n");
#endif
		return -EBUSY;
	}

	++sys_is_open;
	try_module_get(THIS_MODULE);		

#ifdef DEBUG
	printk(KERN_ALERT "SYSDEV: open\n");
#endif
	return 0;
}

/* Release/Close Handler */
static int 
sys_release(struct inode *inode, struct file *file)
{	
	--sys_is_open;			
	module_put(THIS_MODULE);

	/* Reset file pointer */
	current_pointer = 0;

#ifdef DEBUG
	printk(KERN_ALERT "SYSDEV: release\n");
#endif
	return 0;
}

/* Seek Handler */
static loff_t
sys_llseek(struct file *file, loff_t offset, int orig)
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
	printk(KERN_ALERT "SYSDEV: llseek [%d]\n", pointer);
#endif
	return pointer;
}

/* I/O Control Handler */
static int 
sys_ioctl(struct inode *inode, struct file *file, unsigned int cmd, unsigned long arg)
{
	/* Loop through I/O control commands */
	switch (cmd) {
		/* Blocking Read */
		case READ_BLOCK:
			sys_rd_mode = READ_BLOCK;
			break;

		/* Non-Blocking Read */
		case READ_NO_BLOCK:
			sys_rd_mode = READ_NO_BLOCK;
			break;

		/* Blocking Write */
		case WRITE_BLOCK:
			sys_wr_mode = WRITE_BLOCK;
			break;

		/* Non-Blocking Write */
		case WRITE_NO_BLOCK:
			sys_wr_mode = WRITE_NO_BLOCK;
			break;

		/* ASI Output Mode */
		case ASI_BYTE:
			IOWR(ASI_OUTPUT_MODE_BASE, 0x0, 0x1);
			sys_asi_mode = ASI_BYTE;
			break;

		/* ASI Output Mode */
		case ASI_PACKET:
			IOWR(ASI_OUTPUT_MODE_BASE, 0x0, 0x0);
			sys_asi_mode = ASI_PACKET;
			break;

		/* Test Signal */
		case TEST_OFF:
			IOWR(TEST_SIGNAL_BASE, 0x0, 0x7);
			sys_test_signal = TEST_OFF;
			break;

		/* Test Signal */
		case TEST_NULL:
			IOWR(TEST_SIGNAL_BASE, 0x0, 0x0);
			sys_test_signal = TEST_NULL;
			break;

		/* Test Signal */
		case TEST_PN9:
			IOWR(TEST_SIGNAL_BASE, 0x0, 0x1);
			sys_test_signal = TEST_PN9;
			break;

		/* Test Signal */
		case TEST_PN15:
			IOWR(TEST_SIGNAL_BASE, 0x0, 0x2);
			sys_test_signal = TEST_PN15;
			break;

		/* Test Signal */
		case TEST_PN23:
			IOWR(TEST_SIGNAL_BASE, 0x0, 0x3);
			sys_test_signal = TEST_PN23;
			break;

		/* Test Signal */
		case TEST_PN_RND:
			IOWR(TEST_SIGNAL_BASE, 0x0, 0x4);
			sys_test_signal = TEST_PN_RND;
			break;

		/* Output Enable */
		case DEV_IO_ON:
			sys_dev_out = DEV_IO_ON;
			break;

		/* Output Enable */
		case DEV_IO_OFF:
			sys_dev_out = DEV_IO_OFF;
			break;

		/* Control Mux */
		case CMUX_IFX:
			IOWR(CMUX_BASE, 0x0, 0x0);
			break;

		/* Control Mux */
		case CMUX_MUX:
			IOWR(CMUX_BASE, 0x0, 0x1);
			break;

		/* Control PID */
		case CPID_IFX:
			IOWR(CPID_BASE, 0x0, 0x0);
			break;

		/* Control PID */
		case CPID_MUX:
			IOWR(CPID_BASE, 0x0, 0x1);
			break;

		/* Control Table */
		case CTABLE_IFX:
			IOWR(CTABLE_BASE, 0x0, 0x0);
			break;

		/* Control Table */
		case CTABLE_MUX:
			IOWR(CTABLE_BASE, 0x0, 0x1);
			break;

		/* Clear Version Number */
		case CLEARVN_H:
			IOWR(CLEARVN_BASE, 0x0, 0x1);
			break;

		/* Clear Version Number */
		case CLEARVN_L:
			IOWR(CLEARVN_BASE, 0x0, 0x0);
			break;

		/* Clear Control PID */
		case CLEARCP_H:
			//IOWR(CLEARCP_BASE, 0x0, 0x1);
			break;

		/* Clear Control PID */
		case CLEARCP_L:
			//IOWR(CLEARCP_BASE, 0x0, 0x0);
			break;

		/* Switch Standalone */
		case SW_SAC:
			IOWR(SW_BASE, 0x0, 0x0);
			break;

		/* Switch Primary */
		case SW_PRI:
			IOWR(SW_BASE, 0x0, 0x1);
			break;

		/* Switch Secondary */
		case SW_SEC:
			IOWR(SW_BASE, 0x0, 0x0);
			break;


		case TUNER_OFF:
			IOWR(TUNER_BASE, 0x0, 0xF);
			break;

		case TUNER_ASI7:
			IOWR(TUNER_BASE, 0x0, 0x6);
			break;

		case TUNER_ASI8:
			IOWR(TUNER_BASE, 0x0, 0x7);
			break;

		case ASI1_OUT_BTS:
			IOWR(ASI_OUT1_BASE, 0x0, 0x0);
			break;

		case ASI1_OUT_BTSCOMP:
			IOWR(ASI_OUT1_BASE, 0x0, 0x1);
			break;

		case ASI1_OUT_BTSDECOMP:
			IOWR(ASI_OUT1_BASE, 0x0, 0x2);
			break;

		case ASI1_OUT_SAT:
			IOWR(ASI_OUT1_BASE, 0x0, 0x3);
			break;

		case ASI2_OUT_BTS:
			IOWR(ASI_OUT2_BASE, 0x0, 0x0);
			break;

		case ASI2_OUT_BTSCOMP:
			IOWR(ASI_OUT2_BASE, 0x0, 0x1);
			break;

		case ASI2_OUT_BTSDECOMP:
			IOWR(ASI_OUT2_BASE, 0x0, 0x2);
			break;

		case ASI2_OUT_SAT:
			IOWR(ASI_OUT2_BASE, 0x0, 0x3);
			break;

		case LNB_VOLT_13V:
			IOWR(LNB_VOLTAGE_BASE, 0x0, 0x0);
			break;

		case LNB_VOLT_18V:
			IOWR(LNB_VOLTAGE_BASE, 0x0, 0x1);
			break;

		case VCHANNEL_OUTPUT1:
			IORD(VIRTUAL_CHANNEL_OUTPUT1,0x0);
			break;
			
		case VCHANNEL_OUTPUT2:
			IORD(VIRTUAL_CHANNEL_OUTPUT2,0x0);
			break;	

		/* Error */
		default:
			return -EIO;		
	}

	/* Reset file pointer */
	current_pointer = 0;
#ifdef DEBUG
	printk(KERN_ALERT "SYSDEV: ioctl [%u]\n", cmd);
#endif
	return 0;
}

/* Read Handler */
static ssize_t
sys_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
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
	if (copy_to_user(buf /* to */, sys_rd_buf + current_pointer /* from */, transfer_size)) {
		return -EFAULT;
	} else {
		/* Increase the position in the open file */
		current_pointer += transfer_size;
#ifdef DEBUG
		printk(KERN_ALERT "SYSDEV: read\n");
#endif
		return transfer_size;
	}
}

/* Write Handler */
static ssize_t
sys_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
	int remaining_bytes;

	/* Number of writable bytes */
	remaining_bytes = BUF_SIZE - current_pointer;

	if (count > remaining_bytes) {
		/* Can't write beyond the end of the device */
		return -EIO;
	}

	/* Copy data from userspace */
	if (copy_from_user(sys_wr_buf + current_pointer /* to */, buf /* from */, count)) {
		return -EFAULT;
	} else {
		/* Increase the position in the open file */
		current_pointer += count;
		/* Handle data */
		memcpy(sys_rd_buf, sys_wr_buf, BUF_SIZE);
		/*IOWR(ENABLE1_BASE, 0x0, sys_rd_buf[3]);
		IOWR(ENABLE2_BASE, 0x0, sys_rd_buf[7]);
		IOWR(TEST_SIGNAL_BASE, 0x0, sys_rd_buf[11]);
		IOWR(ASI_OUTPUT_MODE_BASE, 0x0, sys_rd_buf[15]);
		IOWR(CMUX_BASE, 0x0, sys_rd_buf[19]);
		IOWR(CLEARVN_BASE, 0x0, sys_rd_buf[23]);*/
#ifdef DEBUG
		printk(KERN_ALERT "SYSDEV: write\n");	
#endif	
		return count;
	}
}

/* Driver Initialization */
static int __init 
sys_init(void)
{
	int ret;

	/* Request allocation of device major number */
	if (register_chrdev_region(sys_dev_number, sys_dev_count, DEVICE_NAME)) {
		printk(KERN_ERR "Can't register device\n"); 
		return -ENODEV;
    	}

	/* Populate sysfs entries */  
	sys_class = class_create(THIS_MODULE, DEVICE_NAME);

	/* Allocate memory for the per-device structure */
	sys_devp = (struct sys_dev*) kmalloc(sizeof (struct sys_dev), GFP_KERNEL);
	if (!sys_devp) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}

	/* Allocate memory for the device buffers */
	sys_rd_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!sys_rd_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}
	sys_wr_buf = (unsigned char*) kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!sys_wr_buf) {
		printk(KERN_ERR "Bad kmalloc\n"); 
		return -ENOMEM;
	}

	/* Request I/O regions */
	if (!request_region(ENABLE1_BASE, ENABLE1_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", ENABLE1_BASE);
		return -EIO;
	}
	if (!request_region(ENABLE2_BASE, ENABLE2_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", ENABLE2_BASE);
		return -EIO;
	}
	if (!request_region(TEST_SIGNAL_BASE, TEST_SIGNAL_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", TEST_SIGNAL_BASE);
		return -EIO;
	}


	if (!request_region(TUNER_BASE, TUNER_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", TUNER_BASE);
		return -EIO;
	}

	if (!request_region(LNB_VOLTAGE_BASE, LNB_VOLTAGE_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", LNB_VOLTAGE_BASE);
		return -EIO;
	}


	if (!request_region(CTABLE_BASE, CTABLE_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", CTABLE_BASE);
		return -EIO;
	}

	if (!request_region(ASI_OUT1_BASE, ASI_OUT1_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", ASI_OUT1_BASE);
		return -EIO;
	}

	if (!request_region(ASI_OUT2_BASE, ASI_OUT2_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", ASI_OUT2_BASE);
		return -EIO;
	}


	if (!request_region(ASI_OUTPUT_MODE_BASE, ASI_OUTPUT_MODE_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", ASI_OUTPUT_MODE_BASE);
		return -EIO;
	}
	if (!request_region(CMUX_BASE, CMUX_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", ASI_OUTPUT_MODE_BASE);
		return -EIO;
	}
	if (!request_region(CPID_BASE, CPID_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", ASI_OUTPUT_MODE_BASE);
		return -EIO;
	}
	/*
	if (!request_region(CTABLE_BASE, CTABLE_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", ASI_OUTPUT_MODE_BASE);
		return -EIO;
	}
	*/
	if (!request_region(CLEARVN_BASE, CLEARVN_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", ASI_OUTPUT_MODE_BASE);
		return -EIO;
	}
	/*if (!request_region(CLEARCP_BASE, CLEARVN_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", ASI_OUTPUT_MODE_BASE);
		return -EIO;
	}*/

	if (!request_region(SW_BASE, SW_SIZE, DEVICE_NAME)) {
		printk(KERN_ERR "SYSDEV: I/O port 0x%x is not free.\n", ASI_OUTPUT_MODE_BASE);
		return -EIO;
	}
	
	/* Connect the file operations with the cdev */
	cdev_init(&sys_devp->cdev, &sys_fops);
	sys_devp->cdev.owner = THIS_MODULE;

	ret = cdev_add(/* cdev structure for the device */ &sys_devp->cdev, 
			/* first device number for which this device is responsible */ sys_dev_number, 
			/* number of consecutive minor numbers corresponding to this device */ sys_dev_count);

	if (ret) {
		printk(KERN_ERR "Bad cdev\n");
		return ret;
	}

	/* Tie with the device model */
	device_create(sys_class, NULL, sys_dev_number, NULL, DEVICE_NAME);

	/* Initialize defaults */
	current_pointer = 0;
	sys_dev_out = DEV_IO_ON;
	sys_rd_mode = READ_BLOCK;
	sys_wr_mode = WRITE_BLOCK;
	sys_test_signal = TEST_OFF;	
	sys_asi_mode = ASI_PACKET;	
	memset(sys_rd_buf, 0xFF, BUF_SIZE);
	memset(sys_wr_buf, 0xFF, BUF_SIZE);
	
	/* Initialize hardware */
	IOWR(ENABLE1_BASE, 0x0, 0x1);
	IOWR(ENABLE2_BASE, 0x0, 0x1);
	IOWR(TEST_SIGNAL_BASE, 0x0, 0x7);

	IOWR(TUNER_BASE, 0x0, 0xF);
	IOWR(LNB_VOLTAGE_BASE, 0x0, 0x0);
	IOWR(CTABLE_BASE, 0x0, 0x0);
	IOWR(ASI_OUT1_BASE, 0x0, 0x0);
	IOWR(ASI_OUT2_BASE, 0x0, 0x0);

	IOWR(ASI_OUTPUT_MODE_BASE, 0x0, 0x0);
	IOWR(CMUX_BASE, 0x0, 0x0);
	IOWR(CPID_BASE, 0x0, 0x0);
	//IOWR(CTABLE_BASE, 0x0, 0x0);
	IOWR(CLEARVN_BASE, 0x0, 0x1);
	IOWR(CLEARVN_BASE, 0x0, 0x0);
	IOWR(CLEARVN_BASE, 0x0, 0x1);
	//IOWR(CLEARCP_BASE, 0x0, 0x1);
	//IOWR(CLEARCP_BASE, 0x0, 0x0);
	//IOWR(CLEARCP_BASE, 0x0, 0x1);
	IOWR(SW_BASE, 0x0, 0x0);

	/* All Done! */
	printk(KERN_ALERT "SYSDEV Driver Initialized\n");
	return 0;
}

/* Driver Exit */
static void __exit
sys_cleanup(void)
{
	cdev_del(&sys_devp->cdev);
	unregister_chrdev_region(sys_dev_number, sys_dev_count);
	device_destroy(sys_class, sys_dev_number);
	class_destroy(sys_class);
	release_region(ENABLE1_BASE, ENABLE1_SIZE);
	release_region(ENABLE2_BASE, ENABLE2_SIZE);
	release_region(TEST_SIGNAL_BASE, TEST_SIGNAL_SIZE);


	release_region(TUNER_BASE, TUNER_SIZE);
	release_region(LNB_VOLTAGE_BASE, LNB_VOLTAGE_SIZE);
	release_region(CTABLE_BASE, CTABLE_SIZE);	
	release_region(ASI_OUT1_BASE, ASI_OUT1_SIZE);
	release_region(ASI_OUT2_BASE, ASI_OUT2_SIZE);


	release_region(ASI_OUTPUT_MODE_BASE, ASI_OUTPUT_MODE_SIZE);
	release_region(CMUX_BASE, CMUX_SIZE);
	release_region(CPID_BASE, CPID_SIZE);
	//release_region(CTABLE_BASE, CTABLE_SIZE);
	release_region(CLEARVN_BASE, CLEARVN_SIZE);
	//release_region(CLEARCP_BASE, CLEARCP_SIZE);
	release_region(SW_BASE, SW_SIZE);
	kfree(sys_devp);
	kfree(sys_rd_buf);
	kfree(sys_wr_buf);

	return;
}
module_init(sys_init);
module_exit(sys_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Franz Wagner");
MODULE_VERSION("Version 1.2");
