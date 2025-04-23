/*
 * app.c
 *
 *  Created on: Apr 23, 2025
 *      Author: iansa
 */

#include "app.h"
#include "hardware.h"
#include "sensors.h"
#include "logger.h"
#include "error_handler.h" // Include error handling module

static void handle_food_request(void);
static void handle_error(void);

void app_setup(void)
{
    hardware_init(); // Inicializa o hardware do alimentador
    sensors_init();  // Configura os sensores
    logger_init();   // Inicializa o sistema de registro de eventos
    logger_log_event("System initialized"); // Log system initialization
}

void app_loop(void)
{
    if (sensors_detect_food_request()) {
        handle_food_request(); // Modularized food request handling
    }

    if (sensors_detect_error()) {
        handle_error(); // Modularized error handling
    }

    hardware_update(); // Atualiza o estado do hardware
    sensors_update();  // Atualiza o estado dos sensores
}

static void handle_food_request(void)
{
    hardware_dispense_food(); // Dispensa comida
    logger_log_event("Food dispensed"); // Registra o evento
}

static void handle_error(void)
{
    logger_log_event("Error detected"); // Registra erro
    hardware_signal_error(); // Sinaliza erro no hardware
    error_handler_process(); // Processa o erro usando módulo de tratamento de erros
}
