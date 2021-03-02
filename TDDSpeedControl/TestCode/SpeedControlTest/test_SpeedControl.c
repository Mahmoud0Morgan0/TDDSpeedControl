/*
 * test_SpeedControl.c
 *
 *  Created on: Mar 1, 2021
 *      Author: IT
 */
#include "../MotorSpy/MotorSpy.h"
#include "../unity/unity.h"
#include "../../ProductionCode/SpeedControl.h"
void setUp(void)
{

}
void tearDown(void)
{

}

void test_SpeedIsMediuimAfterInit()
{
	/*!
			  * @par Given : Speed is unknown
			  * @par When  : SpeedControl init
			  * @par Then  : Speed is in Medium speed
		*/
	SpeedControl_init();
	TEST_ASSERT_EQUAL_INT(MEDIUM,SpeedControl_getSpeed());
}

void test_MotorAngel90AfterInit()
{
	/*!
			  * @par Given : Motor angle is unknown
			  * @par When  : SpeedControl init
			  * @par Then  : MotorAngle is 90
		*/
	SpeedControl_init();
	TEST_ASSERT_EQUAL_INT(90,MotorSpy_getMotorAngle());
}




/*
 * Run the tests
 */
void test_SpeedContorlRunner()
{
	RUN_TEST(test_SpeedIsMediuimAfterInit);
	RUN_TEST(test_MotorAngel90AfterInit);
}

int main(void)
{
	UNITY_BEGIN();
	test_SpeedContorlRunner();
	return UNITY_END();
}
