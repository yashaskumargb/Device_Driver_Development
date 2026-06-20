/*
 * Driver_nvic.h
 *
 *  Created on: 1 Jan 2026
 *      Author: GeeberuBasav
 */

#ifndef DRIVER_NVIC_H_
#define DRIVER_NVIC_H_

#include <stdint.h>
#include "./nvic_specific_regs.h"

#define __IM volatile const /* Used for read only registers | But Hardware can write to this Memory*/
#define __OM volatile 		/* Used for write only registers*/
#define __IOM volatile 		/* Used for read-wrtie registers*/

typedef struct nvic_struct_s nvic_struct_t;

#define NVIC ((volatile nvic_struct_t *)NVIC_BASE)

typedef struct nvic_struct_s{
	__IOM uint32_t nvic_ISER;
	/*Unused Space: 0x104 - 0x180*/
	uint32_t RESERVED1[31];
	__IOM uint32_t nvic_ICER;
	/*Unused Space: 0x184 - 0x200*/
	uint32_t RESERVED2[31];
	__IOM uint32_t nvic_ISPR;
	/*Unused Space: 0x204 - 0x280*/
	uint32_t RESERVED3[31];
	__IOM uint32_t nvic_ICPR;
	/*Unused Space: 0x2844 - 0x400*/
	uint32_t RESERVED4[95];
	__IOM uint32_t nvic_IPR[7];	
}nvic_struct_t;

typedef enum nvic_irq_priority_e
{
	NVIC_IRQ_PRIORITY_0,
	NVIC_IRQ_PRIORITY_1,
	NVIC_IRQ_PRIORITY_2,
	NVIC_IRQ_PRIORITY_3
}nvic_irq_priority_t;

typedef struct nvic_irq_config_s{
	uint8_t IRQ_Num;
	nvic_irq_priority_t priority;
}nvic_irq_config_t;	


void nvic_set_priority(uint8_t IRQ_Num, nvic_irq_priority_t nvicPriority );

void nvic_get_priority(uint8_t IRQ_Num, uint8_t* nvicPriority );

void nvic_enableIRQ(uint8_t IRQNum);

void nvic_disableIRQ(uint8_t IRQNum);
#endif /* DEVICE_DRIVERS_NVIC_DRIVER_NVIC_H_ */
