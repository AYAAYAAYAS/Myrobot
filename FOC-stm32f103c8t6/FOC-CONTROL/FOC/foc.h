#ifndef _FOC_H
#define _FOC_H


#define _2_SQRT3 1.15470053838
#define _SQRT3 1.73205080757
#define _1_SQRT3 0.57735026919
#define _SQRT3_2 0.86602540378
#define _SQRT2 1.41421356237
#define _120_D2R 2.09439510239
#define _PI 3.14159265359
#define _PI_2 1.57079632679
#define _PI_3 1.0471975512
#define _2PI 6.28318530718
#define _3PI_2 4.71238898038
#define _PI_6 0.52359877559
#define PWM_A TIM2->CCR1
#define PWM_B TIM2->CCR2
#define PWM_C TIM2->CCR3
typedef enum{
    CW = 1,
    CCW = -1,
    UNKNOWN = 0
}Direction;

void setPwm(float Ua, float Ub, float Uc);
void setPhaseVoltage(float Uq,float angle_el);
float _normalizeAngle(float angle);
void FOC_Vbus(float power_supply);
void FOC_alignSensor(int _PP,int _DIR);
float _electricalAngle(float shaft_angle, int pole_pairs);
float FOC_M0_Angle();
float velocityOpenloop(float target_velocity);

#endif