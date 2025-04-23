/*
 * app.c
 *
 *  Criado em: 23 de abril de 2025
 *      Autor: iansa
 */

#include "app.h"           // Cabeçalho principal do módulo de aplicação
#include "hardware.h"      // Módulo para controle do hardware
#include "sensors.h"       // Módulo para gerenciamento de sensores
#include "logger.h"        // Módulo para registro de eventos
#include "error_handler.h" // Módulo para tratamento de erros

// Funções estáticas para modularizar o código
static void handle_food_request(void); // Lida com pedidos de comida
static void handle_error(void);        // Lida com erros detectados

/**
 * @brief Configuração inicial do sistema.
 * 
 * Inicializa os módulos de hardware, sensores e logger.
 * Registra um evento indicando que o sistema foi inicializado.
 */
void app_setup(void)
{
    hardware_init(); // Inicializa o hardware do alimentador
    sensors_init();  // Configura os sensores
    logger_init();   // Inicializa o sistema de registro de eventos
    logger_log_event("System initialized"); // Registra a inicialização do sistema
}

/**
 * @brief Loop principal da aplicação.
 * 
 * Executa continuamente verificações de pedidos de comida e erros,
 * além de atualizar o estado do hardware e dos sensores.
 */
void app_loop(void)
{
    if (sensors_detect_food_request()) {
        handle_food_request(); // Lida com pedidos de comida
    }

    if (sensors_detect_error()) {
        handle_error(); // Lida com erros detectados
    }

    hardware_update(); // Atualiza o estado do hardware
    sensors_update();  // Atualiza o estado dos sensores
}

/**
 * @brief Lida com pedidos de comida.
 * 
 * Dispensa comida e registra o evento no sistema de logs.
 */
static void handle_food_request(void)
{
    hardware_dispense_food(); // Dispensa comida
    logger_log_event("Food dispensed"); // Registra o evento de comida dispensada
}

/**
 * @brief Lida com erros detectados.
 * 
 * Registra o erro no sistema de logs, sinaliza o erro no hardware
 * e processa o erro utilizando o módulo de tratamento de erros.
 */
static void handle_error(void)
{
    logger_log_event("Error detected"); // Registra o erro
    hardware_signal_error(); // Sinaliza o erro no hardware
    error_handler_process(); // Processa o erro usando o módulo de tratamento de erros
}

// TODO:
// 1. Implementar funções no módulo `hardware` para controle mais detalhado do hardware.
// 2. Adicionar mais tipos de sensores no módulo `sensors` e suas respectivas verificações.
// 3. Expandir o módulo `logger` para suportar diferentes níveis de log (info, warning, error).
// 4. Melhorar o módulo `error_handler` para incluir estratégias de recuperação de erros.
// 5. Adicionar testes unitários para validar o comportamento de cada módulo.
