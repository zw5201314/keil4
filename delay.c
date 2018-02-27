#include <reg52.h>
#include "car.h"	  	//自己编写的头文件，里面有函数声明

/********************************/
/*      延时函数               	*/
/********************************/
void delayms(uint x)	//输入参数为多少毫秒
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
