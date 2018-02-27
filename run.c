#include <reg52.h>
#include "car.h"	 //�Լ���д��ͷ�ļ��������к�������

/********************************/
/*      	��յ������IOλ			*/
/********************************/
void CleanRun()
{
	left_a = 0;
	left_b = 0;
	right_a = 0;
	right_b = 0;
}

/********************************/
/*	���ݽ��յ������ݣ�����С��	*/
/********************************/
void Run()
{
	uchar delaytime = 50;						//ǰ�������ˡ�����ǰ������ʱʱ��
	uchar little_delaytime = 22;		//ת�����ʱʱ��
	switch(recvbuf)
				{
					case 0x00:	//ֹͣ
					{
						left_a = 0;						//��ת
						left_b = 0;
						right_a = 0;					//��ת
						right_b = 0;
						break;
					}
					case 0x01:	//ǰ��
					{
						left_a = 1;						//��ת
						left_b = 0;
						right_a = 1;					//��ת
						right_b = 0;
						delayms(delaytime);
						break;
					}
					case 0x02:	//����
					{
						left_a = 0;						//��ת
						left_b = 1;
						right_a = 0;					//��ת
						right_b = 1;
						delayms(delaytime);
						break;
					}
					case 0x03:	//��ת
					{
						left_a = 0;						//��ת
						left_b = 0;
						right_a = 1;					//��ת
						right_b = 0;
						delayms(little_delaytime);
						break;
					}
					case 0x04:	//��ת
					{
						left_a = 1;						//��ת
						left_b = 0;
						right_a = 0;					//��ת
						right_b = 0;
						delayms(little_delaytime);
						break;
					}
					case 0x05:	//ǰ��������
					{
						right_a = 1;					//��ת
						right_b = 0;
						left_b = 0;						//������ת
						StartPwm(lefta);			//������ʱ�����趨����PWM������
						delayms(delaytime);		//��ʱһ��ʱ��
						StopPwm();						//�رն�ʱ��
						break;
					}
					case 0x06:	//ǰ�ҷ�������
					{
						left_a = 1;						//��ת
						left_b = 0;
						right_b = 0;					//������ת
						StartPwm(righta);
						delayms(delaytime);
						StopPwm();
						break;
					}
					case 0x07:	//����������
					{
						right_a = 0;					//��ת
						right_b = 1;
						left_a = 0;						//���ٺ�ת
						StartPwm(leftb);
						delayms(delaytime);
						StopPwm();
						break;
					}
					case 0x08:	//���ҷ�������
					{
						left_a = 0;						//��ת
						left_b = 1;
						right_a = 0;					//���ٺ�ת
						StartPwm(rightb);
						delayms(delaytime);
						StopPwm();
						break;
					}
					case 0x09:	//ԭ��˳ʱ����ת
					{
						left_a = 1;
						left_b = 0;
						right_a = 0;
						right_b = 1;
						delayms(delaytime);
						break;
					}
					case 0x0a:	//ԭ����ʱ����ת
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
