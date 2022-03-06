#----------------------------------------------------------------------------

# Target file name (without extension).
# This is the name of the compiled .hex file.
TARGET = simple-speck

# Set platform and target
PLATFORM=CWLITEARM
CRYPTO_TARGET=NONE

# List C source files here.
# Header files (.h) are automatically pulled in.
SRC += simple-speck.c
SRC += speck3264.c

# -----------------------------------------------------------------------------

ifeq ($(CRYPTO_OPTIONS),)
CRYPTO_OPTIONS = AES128C
endif

#Add simpleserial project to build
include deps/Makefile.simpleserial

FIRMWAREPATH = deps/
include $(FIRMWAREPATH)/Makefile.inc


x86:
	gcc speck3264.c -o speck
