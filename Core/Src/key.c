/*
 * key.c
 *
 *  Created on: May 7, 2023
 *      Author: wzc
 */
#include "main.h"
#include "led.h"
#include "key.h"

KEY_STATE KeyState = KEY_RELEASE;

static uint8_t shouldKeyTaskSchedule(void) {
	static uint32_t count = 0;

	if (count == 0) {
		count = SCHEDEUL_PERIOD;
		count--;
		return !0;
	}
	count--;
	return 0;
}

void keyTask(void) {
	uint8_t keyValue;
	static uint32_t count = 0;
	if (!shouldKeyTaskSchedule())
		return;
	keyValue = (GPIO_PIN_RESET == HAL_GPIO_ReadPin(key_GPIO_Port, key_Pin));
	switch (KeyState) {
	case KEY_RELEASE:
	case KEY_UP:
	case KEY_LONG_UP:
		if (keyValue) {
			if(count++ > RM_NOISE_TIME) {
				count = 0;
				KeyState = KEY_DOWN;
			}
		}
		else {
			count = 0;
			KeyState = KEY_RELEASE;
		}

		break;
	case KEY_DOWN:
		if (keyValue)
			KeyState = KEY_HOLD;
		else
			KeyState = KEY_UP;
		break;
	case KEY_HOLD:
		if (keyValue){
			if(count++ >= LONG_PRESS_TIME) {
				count = 0;
				KeyState = KEY_LONG_HOLD;
			}
		}
		else
			KeyState = KEY_UP;
		break;
	case KEY_LONG_HOLD:
		if (!keyValue)
			KeyState = KEY_LONG_UP;
		break;
	}
}

