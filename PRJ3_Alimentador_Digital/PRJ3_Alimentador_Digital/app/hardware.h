#ifndef HARDWARE_H
#define HARDWARE_H


// Estas funções de alto nível para o alimentador digital
// encapsulam chamadas ao HAL (implementadas em Core/Src, ex.: stm32f4xx_hal.c)
// e adicionam lógica específica (dispensa e sinalização de erro).
void hardware_init(void);
void hardware_update(void);
void hardware_dispense_food(void);
void hardware_signal_error(void);


#endif // HARDWARE_H
