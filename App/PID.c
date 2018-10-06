#include "PID.h"


/* �������͵����PID�����ṹ�� */
PID S_D5_PID, MOTOR_PID;
/* ���PID,PID �� I ��û��ʹ�ã�ֻ�� PD6�˴� I ����Ϊ�ٶ�ģʽ�ı�ţ���PID��Ӱ�� */	
int32 S_D5[10][4] = {{37, 0, 15, 16},{ 20, 1, 0, 19}, {24, 2, 15, 28}, {24, 3, 22, 14}, {20, 4, 25, 14}, {24, 5, 24, 13}, {26, 6, 18 , 13}, {25, 7, 27, 14}, {29,8,35,13}};

									



float   MOTOR[3] = {5, 0.4, 0};	//���PID
/* 
 *λ��ʽPID������ʼ��
 */
void 
PlacePID_Init(PID *sptr)
{
	sptr->SumError = 0;
	sptr->LastError = 0;	//Error[-1]
	sptr->PrevError = 0;	//Error[-2]
}
/* 
 *����ʽPID������ʼ��
 */
void 
IncPID_Init(PID *sptr)
{
	sptr->SumError = 0;
	sptr->LastError = 0;	//Error[-1]
	sptr->PrevError = 0;	//Error[-2]	
	sptr->LastSpeed = 0;
}
/* 
 *λ��ʽPID�������
 */
int32 
PlacePID_Control(PID *sprt, int32 NowPiont, int32 SetPoint)
{
	/* ���ٹ��� */
	//DIFFSPEED;
  if(Point >= 50)
  {
      ftm_pwm_init(FTM0, FTM_CH0, 10*1000, 20);
    	Point += 10;
  }
  else
  {
      ftm_pwm_init(FTM0, FTM_CH0, 10*1000, 14);
  }
	/* ��ǰ��� */
	register int32 iError;	
	/* ���ó���ʵ�����ֵ */
	register int32 Actual;
	/* ��̬P */
	float Kp;		
	
	/* ���㵱ǰ��� */
	iError = SetPoint - NowPiont;	

	/*Kp = 1.0 * (iError*iError) / S_D5[Set][KT] + S_D5[Set][KP];	//kPֵ���ֵ�ɶ��κ�����ϵ 
	Actual = Kp * iError + S_D5[Set][KD] * (iError - sprt->LastError);//ֻ��PD 

	/* �����ϴ���� */
	sprt->LastError = iError;
    Actual = iError*9;
	
	return  S_D5_MID - Actual; 
}
/*
 *��������PID�������
 */
int32 
PID_Cascade(PID *sptr, int32 ActualSpeed, int32 SetSpeed)
{
	 /* ��ǰ��� */
	register int32 iError;
	/* ���ó���ʵ������ */
	register int32 Increase;	
	/* ���㵱ǰ��� */
	iError = SetSpeed - ActualSpeed;
	
	Increase = - MOTOR[KP] * (ActualSpeed - sptr->LastSpeed)	//���ٶ�
			   + MOTOR[KI] * iError
			   + MOTOR[KD] * (iError - 2 * sptr->LastError + sptr->PrevError);
	
	sptr->PrevError = sptr->LastError;	//����ǰ�����
	sptr->LastError = iError;		  	//�����ϴ����
	sptr->LastSpeed = ActualSpeed;		//�����ϴ��ٶ�
	
	if (iError < -100)
	{
		Increase -= 400;
	}
	else if (iError < -80)
	{
		Increase -= 300;
	}
	else if (iError < -50)
	{
		Increase -= 250;
	}
	else if (iError < -30)
	{
		Increase -= 200;
	}
	
	return Increase;
        
}	

/*
 *����ʽPID�������
 */
int32 
PID_Realize(PID *sptr, int32 ActualSpeed, int32 SetSpeed)
{
	//��ǰ������Ϊ�Ĵ���������ֻ���������ͺ��ַ��ͱ�������������ٶ�
	register int32 iError,	    //��ǰ���
					Increase;	//���ó���ʵ������
	
	iError = SetSpeed - ActualSpeed;//���㵱ǰ���
	
	Increase = MOTOR[KP] * (iError - sptr->LastError)
			 + MOTOR[KI] * iError
			 + MOTOR[KD] * (iError - 2 * sptr->LastError + sptr->PrevError);
	
	sptr->PrevError = sptr->LastError;	//����ǰ�����
	sptr->LastError = iError;		  	//�����ϴ����
	
	if (iError < -70)
	{
		BangBang_Flag = 1;
		Increase -= 80;
	}
	else if (iError < -50)
	{
		BangBang_Flag = 1;
		Increase -= 50;
	}
	else if (iError < -30)
	{
		BangBang_Flag = 1;
		Increase -= 20;
	}

	if ((iError > 50) && (BangBang_Flag == 1))
	{
		BangBang_Flag = 0;
		Increase +=  170;
	}
	else if (iError > 50)
	{
		Increase += 120;
	}
	
	return Increase;
}



