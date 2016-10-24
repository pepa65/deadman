# deadman
Deadman is an anti-forensic linux kernel module deadman-switch will shut down
the system once the load-time specified USB device gets removed

Inspired by [silk-guardian](), but much simpler in scope

## Build & Use

```shell
make
sudo insmod deadman.ko usb=0xVENDPROD
```
(VEND is the 2-byte hexadecimal code for idVendor and PROD for idProduct)

Instead of 0, the usb parameter can also be set to some default in the code
before compiling.

## Why?

When the drives your machine are fully (or partially) encrypted, they are still
vulnerable when in-use, unencrypted. Requiring the specified USB device to
remain connected is an added security feature; once the system is down,
all encrypted data is only accessible by decrypting it first.

When a USB device is strapped to ones wrist, it will be harder for third
parties to prevent the device to be removed when attacked.

### Other tools

Silk-guardian has broader uses, it can also shred certain files (in case
no encryption is in use), it can respond to unknown USB devices (such as a
"mouse jiggler" as used by law enforcement to keep the system from sleeping, or
a USB drive that someone is wanting to copy files to).

