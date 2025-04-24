#ifndef DISPLAY_H
#define DISPLAY_H

#include "stm32f4xx_hal.h"  // Para funções da HAL

// Função de inicialização do display ST7789
void ST7789_Init(void);

// Função para enviar um comando ao display
void ST7789_WriteCommand(uint8_t cmd);

// Função para enviar dados ao display
void ST7789_WriteData(uint8_t data);

// Função para imprimir uma string no display
void Display_Print(const char *str);

// Função para mostrar o menu no display
void Display_ShowMenu(void);

// Função para mostrar uma mensagem no display
void Display_ShowMessage(const char *msg, uint8_t linha);

// Função para exibir uma barra de progresso no display
void Display_ShowProgressBar(int32_t valorAtual, int32_t valorMaximo);

#endif // DISPLAY_H
