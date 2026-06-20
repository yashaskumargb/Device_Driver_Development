/*
 * Driver_nvic.c
 *
 *  Created on: 1 Jan 2026
 *      Author: GeeberuBasav
 */

#include "./Driver_nvic.h"

void nvic_set_priority(uint8_t IRQ_Num, nvic_irq_priority_t nvicPriority )
{
	NVIC->nvic_IPR[IRQ_Num/4] &=~(0x03<<(6 + 8*(IRQ_Num%4)));
	NVIC->nvic_IPR[IRQ_Num/4] |= ((nvicPriority%4)<<(6 + 8*(IRQ_Num%4)));
}


void nvic_get_priority(uint8_t IRQ_Num, uint8_t* nvicPriority )
{
	*nvicPriority = ((NVIC->nvic_IPR[IRQ_Num/4]) & ((0x03<<(6 + 8*(IRQ_Num%4)))));
}

void nvic_enableIRQ(uint8_t IRQNum)
{
	NVIC->nvic_ISER |=((uint32_t)(0x01<<IRQNum));
}

void nvic_disableIRQ(uint8_t IRQNum)
{
	NVIC->nvic_ICER |=(0x01<<IRQNum);
}