#include "app.h"
#include "Display.h"
#include "main.h"
#include <stdio.h>
#include "stm32f4xx.h"

// --- DEFINIÇÕES DE PINOS ---

#define HX711_DATA_Pin         LOAD_DATA_Pin
#define HX711_DATA_GPIO_Port   LOAD_DATA_GPIO_Port
#define HX711_CLK_Pin          LOAD_CLK_Pin
#define HX711_CLK_GPIO_Port    LOAD_CLK_GPIO_Port

#define MOTOR_Pin              DC1_IN2_Pin
#define MOTOR_GPIO_Port        DC1_IN2_GPIO_Port

#define PESO_CORTE 50  // Valor fictício de corte em gramas
#define TEMPO_AJUSTE 500  // Tempo de ajuste entre as leituras

// --- FUNÇÕES AUXILIARES ---
    // GPIOs já configurados no CubeMX (MX_GPIO_Init já inicializa a célula de carga)

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


// --- FUNÇÕES PRINCIPAIS ---

void App_Init(void) {
    Display_Init();
    Display_ShowMenu();
    Motor_Init();
}

void App_Run(void) {
    int32_t peso = HX711_ReadRaw();  // Leitura inicial do peso
    int32_t pesoAnterior = peso;     // Para verificar variações no peso
    int32_t pesoDiferenca = 0;
    uint32_t tempoInicio = HAL_GetTick();  // Marca o tempo de início da operação

    Display_ShowMessage("Iniciando...", 0);  // Exibe mensagem inicial no display

    // Loop de dispense até atingir o peso de corte
    while (peso < PESO_CORTE) {
        Motor_Dispense();  // Ativa o motor para dispensar ração
        HAL_Delay(TEMPO_AJUSTE);  // Aguarda um tempo para estabilizar a leitura

        peso = HX711_ReadRaw();  // Lê o peso após o dispense

        // Calcula a diferença de peso
        pesoDiferenca = peso - pesoAnterior;

        // Exibe o peso e o progresso no display
        Display_ShowMessage("Pesando...", 0);
        Display_ShowProgressBar(peso, PESO_CORTE);

        // Verifica se a diferença de peso é muito pequena
        if (pesoDiferenca < 1) {
            Display_ShowMessage("Peso está estável", 1);  // Feedback se o peso não mudar
        }

        // Verifica o tempo máximo de dispense, caso queira evitar loops infinitos
        if (HAL_GetTick() - tempoInicio > 30000) {  // Exemplo de timeout de 30 segundos
            Display_ShowMessage("Tempo excedido!", 1);  // Exibe erro se o tempo foi excedido
            Motor_Dispense_Disable();  // Desliga o motor em caso de erro
            return;  // Sai da função
        }

        // Atualiza a variável pesoAnterior para a próxima comparação
        pesoAnterior = peso;
    }

    // Quando atingir o peso de corte, desliga o motor
    Motor_Dispense_Disable();

    // Feedback visual de sucesso
    Display_ShowMessage("Peso alcançado!", 0);

    // Pode adicionar uma pausa antes de finalizar ou reiniciar
    HAL_Delay(1000);
}