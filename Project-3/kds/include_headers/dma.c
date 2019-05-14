#include "dma.h"
#include "buffer.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

void dma_init(void)
{
	//ready = 0;
	// Enable clocks
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

	// Config DMA Mux for ADC operation
	// Disable DMA Mux channel first
	DMAMUX0_CHCFG0 = 0x00;

	// Clear pending errors and/or the done bit
	if (((DMA_DSR_BCR0 & DMA_DSR_BCR_DONE_MASK) == DMA_DSR_BCR_DONE_MASK)
			| ((DMA_DSR_BCR0 & DMA_DSR_BCR_BES_MASK) == DMA_DSR_BCR_BES_MASK)
			| ((DMA_DSR_BCR0 & DMA_DSR_BCR_BED_MASK) == DMA_DSR_BCR_BED_MASK)
			| ((DMA_DSR_BCR0 & DMA_DSR_BCR_CE_MASK) == DMA_DSR_BCR_CE_MASK))
		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;

	DMA_SAR0 = (uint32_t)&ADC0_RA;
	DMA_DAR0 = (uint32_t)start; 				//(uint32_t)&value;
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(DMA_BYTES); // 2 bytes (16 bits) per transfer

	DMA_DCR0 = (DMA_DCR_EINT_MASK|		// Enable interrupt.
			DMA_DCR_SSIZE(2) |			// Set source size to 16 bits
			DMA_DCR_DINC_MASK|		    // No destination increments when the destination address is a peripheral register address
			DMA_DCR_DSIZE(2)			// Set destination size of 16 bits
			);

	// Enable DMA channel and source
	DMAMUX0_CHCFG0 = DMAMUX_CHCFG_ENBL_MASK | DMAMUX_CHCFG_SOURCE(40); //Enables MUX for ADC0 as source
	return 0;
}

void DMA0_IRQHandler(void)
{
	static int i=0;
	for(i=32;i<DMA_BYTES;i++)
	{
		 if(*mid>peak)peak=*mid;
		 mid+=1;
		 midcount+=1;
	}
	if(peak<old_peak){old_peak=old_peak/coeff;}
	else old_peak=peak;

	mid = &buffer[(midcount+0)&(DMA_BYTES-1)];
	peak=*mid;
	start=&buffer[(midcount+0+32)&(DMA_BYTES-1)];
	midcount = (midcount+0)&(DMA_BYTES-1);
	DMA_DAR0=(uint32_t)start;

	/* Enable DMA0*/
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;			// Clear Done Flag
	DMA_DSR_BCR0 |= DMA_DSR_BCR_BCR(DMA_BYTES);		// Set byte count register
	DMA_DCR0 |= DMA_DCR_START_MASK;					//start DMA channel 0 transfer
}



