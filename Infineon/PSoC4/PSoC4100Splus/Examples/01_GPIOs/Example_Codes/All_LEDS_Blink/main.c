#include <stdio.h>
#include <stdint.h>
#include "./../Special_Libraries/cmsis_gcc.h"
#include "./../Special_Libraries/reset.h"

/*Custom Headers*/

#include "./../Device_Drivers/GPIOS/Driver_gpio.h"
#include "./../Device_Drivers/NVIC/Driver_nvic.h"

uint8_t app_heap[512] __attribute__((section (".heap")));
uint8_t app_stack[4096] __attribute__((section (".stack")));

volatile static uint8_t cnt=0;
pin_t LED_ARRAY[] = {    {GPIO_PORT1,PORTx_PIN0} ,
                         {GPIO_PORT1,PORTx_PIN2} ,
                         {GPIO_PORT1,PORTx_PIN4} ,
                         {GPIO_PORT1,PORTx_PIN6} ,
                         {GPIO_PORT2,PORTx_PIN0} ,
                         {GPIO_PORT2,PORTx_PIN2} ,
                         {GPIO_PORT5,PORTx_PIN2} ,
                         {GPIO_PORT5,PORTx_PIN5} ,
                         {GPIO_PORT5,PORTx_PIN7} };
pin_t userBtn = {GPIO_PORT3,PORTx_PIN7};
gpio_config_t LEDx_config = {.driveMode =gpio_driveMode_Mode6_StrongPullUpPullDown,
                      .outputVal = gpio_outputValue_logic_Low,
                      .eventType = gpio_eventType_Disable,
                      .ptr2nvicConfig = NULL};

gpio_config_t btn_config = {.driveMode =gpio_driveMode_Mode2_ResistivePullUp,
                      .outputVal = gpio_outputValue_logic_High,
                      .eventType = gpio_eventType_FallingEdge,
                      .ptr2nvicConfig = NULL};
nvic_irq_config_t btn_irq_cfg ={.IRQ_Num=3,
                                .priority = NVIC_IRQ_PRIORITY_1};                                          
void Delay(uint32_t delayNumber);

int main()
{
    /* Enable Interrupts at CPU level */
    enable_irq();
    int32_t status;
    for(volatile uint8_t i=0;i<9;i++)
    status = gpio_hsiom_init(LED_ARRAY[i],0);
    for(volatile uint8_t i=0;i<9;i++)
    {
    status = gpio_init(LED_ARRAY[i].ptr2portBase,LED_ARRAY[i].pinNum, &LEDx_config);
    if(status ==-1) return 0;
    }

    btn_config.ptr2nvicConfig = &btn_irq_cfg;
    status = gpio_init(userBtn.ptr2portBase,userBtn.pinNum, &btn_config);
    if(status ==-1) return 0;
    for(;;)
    {
        if(cnt%2)
        {
            for(volatile uint8_t i=0;i<9;i++)
            {
                status = gpio_invert_pin(LED_ARRAY[i].ptr2portBase,LED_ARRAY[i].pinNum);
                if(status ==-1) return 0;
            }
        }
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
    gpio_clear_interrupt(userBtn.ptr2portBase,userBtn.pinNum);
    cnt++;
    
    
}
