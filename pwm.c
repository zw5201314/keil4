#include <reg52.h>
#include "car.h"	 			//�Լ���д��ͷ�ļ��������к�������

/********************************/
/*					��������							*/
/********************************/
bit pwm_flag = 0;				//PWMʹ�ܱ�־λ
uchar pwm_state = 0;		//PWM�������ű�־λ

/********************************/
/*      	��PWM����						*/
/********************************/
void StartPwm(uchar state)
{
	pwm_state = state;		//���PWM�������ű�־λ
	pwm_flag = 1;					//ʹ��PWM��־λ
	TR0 = 1;							//���Ͻ����жϳ���Timer0Interrupt
}

/********************************/
/*      �ر�PWM����							*/
/********************************/
void StopPwm()
{
	pwm_state = 0;				//���PWM�������ű�־λ
	pwm_flag = 0;					//���ʹ��PWM��־λ
}

/********************************/
/*      ��ʱ��0��ʼ������				*/
/********************************/
void Timer0_Init(void)
{
    TMOD |= 0x01;					//��ʱ�������ڷ�ʽ1��16�ԼӶ�ʱ����
    TH0 = 0x0DC;					//��ʱ10ms�󴥷��жϺ���Timer0Interrupt(void)
													//TH0 = (65536 - x)/256
													//x = ��ʱ����΢��/((1/����Ƶ��)*12)
													//*12����Ϊ���������� = ʱ������ * ����T ����ͬ��Ƭ����ͬ��
    TL0 = 0x00;						//TH0 = (65536 - x)%256
    EA = 1;								//�����ж�
    ET0 = 1;							//�򿪶�ʱ��0�ж�
    TR0 = 1;							//��ʱ��0�жϱ�־λ������Ϊ1�����Ͻ����жϺ���
													//Timer0Interrupt(void)
}

/********************************/
/*      ��ʱ��0�жϷ�����			*/
/********************************/
void Timer0Interrupt(void) interrupt 1
{
	if(pwm_flag)						//���PWMʹ�ܱ�־λ������������װ�ʱ������
	{
    TH0 = 0x0DC;					//����װ�ʱ�����ݣ�10ms�󴥷��ж�
    TL0 = 0x00;
	}
  switch(pwm_state)				//����״̬��ת��ҪPWM���������
	{
		case lefta: 					//lefta��leftb��righta��rightb	��car.h���Ѷ���
			left_a = ~left_a;		//left_a��left_b��right_a��right_b	��car.h���Ѷ���
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

