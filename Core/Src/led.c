#include "main.h"
#include "led.h"
uint32_t mIgOnTime = LED_STATUS_IDLE_ON_TIME;
uint32_t mIgOffTime = LED_STATUS_IDLE_OFF_TIME;
uint32_t mCounter = 0;
uint8_t isON = 0;
void setLedTime(uint32_t igOnTime, uint32_t igOffTime) {
	mIgOnTime = igOnTime / KHZ;
	mIgOffTime = igOffTime / KHZ;
	clearLedSchedualTime();
}
void clearLedSchedualTime(void) {
	mCounter = 0;
}
static uint8_t shouldLedTaskSchedule(void) {
	static uint32_t count = 0;
	if (isON != 0) {
		if (count == 0) {
			count = mIgOffTime;
			isON = 0;
			return !0;
		}
	} else {
		if (count == 0) {
			count = mIgOnTime;
			isON = !0;
			return !0;
		}
	}
	count--;
	return 0;
}
void ledTask(void) {
	if (!shouldLedTaskSchedule())
		return;
	if (isON)
		HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_RESET);
}
