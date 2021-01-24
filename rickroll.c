#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "rickroll"

static int dev_open(struct inode* _inode, struct file* _file);
static int dev_release(struct inode* _inode, struct file* _file);
static ssize_t dev_read(struct file* _file, char* _buffer, size_t _len, loff_t* _offset);
static ssize_t dev_write(struct file* _file, const char* _buffer, size_t _len, loff_t* _offset);

static struct file_operations fops = {
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};

static int major;

static int __init rickroll_init(void) {
    major = register_chrdev(0, DEVICE_NAME, &fops);
    if (major < 0) {
        printk(KERN_ALERT "Rickroll load failed\n");
        return major;
    }
    printk(KERN_INFO "Rickroll module has been loaded. major number: %d\n", major);
    return 0;
}

static void __exit rickroll_exit(void) {
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_INFO "Rickroll module has been unloaded\n");
}

static int dev_open(struct inode* _inode, struct file* file) {
    printk(KERN_INFO "Rickroll device opened\n");
    return 0;
}

static ssize_t dev_write(struct file* _file, const char* _buffer, size_t _len, loff_t* _offset) {
    printk(KERN_INFO "Sorry, writing to the rickroll device literally makes no sense\n");
    return -EFAULT;
}

static int dev_release(struct inode* _inode, struct file* _file) {
    printk(KERN_INFO "Rickroll device closed\n");
    return 0;
}

static ssize_t dev_read(struct file* _file, char* _buffer, size_t _len, loff_t* _offset) {
    int errors = 0;
    const char* message = "https://youtu.be/dQw4w9WgXcQ ";
    int message_len = strlen(message);
    errors = copy_to_user(_buffer, message, message_len);
    return errors == 0 ? message_len : -EFAULT;
}

module_init(rickroll_init);
module_exit(rickroll_exit);
