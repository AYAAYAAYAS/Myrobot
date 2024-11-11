#ifndef _APP_RT_THREAD_H_
#define _APP_RT_THREAD_H_

void MX_RT_Thread_Init(void);
void Servo_task_entry(void *parameter);
void Serial_task_entry(void *parameter);
void MPU6050_task_entry(void *parameter);

#endif
