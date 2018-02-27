#include <reg52.h>
#include "car.h"	 			//自己编写的头文件，里面有函数声明

/********************************/
/*					变量声明							*/
/********************************/
bit pwm_flag = 0;				//PWM使能标志位
uchar pwm_state = 0;		//PWM控制引脚标志位

/********************************/
/*      	打开PWM控制						*/
/********************************/
void StartPwm(uchar state)
{
	pwm_state = state;		//检测PWM控制引脚标志位
	pwm_flag = 1;					//使能PWM标志位
	TR0 = 1;							//马上进入中断程序Timer0Interrupt
}

/********************************/
/*      关闭PWM控制							*/
/********************************/
void StopPwm()
{
	pwm_state = 0;				//清空PWM控制引脚标志位
	pwm_flag = 0;					//清空使能PWM标志位
}

/********************************/
/*      定时器0初始化函数				*/
/********************************/
void Timer0_Init(void)
{
    TMOD |= 0x01;					//定时器工作在方式1（16自加定时器）
    TH0 = 0x0DC;					//定时10ms后触发中断函数Timer0Interrupt(void)
													//TH0 = (65536 - x)/256
													//x = 定时多少微妙/((1/晶振频率)*12)
													//*12是因为：机器周期 = 时钟周期 * 多少T （不同单片机不同）
    TL0 = 0x00;						//TH0 = (65536 - x)%256
    EA = 1;								//打开总中断
    ET0 = 1;							//打开定时器0中断
    TR0 = 1;							//定时器0中断标志位，设置为1即马上进入中断函数
													//Timer0Interrupt(void)
}

/********************************/
/*      定时器0中断服务函数			*/
/********************************/
void Timer0Interrupt(void) interrupt 1
{
	if(pwm_flag)						//如果PWM使能标志位开启，则重新装填定时器数据
	{
    TH0 = 0x0DC;					//重新装填定时器数据，10ms后触发中断
    TL0 = 0x00;
	}
  switch(pwm_state)				//根据状态翻转需要PWM输出的引脚
	{
		case lefta: 					//lefta、leftb、righta、rightb	在car.h中已定义
			left_a = ~left_a;		//left_a、left_b、right_a、right_b	在car.h中已定义
			break;
		case leftb: 
			left_b = ~left_b;
			break;
		case righta: 
			right_a = ~right_a;
			break;
		case rightb: 
			right_b = ~right_b;
			break;
	}
}

