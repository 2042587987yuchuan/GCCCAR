#ifndef __CONTROL_H__
#define __CONTROL_H__
#include "include.h"
#include "common.h"

/* 
 *�������˿�(PTC1~PTC4)
 *����������Ƶ��
 */
#define MOTOR_FTM   FTM0
#define MOTOR1_PWM  FTM_CH0
#define MOTOR2_PWM  FTM_CH1
#define MOTOR3_PWM  FTM_CH2
#define MOTOR4_PWM  FTM_CH3
#define MOTOR_HZ    (10*1000)	/* ����ģʽ�£�Ƶ��Ӧ���� 30~100�� ����ģʽ�£�Ƶ��Ӧ���� 20k ���� */

/* 
 *�������˿�(PTB0) 
 *���Ƶ�� 100(HZ)
 *8420(�°���),8550(������)
 */
#define S_D5_FTM FTM1 
#define S_D5_CH  FTM_CH0
#define S_D5_HZ  (100)
#define S_D5_MID 8420
								
extern int32 MOTOR_Duty;
extern int32 MOTOR_Speed;
extern int32 RC_Get;
extern uchar Run_Flag;
extern uchar Game_End;
extern uchar Stop_Flag;
extern uchar BangBang_Flag;
extern char Set;
extern int32 S_D5_Duty;
/* Ŀ�������� */
extern uint8   Point_Mid;
/* ���������������������Ϊ int32 ������ */
extern int32 Pulses_Count;


/* ����ٶȲ��� */
void speed_measure();
/* �����߼����ͣ������ */
void Start_Control(void);
/* ����ʽPID���ص���ٶ� */
void MOTOR_Control(void);
/* �޷����� */
int32 range_protect(int32 duty, int32 min, int32 max); 

#endif /* __CONTROL_H__ */