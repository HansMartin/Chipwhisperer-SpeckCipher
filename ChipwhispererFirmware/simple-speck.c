#include "hal.h"
#include <stdint.h>
#include <stdlib.h>

#include "simpleserial.h"
#include "speck.h"

u8 gkey[8] = {0x00};


uint8_t get_key(uint8_t* k, uint8_t len) {
	simpleserial_put('o', 8, gkey);
	return 0x00;
}

uint8_t set_key(uint8_t* key, uint8_t len) {
    memcpy(gkey, key, 8);
    return 0x00;
}

uint8_t get_pt(uint8_t* pt, uint8_t len) {

	trigger_high();

        // Only for testing purposes
        volatile uint8_t testing_output[] = {0x42, 0x41, 0x41, 0x41,0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 };

	trigger_low();

	simpleserial_put('r', 16, testing_output);

	return 0x00;
}


uint8_t encrypt_block(uint8_t* pt, uint8_t len) {

    trigger_high(); // TRIGGER START

    u8 key[8] = {0x00};
    memcpy(key, gkey, 8); // copy the globally set encryption key
    u8 ct[4] = {0x00};
    Speck3264_EncryptBlock(pt, key, ct); // the encryption happens here

    trigger_low(); // TRIGGER STOP

    simpleserial_put('c', 4, ct);
    return 0x00;
}


uint8_t reset(uint8_t* x, uint8_t len) {
	simpleserial_put('r', 0, NULL);
	// Reset key here if needed
	return 0x00;
}


int main(void) {
    platform_init();
	init_uart();
	trigger_setup();

        // Setup the Simple Serial Options
	simpleserial_init();
	simpleserial_addcmd('p', 16, get_pt);
	simpleserial_addcmd('e', 4, encrypt_block);
	simpleserial_addcmd('k', 4, get_key);
	simpleserial_addcmd('s', 8, set_key);
	simpleserial_addcmd('x', 0, reset);

	while(1)
		simpleserial_get();
}
