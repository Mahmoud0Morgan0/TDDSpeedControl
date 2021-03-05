/**
 * @file MotorSpy.c
 * @author Mahmoud Morgan
 * @brief motor spy driver the help testing the speed control module
 * @version 0.1
 * @date 2021-03-05
 *
 * @copyright Copyright (c) 2021
 *
 */

/**
 * @brief Defines the Angle of motor
 *
 */
static int motorAngle ;
/**
 * @brief initialize the motor spy driver
 *
 */
void Motor_init(void)
{
	motorAngle=90;
}
/**
 * @brief get the motor angle
 *
 * @return int the motor angle
 */
int MotorSpy_getMotorAngle()
{
	return motorAngle;
}
/**
 * @brief set the motor angle
 *
 * @param angle motor angle to be set
 */
void MotorSpy_setMotorAngle(int angle)
{
	 motorAngle= angle;
}
/**
 * @brief Increment motor angle by 1
 *
 */
void Motor_incAngle()
{
	motorAngle++;
}
/**
 * @brief decrement motor angle by 1
 *
 */
void Motor_decAngle()
{
	motorAngle--;
}

