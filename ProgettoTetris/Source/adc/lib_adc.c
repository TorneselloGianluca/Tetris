#include "LPC17xx.h"
#include "adc.h"

/*----------------------------------------------------------------------------
  Function that initializes ADC
 *----------------------------------------------------------------------------*/
void ADC_init (void) {

  LPC_PINCON->PINSEL3 |=  (3UL<<30);      /* P1.31 is AD0.5                     */

  LPC_SC->PCONP       |=  (1<<12);      /* Enable power to ADC block          */

  LPC_ADC->ADCR        =  (1<< 5) |     /* select AD0.5 pin                   */
                          (4<< 8) |     /* ADC clock is 25MHz/5               */
                          (1<<21);      /* enable ADC                         */ 

  LPC_ADC->ADINTEN     =  (1<< 8);      /* global enable interrupt            */

  NVIC_EnableIRQ(ADC_IRQn);             /* enable ADC Interrupt               */
}

void ADC_start_conversion (void) {
	LPC_ADC->ADCR |=  (1<<24);            /* Start A/D Conversion 				*/
}


void init_random_seed(void) {
    // piccola attesa per permettere almeno una conversione ADC
 	volatile int i;
    for (i=0; i < 100000; i++);

    uint32_t seed =
        AD_current ^
        (volume << 4) ^
        LPC_TIM0->TC ^
        LPC_GPIO1->FIOPIN;

    srand(seed);
}