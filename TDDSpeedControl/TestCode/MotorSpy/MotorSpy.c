/*
 * MotorSpy.c
 *
 *  Created on: Mar 1, 2021
 *      Author: IT
 */
static int motorAngle ;

void Motor_init(void)
{
	motorAngle=90;
}

int MotorSpy_getMotorAngle()
{
	return motorAngle;
}
void MotorSpy_setMotorAngle(int angle)
{
	 motorAngle= angle;
}
void Motor_incAngle()
{
	motorAngle++;
}

void Motor_decAngle()
{
	motorAngle--;
}

