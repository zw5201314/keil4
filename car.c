#include <reg52.h>
#include "car.h"	 //自己编写的头文件
/********************************/
/*     		 		主函数			 		  	*/
/********************************/
main()
{
		Serial_Init();		//初始化串口
		Timer0_Init();		//初始化定时器0
		while(1)
		{
			if(recvend)    	//检测接收标志位，有数据到则进入处理
			{
				recvend=0;	 	//清空该标志位
				Run();				//根据接收到数据作出处理
// 				CleanRun();		//清零电机控制IO口
			}
		}	
	 return 0;
}


