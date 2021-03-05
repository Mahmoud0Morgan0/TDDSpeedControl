

#ifndef TESTCODE_FAKESWITCH_FAKESWITCH_H_
#define TESTCODE_FAKESWITCH_FAKESWITCH_H_
/** \brief Enumerate the states of switches*/
typedef enum
{
	SW_PREPRESSED,		/**< The switch is in prepressed state */
	SW_PRESSED,			/**< The switch is in pressed state */
	SW_PRERELEASED,		/**< The switch is in prereleased state */
	SW_RELEASED			/**< The switch is in released state */
}SW_State_t;
void FakeSw_init(void);
SW_State_t FakeSw_Positive_getState(void);
SW_State_t FakeSw_Negative_getState(void);
SW_State_t FakeSw_P_getState(void);

int FakeSw_pSw_getPeriod(void);
void FakeSw_pSw_setPeriod(int period);
void FakeSw_Positive_setState(SW_State_t state);
void FakeSw_Negative_setState(SW_State_t state);
void FakeSw_P_setState(SW_State_t state);
#endif /* TESTCODE_FAKESWITCH_FAKESWITCH_H_ */
