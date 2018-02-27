#include <reg52.h>
#include "car.h"	 							//自己编写的头文件，里面有函数声明

/********************************/
/*					变量声明						*/
/********************************/
uchar recvbuf_temp[3] = {0};		//接收数据临时储存数组
uchar recvbuf = 0;							//接收数据
uchar recvflag = 0;							//接收临时数组下标
bit recvend = 0;								//接收完成标志位

/********************************/
/*				串口初始化函数				*/
/********************************/
void Serial_Init()
{
	TMOD=0x20;		 	//设置定时器1工作在方式2（8位自动重装）
	TH1=0xfd;		 		//设置波特率为9600
									//设置初值 9600=(2的SMOD次方/32)*（TI溢出率）=（1/32）*11059200/(256-TH1)*12
	TL1=0xfd;
	TR1=1;			 		//开启定时器1
	SM0=0;			 		//设置串行口工作在方式1（8位数据）
	SM1=1;
	REN=1;         	//允许串行接收位
	EA=1;          	//开启总中断
	ES=1;			//开启串口中断
}

/********************************/
/*     		 串口中断函数			    */
/********************************/
//从串口返回的数据格式：
//十六进制：数据 0D 0A 
void UARTInterrupt(void) interrupt 4		
{
	if(RI)																		//接收中断标志位
	{
		RI=0;																		//清空接收中断标志位
		recvbuf_temp[recvflag++] = SBUF;				//接收数据到临时数组
		switch(recvflag)												//检测接收到第几位
		{
				case 2: if(recvbuf_temp[1] != 0x0D )//接收0x0D检测
									{
										recvflag = 0;						//如果倒数第二个符号不是0x0D,清零数组下标
										return ;
									}break;
				case 3: if(recvbuf_temp[2] != 0x0A )	//接收0x0A检测
									{
										recvflag = 0;						//如果倒数第一个符号不是0x0A,清零数组下标
										return ;
									}
									else											//接收完成
										{
											recvend = 1;					//接收完成标志位
											recvbuf = recvbuf_temp[0];		
											recvflag = 0;					//清零数组下标
											return ;
										}
									break;
		}//end switch
	}//end if(IR)
}

/********************************/
/*     		 字符串发送函数		    */
/********************************/
//  void UartSendString(uchar *datatmp,uchar len)
// {
// 	int i = 0;
// 	ES=0;	  				//关闭串口中断
// 	for(i = 0 ;i < len; i++)
// 	{
// 		SBUF=*(datatmp++);
// 		while(!TI);			//发送数据后，TI自动置1
// 		TI=0;						//TI置0，才能进行下次发送
// 	}
// 	ES=1;						//打开串口中断
// }

/********************************/
/*     		 单个字符发送函数	    */
/********************************/
//  void UartSendByte(uchar datatmp)
// {
// 	ES=0;	  				//关闭串口中断
// 	SBUF=datatmp;		//发送数据a到SBUF，即将单片机的数据发送到计算机
// 	while(!TI);			//发送数据后，TI自动置1
// 	TI=0;						//TI置0，才能进行下次发送
// 	ES=1;						//打开中断
// }