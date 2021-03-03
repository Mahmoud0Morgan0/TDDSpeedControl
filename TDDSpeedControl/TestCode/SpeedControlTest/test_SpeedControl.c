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
#include "stdio.h"
#include "stdlib.h"

SW_State_t posistiveSw;
SW_State_t negativeSw;
SW_State_t pSW;
int pSWperiod;
void setUp(void)
{
	SpeedControl_init();
	 posistiveSw=SW_RELEASED;
	 negativeSw=SW_RELEASED;
	 pSW=SW_RELEASED;
	 pSWperiod=0;

}
void tearDown(void)
{

}


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
		printf("Data from the file:\n%s\n", pos_SW);
		printf("Data from the file:\n%s\n", neg_SW);
		printf("Data from the file:\n%s\n", p_SW);
		printf("Data from the file:\n%d\n", period);
	}

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

	pSWperiod=period;

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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 2);
	FakeSw_Positive_setState(posistiveSw);
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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 3);
	FakeSw_Negative_setState(negativeSw);
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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 4);
	FakeSw_P_setState(pSW);
	FakeSw_pSw_setPeriod(pSWperiod);
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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 5);
	FakeSw_P_setState(pSW);
	FakeSw_pSw_setPeriod(pSWperiod);
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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 6);
	FakeSw_P_setState(pSW);
	FakeSw_pSw_setPeriod(pSWperiod);
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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 7);
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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 8);
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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 9);
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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 10);
	FakeSw_Positive_setState(posistiveSw);
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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 11);
	FakeSw_Negative_setState(negativeSw);
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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 12);
	FakeSw_Negative_setState(negativeSw);
	FakeSw_Positive_setState(posistiveSw);
	FakeSw_P_setState(pSW);
	FakeSw_pSw_setPeriod(pSWperiod);
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
	fetchData(&posistiveSw, &negativeSw, &pSW, &pSWperiod, 13);
	FakeSw_Negative_setState(negativeSw);
	FakeSw_Positive_setState(posistiveSw);
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
