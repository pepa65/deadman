#define pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#include <linux/module.h>
#include <linux/usb.h>
#include <linux/reboot.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("pepa65 <solusos@passchier.net>");
MODULE_DESCRIPTION("Kernel module that shuts down the system when a specified USB device is removed.");

// Run like: insmod deadman.ko usb=0xVENDPROD
static int usb = 0;
MODULE_PARM_DESC(usb, "USB identifier: idVendor * 0x10000 + idProduct");
module_param(usb, int, 0644);
static uint16_t v, p;

// Shut down when deadman-switch USB device is removed
static int notify(struct notifier_block *self, unsigned long action, struct usb_device *dev) {
	if (usb) {
		if (action == USB_DEVICE_REMOVE
				&& v == dev->descriptor.idVendor
				&& p == dev->descriptor.idProduct) {
			printk("Shutting down\n");
			//kernel_power_off();
		}
	}
	return 0;
}
static struct notifier_block usb_notify = {
	.notifier_call = notify,
};

// Module inserted
static int __init deadman_init(void) {
	v = usb / 0x10000;
	p = usb % 0x10000;

	usb_register_notify(&usb_notify);
	pr_info("loaded for USB_DEVICE(0x%x,0x%x)\n", v, p);
	return 0;
}
module_init(deadman_init);

// Module removed
static void __exit deadman_exit(void)
{
	usb_unregister_notify(&usb_notify);
	pr_info("unloaded\n");
}
module_exit(deadman_exit);
