#include "hardware.h"
#include "stm32f4xx_hal.h"   // para acesso às funções HAL
#include "stm32f4xx.h"       // para definição de __IO e outros tipos
#include "stm32f4xx_hal_rcc.h"


// Definição dos pinos
#define DISPENSE_PIN GPIO_PIN_0
#define DISPENSE_GPIO_PORT GPIOA

#define ERROR_LED_PIN GPIO_PIN_1
#define ERROR_LED_GPIO_PORT GPIOB

#define SENSOR_PIN GPIO_PIN_2
#define SENSOR_GPIO_PORT GPIOC

#define MOTOR_PIN GPIO_PIN_3
#define MOTOR_GPIO_PORT GPIOD

#define BUZZER_PIN GPIO_PIN_4
#define BUZZER_GPIO_PORT GPIOE

void hardware_init(void)
{
    // Inicializa o HAL e configura os clocks
    HAL_Init();
}

void hardware_update(void)
{
    // Exemplo de lógica para dispensar alimento baseado em uma condição
    static uint32_t last_dispense_time = 0;
    uint32_t current_time = HAL_GetTick();

    // Dispensar alimento a cada 10 segundos (10000 ms)
    if ((current_time - last_dispense_time) >= 10000)
    {
        hardware_dispense_food();
        last_dispense_time = current_time;
    }
}

void hardware_dispense_food(void)
{
    // Verifica se o pino está configurado corretamente
    GPIO_PinState pin_state = HAL_GPIO_ReadPin(DISPENSE_GPIO_PORT, DISPENSE_PIN);
    if (pin_state == GPIO_PIN_RESET)
    {
        // Ativa o pino para dispensar alimento
        HAL_GPIO_WritePin(DISPENSE_GPIO_PORT, DISPENSE_PIN, GPIO_PIN_SET);
        HAL_Delay(500); // tempo para dispensar

        // Desativa o pino após o tempo de dispensação
        HAL_GPIO_WritePin(DISPENSE_GPIO_PORT, DISPENSE_PIN, GPIO_PIN_RESET);
    }
    else
    {
        // Caso o pino já esteja ativo, sinaliza erro
        hardware_signal_error();
    }
}

void hardware_signal_error(void)
{
    // Liga o LED de erro
    HAL_GPIO_WritePin(ERROR_LED_GPIO_PORT, ERROR_LED_PIN, GPIO_PIN_SET);

    // Pisca o LED de erro 3 vezes para indicar falha
    for (int i = 0; i < 3; i++)
    {
        HAL_GPIO_TogglePin(ERROR_LED_GPIO_PORT, ERROR_LED_PIN);
        HAL_Delay(200); // 200 ms de intervalo
        HAL_GPIO_TogglePin(ERROR_LED_GPIO_PORT, ERROR_LED_PIN);
        HAL_Delay(200);
    }

    // Mantém o LED de erro ligado após piscar
    HAL_GPIO_WritePin(ERROR_LED_GPIO_PORT, ERROR_LED_PIN, GPIO_PIN_SET);
}
