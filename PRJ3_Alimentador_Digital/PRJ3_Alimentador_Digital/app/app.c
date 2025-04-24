#include "app.h"
#include <stdio.h>

// --- DEFINIÇÕES DE PINOS ---

#define HX711_DATA_Pin         LOAD_DATA_Pin
#define HX711_DATA_GPIO_Port   LOAD_DATA_GPIO_Port
#define HX711_CLK_Pin          LOAD_CLK_Pin
#define HX711_CLK_GPIO_Port    LOAD_CLK_GPIO_Port

#define MOTOR_Pin              DC1_IN2_Pin
#define MOTOR_GPIO_Port        DC1_IN2_GPIO_Port

// --- FUNÇÕES AUXILIARES ---

static void HX711_Init(void) {
    // GPIOs já configurados no CubeMX (MX_GPIO_Init já inicializa a célula de carga)
}

static int32_t HX711_ReadRaw(void) {
    int32_t data = 0;

    while (HAL_GPIO_ReadPin(HX711_DATA_GPIO_Port, HX711_DATA_Pin)); // Aguarda sinal LOW

    for (int i = 0; i < 24; i++) {
        HAL_GPIO_WritePin(HX711_CLK_GPIO_Port, HX711_CLK_Pin, GPIO_PIN_SET);
        data = (data << 1) | HAL_GPIO_ReadPin(HX711_DATA_GPIO_Port, HX711_DATA_Pin);
        HAL_GPIO_WritePin(HX711_CLK_GPIO_Port, HX711_CLK_Pin, GPIO_PIN_RESET);
    }

    // Ganho 128
    HAL_GPIO_WritePin(HX711_CLK_GPIO_Port, HX711_CLK_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(HX711_CLK_GPIO_Port, HX711_CLK_Pin, GPIO_PIN_RESET);

    if (data & 0x800000) data |= 0xFF000000;

    return data;
}

static void Motor_Init(void) {
    HAL_GPIO_WritePin(MOTOR_GPIO_Port, MOTOR_Pin, GPIO_PIN_RESET);
}

void Motor_Dispense
(void)
{
    // Ativa o motor para abrir a tampa
    HAL_GPIO_WritePin(DC1_IN1_GPIO_Port, DC1_IN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DC1_IN2_GPIO_Port, DC1_IN2_Pin, GPIO_PIN_RESET);

    HAL_Delay(500); // tempo para abrir a tampa (ajuste conforme necessário)

    // Para o motor para impedir movimento adicional
    HAL_GPIO_WritePin(DC1_IN1_GPIO_Port, DC1_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DC1_IN2_GPIO_Port, DC1_IN2_Pin, GPIO_PIN_RESET);

    // Aguarda um tempo para liberar a ração
    HAL_Delay(1000); // tempo para ração ser liberada (ajuste conforme necessário)

    // Ativa o motor para fechar a tampa
    HAL_GPIO_WritePin(DC1_IN1_GPIO_Port, DC1_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DC1_IN2_GPIO_Port, DC1_IN2_Pin, GPIO_PIN_SET);

    HAL_Delay(200); // tempo para fechar a tampa (ajuste conforme necessário)

    // Para o motor
    HAL_GPIO_WritePin(DC1_IN1_GPIO_Port, DC1_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DC1_IN2_GPIO_Port, DC1_IN2_Pin, GPIO_PIN_RESET);
}


static void Motor_Dispense_Disable(void) {
    HAL_GPIO_WritePin(DC1_IN1_GPIO_Port, DC1_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DC1_IN2_GPIO_Port, DC1_IN2_Pin, GPIO_PIN_RESET);
}

static void Display_Init(void) {
    HAL_Delay(100); // Simula inicialização
}

static void Display_Print(const char *str) {
    // Apenas simula o uso do display
    (void)str;
}

// --- FUNÇÕES PRINCIPAIS ---

void App_Init(void) {
    Display_Init();
    HX711_Init();
    Motor_Init();
    Display_Print("Iniciando...");
}

void App_Run(void) {
    const int32_t pesoCorte = 50; // Valor fictício de corte em gramas
    int32_t peso = HX711_ReadRaw();

    while (peso < pesoCorte) {
        Motor_Dispense();  
        HAL_Delay(500); // Aguarda um tempo para estabilizar a leitura
        peso = HX711_ReadRaw();
    }
    Motor_Dispense_Disable();
   
}
