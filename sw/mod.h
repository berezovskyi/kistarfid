/* 
 * File:   mod.h
 * Author: andrew
 *
 * Created on October 25, 2016, 6:46 PM
 */

#ifndef MOD_H
#define	MOD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <pic12f1612.h>

void mod_start();
void mod_end();
void mod_1();
void mod_0();
void mod_byte(uint8_t byte);



#ifdef	__cplusplus
}
#endif

#endif	/* MOD_H */

