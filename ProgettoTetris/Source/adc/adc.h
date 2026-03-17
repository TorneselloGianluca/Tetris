#include <string.h>
extern unsigned short AD_current;
extern int volume;

/* lib_adc.c */
void ADC_init (void);
void ADC_start_conversion (void);

/* IRQ_adc.c */
void ADC_IRQHandler(void);

void init_random_seed(void);
