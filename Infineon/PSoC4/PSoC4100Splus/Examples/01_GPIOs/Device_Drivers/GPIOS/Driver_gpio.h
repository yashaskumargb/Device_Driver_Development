/*
 * gpio.h
 *
 *  Created on: 1 Jan 2026
 *      Author: GeeberuBasav
 */

#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_

#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "./gpio_specific_regs.h"
#include "./../NVIC/Driver_nvic.h"

#define __IM volatile const /* Used for read only registers | But Hardware can write to this Memory*/
#define __OM volatile 		/* Used for write only registers*/
#define __IOM volatile 		/* Used for read-wrtie registers*/

typedef struct gpio_struct_s gpio_struct_t;

#define GPIO_PORT0 ((volatile gpio_struct_t*)PORT0_BASE)
#define GPIO_PORT1 ((volatile gpio_struct_t*)PORT1_BASE)
#define GPIO_PORT2 ((volatile gpio_struct_t*)PORT2_BASE)
#define GPIO_PORT3 ((volatile gpio_struct_t*)PORT3_BASE)
#define GPIO_PORT4 ((volatile gpio_struct_t*)PORT4_BASE)
#define GPIO_PORT5 ((volatile gpio_struct_t*)PORT5_BASE)
#define GPIO_PORT6 ((volatile gpio_struct_t*)PORT5_BASE)
#define GPIO_PORT7 ((volatile gpio_struct_t*)PORT5_BASE)

typedef struct gpio_struct_s{
	__IOM uint32_t portx_DR;
	__IM  uint32_t portx_PS;
	__IOM uint32_t portx_PC;
	__IOM uint32_t portx_INTR_CFG;
	__IOM uint32_t portx_INTR;
	__IM uint32_t RESERVED1;
	 uint32_t portx_PC2;
	/*Unused Space: 0x01C - 0x040*/
	__IM uint32_t RESERVED2[9];
	__IOM uint32_t portx_DR_SET;
	__IOM uint32_t portx_DR_CLR;
	__IOM uint32_t portx_DR_INV;
}gpio_struct_t;

typedef struct pin_s{
	volatile gpio_struct_t* ptr2portBase;
	uint8_t pinNum;
}pin_t;
typedef enum gpio_driveMode_e{
	gpio_driveMode_Mode0_Analog,
	gpio_driveMode_Mode1_Input,
	gpio_driveMode_Mode2_ResistivePullUp,
	gpio_driveMode_Mode3_ResistivePullDown,
	gpio_driveMode_Mode4_StrongPullDown,
	gpio_driveMode_Mode5_StrongPullUp,
	gpio_driveMode_Mode6_StrongPullUpPullDown,
	gpio_driveMode_Mode7_WeakPullUpPullDown
}gpio_driveMode_t;

typedef enum gpio_outputValue_e
{
	gpio_outputValue_logic_Low,
	gpio_outputValue_logic_High
}gpio_outputValue_t;

typedef enum gpio_eventType_e{
	gpio_eventType_Disable,
	gpio_eventType_RisingEdge,
	gpio_eventType_FallingEdge,
	gpio_eventType_Both
	
}gpio_eventType_t;

typedef enum{
	IOx_SEL_GPIO = 0,
	IOx_SEL_GPIO_DSI ,
	IOx_SEL_DSI_DSI ,
	IOx_SEL_DSI_GPIO ,
	IOx_SEL_CSD_SENSE ,
	IOx_SEL_CSD_SHIELD,
	IOx_SEL_AMUXA ,
	IOx_SEL_AMUXB ,
	IOx_SEL_ACT_0 ,
	IOx_SEL_ACT_1 ,
	IOx_SEL_ACT_2 ,
	IOx_SEL_ACT_3 ,
	IOx_SEL_LCD_COM ,
	IOx_SEL_DS_0 ,
	IOx_SEL_LCD_SEG ,
	IOx_SEL_DS_1 ,
	IOx_SEL_DS_2 ,
	IOx_SEL_DS_3 ,
}io_sel_t;

typedef struct gpio_config_s{
	gpio_driveMode_t driveMode;
	gpio_outputValue_t outputVal;
	gpio_eventType_t eventType;
	nvic_irq_config_t *ptr2nvicConfig;
}gpio_config_t;

/*configure HSIOM Before any gpio activity*/
int32_t gpio_hsiom_init( pin_t pin,io_sel_t io_sel);
/*API to intialize the pinNum of port pointed by ptr2gpioBase to configurations given in gpio_config struct*/
int32_t gpio_init(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum, const gpio_config_t *gpio_config );

/*API to set the output of pin to logic 1*/
int32_t gpio_set_pin(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum);

/*API to set the output of the pin logic 0*/
int32_t gpio_clear_pin(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum);

/*API to toggle the output of the pin */
int32_t gpio_invert_pin(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum);

/*API to set the output of the pin logic 0*/
int32_t gpio_read_pin(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum,uint8_t *pinState);

/*API to clear the IRQ detected on the pin*/
int32_t gpio_clear_interrupt(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum);

/*API to de intialize the pinNum of port pointed by ptr2gpioBase to IDLE mode*/
int32_t gpio_deInit(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum);

#endif /* DEVICE_DRIVERS_GPIOS_DRIVER_GPIO_H_ */
