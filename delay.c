#include <reg52.h>
#include "car.h"	  	//�Լ���д��ͷ�ļ��������к�������

/********************************/
/*      ��ʱ����               	*/
/********************************/
void delayms(uint x)	//�������Ϊ���ٺ���
{
	uint i;
	while(x--)
	{
		for(i=0;i<113;i++);
	}
}

// void Delay(uint cnt)
// {
//  	while(--cnt);
// }
