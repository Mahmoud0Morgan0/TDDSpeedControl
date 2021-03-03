


#include"SpeedControl.h"
#include"../TestCode/MotorSpy/MotorSpy.h"
#include"../TestCode/FakeSwitch/FakeSwitch.h"

static Speed_t speed ;


Speed_t SpeedControl_getSpeed()
{
	return speed;
}

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



void SpeedControl_init()
{
	Motor_init();
	speed= MEDIUM;
	FakeSw_init();
}

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


