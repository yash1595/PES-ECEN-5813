#include "adc.h"
#include "fsl_debug_console.h"
#include "nvic.h"

void ADC_Init16b(void)
{
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;								//Initializes the Clock for the ADC port

	ADC0_SC1A = (ADC_SC1_DIFF(1)|ADC_SC1_AIEN(0)|ADC_SC1_ADCH(0));	//Sets up differential mode,interrupts disabled,channel-0(DAD0)

	ADC0_CFG1 |= (ADC_CFG1_MODE(3) |								//Mode=16-bit,Bus Clock,Clock divide by 4
				  ADC_CFG1_ADICLK(0)|
			      ADC_CFG1_ADIV(2));

	ADC0_SC2 |= ADC_SC2_DMAEN_MASK;									//Enables the DMA mask for the ADC

	ADC0_SC3 = (ADC_SC3_ADCO(1));									//Continuous trigger mode

	ADC0_SC1A |= (ADC_SC1_ADCH(0));									//ADC Channel 0
}





