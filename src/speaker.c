#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/ioport.h>
#include <asm/uaccess.h>
#include <asm.io.h>
#include <../include/speaker.h>

static int Device_Open = 0;
static int speaker_open(struct inode *inode, struct file *file)
{
	//open the speaker device
	if(Deivce_Open)
		return -EBUSY;
	Device_Open++;
	printk("Device has been opened!"\n);
	return 0;
}

static int speaker_release(struct inode *inode, struct file *file)
{
	//close the speaker device
	Device_Open--;
	//close the speaker
	outb_p(0, 0x61);
	return 0;
}

static ssize_t speaker_write(struct file *file, const char *buffer, size_t length, loff_t *offset)
{
	outb_p(0xb6, 0x43);//use 1011,0110 to initialize
	outb_p(buffer[0], 0x42);//write the inital value
	outb_p(buffer[1], 0x42);
	outb_p(3, 0x42);//open the speaker
	return 0;
}

struct file_operations Fops = {
        write:speaker_write,
        open:speaker_open,
        release:speak_release,
}

int init_module()	//initialize the speaker module
{
	int major;
	major = register_chrdev(MAJOR_NUM, DEVICE_NAME, &Fops);//register the deive
	if(major < 0){
		printk("Register error!\n");
		return major;
	}
	printk("Resiter successfully!\nThe MAJOR_NUM is %d!\n", MAJOR_NUM);
	return 0;
}

void cleanup_module()
{
	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);// uninstall the speaker module
	printk("Uninstall successfully!\n");
}

MODULE_LICENSE("GPL");
