#include "display.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

#define ST7789_RESET_PIN     GPIO_PIN_4  // PA4
#define ST7789_DC_PIN        GPIO_PIN_5  // PA5
#define ST7789_BL_PIN        GPIO_PIN_6  // PA6

#define ST7789_RESET_PORT    GPIOA
#define ST7789_DC_PORT       GPIOA
#define ST7789_BL_PORT       GPIOA

extern SPI_HandleTypeDef hspi1;  // SPI1, configurado no CubeIDE

// Função auxiliar para enviar um comando para o display
void ST7789_WriteCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(ST7789_DC_PORT, ST7789_DC_PIN, GPIO_PIN_RESET);  // DC = 0 (comando)
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
}

// Função auxiliar para enviar dados para o display
void ST7789_WriteData(uint8_t data) {
    HAL_GPIO_WritePin(ST7789_DC_PORT, ST7789_DC_PIN, GPIO_PIN_SET);  // DC = 1 (dados)
    HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
}

// Inicialização básica do display ST7789
void ST7789_Init(void) {
    // Reset físico
    HAL_GPIO_WritePin(ST7789_RESET_PORT, ST7789_RESET_PIN, GPIO_PIN_RESET);
    HAL_Delay(50);
    HAL_GPIO_WritePin(ST7789_RESET_PORT, ST7789_RESET_PIN, GPIO_PIN_SET);
    HAL_Delay(150);

    // Sequência de inicialização
    ST7789_WriteCommand(0x01);  // Software reset
    HAL_Delay(150);

    ST7789_WriteCommand(0x11);  // Sleep out
    HAL_Delay(120);

    ST7789_WriteCommand(0x36);  // Memory data access control
    ST7789_WriteData(0x00);     // Default rotation (ajustável)

    ST7789_WriteCommand(0x3A);  // Pixel format
    ST7789_WriteData(0x55);     // 16 bits por pixel

    ST7789_WriteCommand(0x29);  // Display ON
    HAL_Delay(50);

    // Ativa backlight (caso seja controlado via GPIO)
    HAL_GPIO_WritePin(ST7789_BL_PORT, ST7789_BL_PIN, GPIO_PIN_SET);
}

// Função para imprimir uma string no display (simulação temporária)
void Display_Print(const char *str) {
    printf("%s\n", str);  // Simula no console
}

// Função para mostrar o menu no display (simulação)
void Display_ShowMenu(void) {
    printf("\n=== Menu Principal ===\n");
    printf("1. Servir ração\n");
    printf("2. Configurar horário\n");
    printf("3. Sair\n");
    printf("======================\n");
}

// Função para exibir mensagem simulada
void Display_ShowMessage(const char *msg, uint8_t linha) {
    printf("Mensagem linha %d: %s\n", linha, msg);
}

// Função de barra de progresso (simulação)
void Display_ShowProgressBar(int32_t valorAtual, int32_t valorMaximo) {
    int32_t progresso = (valorAtual * 100) / valorMaximo;
    if (progresso > 100) progresso = 100;

    printf("Progresso: [");
    for (int i = 0; i < 50; i++) {
        if (i < progresso / 2) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %ld%%\n", progresso);
}
