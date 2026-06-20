

#include "./Driver_gpio.h"


int32_t gpio_hsiom_init( pin_t pin,io_sel_t io_sel)
{
	uint32_t offset = ((uint32_t)(pin.ptr2portBase))&(0x0F00);

	*((volatile uint32_t*)(HSIOM_PORT_SEL_x_BASE + offset)) &=~(0x0F<<(4*pin.pinNum));
	*((volatile uint32_t*)(HSIOM_PORT_SEL_x_BASE + offset)) |= (io_sel<<(4*pin.pinNum));
	return 0;
}

int32_t gpio_init(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum, const gpio_config_t *gpio_config )
{
	if((ptr2gpioBase== NULL)||(pinNum>=8)||(gpio_config==NULL))
		return -1;
	else
	{
		/*Configure the drive mode*/
		ptr2gpioBase->portx_PC &=~(0x07<<(3*pinNum));
		ptr2gpioBase->portx_PC |= (gpio_config->driveMode<<(3*pinNum));
		
		/*write the initial value to pin*/
		if((gpio_config->outputVal)==gpio_outputValue_logic_Low)
			ptr2gpioBase->portx_DR_CLR =(1<<pinNum);
		else if((gpio_config->outputVal)==gpio_outputValue_logic_High)
			ptr2gpioBase->portx_DR_SET =(1<<pinNum);
		
		/*Configure the event type | Valid in case of input interrupt mode*/
		ptr2gpioBase->portx_INTR_CFG &=~(0x03<<(2*pinNum));
		ptr2gpioBase->portx_INTR_CFG |= (gpio_config->eventType<<(2*pinNum));
		
		/*If INTR_CFG is non zero --> Not disabled*/
		if(gpio_config->eventType != gpio_eventType_Disable )
		{
			//Set the priority
			nvic_set_priority(gpio_config->ptr2nvicConfig->IRQ_Num,
							  gpio_config->ptr2nvicConfig->priority);
			//Clear the the pending the IRQ request in from that pin/peripheral if any
			int32_t status = gpio_clear_interrupt(ptr2gpioBase,pinNum);
			if(status ==-1) return -1;
			//Enable the IRQ at NVIC level
			nvic_enableIRQ(gpio_config->ptr2nvicConfig->IRQ_Num);
		}
	}
	return 0;

}

int32_t gpio_set_pin(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum)
{
	if((ptr2gpioBase== NULL)||(pinNum>=8))
	return -1;
	else
		ptr2gpioBase->portx_DR_SET = (1<<pinNum);
	
	return 0;
}


int32_t gpio_clear_pin(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum)
{
	if((ptr2gpioBase == NULL)||(pinNum>=8))
	return -1;
	else
		ptr2gpioBase->portx_DR_CLR = (1<<pinNum);
	return 0;
}


int32_t gpio_invert_pin(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum)
{
	if((ptr2gpioBase == NULL)||(pinNum>=8))
	return -1;
	else
		ptr2gpioBase->portx_DR_INV = (1<<pinNum);
	return 0;

}
int32_t gpio_read_pin(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum,uint8_t *pinState)
{
	if((ptr2gpioBase== NULL)||(pinNum>=8)||(pinState==NULL))
		return -1;
	else
		*pinState = (((ptr2gpioBase->portx_PS)&(0x01<<pinNum))>>pinNum);

	return 0;

}

int32_t gpio_deInit(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum)
{
	if((ptr2gpioBase == NULL)||(pinNum>=8))
	return -1;
	else
 	{ 
		gpio_clear_pin(ptr2gpioBase, pinNum);
		
		ptr2gpioBase->portx_PC &=~(0x07<<(3*pinNum));
 	
	};
 	
 	return 0;
	
}

int32_t gpio_clear_interrupt(volatile gpio_struct_t* ptr2gpioBase, uint32_t pinNum)
{
	if((ptr2gpioBase == NULL)||(pinNum>=8))
	return -1;
	else
		ptr2gpioBase->portx_INTR = (1<<pinNum);
	return 0;
}