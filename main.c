#include <msp430f5529.h>
#include "CC1100.h"
#include "MSP430PORT_DEF.h"
#include "BCSplus_init.h"

#define		INT8U		unsigned char
#define		INT16U		unsigned int
#define     INT32U      unsigned long int
//#define     txmode

INT8U  TxBuf[8]= {0x08,0X00,0X00,0X00,0X00,0X00,0X00,0X00};	  //8字节长发送的数据包
INT8U  RxBuf[8]= {0};   //8字节长接收的数据包
INT8U  ActBuf[8]= {0X08, 'A', 'C', 'K', '\r', '\n'};  //8字节的回复响应
INT8U  PKLEN = 0;        //测试配置是否成功用

/*======== main ========*/
int main(void)
{
    INT8U i = 0;
    INT8U right_cnt = 0;
    BCSplus_graceInit();
    SpiInit();      //cc1101 SPI接口初始化
	POWER_UP_RESET_CC1100(); //上电复位CC1101
	halRfWriteRfSettings();  //配置CC1101的寄存器
    PKLEN = halSpiReadReg(CCxxx0_PKTLEN);  //测试配置是否成功
	halSpiWriteBurstReg(CCxxx0_PATABLE, PaTabel, 8); //配置天线增益
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
#ifdef txmode
   setSleepMpde(); //设置CC1101进入低功耗状态
   while(1) //发送端
   {
        //__bis_SR_register(LPM4_bits+GIE);  // Enter LPM0
        //PWM_set(moto_1st,PwmWith[PwmWidthNum]);   //设置本机的PWM输出
        TxBuf[1]= 1;
        TxBuf[2]= 2;
        TxBuf[3]= 3;
        TxBuf[4]= 4;
        TxBuf[5]= 5;
        TxBuf[6]= 6;
        TxBuf[7]= 7;

        halRfSendPacket(TxBuf,8);// 传输TxBuf指向的数据
        P1OUT ^= BIT0;
        for(i=1;i<8;i++)
        {
        	TxBuf[i]=0;
        }  //保留TxBuf[0]作为ID号
        setRxMode();     //设置为接收模式
        if(halRfReceivePacket(RxBuf,&leng)) //设置为接收模式
        {
            for(i=0;i<6;i++) //检验是否接受OK
            {
                if(*(RxBuf+i)==(ActBuf[i])) right_cnt++;
            }
            if(right_cnt<6) //检验出错
            {

            }
            else
            {

            }

            right_cnt=0;
        }
        halSpiStrobe(CCxxx0_SIDLE);		//进入IDEL
        setSleepMpde(); //设置CC1101进入低功耗状态
   }
#else
    CC1101_InitWOR(1880); //初始化CC1101进入WOR模式
    while(1) //接收端
    {
  	    if(halRfReceivePacket(RxBuf,&leng))
		{
            if(RxBuf[0]!=0x08) continue; //如果数据出错，继续读取数据帧

            if(RxBuf[1]==0X01)
            {
                P1OUT ^= BIT0;
            }

            if(RxBuf[4]==0X04)
            {

            }

            if(RxBuf[7]==0X07)
            {

            }

            for(i=0;i<8;i++)
            {
            	RxBuf[i]=0;
            }
            halRfSendPacket(ActBuf,8); //加入回复ACK，这样可以测试双向通信，及距离
            setRxMode();//设置为接收模式
            //可以测试一下WOR电磁波唤醒。
		}
        else   //通过按键来改变本地的PWM输出
        {

        }
        //CC1101_WOR(); //再次进入WOR模式
        //__bis_SR_register(LPM0_bits+GIE);   // Enter LPM0
	}
#endif
}

