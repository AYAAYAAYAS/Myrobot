#include "main.h"
extern float theta_err,rho_err;
extern uint8_t buffer_1_i,buffer_1_f,buffer_2_i,buffer_2_f,buffer_3;
int Angle_err; 
int A_TH=30; //角度阈值
extern uint8_t TL,TR;
extern uint8_t speed_L,speed_R;
int Motor_L ,Motor_R;
void camera_trace()
{
	Angle_err=rho_err;
	if(Angle_err>A_TH)
	{
	
		if(Angle_err>5)
		{
			set_motor(0,50);
		}
		if(Angle_err<-5)
		{
			set_motor(50,0);
		}
	}
	
	if(Angle_err<A_TH)
	{
				Motor_L = Position_PID(speed_L,TR);  /* 位置式位置控制 */  
				Motor_R = Position_PID(speed_R,TR); 
				set_motor(Motor_L ,Motor_R );
	}
}
