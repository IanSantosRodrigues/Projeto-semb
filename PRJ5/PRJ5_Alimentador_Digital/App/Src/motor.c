#include "motor.h"

void Motor_Init(void) {
    HAL_GPIO_WritePin(DC1_IN1_GPIO_Port, DC1_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DC1_IN2_GPIO_Port, DC1_IN2_Pin, GPIO_PIN_RESET);
}

void Motor_OpenLid(void) {
    HAL_GPIO_WritePin(DC1_IN1_GPIO_Port, DC1_IN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DC1_IN2_GPIO_Port, DC1_IN2_Pin, GPIO_PIN_RESET);
    HAL_Delay(300);
    Motor_Stop();
}

void Motor_CloseLid(void) {
    HAL_GPIO_WritePin(DC1_IN1_GPIO_Port, DC1_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DC1_IN2_GPIO_Port, DC1_IN2_Pin, GPIO_PIN_SET);
    HAL_Delay(300);
    Motor_Stop();
}

void Motor_Stop(void) {
    HAL_GPIO_WritePin(DC1_IN1_GPIO_Port, DC1_IN1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DC1_IN2_GPIO_Port, DC1_IN2_Pin, GPIO_PIN_RESET);
}
