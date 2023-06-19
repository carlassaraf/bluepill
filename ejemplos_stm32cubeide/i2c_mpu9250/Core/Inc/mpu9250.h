/*
 * mpu9250.h
 *
 *  Created on: Mar 29, 2023
 *      Author: carlassaraf
 */

#ifndef INC_MPU9250_H_
#define INC_MPU9250_H_

#include "stm32f1xx_hal.h"

// By default these devices  are on bus address 0x68
#define MPU9250_ADDR 	(0x68 << 1)

void mpu9250_reset(I2C_HandleTypeDef *hi2c);
void mpu9250_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp);

#endif
