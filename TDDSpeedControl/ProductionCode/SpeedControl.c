
/**
 * @file test_SpeedControl.c
 * @author Mahmoud Morgan
 * @brief The implementation for SpeedControl Model which takes switches state to control Motor angles.
 * @version 0.1
 * @date 2021-03-05
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @file dio.c
* @brief The implementation for SpeedControl Model which takes switches state to control Motor angles.
*/
/**********************************************************************
* Includes
**********************************************************************/

#include"SpeedControl.h"
#include"../TestCode/MotorSpy/MotorSpy.h"
#include"../TestCode/FakeSwitch/FakeSwitch.h"

/**********************************************************************
* Module Preprocessor Constants
**********************************************************************/
/*********************************************************************
* Module Preprocessor Macros
**********************************************************************/
/**********************************************************************
* Module Typedefs
**********************************************************************/
/**********************************************************************
* Module Variable Definitions
**********************************************************************/
/**
* @brief Defines the speed of Motor and it has 3 possible values Min,Med and Max
*/
static Speed_t speed ;

/**********************************************************************
* Function Prototypes
**********************************************************************/
/**********************************************************************
* Function Definitions
**********************************************************************/
/*********************************************************************
* Function : SpeedControl_getSpeed()
*//**
* \b Description:
*
* This function is used to return speed of motor
*
* PRE-CONDITION: the speed control module is initialized <br>
*
*
* POST-CONDITION: caller gets the speed of motor.
*
*
* @return the Speed_t speed of motor
*
* \b Example:
* @code
* Speed_t s = SpeedControl_getSpeed();
* @endcode
*
* @see SpeedControl_setSpeed
* @see SpeedControl_init
* @see SpeedControl_update
*
**********************************************************************/
Speed_t SpeedControl_getSpeed()
{
	return speed;
}
/*********************************************************************
* Function : SpeedControl_setSpeed()
*//**
* \b Description:
*
* This function is used set the speed of motor
*
* PRE-CONDITION: the speed control module is initialized <br>
*
*
* POST-CONDITION: the speed of motor is set to specific value.
*
*
* @param the specific value of speed to be set
*
* \b Example:
* @code
* SpeedControl_setSpeed(MAXIMUM);
* @endcode
*
* @see SpeedControl_getSpeed
* @see SpeedControl_init
* @see SpeedControl_update
*
**********************************************************************/
void SpeedControl_setSpeed(Speed_t sp)
{
	speed=sp;
}


static void mapAnglesToSpeed(void)
{
	if(MotorSpy_getMotorAngle()==10)
		speed=MAXIMUM;
	else if (MotorSpy_getMotorAngle()==90)
		speed=MEDIUM;
	else if (MotorSpy_getMotorAngle()==140)
		speed=MINIMUM;
}

/*********************************************************************
* Function : SpeedControl_init()
*//**
* \b Description:
*
* This function is used to initialize speed control module
*
* PRE-CONDITION: the speed control module is not initialized <br>
*
*
* POST-CONDITION: the speed control module is initialized.
*
*
*
*
* \b Example:
* @code
* SpeedControl_init();
* @endcode
*
* @see SpeedControl_setSpeed
* @see SpeedControl_getSpeed
* @see SpeedControl_update
*
**********************************************************************/

void SpeedControl_init()
{
	Motor_init();
	speed= MEDIUM;
	FakeSw_init();
}
/*********************************************************************
* Function : SpeedControl_update()
*//**
* \b Description:
*
* This function is used to control the speed
*
* PRE-CONDITION: the speed control module is initialized <br>
*
*
* POST-CONDITION: switches are checked and speed is changed according to them.
*
*
*
*
* \b Example:
* @code
* SpeedControl_update();
* @endcode
*
* @see SpeedControl_setSpeed
* @see SpeedControl_getSpeed
* @see SpeedControl_init
*
**********************************************************************/
void SpeedControl_update()
{
	mapAnglesToSpeed();
	if(FakeSw_Positive_getState()==SW_PREPRESSED && speed!=MAXIMUM && FakeSw_P_getState() != SW_PRESSED && FakeSw_Negative_getState()!=SW_PREPRESSED)
	{

		/*if(speed!=MAXIMUM)
		{
			Motor_decAngle();
		}*/
		Motor_decAngle();
	}
	else if(FakeSw_Negative_getState()==SW_PREPRESSED && speed!=MINIMUM && FakeSw_P_getState() != SW_PRESSED)
	{
		/*if(speed!=MAXIMUM)
		  {
			  Motor_decAngle();
		  }*/
		Motor_incAngle();
	}
	else if(FakeSw_P_getState()==SW_PRESSED && FakeSw_pSw_getPeriod()>=30)
	{
		Motor_incAngle();
	}
}


