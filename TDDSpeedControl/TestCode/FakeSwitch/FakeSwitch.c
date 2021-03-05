/**
 * @file FakeSwitch.c
 * @author Mahmoud Morgan
 * @brief Fake switch driver to help testing speeccontrol module
 * @version 0.1
 * @date 2021-03-05
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "FakeSwitch.h"

/**
 * @brief Defines the state of +ve switch
 *
 */
static SW_State_t positiveState;
/**
 * @brief Defines the state of -ve switch
 *
 */
static SW_State_t negativeState;
/**
 * @brief Defines the state of p switch
 *
 */
static SW_State_t pState;
/**
 * @brief Defines the period of p switch
 *
 */
static int pSW_period;
/**
 * @brief init the switch driver
 *
 */
void FakeSw_init(void)
{
	positiveState = SW_RELEASED;
	negativeState= SW_RELEASED;
	pState= SW_RELEASED;
	pSW_period=0;
}
/**
 * @brief get the period of p switch
 *
 * @return int period of p switch
 */
int FakeSw_pSw_getPeriod(void)
{
	return pSW_period;
}
/**
 * @brief set the period of p switch
 *
 * @param period period of p switch
 */
void FakeSw_pSw_setPeriod(int period)
{
	pSW_period=period;
}
/**
 * @brief get the state of +ve switch
 *
 * @return SW_State_t state of +ve switch
 */
SW_State_t FakeSw_Positive_getState(void)
{
	return positiveState;
}
/**
 * @brief get the state of -ve switch
 *
 * @return SW_State_t state of -ve switch
 */
SW_State_t FakeSw_Negative_getState(void)
{
	return negativeState;
}
/**
 * @brief get the state of p switch
 *
 * @return SW_State_t state of +p switch
 */
SW_State_t FakeSw_P_getState(void)
{
	return pState;
}
/**
 * @brief set the state of +ve switch
 *
 * @param state state of +ve switch
 */
void FakeSw_Positive_setState(SW_State_t state)
{
	positiveState= state;
}
/**
 * @brief set the state of -ve switch
 *
 * @param state state of -ve switch
 */
void FakeSw_Negative_setState(SW_State_t state)
{
	negativeState=state;
}
/**
 * @brief set the state of p switch
 *
 * @param state state of p switch
 */
void FakeSw_P_setState(SW_State_t state)
{
	pState=state;
}
