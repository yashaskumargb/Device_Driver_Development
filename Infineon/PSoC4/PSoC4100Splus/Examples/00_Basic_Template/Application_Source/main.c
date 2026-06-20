#include <stdio.h>
#include <stdint.h>
#include "./../Special_Libraries/cmsis_gcc.h"
#include "./../Special_Libraries/reset.h"
#include "./../Device_Drivers/GPIO/gpio.h"

uint8_t app_heap[512] __attribute__((section (".heap")));
uint8_t app_stack[4096] __attribute__((section (".stack")));

/* Flag used to toggle LED based on button input */
uint8_t invertFLAG = 0;

void Delay(uint32_t delayNumber);

int main()
{
    /* Enable Interrupts at CPU level */
    enable_irq();

    *((uint32_t *)0x40040200) = (1 << 2); // Set default output value of P2.2 to 1 (GPIO_PRT2_DR)
    *((uint32_t *)0x40040208) = (6 << 6); // Set drive mode of P2.2 to Digital OP Push Pull (GPIO_PRT2_PC)

    *((uint32_t *)0x40040100) = (1 << 6); // Set default output value of P1.6 to 1 (GPIO_PRT1_DR)
    *((uint32_t *)0x40040108) = (6 << 18); // Set output value of P1.6 to to Digital OP Push Pull (GPIO_PRT1_PC)
   
    *((uint32_t *)0x40040308) = (*((uint32_t *)0x40040308)) | (2 << 21); // Set output value of P3.7 to to Digital Input resistive pull up (GPIO_PRT3_PC)
    *((uint32_t *)0x40040300) = (1 << 7); // Set default output value of P3.7 to 1 (GPIO_PRT3_DR)
    *((uint32_t *)0x4004030C) = (2 << 14); // Enable falling edge interrupt detection for P3.7 (GPIO_PRT3_INTR_CFG)

    /* Set priorit level of the P3.7 user button (CM0P_IPRx) */
    *((uint32_t *)0xE000E400) = (3 << 30);

    /* Clearing and enabling the GPIO interrupt in NVIC for IRQ3 */
    *((uint32_t *)0xE000E280) = 0xFFFFFFFF; // (CM0P_ICPR) 
    *((uint32_t *)0xE000E100) = (1 << 3);   // (CM0P_ISER) 

    for(;;)
    {
        /* In an infinite loop toggle the LED 2.2, perform blinkey operation */
        *((uint32_t *)0x40040200) = (0 << 2); // Set output value of P2.2 to 0 (GPIO_PRT2_DR)
        Delay(60000);

        *((uint32_t *)0x40040200) = (1 << 2); // Set output value of P2.2 to 1 (GPIO_PRT2_DR)
        Delay(60000);  
    }

    return 0;
}

/* Simple software based delay function */
void Delay(uint32_t delayNumber)
{
    for(uint32_t i=0; i<delayNumber; i++);
    for(uint32_t i=0; i<delayNumber; i++);
}

/* Interrupt handler for the button */
void ioss_interrupts_gpio_3_IRQHandler(void)
{
     uint32_t readVal;
    
     /* Clear the interrupt status at the GPIO peripheral to enable the next interrupt */
    *((uint32_t *)0x40040310) = (1 << 7); // Clear Interrupt for P3.7 (GPIO_PRT3_INTR)
    
    readVal = *((uint32_t *)0x40040304); // Read the P3.7 Input register and store into readVal (GPIO_PRT3_PS)
    if(((readVal >> 7) & 1) == 0u)
    {
        if(invertFLAG == 1u)
        {
            *((uint32_t *)0x40040100) = (1 << 6); // Set output value of P1.6 to 1 (GPIO_PRT1_DR)
            invertFLAG = 0u;
        }
        else if(invertFLAG == 0u)
        {         
            *((uint32_t *)0x40040100) = (0 << 6); // Set output value of P1.6 to 0 (GPIO_PRT1_DR)
            invertFLAG = 1u;          
        }
    }  
}


