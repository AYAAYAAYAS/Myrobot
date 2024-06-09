#include "main.h"
#include "foc.h"


#define PWM_A TIM1->CCR1
#define PWM_B TIM1->CCR2
#define PWM_C TIM1->CCR3
#define M1_Enable HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET)
#define M1_Disable HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET)

#define _constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

float voltage_power_supply;
float voltage_limit;
float voltage_sensor_align;

float Ualpha ,Ubeta=0 ,Ua=0 ,Ub=0 ,Uc=0;
int PP,DIR;  //磁极对数

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
  float dc_a = _constrain(Ua / voltage_power_supply, 0.0f , 1.0f );
  float dc_b = _constrain(Ub / voltage_power_supply, 0.0f , 1.0f );
  float dc_c = _constrain(Uc / voltage_power_supply, 0.0f , 1.0f );

  PWM_A=dc_a*4095;
  PWM_B=dc_b*4095;
  PWM_C=dc_c*4095;
}

void setTorque(float Uq,float angle_el) {
  Uq=_constrain(Uq,-voltage_power_supply/2,voltage_power_supply/2);
  float Ud=0;
  angle_el = _normalizeAngle(angle_el);
  // 帕克逆变换
  Ualpha =  -Uq*sin(angle_el); 
  Ubeta =   Uq*cos(angle_el); 

  // 克拉克逆变换
  Ua = Ualpha + voltage_power_supply/2;
  Ub = (sqrt(3)*Ubeta-Ualpha)/2 + voltage_power_supply/2;
  Uc = (-Ualpha-sqrt(3)*Ubeta)/2 + voltage_power_supply/2;
  setPwm(Ua,Ub,Uc);
}

void FOC_Vbus(float power_supply)
{
  voltage_power_supply=power_supply;
  HAL_Delay(1000);
 }


//电角度
 float _electricalAngle(){
  return  _normalizeAngle((float)(DIR *  PP) * getAngle_Without_track()-zero_electric_angle);
}

void FOC_alignSensor(int _PP,int _DIR)
{ 
  PP=_PP;
  DIR=_DIR;
  setTorque(3, _3PI_2);
  HAL_Delay(3000);
  zero_electric_angle=_electricalAngle();
  setTorque(0, _3PI_2);
}

float FOC_M0_Angle()
{
  return getAngle();
}