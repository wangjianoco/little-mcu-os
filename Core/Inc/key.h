/*
 * key.h
 *
 *  Created on: May 7, 2023
 *      Author: wzc
 */

#ifndef INC_KEY_H_
#define INC_KEY_H_

#define RM_NOISE_TIME (10/KHZ)
#define LONG_PRESS_TIME (1000/KHZ)
typedef enum
{
	KEY_UP,
	KEY_LONG_UP,
	KEY_DOWN,
	KEY_RELEASE,
	KEY_HOLD,
	KEY_LONG_HOLD
}KEY_STATE;
extern KEY_STATE KeyState;

void keyTask(void);

#define SCHEDEUL_PERIOD 1
#endif /* INC_KEY_H_ */
