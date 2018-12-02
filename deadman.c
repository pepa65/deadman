#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

// Required: libelf-dev
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/reboot.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("pepa65 <pepa65@passchier.net>, Greg Kroah-Hartman, Nate Brune");
MODULE_DESCRIPTION("Panic on removal of 'deadman' USB device or any USB device being inserted.");
MODULE_PARM_DESC(id, "USB ID of the deadman device: 'id=0x1234abcd' (vendor 0x1234, product 0xabcd)");
MODULE_PARM_DESC(ins, "Panic on any USB device being inserted: 'ins=1'");
MODULE_PARM_DESC(off, "Don't turn the computer off on panic: 'off=0'");

// Default USB device ID of trigger
static unsigned int id = 0xabcd1234;
module_param(id, int, 0644);

// By default inserted USB devices don't triggers a panic, override: ins=1
static int ins = 0;
module_param(ins, int, 0644);

// By default the computer turns off on panic, override: off=0
static int off = 1;
module_param(off, int, 0644);

static void start_panic(struct usb_device *dev){
	struct device *mark;
	for (mark = &dev->dev; mark; mark = mark->parent) mutex_unlock(&mark->mutex);
	if (off){
		printk("Powering off\n");
		kernel_power_off();
	}
	pr_info("Not powering off\n");
}

static void usb_inserted(struct usb_device *dev){
	unsigned int d = 0x10000*dev->descriptor.idVendor+dev->descriptor.idProduct;
	pr_info("USB device 0x%08x inserted\n", d);
	start_panic(dev);
}

static int usb_removed(struct usb_device *dev){
	unsigned int d = 0x10000*dev->descriptor.idVendor+dev->descriptor.idProduct;
	pr_info("USB device 0x%08x removed\n", d);
	if (d == id) start_panic(dev);
	return 0;
}

static int notify(struct notifier_block *self, unsigned long act, void *dev){
	if (act == USB_DEVICE_REMOVE) usb_removed(dev);
	if (ins && act == USB_DEVICE_ADD) usb_inserted(dev);
	return 0;
}
static struct notifier_block usb_notify = {.notifier_call = notify};

static int __init deadman_init(void){
	usb_register_notify(&usb_notify);
	if (id) pr_info("Watching removal of USB device 0x%08x\n", id);
	if (ins) pr_info("Watching insertion of any USB device");
	if (!ins && !id) pr_info("Loaded but not functional");
	return 0;
}
module_init(deadman_init);

static void __exit deadman_exit(void) {
	usb_unregister_notify(&usb_notify);
	if (id) pr_info("Stopped watching USB device 0x%08x\n", id);
	if (ins) pr_info("Stopped watching insertion of USB devices");
	if (!ins && !id) pr_info("Unloaded");
}
module_exit(deadman_exit);
