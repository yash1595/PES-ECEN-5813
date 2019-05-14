/*
 * nvic.h
 *
 *  Created on: Nov 6, 2012
 *      Author: B34443
 */

#ifndef NVIC_H_
#define NVIC_H_

#include "MKL25Z4.h"
//#include "circular_buff_init.h"
#define INTERRUPT	1
#define	UART_MODE	INTERRUPT
/*ARM Cortex M0 implementation for interrupt priority shift*/
#define ARM_INTERRUPT_LEVEL_BITS          2

#define EnableInterrupts __asm(" CPSIE i");
#define DisableInterrupts __asm(" CPSID i");

void enable_irq (int irq)
{
    if (irq > 32)
        __asm("nop");
    else
    {
      NVIC->ICPR[0] = 1<<irq%32;
      NVIC->ISER[0] = 1<<irq%32;
    }
}

void disable_irq (int irq)
{
    if (irq > 32)
        __asm("nop");
    else
      /* Set the ICER register accordingly */
      NVIC->ICER[0] = 1<<irq%32;
}
/***********************************************************************/
/*
 * Initialize the NVIC to set specified IRQ priority.
 *
 * NOTE: The function only initializes the NVIC to set a single IRQ priority.
 * Interrupts will also need to be enabled in the ARM core. This can be
 * done using the EnableInterrupts macro.
 *
 * Parameters:
 * irq    irq number to be enabled (the irq number NOT the vector number)
 * prio   irq priority. 0-3 levels. 0 max priority
 */

void set_irq_priority (int irq, int prio)
{
    /*irq priority pointer*/
    uint32_t *prio_reg;
    uint8_t err = 0;
    uint8_t div = 0;
    uint8_t off = 0;

    /* Make sure that the IRQ is an allowable number. Right now up to 32 is
     * used.
     *
     * NOTE: If you are using the interrupt definitions from the header
     * file, you MUST SUBTRACT 16!!!
     */
    if (irq > 32)
    {
        err = 1;
    }

    if (prio > 3)
    {
        err = 1;
    }

    if (err != 1)
    {
        /* Determine which of the NVICIPx corresponds to the irq */
        div = irq / 4;
        off = irq % 4;
        prio_reg = (uint32_t *)((uint32_t)&NVIC->IP[div]);
        /* Assign priority to IRQ */
        *prio_reg |= ( (prio&0x3) << (8 - ARM_INTERRUPT_LEVEL_BITS) ) << (off  * 8);
    }
}

#endif /* NVIC_H_ */
