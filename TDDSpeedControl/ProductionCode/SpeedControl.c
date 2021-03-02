


#include"SpeedControl.h"
#include"../TestCode/MotorSpy/MotorSpy.h"

static Speed_t speed ;
void SpeedControl_init()
{
	Motor_init();
	speed= MEDIUM;
}

void SpeedControl_update()
{

}

Speed_t SpeedControl_getSpeed()
{
	return speed;
}
