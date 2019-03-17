
#ifndef __NRF24L01P_H
#define __NRF24L01P_H

#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "spi.h"

/***********NRF24L01Pָ��***********/
#define RF_R_REGISTER          0x00  //������/״̬�Ĵ���    
#define RF_W_REGISTER          0x20  //д����/״̬�Ĵ���    
#define RF_R_RX_PAYLOAD        0x61  //��RX�غ�             
#define RF_W_TX_PAYLOAD        0xA0  //дTX�غ�             
#define RF_FLUSH_TX            0xE1  //���TX FIFO         
#define RF_FLUSH_RX            0xE2  //���RX FIFO          
#define RF_REUSE_TX_PL         0xE3  //����ʹ����һ��TX�غ� 
#define RF_R_RX_PL_WID         0x60  //��RX�غɿ��

#define RF_W_ACK_PAYLOAD_P0    0xA8  //����ͨ��0 ACK
#define RF_W_ACK_PAYLOAD_P1    0xA9  //����ͨ��1 ACK
#define RF_W_ACK_PAYLOAD_P2    0xAA  //����ͨ��2 ACK
#define RF_W_ACK_PAYLOAD_P3    0xAB  //����ͨ��3 ACK
#define RF_W_ACK_PAYLOAD_P4    0xAC  //����ͨ��4 ACK
#define RF_W_ACK_PAYLOAD_P5    0xAD  //����ͨ��5 ACK

#define RF_W_TX_PAYLOAD_NOACK  0xB0  //����ACK
#define RF_NOP                 0xFF  //�ղ���	            

/**********NRF24L01P�Ĵ���**********/
#define RF_CONFIG       0x00  //���üĴ���                
#define RF_EN_AA        0x01  //ʹ���Զ�Ӧ��
#define RF_EN_RXADDR    0x02  //ʹ������ͨ��         
#define RF_SETUP_AW     0x03  //���õ�ַ���
#define RF_SETUP_RETR   0x04  //�����Զ��ط�             
#define RF_RF_CH        0x05  //RFͨ��                        
#define RF_RF_SETUP     0x06  //RF���üĴ���                    
#define RF_STATUS       0x07  //״̬�Ĵ���                   

#define RF_RX_OK        0x40  //���������ж�
#define RF_TX_OK        0x20  //���ݷ�������ж�
#define RF_MAX_TX       0x10  //�ﵽ�����ط��ж�

#define RF_OBSERVE_TX   0x08  //���ͼ��Ĵ���       
#define RF_RPD          0x09  //�ز����Ĵ���         
#define RF_RX_ADDR_P0   0x0A  //����ͨ��0���յ�ַ 
#define RF_RX_ADDR_P1   0x0B  //����ͨ��1���յ�ַ 
#define RF_RX_ADDR_P2   0x0C  //����ͨ��2���յ�ַ 
#define RF_RX_ADDR_P3   0x0D  //����ͨ��3���յ�ַ 
#define RF_RX_ADDR_P4   0x0E  //����ͨ��4���յ�ַ  
#define RF_RX_ADDR_P5   0x0F  //����ͨ��5���յ�ַ 
#define RF_TX_ADDR      0x10  //���͵�ַ           
#define RF_RX_PW_P0     0x11  //��������ͨ��0��Ч���ݿ��
#define RF_RX_PW_P1     0x12  //��������ͨ��1��Ч���ݿ��
#define RF_RX_PW_P2     0x13  //��������ͨ��2��Ч���ݿ��
#define RF_RX_PW_P3     0x14  //��������ͨ��3��Ч���ݿ��
#define RF_RX_PW_P4     0x15  //��������ͨ��4��Ч���ݿ��
#define RF_RX_PW_P5     0x16  //��������ͨ��5��Ч���ݿ��
#define RF_FIFO_STATUS  0x17  //FIFO״̬�Ĵ���              
#define RF_DYNPD        0x1C  //ʹ��/��ֹ��̬�غ�						
#define RF_FEATURE      0x1D  //���ܼĴ���

#define RF_csnEn()  GPIO_ResetBits(GPIOB,GPIO_Pin_0) 
#define RF_csnDis() GPIO_SetBits(GPIOB,GPIO_Pin_0)          //CSN
#define RF_ceEn()   GPIO_ResetBits(GPIOB,GPIO_Pin_1) 
#define RF_ceDis()  GPIO_SetBits(GPIOB,GPIO_Pin_1)          //CE
#define RF_getIrq() GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2) //IRQ	
												 
extern u8   RF_checkF(void);  
extern void RF_confF(void); 
extern void RF_initF(void);  

extern u8   RF_readRegF(u8 readAddr); 
extern void RF_writeRegF(u8 writeAddr,u8 writeData); 
extern void RF_readRegsF(u8 readAddr,u8 *readData,u8 len);   
extern void RF_writeRegsF(u8 writeAddr,u8 *writeData,u8 len); 

extern void RF_irqTxF(u8 ch);
extern u8   RF_irqRxAckF(u8 ch);

#endif
