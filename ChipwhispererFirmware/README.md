# Chipwhisperer Firmware Speck


This project is the main Chipwhisperer SimpleSerial project, adjusted to use the Speck Cipher for encryption.

## Firmware Setup

The linux ARM compiler tools are required to build the code. Detailed instructions can be found on the official Chipwhisperer page.
If the tools are installed, its a matter of a simple `make` to build the firmware for the CW. `make clean` gets rid of the firmware build files.


For local testing of the Speck implementation, a x86 binary can be build with: `make x86` which produces the `speck` binary for testing.



### Flashing on the CW

The following Python code can be used to flash the firmware on the CW:

```python
import chipwhisperer as cw
import time

PATH="/path/to/the/firmware_CWLITEARM.hex"

def flash(scope, prog):
    cw.program_target(scope, prog, PATH)

def reset_target(scope):
    scope.io.nrst = 'low'
    time.sleep(0.05)
    scope.io.nrst = 'high_z'
    time.sleep(0.05)

try:
    if not scope.connectStatus:
        scope.con()
except NameError:
    scope = cw.scope()

try:
    target = cw.target(scope)
except IOError:
    print("INFO: Caught exception on reconnecting to target - attempting to reconnect to scope first.")
    print("INFO: This is a work-around when USB has died without Python knowing. Ignore errors above this line.")
    scope = cw.scope()
    target = cw.target(scope)

print("INFO: Found ChipWhisperer😍")

prog = cw.programmers.STM32FProgrammer
time.sleep(0.05)
scope.default_setup()

# Reset (not always required)
reset_target(scope)

flash(scope, prog)
```



## Simple Serial

The following options can be used for the program:

```
s <8-byte-key>          // Set the encryption key
k                       // Get the key that is setup
e <4-byte-plaintext>    // Encrypt one block with the speck cipher
c                       // Read the ciphertext after the encryption
```


As python code, it looks like this. To setup an encryption key:

```python
encryption_key = b"\x11\x22\x33\x44\x55\x66\x77\x88"
if len(encryption_key) == 8:
    target.simpleserial_write("s", encryption_key)
```

And to use that key to encrypt a plaintext block and reveice the result:

```python
pt = b"\x4c\x69\x74\x65"
target.simpleserial_write("e", pt)
target.simpleserial_read("c", 4)
```


