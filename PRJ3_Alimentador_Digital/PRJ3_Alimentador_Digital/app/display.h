#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

// Função de inicialização do display
void Display_Init(void);

// Função para imprimir uma string no display
void Display_Print(const char *str);

// Função para mostrar o menu no display
void Display_ShowMenu(void);

// Função para exibir uma mensagem no display (adicionada)
void Display_ShowMessage(const char *msg, uint8_t linha);

// Função para exibir uma barra de progresso no display (adicionada)
void Display_ShowProgressBar(int32_t valorAtual, int32_t valorMaximo);

#endif // DISPLAY_H
