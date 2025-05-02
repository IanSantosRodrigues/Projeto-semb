#include "app.h"


#define HX711_DATA_Pin         LOAD_DATA_Pin
#define HX711_DATA_GPIO_Port   LOAD_DATA_GPIO_Port
#define HX711_CLK_Pin          LOAD_CLK_Pin
#define HX711_CLK_GPIO_Port    LOAD_CLK_GPIO_Port

#define PESO_CORTE 50
#define TEMPO_AJUSTE 500


static int32_t HX711_ReadRaw(void) {
    int32_t data = 0;

    while (HAL_GPIO_ReadPin(HX711_DATA_GPIO_Port, HX711_DATA_Pin));

    for (int i = 0; i < 24; i++) {
        HAL_GPIO_WritePin(HX711_CLK_GPIO_Port, HX711_CLK_Pin, GPIO_PIN_SET);
        data = (data << 1) | HAL_GPIO_ReadPin(HX711_DATA_GPIO_Port, HX711_DATA_Pin);
        HAL_GPIO_WritePin(HX711_CLK_GPIO_Port, HX711_CLK_Pin, GPIO_PIN_RESET);
    }

    HAL_GPIO_WritePin(HX711_CLK_GPIO_Port, HX711_CLK_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(HX711_CLK_GPIO_Port, HX711_CLK_Pin, GPIO_PIN_RESET);

    if (data & 0x800000) data |= 0xFF000000;

    return data;
}

static void DispensarRacaoAtePeso(int32_t pesoAlvo) {
    int32_t peso = HX711_ReadRaw();
    int32_t pesoAnterior = peso;
    uint32_t tempoInicio = HAL_GetTick();

    Display_ShowMessage("Abrindo tampa...", 0);
    Motor_OpenLid();

    while (peso < pesoAlvo) {
        HAL_Delay(TEMPO_AJUSTE);
        peso = HX711_ReadRaw();
        int32_t delta = peso - pesoAnterior;

        Display_ShowProgressBar(peso, pesoAlvo);

        if (delta < 1) {
            Display_ShowMessage("Peso está estável", 1);
        }

        if ((HAL_GetTick() - tempoInicio) > 30000) {
            Display_ShowMessage("Tempo excedido!", 1);
            return;
        }

        pesoAnterior = peso;
    }

    Display_ShowMessage("Fechando tampa...", 0);
    Motor_CloseLid();

    Display_ShowMessage("Peso alcançado!", 0);
    HAL_Delay(1000);
}

void App_Init(void) {
    ST7789_Init();
    Display_ShowMenu();
    Motor_Init();
}

void App_Run(void) {
    DispensarRacaoAtePeso(PESO_CORTE);
}
