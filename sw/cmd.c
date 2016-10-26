#include "crc_pic.h"
#include "mod.h"

static const uint8_t cmd_inventory_data[10] = {
	0x0, 0x0, 0xEE, 0xFE,
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

static uint8_t cmd_read_data[5] = {
	0x0,
	'A', 'R', 'N', 'E',
};


void cmd_read() {
	crc_compute(cmd_read_data, sizeof (cmd_read_data) / sizeof (cmd_read_data[0]));
	mod_start();
	mod_byte(cmd_read_data[0]);
	mod_byte(cmd_read_data[1]);
	mod_byte(cmd_read_data[2]);
	mod_byte(cmd_read_data[3]);
	mod_byte(cmd_read_data[4]);
	mod_byte(crc_lo); //crc
	mod_byte(crc_hi); //crc
	mod_end();
}