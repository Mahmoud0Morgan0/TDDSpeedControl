/**
 * @file test_SpeedControl.c
 * @author Mahmoud Morgan
 * @brief tests for speed control module
 * @version 0.1
 * @date 2021-03-05
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "../MotorSpy/MotorSpy.h"
#include "../unity/unity.h"
#include "../../ProductionCode/SpeedControl.h"
#include "../FakeSwitch/FakeSwitch.h"
#include "stdio.h"
#include "stdlib.h"

/**
 * @brief  Defines the State for +ve switch
 *
 */
SW_State_t posistiveSw;
/**
 * @brief Defines the State for -ve switch
 *
 */
SW_State_t negativeSw;
/**
 * @brief Defines the State for p switch
 *
 */
SW_State_t pSW;
/**
 * @brief Defines the period for p switch
 *
 */
int pSWperiod;
/**
 * @brief Defines the File where motor angles will be written
 *
 */
FILE *motor;
void setUp(void)
{
	SpeedControl_init();
	posistiveSw = SW_RELEASED;
	negativeSw = SW_RELEASED;
	pSW = SW_RELEASED;
	pSWperiod = 0;
}
void tearDown(void)
{

}
/**
 * @brief write motor angle to motor.txt file
 *
 * @param expected the expected result for test case
 * @param result the actual value of motor angle
 */
void writeAngleToFile(int result)
{

	if (motor == NULL) {
		printf("Error! opening file");
		// Program exits if file pointer returns NULL.
		exit(1);
	}
	fprintf(motor, "%d\n",result);

}
/**
 * @brief collect test data from switches.txt file
 *
 * @param posistiveSw state of +ve switch
 * @param negativeSw state of -ve switch
 * @param pSW state of p switch
 * @param pSWperiod period of p switch
 * @param testNum number of test case
 */
void fetchData(SW_State_t *posistiveSw,SW_State_t *negativeSw,SW_State_t *pSW,int *pSWperiod,int testNum)
{
	int i = 0;

	FILE *fptr;
	if ((fptr = fopen("switch.txt", "r")) == NULL) {
		printf("Error! opening file");
		// Program exits if file pointer returns NULL.
		exit(1);
	}
	char pos_SW[20];
	char neg_SW[20];
	char p_SW[20];
	int period = 0;
	for (i = 0; i < testNum; i++) {
		memset(pos_SW, 0, 20);
		memset(neg_SW, 0, 20);
		memset(p_SW, 0, 20);
		fscanf(fptr, "%s\t%s\t%s\t%d\n", pos_SW, neg_SW, p_SW, &period);

	}
	printf("Data from the file:\n%s\n", pos_SW);
	printf("Data from the file:\n%s\n", neg_SW);
	printf("Data from the file:\n%s\n", p_SW);
	printf("Data from the file:\n%d\n", period);
	if (strcmp(pos_SW, "pre_pressed")) {
		*posistiveSw = SW_PREPRESSED;
	} else if (strcmp(pos_SW, "pressed")) {
		*posistiveSw = SW_PRESSED;
	} else if (strcmp(pos_SW, "released")) {
		*posistiveSw = SW_RELEASED;
	} else if (strcmp(pos_SW, "pre_released")) {
		*posistiveSw = SW_PRERELEASED;
	} else
		printf("Wrong data for positive switch\n");


	if (strcmp(neg_SW, "pre_pressed")) {
		*negativeSw = SW_PREPRESSED;
	} else if (strcmp(neg_SW, "pressed")) {
		*negativeSw = SW_PRESSED;
	} else if (strcmp(neg_SW, "released")) {
		*negativeSw = SW_RELEASED;
	} else if (strcmp(neg_SW, "pre_released")) {
		*negativeSw = SW_PRERELEASED;
	} else
		printf("Wrong data for negative switch\n");

	if (strcmp(p_SW, "pre_pressed")) {
		*pSW = SW_PREPRESSED;
	} else if (strcmp(p_SW, "pressed")) {
		*pSW = SW_PRESSED;
	} else if (strcmp(p_SW, "released")) {
		*pSW = SW_RELEASED;
	} else if (strcmp(p_SW, "pre_released")) {
		*pSW = SW_PRERELEASED;
	} else
		printf("Wrong data for P switch\n");

	*pSWperiod=period;

}
/**
 * @brief test that the speed is medium after init
 *
 */
void test_SpeedIsMediuimAfterInit()
{
	/*!
			  * @par Given : Speed is unknown
			  * @par When  : SpeedControl init
			  * @par Then  : Speed is in Medium speed
		*/
	SpeedControl_init();
	TEST_ASSERT_EQUAL_INT(MEDIUM,SpeedControl_getSpeed());
	writeAngleToFile(MotorSpy_getMotorAngle());
}
/**
 * @brief test that the motor angle is 90 after init
 *
 */
void test_MotorAngel90AfterInit()
{
	/*!
			  * @par Given : Motor angle is unknown
			  * @par When  : SpeedControl init
			  * @par Then  : MotorAngle is 90
		*/
	SpeedControl_init();
	TEST_ASSERT_EQUAL_INT(90,MotorSpy_getMotorAngle());
	writeAngleToFile(MotorSpy_getMotorAngle());
}
/**
 * @brief test that if positive sw is prepressed motor angle is decremented
 *
 */
void test_PositiveSWDecrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 90 +ve Sw released
			  * @par When  : +ve is prepressed
			  * @par Then  : MotorAngle is 91
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 2);
	FakeSw_Positive_setState(posistiveSw);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(89,MotorSpy_getMotorAngle());

}
/**
 * @brief tests that if negative switch is prepressed motor angle is incremented
 *
 */
void test_NegativeSWIncrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 90 -ve Sw released
			  * @par When  : -ve is prepressed
			  * @par Then  : MotorAngle is 89
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 3);
	FakeSw_Negative_setState(negativeSw);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(91,MotorSpy_getMotorAngle());

}
/**
 * @brief test that if p switch is pressed for 30 seconds , motor angle is incremented
 *
 */
void test_pSWD_30_incrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 90 pSw released
			  * @par When  : -p is pressed for 30 seconds
			  * @par Then  : MotorAngle is 89
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 4);
	FakeSw_P_setState(pSW);
	FakeSw_pSw_setPeriod(pSWperiod);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(91,MotorSpy_getMotorAngle());
}
/**
 * @brief tests that if the p switch is pressed for less than 30 seconds , motor angles are not changed
 *
 */
void test_pSWD_Less30_doNothing()
{
	/*!
			  * @par Given : Motor angle is 90 pSw released
			  * @par When  : -p is pressed for less than30 seconds
			  * @par Then  : MotorAngle is 90
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 5);
	FakeSw_P_setState(pSW);
	FakeSw_pSw_setPeriod(pSWperiod);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(90,MotorSpy_getMotorAngle());

}
/**
 * @brief test that if p pressed for more than 30 second , motor angles is incremented
 *
 */
void test_pSWD_More30_incrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 90 pSw released
			  * @par When  : -p is pressed for more than30 seconds
			  * @par Then  : MotorAngle is 89
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 6);
	FakeSw_P_setState(pSW);
	FakeSw_pSw_setPeriod(pSWperiod);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(91,MotorSpy_getMotorAngle());
}
/**
 * @brief test that if motor angle is 10 then it's max speed
 *
 */
void test_Map_10_MotorAnglesTo_MaxSpeed()
{
	/*!
			  * @par Given : Motor angle is unknown
			  * @par When  : Motor angles is 10
			  * @par Then  : Speed = MAX
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 7);
	MotorSpy_setMotorAngle(10);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(MAXIMUM,SpeedControl_getSpeed());

}
/**
 * @brief test that if motor angle is 90 then it's med speed
 *
 */
void test_Map_90_MotorAnglesTo_MedSpeed()
{
	/*!
			  * @par Given : Motor angle is unknown
			  * @par When  : Motor angles is 90
			  * @par Then  : Speed = Med
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 8);
	SpeedControl_setSpeed(MAXIMUM);
	MotorSpy_setMotorAngle(90);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(MEDIUM,SpeedControl_getSpeed());

}
/**
 * @brief test that if motor angle is 140 then it's min speed
 *
 */
void test_Map_140_MotorAnglesTo_MinSpeed()
{
	/*!
			  * @par Given : Motor angle is unknown
			  * @par When  : Motor angles is 140
			  * @par Then  : Speed = Min
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 9);
	SpeedControl_setSpeed(MAXIMUM);
	MotorSpy_setMotorAngle(140);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(MINIMUM,SpeedControl_getSpeed());

}
/**
 * @brief test that if it's max speed and positive switch is prepressed the motor angles is not decremented
 *
 */
void test_MAXSPEED_PositiveSWdoesNotDecrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 10 +ve Sw released
			  * @par When  : +ve is prepressed and Speed is Max
			  * @par Then  : MotorAngle is 10
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 10);
	FakeSw_Positive_setState(posistiveSw);
	MotorSpy_setMotorAngle(10);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(10,MotorSpy_getMotorAngle());

}
/**
 * @brief test that if it's min speed and negative sw is prepressed , motor angles is not incremented
 *
 */
void test_MinSPEED_NegativeSWdoesNotIncrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 140 +ve Sw released
			  * @par When  : -ve is prepressed and Speed is Min
			  * @par Then  : MotorAngle is 140
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 11);
	FakeSw_Negative_setState(negativeSw);
	MotorSpy_setMotorAngle(140);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(140,MotorSpy_getMotorAngle());

}
/**
 * @brief test that if it's min speed and p sw is pressed for 30 sec or more , motor angles is not incremented
 *
 */
void test_MinSPEED_P_SWdoesNotIncrementMotorAngle()
{
	/*!
			  * @par Given : Motor angle is 140 +ve Sw released
			  * @par When  : -ve is prepressed and Speed is Min
			  * @par Then  : MotorAngle is 140
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 12);
	FakeSw_P_setState(pSW);
	FakeSw_pSw_setPeriod(pSWperiod);
	MotorSpy_setMotorAngle(140);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(140,MotorSpy_getMotorAngle());

}
/**
 * @brief test that p switch is the highest priority
 *
 */
void test_Priority_pSW_NegativeSw_PositiveSw_PswProcess()
{
	/*!
			  * @par Given : Motor angle is 90
			  * @par When  : pSw is pressed -veSw is prepressed +veSw is prepressed and period of p is less 30
			  * @par Then  : MotorAngle is 90
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 13);
	FakeSw_Negative_setState(negativeSw);
	FakeSw_Positive_setState(posistiveSw);
	FakeSw_P_setState(pSW);
	FakeSw_pSw_setPeriod(pSWperiod);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(90,MotorSpy_getMotorAngle());

}
/**
 * @brief tests that -ve switch is higher priority than +ve switch
 *
 */
void test_Priority_NegativeSw_PositiveSw_NegativeswProcess()
{
	/*!
			  * @par Given : Motor angle is 90
			  * @par When  : pSw is pressed -veSw is prepressed +veSw is prepressed and period of p is less 30
			  * @par Then  : MotorAngle is 90
		*/
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 14);
	FakeSw_Negative_setState(negativeSw);
	FakeSw_Positive_setState(posistiveSw);
	SpeedControl_update();
	writeAngleToFile(MotorSpy_getMotorAngle());
	TEST_ASSERT_EQUAL_INT(91,MotorSpy_getMotorAngle());

}



/**
 * @brief Runner that collect test cases to be run in main
 *
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
	RUN_TEST(test_MinSPEED_P_SWdoesNotIncrementMotorAngle);
	RUN_TEST(test_Priority_pSW_NegativeSw_PositiveSw_PswProcess);
	RUN_TEST(test_Priority_NegativeSw_PositiveSw_NegativeswProcess);
}
/**
 * @brief the entry point of project
 *
 * @return int 0 if code run correctly
 */
int main(void)
{
	UNITY_BEGIN();
	motor = fopen("motor.txt", "w");
	fprintf(motor, "Motor Angle\n");
	test_SpeedContorlRunner();
	return UNITY_END();
}
