#include "display.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

// Definindo os pinos de controle do display
#define ST7789_RESET_PIN     GPIO_PIN_4  // PA4
#define ST7789_DC_PIN        GPIO_PIN_5  // PA5
#define ST7789_BL_PIN        GPIO_PIN_6  // PA6
#define ST7789_CS_PIN        GPIO_PIN_7  // PB7

extern SPI_HandleTypeDef hspi1;  // SPI1, configurado no CubeMX ou manualmente

// Função de inicialização do ST7789
void ST7789_Init(void) {
    // Reset do display
    HAL_GPIO_WritePin(GPIOA, ST7789_RESET_PIN, GPIO_PIN_RESET);  // Reseta o display
    HAL_Delay(50);  // Tempo de reset
    HAL_GPIO_WritePin(GPIOA, ST7789_RESET_PIN, GPIO_PIN_SET);    // Finaliza o reset
    HAL_Delay(150);  // Aguarda o display iniciar após reset

    // Configurações iniciais do display
    ST7789_WriteCommand(0x01);  // Software Reset
    HAL_Delay(150);  // Aguardar reset

    ST7789_WriteCommand(0x11);  // Sleep Out
    HAL_Delay(255);  // Aguardar wake-up do display

    ST7789_WriteCommand(0x36);  // Memory Data Access Control
    ST7789_WriteData(0x00);     // Definir a orientação para landscape (se necessário)

    ST7789_WriteCommand(0x3A);  // Interface Pixel Format
    ST7789_WriteData(0x55);     // 16 bits por pixel

    // (Comandos de configuração adicionais seguem conforme necessário)

    ST7789_WriteCommand(0x29);  // Display ON
    HAL_Delay(50);  // Aguardar um pouco após ativar o display
}

// Função auxiliar para enviar um comando para o display
void ST7789_WriteCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(GPIOA, ST7789_DC_PIN, GPIO_PIN_RESET);  // DC = 0 para comando
    HAL_GPIO_WritePin(GPIOB, ST7789_CS_PIN, GPIO_PIN_RESET);  // Chip select baixo
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);         // Envia comando via SPI
    HAL_GPIO_WritePin(GPIOB, ST7789_CS_PIN, GPIO_PIN_SET);    // Chip select alto
}

// Função auxiliar para enviar dados para o display
void ST7789_WriteData(uint8_t data) {
    HAL_GPIO_WritePin(GPIOA, ST7789_DC_PIN, GPIO_PIN_SET);  // DC = 1 para dados
    HAL_GPIO_WritePin(GPIOB, ST7789_CS_PIN, GPIO_PIN_RESET);  // Chip select baixo
    HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);         // Envia dados via SPI
    HAL_GPIO_WritePin(GPIOB, ST7789_CS_PIN, GPIO_PIN_SET);    // Chip select alto
}

// Função para imprimir uma string no display (simulação)
void Display_Print(const char *str) {
    printf("%s\n", str);  // Simula a impressão no console
}

// Função para mostrar o menu no display (simulação)
void Display_ShowMenu(void) {
    printf("\n=== Menu Principal ===\n");
    printf("1. Servir ração\n");
    printf("2. Configurar horário\n");
    printf("3. Sair\n");
    printf("======================\n");
}

// Função para exibir uma mensagem no display (simulação)
void Display_ShowMessage(const char *msg, uint8_t linha) {
    printf("Mensagem linha %d: %s\n", linha, msg);
}

// Função para exibir uma barra de progresso no display (simulação)
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
    printf("] %ld%%\n", progresso);  // Usando %ld para int32_t
}
