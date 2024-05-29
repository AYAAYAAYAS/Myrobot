#include "mian.h"


#define PP 1  //磁极对数
#define PWM_A TIM1->CCR1
#define PWM_B TIM1->CCR2
#define PWM_B TIM1->CCR3

int DIR=1;//编码器读值方向


// 归一化角度到 [0,2PI]
float _normalizeAngle(float angle){
  float a = fmod(angle, _2PI);   //取余运算可以用于归一化，列出特殊值例子算便知
  return a >= 0 ? a : (a + _2PI);  
}