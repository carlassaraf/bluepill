/*
 * mpu9250.c
 *
 *  Created on: Mar 29, 2023
 *      Author: carlassaraf
 */

#include "mpu9250.h"

// I2C usado
I2C_HandleTypeDef *i2c;

void mpu9250_reset(I2C_HandleTypeDef *hi2c) {
	// Guardo el I2C usado
	i2c = hi2c;
    // Two byte reset. First byte register, second byte data
    // There are a load more options to set up the device in different ways that could be added here
    uint8_t buf[] = {0x6B, 0x00};
    HAL_I2C_Master_Transmit(i2c, MPU9250_ADDR, buf, 2, 100);
}

void mpu9250_read_raw(int16_t accel[3], int16_t gyro[3], int16_t *temp) {
    // For this particular device, we send the device the register we want to read
    // first, then subsequently read from the device. The register is auto incrementing
    // so we don't need to keep sending the register we want, just the first.

    uint8_t buffer[6];

    // Start reading acceleration registers from register 0x3B for 6 bytes
    uint8_t val = 0x3B;
    HAL_I2C_Master_Transmit(i2c, MPU9250_ADDR, &val, 1, 100);
    HAL_I2C_Master_Receive(i2c, MPU9250_ADDR, buffer, 6, 100);

    for (int i = 0; i < 3; i++) {
        accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

    // Now gyro data from reg 0x43 for 6 bytes
    // The register is auto incrementing on each read
    val = 0x43;
    HAL_I2C_Master_Transmit(i2c, MPU9250_ADDR, &val, 1, 100);
    HAL_I2C_Master_Receive(i2c, MPU9250_ADDR, buffer, 6, 100);

    for (int i = 0; i < 3; i++) {
        gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);;
    }

    // Now temperature from reg 0x41 for 2 bytes
    // The register is auto incrementing on each read
    val = 0x41;
    HAL_I2C_Master_Transmit(i2c, MPU9250_ADDR, &val, 1, 100);
    HAL_I2C_Master_Receive(i2c, MPU9250_ADDR, buffer, 2, 100);

    *temp = buffer[0] << 8 | buffer[1];
}
