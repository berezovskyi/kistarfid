#include "crc_pic.h"
#include "mod.h"
#include "adc.h"

static const uint8_t cmd_inventory_data[10] = {
	0x0, 0x0, 0x0, 0xFE,
	0xCA, 0xEF, 0xBE, 0xAD,
	0xDE, 0xE0
};


void cmd_inventory() {
	crc_compute(cmd_inventory_data, sizeof (cmd_inventory_data) / sizeof (cmd_inventory_data[0]));
	mod_start();
	mod_byte(cmd_inventory_data[0]);
	mod_byte(cmd_inventory_data[1]);
	mod_byte(cmd_inventory_data[2]);
	mod_byte(cmd_inventory_data[3]);
	mod_byte(cmd_inventory_data[4]);
	mod_byte(cmd_inventory_data[5]);
	mod_byte(cmd_inventory_data[6]);
	mod_byte(cmd_inventory_data[7]);
	mod_byte(cmd_inventory_data[8]);
	mod_byte(cmd_inventory_data[9]);
	mod_byte(crc_lo); //crc
	mod_byte(crc_hi); //crc
	mod_end();
}

static uint8_t cmd_read_data[6] = {
	0x40,	/* Option flag set -> security status included */
	0x0,	/* Security status */
	0xDE, 0xAD, 0xEF, 0xBE,
};


void cmd_read() {
	cmd_read_data[2] = adc_get_low();
	cmd_read_data[3] = adc_get_high();
	crc_compute(cmd_read_data, sizeof (cmd_read_data) / sizeof (cmd_read_data[0]));
	mod_start();
	mod_byte(cmd_read_data[0]);
	mod_byte(cmd_read_data[1]);
	mod_byte(cmd_read_data[2]);
	mod_byte(cmd_read_data[3]);
	mod_byte(cmd_read_data[4]);
	mod_byte(cmd_read_data[5]);
	mod_byte(crc_lo); //crc
	mod_byte(crc_hi); //crc
	mod_end();
}
