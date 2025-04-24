#include "app.h"
#include "main.h" // Para HAL, GPIO, etc

// Simulação: LED indica alimentação
#define FEED_LED_PIN     GPIO_PIN_5
#define FEED_LED_PORT    GPIOA

// Variáveis de estado (você pode criar uma FSM mais elaborada depois)
static uint8_t petFed = 0;

void App_Init(void)
{
    // Aqui você inicializa o que for necessário
    // Ex: configurações de periféricos feitas no MX_GPIO_Init(), MX_TIMx_Init(), etc.
    petFed = 0;

    // Se quiser começar com LED desligado
    HAL_GPIO_WritePin(FEED_LED_PORT, FEED_LED_PIN, GPIO_PIN_RESET);
}

void App_Run(void) {
    static uint32_t lastTick = 0;
    if (HAL_GetTick() - lastTick > 1000) {
        HAL_GPIO_TogglePin(DC1_IN2_GPIO_Port, DC1_IN2_Pin);
        lastTick = HAL_GetTick();
    }
}
