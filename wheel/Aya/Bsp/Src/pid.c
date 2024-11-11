#include "pid.h"


Position_pid P_pid; //位置式pid
Incremental_pid I_pid;//增量式pid
/**PID参数初始化****/
void PID_Init(float P_kp ,float P_ki ,float P_kd  ,float I_kp ,float I_ki ,float I_kd)
{

	P_pid.Position_kp=P_kp,
  P_pid.Position_ki=P_ki,
  P_pid.Position_kd=P_kd;
	P_pid.Intergal_Bias=0;

 	I_pid.Incremental_kp=I_kp; 
	I_pid.Incremental_ki=I_ki;
	I_pid.Incremental_kd=I_kd;
	I_pid.Last_Bias=0;
	I_pid.Prev_Bias=0;
}	 

int limit_(float Data,float max)
{
	if(Data<-max)Data=-max;
	if(Data>max)Data=max;
	return Data;
}	 

/***********************位置式pid控制器*****************/
int Position_PID(float Reality,float Target)
{
	static float Pwm;
	P_pid.reality=Reality;
	P_pid.target=Target;

	P_pid.Bias=P_pid.target-P_pid.reality;
	P_pid.Intergal_Bias+=P_pid.Bias;

	// 限制积分
	if(P_pid.Intergal_Bias>4000)P_pid.Intergal_Bias=4000;
	if(P_pid.Intergal_Bias<-4000)P_pid.Intergal_Bias=-4000;

	Pwm = (P_pid.Position_kp * P_pid.Bias) 
		+ (P_pid.Position_ki * P_pid.Intergal_Bias) 
		+ (P_pid.Position_kd * (P_pid.Bias - P_pid.Last_Bias));
	P_pid.Last_Bias = P_pid.Bias;

	return Pwm;

}


/***********************增量pid控制器*****************/
int Incremental_PID(float Reality,float Target)
{
	static float Pwm;

	I_pid.reality=Reality;
	I_pid.target=Target;

	I_pid.Bias=I_pid.target-I_pid.reality;
	
	Pwm += (I_pid.Incremental_kp * (I_pid.Bias - I_pid.Last_Bias))
		 + (I_pid.Incremental_ki * I_pid.Bias)
		 + (I_pid.Incremental_kd * (I_pid.Bias - 2*I_pid.Last_Bias+I_pid.Prev_Bias));

	I_pid.Prev_Bias = I_pid.Last_Bias;
	I_pid.Last_Bias = I_pid.Bias;
	return Pwm;
}

 

