#include <reg52.h>
#include "car.h"	 //自己编写的头文件，里面有函数声明

/********************************/
/*      	清空电机控制IO位			*/
/********************************/
void CleanRun()
{
	left_a = 0;
	left_b = 0;
	right_a = 0;
	right_b = 0;
}

/********************************/
/*	根据接收到的数据，控制小车	*/
/********************************/
void Run()
{
	uchar delaytime = 50;						//前进、后退、侧向前进的延时时间
	uchar little_delaytime = 22;		//转弯的延时时间
	switch(recvbuf)
				{
					case 0x00:	//停止
					{
						left_a = 0;						//不转
						left_b = 0;
						right_a = 0;					//不转
						right_b = 0;
						break;
					}
					case 0x01:	//前进
					{
						left_a = 1;						//正转
						left_b = 0;
						right_a = 1;					//正转
						right_b = 0;
						delayms(delaytime);
						break;
					}
					case 0x02:	//后退
					{
						left_a = 0;						//反转
						left_b = 1;
						right_a = 0;					//反转
						right_b = 1;
						delayms(delaytime);
						break;
					}
					case 0x03:	//左转
					{
						left_a = 0;						//不转
						left_b = 0;
						right_a = 1;					//正转
						right_b = 0;
						delayms(little_delaytime);
						break;
					}
					case 0x04:	//右转
					{
						left_a = 1;						//正转
						left_b = 0;
						right_a = 0;					//不转
						right_b = 0;
						delayms(little_delaytime);
						break;
					}
					case 0x05:	//前左方向运行
					{
						right_a = 1;					//正转
						right_b = 0;
						left_b = 0;						//半速正转
						StartPwm(lefta);			//开启定时器，设定产生PWM的引脚
						delayms(delaytime);		//延时一段时间
						StopPwm();						//关闭定时器
						break;
					}
					case 0x06:	//前右方向运行
					{
						left_a = 1;						//正转
						left_b = 0;
						right_b = 0;					//半速正转
						StartPwm(righta);
						delayms(delaytime);
						StopPwm();
						break;
					}
					case 0x07:	//后左方向运行
					{
						right_a = 0;					//后转
						right_b = 1;
						left_a = 0;						//半速后转
						StartPwm(leftb);
						delayms(delaytime);
						StopPwm();
						break;
					}
					case 0x08:	//后右方向运行
					{
						left_a = 0;						//后转
						left_b = 1;
						right_a = 0;					//半速后转
						StartPwm(rightb);
						delayms(delaytime);
						StopPwm();
						break;
					}
					case 0x09:	//原地顺时针旋转
					{
						left_a = 1;
						left_b = 0;
						right_a = 0;
						right_b = 1;
						delayms(delaytime);
						break;
					}
					case 0x0a:	//原地逆时针旋转
					{
						left_a = 0;
						left_b = 1;
						right_a = 1;
						right_b = 0;
						delayms(delaytime);
						break;
					}
				}
}
