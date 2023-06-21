/*
 * eeprom.c
 *
 *  Created on: May 7, 2023
 *      Author: wzc
 */

#include "main.h"
#include "led.h"
#include "key.h"
#include "eeprom.h"

extern I2C_HandleTypeDef hi2c1;

const uint8_t BOOT_FROM_FLASH[4] = { 0x0c, 0x01, 0x00, 0x20 };
const uint8_t BOOT_FROM_EMMC[4] = { 0x60, 0x00, 0x00, 0x00 };

#define I2C_TIMEOUT 50

static uint8_t shouldEepromTaskSchedule(void) {
	if (KeyState == KEY_UP || KeyState == KEY_LONG_UP) {
		return !0;
	}
	return 0;
}
static void writeBootWord(uint8_t *bootWord, uint8_t bootWordSize) {
	HAL_StatusTypeDef status;
	uint8_t data[4];
	status = HAL_I2C_Mem_Write(&hi2c1, EEPROM_ADDR, 0x00, I2C_MEMADD_SIZE_8BIT,
			bootWord, bootWordSize, I2C_TIMEOUT);
	if (status != HAL_OK) {
		if (hi2c1.ErrorCode == HAL_I2C_ERROR_AF) {
			setLedTime(LED_STATUS_NACK_ON_TIME, LED_STATUS_NACK_OFF_TIME);
		} else {
			setLedTime(LED_STATUS_ERROR_ON_TIME, LED_STATUS_ERROR_OFF_TIME);
		}
		return;
	} else {
		HAL_Delay(20);
		status = HAL_I2C_Mem_Read(&hi2c1, EEPROM_ADDR, 0x00,
				I2C_MEMADD_SIZE_8BIT, data, sizeof(data), I2C_TIMEOUT);
		if (status != HAL_OK) {
			if (hi2c1.ErrorCode == HAL_I2C_ERROR_AF) {
				setLedTime(LED_STATUS_NACK_ON_TIME, LED_STATUS_NACK_OFF_TIME);
			} else {
				setLedTime(LED_STATUS_ERROR_ON_TIME, LED_STATUS_ERROR_OFF_TIME);
			}
			return;
		}
		if (data[0] == bootWord[0] && data[1] == bootWord[1]
				&& data[2] == bootWord[2]) {
			setLedTime(LED_STATUS_OK_ON_TIME, LED_STATUS_OK_OFF_TIME);
		} else {
			setLedTime(LED_STATUS_ERROR_ON_TIME, LED_STATUS_ERROR_OFF_TIME);
		}
	}
}
void eepromTask(void) {
	//static uint32_t count = 0;

	//writeBootWord((uint8_t*)BOOT_FROM_FLASH, sizeof(BOOT_FROM_FLASH));
	if (!shouldEepromTaskSchedule())
		return;
	if (KeyState == KEY_UP) {
		writeBootWord((uint8_t*) BOOT_FROM_FLASH, sizeof(BOOT_FROM_FLASH));
	} else if (KeyState == KEY_LONG_UP) {
		writeBootWord((uint8_t*) BOOT_FROM_EMMC, sizeof(BOOT_FROM_EMMC));
	}
}
