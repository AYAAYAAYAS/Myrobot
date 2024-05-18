float Q_angle=0.001, Q_gyro=0.003, R_angle=0.5, dt=0.005;
float P[2][2] = {{ 1, 0 },{ 0, 1 }};
float Pdot[4] ={0,0,0,0};

const char C_0 = 1;

float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1,angle,angle_dot;
void Kalman_Filter(float angle_m,float gyro_m)            //gyro_m:gyro_measure
{
    angle+=(gyro_m-q_bias) * dt;//先验估计
    Pdot[0]=Q_angle - P[0][1] - P[1][0];// Pk-' 先验估计误差协方差的微分
    Pdot[1]=- P[1][1];
    Pdot[2]=- P[1][1];
    Pdot[3]=Q_gyro;
    P[0][0] += Pdot[0] * dt;// Pk- 先验估计误差协方差微分的积分 = 先验估计误差协方差
    P[0][1] += Pdot[1] * dt;
    P[1][0] += Pdot[2] * dt;
    P[1][1] += Pdot[3] * dt;
    angle_err = angle_m - angle;//zk-先验估计
    PCt_0 = C_0 * P[0][0];
    PCt_1 = C_0 * P[1][0];
    E = R_angle + C_0 * PCt_0;
    K_0 = PCt_0 / E;//Kk
    K_1 = PCt_1 / E;
    t_0 = PCt_0;
    t_1 = C_0 * P[0][1];

    P[0][0] -= K_0 * t_0;//后验估计误差协方差
    P[0][1] -= K_0 * t_1;
    P[1][0] -= K_1 * t_0;
    P[1][1] -= K_1 * t_1;
    angle    += K_0 * angle_err;//后验估计
    q_bias    += K_1 * angle_err;//后验估计
    angle_dot = gyro_m-q_bias;//输出值（后验估计）的微分 = 角速度
}
