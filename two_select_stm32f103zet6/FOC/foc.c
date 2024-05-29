#include "main.h"
int Ualpha,Ubeta;//定义Uα以及Uβ
int Ua,Ub,Uc; //定义三相电压
int dc_a=0,dc_b=0,dc_c=0;
#define _2PI 6.28318530718
#define voltage_power_supply 12//实际输入电压，避免电压产生0，将产生的正弦波上移6V，从而达到维持在正区间的目的
#define voltage_limit 12 //限制最大电压
#define constrain(entry,Min,Max) ((entry)<(Min)?(Min):((entry)>(Max)?(Max):(entry)))//约束电压
#define PWM_Period 1280
#define PWM_A TIM8->CCR1
#define PWM_B TIM8->CCR2
#define PWM_C TIM8->CCR3

float shaftAngle(void){
    

}

//电角度计算 机械角度*磁极对数
float electricalAngle(float shaft_angle, int pole_pairs) {
  return (shaft_angle * pole_pairs);
}
//设置电角度在0-2PI->0-360°之间
float normalizeAngle(float angle){
    float a = fmod(angle,_2PI);
    return a>=0?a:(a+_2PI)
}

//设置PWM值
void setPwm(float Ua,float Ub,float Uc){
    //对计算的三相电压进行限制幅度
    Ua=constrain(Ua, 0.0f,voltage_limit);
    Ub=constrain(Ub, 0.0f,voltage_limit);
    Uc=constrain(Uc, 0.0f,voltage_limit);

    //限制占空比
    dc_a = _constrain(Ua / voltage_power_supply, 0.0f , 1.0f );
    dc_b = _constrain(Ub / voltage_power_supply, 0.0f , 1.0f );
    dc_c = _constrain(Uc / voltage_power_supply, 0.0f , 1.0f );

    PWM_A = dc_a*PWM_Period;
    PWM_B = dc_b*PWM_Period;
    PWM_C = dc_c*PWM_Period;

}

void setPhaseVoltage(float Uq,float Ud, float angle_el){
    angle_el = normalizeAngle();

    //帕克逆变换，Id=0
    Ualpha = Ud*cos(angle_el)-Uq*sin(angle_el);
    Ubeta = Uq*cos(angle_el)+Ud*sin(angle_el);

    //克拉克逆变换
    Ua = Ualpha+voltage_power_supply/2;
    Ub = (sqrt(3)*Ubeta-Ualpha)/2+voltage_power_supply/2;
    Uc = (-Ualpha-sqrt(3)*Ubeta)/2+voltage_power_supply/2;

    setPwm(Ua,Ub,Uc);
}