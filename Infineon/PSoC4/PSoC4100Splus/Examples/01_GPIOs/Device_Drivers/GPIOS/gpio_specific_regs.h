/*
 * gpio_specific_regs.h
 *
 *  Created on: 1 Jan 2026
 *      Author: GeeberuBasav
 */

#ifndef GPIO_SPECIFIC_REGS_H_
#define GPIO_SPECIFIC_REGS_H_

#pragma once

/*Port Base Address*/
#define PORT0_BASE 0x40040000UL
#define PORT1_BASE 0x40040100UL
#define PORT2_BASE 0x40040200UL
#define PORT3_BASE 0x40040300UL
#define PORT4_BASE 0x40040400UL
#define PORT5_BASE 0x40040500UL
#define PORT6_BASE 0x40040600UL
#define PORT7_BASE 0x40040700UL

/*PORTx I/O Registers*/

#define PORTx_DR 		0x000UL
#define PORTx_PS 		0x004UL
#define PORTx_PC 		0x008UL
#define PORTx_INTR_CFG  0x00CUL
#define PORTx_INTR		0x010UL
#define PORTx_PC2 		0x018UL
#define PORTx_DR_SET    0x040UL
#define PORTx_DR_CLR	0x044UL
#define PORTx_DR_INV    0x048UL


#define HSIOM_PORT_SEL_0 0x40020000UL
#define HSIOM_PORT_SEL_1 0x40020100UL
#define HSIOM_PORT_SEL_2 0x40020200UL
#define HSIOM_PORT_SEL_3 0x40020300UL
#define HSIOM_PORT_SEL_4 0x40020400UL
#define HSIOM_PORT_SEL_5 0x40020500UL
#define HSIOM_PORT_SEL_6 0x40020600UL
#define HSIOM_PORT_SEL_7 0x40020700UL

#define HSIOM_PORT_SEL_x_BASE HSIOM_PORT_SEL_0


/*Pin Numbers*/

#define PORTx_PIN0 0 
#define PORTx_PIN1 1 
#define PORTx_PIN2 2 
#define PORTx_PIN3 3 
#define PORTx_PIN4 4 
#define PORTx_PIN5 5 
#define PORTx_PIN6 6 
#define PORTx_PIN7 7


#endif /* DEVICE_DRIVERS_GPIOS_GPIO_SPECIFIC_REGS_H_ */
