/*
 * FakeSwitch.c
 *
 *  Created on: Mar 2, 2021
 *      Author: IT
 */
#include "FakeSwitch.h"
static SW_State_t positiveState;
static SW_State_t negativeState;
static SW_State_t pState;

void FakeSw_init(void)
{
	positiveState = SW_RELEASED;
	negativeState= SW_RELEASED;
	pState= SW_RELEASED;
}
SW_State_t FakeSw_Positive_getState(void)
{
	return positiveState;
}
SW_State_t FakeSw_Negative_getState(void)
{
	return negativeState;
}
SW_State_t FakeSw_P_getState(void)
{
	return pState;
}

void FakeSw_Positive_setState(SW_State_t state)
{
	positiveState= state;
}
void FakeSw_Negative_setState(SW_State_t state)
{
	negativeState=state;
}
void FakeSw_P_setState(SW_State_t state)
{
	pState=state;
}
