#include "Display.h"
#include <stdio.h>  // Para simulação no console
#include "stm32f4xx.h"

// Definindo o número de opções do menu
typedef enum {
    MENU_OPCAO_SERVIR = 0,
    MENU_OPCAO_CONFIGURAR,
    MENU_OPCAO_SAIR,
    MENU_TOTAL_OPCOES
} MenuOpcao;

// As opções que o menu vai exibir
static const char *menu_opcoes[MENU_TOTAL_OPCOES] = {
    "1. Servir ração",
    "2. Configurar horario",
    "3. Sair"
};

// Função de inicialização do display
void Display_Init(void) {
    HAL_Delay(100);  // Simula o tempo de inicialização do display
    // Aqui você pode adicionar mais código para configurar o display.
}

// Função para imprimir uma string no display
void Display_Print(const char *str) {
    // Como o display real ainda não está configurado, vamos simular a impressão
    printf("%s\n", str);  // Simula a impressão no console
}

// Função para mostrar o menu no display
void Display_ShowMenu(void) {
    printf("\n=== Menu Principal ===\n");

    for (int i = 0; i < MENU_TOTAL_OPCOES; ++i) {
        Display_Print(menu_opcoes[i]);
    }

    printf("======================\n");
}

// Função para exibir uma mensagem no display
void Display_ShowMessage(const char *msg, uint8_t linha) {
    // Para simular, apenas imprime a mensagem no console
    printf("Mensagem linha %d: %s\n", linha, msg);
}

// Função para exibir uma barra de progresso no display
void Display_ShowProgressBar(int32_t valorAtual, int32_t valorMaximo) {
    // Calculando a porcentagem de progresso
    int32_t progresso = (valorAtual * 100) / valorMaximo;

    // Limitando a barra a 100%
    if (progresso > 100) {
        progresso = 100;
    }

    // Exibindo a barra de progresso no console
    printf("Progresso: [");
    for (int i = 0; i < 50; i++) {
        if (i < progresso / 2) {  // Cada ">" representa 2% de progresso
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %ld%%\n", progresso);  // Usando %ld para int32_t

}
