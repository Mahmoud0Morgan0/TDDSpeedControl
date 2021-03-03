/*
 * SpeedControl.h
 *
 *  Created on: Mar 1, 2021
 *      Author: IT
 */

#ifndef PRODUCTIONCODE_SPEEDCONTROL_H_
#define PRODUCTIONCODE_SPEEDCONTROL_H_

typedef enum
{
	MINIMUM,MEDIUM,MAXIMUM
}Speed_t;

void SpeedControl_init(void);
void SpeedControl_update(void);
Speed_t SpeedControl_getSpeed();
void SpeedControl_setSpeed(Speed_t sp);
#endif /* PRODUCTIONCODE_SPEEDCONTROL_H_ */
