/*
 * led.h
 *
 *  Created on: May 7, 2023
 *      Author: wzc
 */

#ifndef INC_LED_H_
#define INC_LED_H_
void ledTask(void);
void setLedTime(uint32_t igOnTime, uint32_t igOffTime);
void clearLedSchedualTime(void);

#define LED_STATUS_OK_ON_TIME 500
#define LED_STATUS_OK_OFF_TIME 500

#define LED_STATUS_IDLE_ON_TIME 1000
#define LED_STATUS_IDLE_OFF_TIME 1000

#define LED_STATUS_ERROR_ON_TIME 500
#define LED_STATUS_ERROR_OFF_TIME 1500

#define LED_STATUS_NACK_ON_TIME 1500
#define LED_STATUS_NACK_OFF_TIME 500

#endif /* INC_LED_H_ */
