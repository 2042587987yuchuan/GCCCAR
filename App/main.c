/*
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.2
 * @date       2014-10-04
 */
#include "include.h"


/* 
 * 定义存储接收图像的数组 
 * 由于鹰眼摄像头是一字节8个像素，因而需要解压为 1字节1个像素，方便处理
 * 假如需要二维数组，只需要改成 uint8 img[CAMERA_H][CAMERA_W];
 * imgbuff是采集的缓冲区，img是解压后的缓冲区。imgbuff用于采集图像，img用于图像处理.
 */
                   




void 
main()
{
    /* 设置中断向量表与中断服务函数的映射 */
    set_vector_handler(PORTA_VECTORn, PORTA_IRQHandler);
    set_vector_handler(DMA0_VECTORn, DMA0_IRQHandler);
    /* 目标点横坐标 */
    //uint8 Point = 40;
    /* 保存识别到的中点数量 */
    //uint8 Mid_Count;
    /* 电机、舵机初始化 */  
    motorinit();
    /* 摄像头初始化 */
    camera_init(imgbuff);
    /* 用来观察程序中的中间输出数据 */
    char Pointstr[10];
    char Dutystr1[10];
    char Dutystr2[10];

    while(1)
    {
      /* 获取图像 */
      camera_get_img();
      /* 解压图像 */
      img_extract(img, imgbuff, CAMERA_SIZE);
      /* 图像分析，得到中点数量 */
      Mid_Count = Image_GetLine(img);
      /* 使用加权平均或取目标点横坐标 */	
      Point = Point_Weight();
      /*
      sprintf(Pointstr,"%d  ", Point);
      uart_putstr(UART5,Pointstr);
      */
      /* 使用位置式PID解算,获取所需舵机占空比*/
      S_D5_Duty = PlacePID_Control(&S_D5_PID, 40, Point);
      /*
      sprintf(Dutystr1,"%d  ",S_D5_Duty);
      uart_putstr(UART5,Dutystr1);
      */
      /* 限幅保护，防止舵机转角过大被打坏，坏板子(8350~8750)，好板子(8270~8570) */
      S_D5_Duty = range_protect(S_D5_Duty, 8270, 8570);
      /*
      sprintf(Dutystr2,"%d  \n",S_D5_Duty);
      uart_putstr(UART5,Dutystr2);
      */
      /* 修改舵机占空比 */
      ftm_pwm_duty(S_D5_FTM, S_D5_CH, S_D5_Duty);
      /* vcan_sendimg(imgbuff,CAMERA_SIZE); */
      
        
    }
}

