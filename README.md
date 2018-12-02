# deadman
Deadman is linux kernel module deadman-switch that responds to removal of a specific USB device (or the insertion of any).

## Build & Use
* Build: `make`
* Install: `sudo make install`
* Usage: `sudo insmod <path>/deadman.ko [id=0xVENDPROD] [off=0] [ins=1] [log=0]`
* Usage (if installed): `sudo modprobe deadman [id=0xVENDPROD] [off=0] [ins=1] [log=0]`
  - `id`: *VEND* is the 2-byte hexadecimal code for idVendor and *PROD* for idProduct. The `id` parameter can also be set to a default device in the source before building.
  - `off`: if `off=0` is given, the computer will not turn off at a panic.
  - `ins`: if ins=1 is given, any USB device getting inserted triggers a panic.
  - `log`: if `log=0` is given, no messages will be logged anywhere.

## Rationale
When information on the computer is encrypted, it is still accessible when in use, unencrypted. Only when turned off does the encryption fully protect the information, and when a computer is seized by a competent agent while running, unencrypted information can be accessed. If the computer can be made to turn off in an emergency, it will heightens the security. A deadman USB device only needs to be removed to trigger a power-off, and when it is strapped to ones wrist, it will be harder to prevent the removal when attacked. Another attack is insertion of a USB device into a running system, and this can also be made to trigger a power-off.
