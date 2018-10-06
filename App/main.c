/*
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.2
 * @date       2014-10-04
 */
#include "include.h"


/* 
 * ����洢����ͼ������� 
 * ����ӥ������ͷ��һ�ֽ�8�����أ������Ҫ��ѹΪ 1�ֽ�1�����أ����㴦��
 * ������Ҫ��ά���飬ֻ��Ҫ�ĳ� uint8 img[CAMERA_H][CAMERA_W];
 * imgbuff�ǲɼ��Ļ�������img�ǽ�ѹ��Ļ�������imgbuff���ڲɼ�ͼ��img����ͼ����.
 */
                   




void 
main()
{
    /* �����ж����������жϷ�������ӳ�� */
    set_vector_handler(PORTA_VECTORn, PORTA_IRQHandler);
    set_vector_handler(DMA0_VECTORn, DMA0_IRQHandler);
    /* Ŀ�������� */
    //uint8 Point = 40;
    /* ����ʶ�𵽵��е����� */
    //uint8 Mid_Count;
    /* ����������ʼ�� */  
    motorinit();
    /* ����ͷ��ʼ�� */
    camera_init(imgbuff);
    /* �����۲�����е��м�������� */
    char Pointstr[10];
    char Dutystr1[10];
    char Dutystr2[10];

    while(1)
    {
      /* ��ȡͼ�� */
      camera_get_img();
      /* ��ѹͼ�� */
      img_extract(img, imgbuff, CAMERA_SIZE);
      /* ͼ��������õ��е����� */
      Mid_Count = Image_GetLine(img);
      /* ʹ�ü�Ȩƽ����ȡĿ�������� */	
      Point = Point_Weight();
      /*
      sprintf(Pointstr,"%d  ", Point);
      uart_putstr(UART5,Pointstr);
      */
      /* ʹ��λ��ʽPID����,��ȡ������ռ�ձ�*/
      S_D5_Duty = PlacePID_Control(&S_D5_PID, 40, Point);
      /*
      sprintf(Dutystr1,"%d  ",S_D5_Duty);
      uart_putstr(UART5,Dutystr1);
      */
      /* �޷���������ֹ���ת�ǹ��󱻴򻵣�������(8350~8750)���ð���(8270~8570) */
      S_D5_Duty = range_protect(S_D5_Duty, 8270, 8570);
      /*
      sprintf(Dutystr2,"%d  \n",S_D5_Duty);
      uart_putstr(UART5,Dutystr2);
      */
      /* �޸Ķ��ռ�ձ� */
      ftm_pwm_duty(S_D5_FTM, S_D5_CH, S_D5_Duty);
      /* vcan_sendimg(imgbuff,CAMERA_SIZE); */
      
        
    }
}

