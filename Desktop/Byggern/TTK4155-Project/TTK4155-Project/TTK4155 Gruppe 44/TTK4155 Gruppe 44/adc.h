
#ifndef ADC_H_
#define ADC_H_

#include <avr/interrupt.h>

void ADC_init();
uint8_t ADC_read(char channel);

#endif /* ADC_H_ */