#ifndef __PID_H__
#define __PID_H__
#include "include.h"
#include "common.h"

#define KP 0
#define KI 1
#define KD 2
#define KT 3

#define DIFFSPEED	if(Point >= 50)\
    				{\
        				ftm_pwm_init(FTM0, FTM_CH0, 10*1000, 25);\
    					Point += 10;\
    				}\
    				else\
    				{\
        				ftm_pwm_init(FTM0, FTM_CH0, 10*1000, 13);\
    				}

typedef struct PID
{
	/* ����ۼ� */
	long SumError;		
	/*�ϴ����*/
	int32 LastError;	//Error[-1]
	/* ���ϴ���� */
	int32 PrevError;	//Error[-2]	
	/* �ϴ��ٶ� */
	int32 LastSpeed;	//Speed[-1]
} PID;
/* �������͵����PID�����ṹ�� */
extern PID S_D5_PID, MOTOR_PID;

/* λ��ʽPID������ʼ�� */
void PlacePID_Init(PID *sptr);

/* ����ʽPID������ʼ�� */
void IncPID_Init(PID *sptr);

/* λ��ʽPID������� */
int32 PlacePID_Control(PID *sprt, int32 NowPiont, int32 SetPoint);

/*����ʽ����PID���� */
int32 PID_Cascade(PID *sprt, int32 NowPiont, int32 SetPoint);

/* ����ʽPID���� */
int32 PID_Realize(PID *sptr, int32 ActualSpeed, int32 SetSpeed);

#endif /* __PID_H__ */
