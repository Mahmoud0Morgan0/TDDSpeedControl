/*
 * test_SpeedControl.c
 *
 *  Created on: Mar 1, 2021
 *      Author: IT
 */
#include "../MotorSpy/MotorSpy.h"
#include "../unity/unity.h"
#include "../../ProductionCode/SpeedControl.h"
#include "../FakeSwitch/FakeSwitch.h"
void setUp(void)
{
	SpeedControl_init();
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

void test_PositiveSWDecrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 90 +ve Sw released
			  * @par When  : +ve is prepressed
			  * @par Then  : MotorAngle is 91
		*/
	FakeSw_Positive_setState(SW_PREPRESSED);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(89,MotorSpy_getMotorAngle());
}

void test_NegativeSWIncrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 90 -ve Sw released
			  * @par When  : -ve is prepressed
			  * @par Then  : MotorAngle is 89
		*/
	FakeSw_Negative_setState(SW_PREPRESSED);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(91,MotorSpy_getMotorAngle());
}

void test_pSWD_30_incrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 90 pSw released
			  * @par When  : -p is pressed for 30 seconds
			  * @par Then  : MotorAngle is 89
		*/
	FakeSw_P_setState(SW_PRESSED);
	FakeSw_pSw_setPeriod(30);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(91,MotorSpy_getMotorAngle());
}

void test_pSWD_Less30_doNothing()
{
	/*!
			  * @par Given : Motor angle is 90 pSw released
			  * @par When  : -p is pressed for less than30 seconds
			  * @par Then  : MotorAngle is 90
		*/
	FakeSw_P_setState(SW_PRESSED);
	FakeSw_pSw_setPeriod(25);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(90,MotorSpy_getMotorAngle());
}

void test_pSWD_More30_incrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 90 pSw released
			  * @par When  : -p is pressed for more than30 seconds
			  * @par Then  : MotorAngle is 89
		*/
	FakeSw_P_setState(SW_PRESSED);
	FakeSw_pSw_setPeriod(35);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(91,MotorSpy_getMotorAngle());
}

void test_Map_10_MotorAnglesTo_MaxSpeed()
{
	/*!
			  * @par Given : Motor angle is unknown
			  * @par When  : Motor angles is 10
			  * @par Then  : Speed = MAX
		*/

	MotorSpy_setMotorAngle(10);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(MAXIMUM,SpeedControl_getSpeed());
}

void test_Map_90_MotorAnglesTo_MedSpeed()
{
	/*!
			  * @par Given : Motor angle is unknown
			  * @par When  : Motor angles is 90
			  * @par Then  : Speed = Med
		*/
	SpeedControl_setSpeed(MAXIMUM);
	MotorSpy_setMotorAngle(90);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(MEDIUM,SpeedControl_getSpeed());
}

void test_Map_140_MotorAnglesTo_MinSpeed()
{
	/*!
			  * @par Given : Motor angle is unknown
			  * @par When  : Motor angles is 140
			  * @par Then  : Speed = Min
		*/
	SpeedControl_setSpeed(MAXIMUM);
	MotorSpy_setMotorAngle(140);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(MINIMUM,SpeedControl_getSpeed());
}
void test_MAXSPEED_PositiveSWdoesNotDecrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 10 +ve Sw released
			  * @par When  : +ve is prepressed and Speed is Max
			  * @par Then  : MotorAngle is 10
		*/
	FakeSw_Positive_setState(SW_PREPRESSED);
	MotorSpy_setMotorAngle(10);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(10,MotorSpy_getMotorAngle());
}

void test_MinSPEED_NegativeSWdoesNotIncrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 140 +ve Sw released
			  * @par When  : -ve is prepressed and Speed is Min
			  * @par Then  : MotorAngle is 140
		*/
	FakeSw_Negative_setState(SW_PREPRESSED);
	MotorSpy_setMotorAngle(140);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(140,MotorSpy_getMotorAngle());
}

void test_Priority_pSW_NegativeSw_PositiveSw_PswProcess()
{
	/*!
			  * @par Given : Motor angle is 90
			  * @par When  : pSw is pressed -veSw is prepressed +veSw is prepressed and period of p is less 30
			  * @par Then  : MotorAngle is 90
		*/
	FakeSw_Negative_setState(SW_PREPRESSED);
	FakeSw_Positive_setState(SW_PREPRESSED);
	FakeSw_P_setState(SW_PRESSED);
	FakeSw_pSw_setPeriod(25);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(90,MotorSpy_getMotorAngle());
}

void test_Priority_NegativeSw_PositiveSw_NegativeswProcess()
{
	/*!
			  * @par Given : Motor angle is 90
			  * @par When  : pSw is pressed -veSw is prepressed +veSw is prepressed and period of p is less 30
			  * @par Then  : MotorAngle is 90
		*/
	FakeSw_Negative_setState(SW_PREPRESSED);
	FakeSw_Positive_setState(SW_PREPRESSED);
	SpeedControl_update();
	TEST_ASSERT_EQUAL_INT(91,MotorSpy_getMotorAngle());
}



/*
 * Run the tests
 */
void test_SpeedContorlRunner()
{
	RUN_TEST(test_SpeedIsMediuimAfterInit);
	RUN_TEST(test_MotorAngel90AfterInit);
	RUN_TEST(test_PositiveSWDecrementMotorAngle);
	RUN_TEST(test_NegativeSWIncrementMotorAngle);
	RUN_TEST(test_pSWD_30_incrementMotorAngle);
	RUN_TEST(test_pSWD_Less30_doNothing);
	RUN_TEST(test_pSWD_More30_incrementMotorAngle);
	RUN_TEST(test_Map_10_MotorAnglesTo_MaxSpeed);
	RUN_TEST(test_Map_90_MotorAnglesTo_MedSpeed);
	RUN_TEST(test_Map_140_MotorAnglesTo_MinSpeed);
	RUN_TEST(test_MAXSPEED_PositiveSWdoesNotDecrementMotorAngle);
	RUN_TEST(test_MinSPEED_NegativeSWdoesNotIncrementMotorAngle);
	RUN_TEST(test_Priority_pSW_NegativeSw_PositiveSw_PswProcess);
	RUN_TEST(test_Priority_NegativeSw_PositiveSw_NegativeswProcess);

}

int main(void)
{
	UNITY_BEGIN();
	test_SpeedContorlRunner();
	return UNITY_END();
}
