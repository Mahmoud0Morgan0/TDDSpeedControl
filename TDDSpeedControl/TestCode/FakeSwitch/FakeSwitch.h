/*
 * FakeSwitch.h
 *
 *  Created on: Mar 2, 2021
 *      Author: IT
 */

#ifndef TESTCODE_FAKESWITCH_FAKESWITCH_H_
#define TESTCODE_FAKESWITCH_FAKESWITCH_H_

typedef enum
{
	SW_PREPRESSED,SW_PRESSED,SW_PRERELEASED, SW_RELEASED
}SW_State_t;
void FakeSw_init(void);
SW_State_t FakeSw_Positive_getState(void);
SW_State_t FakeSw_Negative_getState(void);
SW_State_t FakeSw_P_getState(void);

void FakeSw_Positive_setState(SW_State_t state);
void FakeSw_Negative_setState(SW_State_t state);
void FakeSw_P_setState(SW_State_t state);
#endif /* TESTCODE_FAKESWITCH_FAKESWITCH_H_ */
