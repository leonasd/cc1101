#include <msp430f5529.h>
#include "CC1100.h"
#include "MSP430PORT_DEF.h"
#include "BCSplus_init.h"

#define		INT8U		unsigned char
#define		INT16U		unsigned int
#define     INT32U      unsigned long int
//#define     txmode

INT8U  TxBuf[8]= {0x08,0X00,0X00,0X00,0X00,0X00,0X00,0X00};	  //8�ֽڳ����͵����ݰ�
INT8U  RxBuf[8]= {0};   //8�ֽڳ����յ����ݰ�
INT8U  ActBuf[8]= {0X08, 'A', 'C', 'K', '\r', '\n'};  //8�ֽڵĻظ���Ӧ
INT8U  PKLEN = 0;        //���������Ƿ�ɹ���

/*======== main ========*/
int main(void)
{
    INT8U i = 0;
    INT8U right_cnt = 0;
    BCSplus_graceInit();
    SpiInit();      //cc1101 SPI�ӿڳ�ʼ��
	POWER_UP_RESET_CC1100(); //�ϵ縴λCC1101
	halRfWriteRfSettings();  //����CC1101�ļĴ���
    PKLEN = halSpiReadReg(CCxxx0_PKTLEN);  //���������Ƿ�ɹ�
	halSpiWriteBurstReg(CCxxx0_PATABLE, PaTabel, 8); //������������
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;
#ifdef txmode
   setSleepMpde(); //����CC1101����͹���״̬
   while(1) //���Ͷ�
   {
        //__bis_SR_register(LPM4_bits+GIE);  // Enter LPM0
        //PWM_set(moto_1st,PwmWith[PwmWidthNum]);   //���ñ�����PWM���
        TxBuf[1]= 1;
        TxBuf[2]= 2;
        TxBuf[3]= 3;
        TxBuf[4]= 4;
        TxBuf[5]= 5;
        TxBuf[6]= 6;
        TxBuf[7]= 7;

        halRfSendPacket(TxBuf,8);// ����TxBufָ�������
        P1OUT ^= BIT0;
        for(i=1;i<8;i++)
        {
        	TxBuf[i]=0;
        }  //����TxBuf[0]��ΪID��
        setRxMode();     //����Ϊ����ģʽ
        if(halRfReceivePacket(RxBuf,&leng)) //����Ϊ����ģʽ
        {
            for(i=0;i<6;i++) //�����Ƿ����OK
            {
                if(*(RxBuf+i)==(ActBuf[i])) right_cnt++;
            }
            if(right_cnt<6) //�������
            {

            }
            else
            {

            }

            right_cnt=0;
        }
        halSpiStrobe(CCxxx0_SIDLE);		//����IDEL
        setSleepMpde(); //����CC1101����͹���״̬
   }
#else
    CC1101_InitWOR(1880); //��ʼ��CC1101����WORģʽ
    while(1) //���ն�
    {
  	    if(halRfReceivePacket(RxBuf,&leng))
		{
            if(RxBuf[0]!=0x08) continue; //������ݳ���������ȡ����֡

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
            halRfSendPacket(ActBuf,8); //����ظ�ACK���������Բ���˫��ͨ�ţ�������
            setRxMode();//����Ϊ����ģʽ
            //���Բ���һ��WOR��Ų����ѡ�
		}
        else   //ͨ���������ı䱾�ص�PWM���
        {

        }
        //CC1101_WOR(); //�ٴν���WORģʽ
        //__bis_SR_register(LPM0_bits+GIE);   // Enter LPM0
	}
#endif
}

