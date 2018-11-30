# deadman
Deadman is an anti-forensic linux kernel module deadman-switch that responds to usb events. By default it turns of when a specific USB device is removed. It can also respond to any USB device being plugged in (for the very paranoid).

Inspired by [silk-guardian](https://github.com/pepa65/silk-guardian.git), but much simpler in scope.

## Build & Use

* Required: libelf-dev

Build: `make`

Usage: `sudo insmod deadman.ko [id=0xVENDPROD] [off=0] [ins=1]
```
* `id`: *VEND* is the 2-byte hexadecimal code for idVendor and *PROD* for idProduct. The `id` parameter can also be set to a default device in the source before building.
* `ins`: if ins=1 is passed, any USB device getting inserted triggers a panic.
* `off`: if `off=0` is passed, the computer will not turn off at a panic.

## Why?

When the drives your machine are fully (or partially) encrypted, they are still vulnerable when in-use, unencrypted. Requiring the specified USB device to remain connected is an added security feature; once the system is down, all encrypted data is only accessible by decrypting it first.

When a USB device is strapped to ones wrist, it will be harder for third parties to prevent the device to be removed when attacked.

### Other tools

Silk-guardian has broader uses, it can also shred certain files (in case no encryption is in use), it can respond to unknown USB devices (such as a "mouse jiggler" as used by law enforcement to keep the system from sleeping, or a USB drive that someone is wanting to copy files to).
