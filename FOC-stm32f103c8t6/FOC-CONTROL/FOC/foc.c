#include "main.h"

#define M1_Enable HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET)
#define M1_Disable HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET)

#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

float voltage_power_supply=12.6;
float voltage_limit;
float voltage_sensor_align;
float zero_electric_angle=0;
float Ualpha ,Ubeta=0 ,Ua=0 ,Ub=0 ,Uc=0;
int PP,DIR;  //磁极对数
float shaft_angle=0;
void Motor_Init(void){
    if(voltage_sensor_align>voltage_limit)
        voltage_sensor_align = voltage_limit;
    
    PP=7;
    DIR = UNKNOWN;
    M1_Enable;
}


// 归一化角度到 [0,2PI]
float _normalizeAngle(float angle){
  float a = fmod(angle, _2PI);   //取余运算可以用于归一化，列出特殊值例子算便知
  return a >= 0 ? a : (a + _2PI);  
}

void setPwm(float Ua, float Ub, float Uc) {

  // 计算占空比
  // 限制占空比从0到1
  float dc_a = constrain(Ua / voltage_power_supply, 0.0f , 1.0f );
  float dc_b = constrain(Ub / voltage_power_supply, 0.0f , 1.0f );
  float dc_c = constrain(Uc / voltage_power_supply, 0.0f , 1.0f );

  PWM_A=dc_a*1260;
  PWM_B=dc_b*1260;
  PWM_C=dc_c*1260;
}

void setPhaseVoltage(float Uq,float angle_el)
{
	uint32_t sector;
	float T0,T1,T2;
  Uq=constrain(Uq,-voltage_power_supply/2,voltage_power_supply/2);
  float Ud=0;
  angle_el = _normalizeAngle(angle_el);
  // 帕克逆变换
  Ualpha =  -Uq*sin(angle_el); 
  Ubeta =   Uq*cos(angle_el); 
	Ua = Ualpha + voltage_power_supply/2;
  Ub = (sqrt(3)*Ubeta-Ualpha)/2 + voltage_power_supply/2;
  Uc = (-Ualpha-sqrt(3)*Ubeta)/2 + voltage_power_supply/2;
  // 克拉克逆变换
//	sector = (angle_el / _PI_3) + 1;
//  T0 = 1 - T1 - T2;
//  T1 = sqrt(3)*sin(sector*_PI_3 - angle_el)*Uq;
//  T2 = (-Ualpha-sqrt(3)*Ubeta)/2 + voltage_power_supply/2;
//	switch(sector)
//	{
//		case 1:
//			Ua = T1 + T2 + T0/2;
//			Ub = T2 + T0/2;
//			Uc = T0/2;
//			break;
//		case 2:
//			Ua = T1 +  T0/2;
//			Ub = T1 + T2 + T0/2;
//			Uc = T0/2;
//			break;
//		case 3:
//			Ua = T0/2;
//			Ub = T1 + T2 + T0/2;
//			Uc = T2 + T0/2;
//			break;
//		case 4:
//			Ua = T0/2;
//			Ub = T1+ T0/2;
//			Uc = T1 + T2 + T0/2;
//			break;
//		case 5:
//			Ua = T2 + T0/2;
//			Ub = T0/2;
//			Uc = T1 + T2 + T0/2;
//			break;
//		case 6:
//			Ua = T1 + T2 + T0/2;
//			Ub = T0/2;
//			Uc = T1 + T0/2;
//			break;
//		default:  // possible error state
//			Ua = 0;
//			Ub = 0;
//			Uc = 0;
//	}
  setPwm(Ua,Ub,Uc);
}

void FOC_Vbus(float power_supply)
{
  voltage_power_supply=power_supply;
  HAL_Delay(1000);
 }


//电角度
 float _electricalAngle(float shaft_angle, int pole_pairs)
{
  return (shaft_angle * pole_pairs);
}

void FOC_alignSensor(int _PP,int _DIR)
{ 
  PP=_PP;
  DIR=_DIR;
 setPhaseVoltage(3, _3PI_2);
  HAL_Delay(3000);
  zero_electric_angle=_electricalAngle(shaft_angle,7);
  setPhaseVoltage(0, _3PI_2);
}

float FOC_M0_Angle()
{
  return getAngle();
}
//开环速度
float velocityOpenloop(float target_velocity)
{
	float Ts=10;//设置间隔时间为10ms
	shaft_angle=_normalizeAngle(shaft_angle+target_velocity*Ts);
	float Uq = voltage_power_supply/3;
	setPhaseVoltage(Uq,_electricalAngle(shaft_angle, 7));
	return Uq;
}