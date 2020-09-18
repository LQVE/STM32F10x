






/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �������ԣ��ж�ģʽ/EXTIģʽ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 

#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_exti.h" 


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */ 
int main(void)
{
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();
	  	
	/* ��ʼ��EXTI�жϣ����°����ᴥ���жϣ�
  *  �����жϻ����stm32f4xx_it.c�ļ��еĺ���
	*  KEY1_IRQHandler��KEY2_IRQHandler�������жϣ���תLED�ơ�
	*/
	EXTI_Key_Config(); 
	
	/* �ȴ��жϣ�����ʹ���жϷ�ʽ��CPU������ѯ���� */
	while(1)                            
	{
	}
}
/*********************************************END OF FILE**********************/












#include "stm32f10x.h"
#include "bsp_SysTick.h"
#include "bsp_led.h"

/*
 * t : ��ʱʱ�� 
 * Ticks : ���ٸ�ʱ�����ڲ���һ���ж� 
 * f : ʱ��Ƶ�� 72000000
 * t = Ticks * 1/f = (72000000/100000) * (1/72000000) = 10us 
 */ 

/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{	
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();

	/* ����SysTick Ϊ10us�ж�һ�� */
	SysTick_Init();
#if 0 
	for(;;)
	{

		LED1( ON ); 
	    Delay_us(100000);    	// 100000 * 10us = 1000ms
		//Delay_ms(100);
		LED1( OFF );
	  
		LED2( ON );
	    Delay_us(100000);		// 100000 * 10us = 1000ms
		//Delay_ms(100);
		LED2( OFF );
	
		LED3( ON );
	    Delay_us(100000);		// 100000 * 10us = 1000ms
		//Delay_ms(100);
		LED3( OFF );
	}     
#else
	for(;;)
	{

		LED1( ON ); 
		SysTick_Delay_Ms( 1000 );
		LED1( OFF );
	  
		LED2( ON );
		SysTick_Delay_Ms( 1000 );
		LED2( OFF );
	
		LED3( ON );
		SysTick_Delay_Ms( 1000 );
		LED3( OFF );
	} 
#endif	
}





//  ============================================================================================================================
//    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
//  ============================================================================================================================
//   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for 
//                         |                                   |                             |   4 bits for subpriority
//  ----------------------------------------------------------------------------------------------------------------------------
//   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
//                         |                                   |                             |   3 bits for subpriority
//  ----------------------------------------------------------------------------------------------------------------------------    
//   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
//                         |                                   |                             |   2 bits for subpriority
//  ----------------------------------------------------------------------------------------------------------------------------    
//   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
//                         |                                   |                             |   1 bits for subpriority
//  ----------------------------------------------------------------------------------------------------------------------------    
//   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
//                         |                                   |                             |   0 bits for subpriority                       
//  ============================================================================================================================












/*********************************************END OF FILE**********************/











/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	/* ����һ���ַ��� */ 
	Usart_SendString( DEBUG_USARTx,"����һ�������жϽ��ջ���ʵ��\n");
	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/









// DMA-�洢�����洢��ģʽ �����ڲ���FLASH���ڲ���SRAM
	
#include "stm32f10x.h"
#include "./led/bsp_led.h"


// ��ʹ�ô洢�����洢��ģʽʱ��ͨ���������ѡ��û��Ӳ�ԵĹ涨
#define DMA_CHANNEL     DMA1_Channel6
#define DMA_CLOCK       RCC_AHBPeriph_DMA1

// ������ɱ�־
#define DMA_FLAG_TC     DMA1_FLAG_TC6

// Ҫ���͵����ݴ�С
#define BUFFER_SIZE     32

/* ����aSRC_Const_Buffer������ΪDMA��������Դ
 * const�ؼ��ֽ�aSRC_Const_Buffer�����������Ϊ��������
 * ��ʾ���ݴ洢���ڲ���FLASH��
 */
const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
/* ����DMA����Ŀ��洢��
 * �洢���ڲ���SRAM��																		
 */
uint32_t aDST_Buffer[BUFFER_SIZE];

#define SOFT_DELAY Delay(0x0FFFFF);
void Delay(__IO u32 nCount); 
uint8_t Buffercmp(const uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);
void DMA_Config(void);																	
																		
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main(void)
{
  /* �����űȽϽ������ */
  uint8_t TransferStatus;
  
	/* LED �˿ڳ�ʼ�� */
	LED_GPIO_Config();
    
  /* ����RGB��ɫ��Ϊ��ɫ */
  LED_PURPLE;  
  
  /* ����ʱ���� */
  Delay(0xFFFFFF);  
  
  /* DMA�������� */
  DMA_Config(); 
  
  /* �ȴ�DMA������� */
  while(DMA_GetFlagStatus(DMA_FLAG_TC)==RESET)
  {
    
  }   
  
  /* �Ƚ�Դ�����봫������� */
  TransferStatus=Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
  
  /* �ж�Դ�����봫������ݱȽϽ��*/
  if(TransferStatus==0)  
  {
    /* Դ�����봫������ݲ����ʱRGB��ɫ����ʾ��ɫ */
    LED_RED;
  }
  else
  { 
    /* Դ�����봫����������ʱRGB��ɫ����ʾ��ɫ */
    LED_BLUE;
  }

	while (1)
	{		
	}
}

void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}

void DMA_Config(void)
{
	  DMA_InitTypeDef DMA_InitStructure;
	
		// ����DMAʱ��
		RCC_AHBPeriphClockCmd(DMA_CLOCK, ENABLE);
		// Դ���ݵ�ַ
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)aSRC_Const_Buffer;
		// Ŀ���ַ
		DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer;
		// �������赽�洢����������������ڲ���FLASH��	
		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
		// �����С	
		DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
		// ���裨�ڲ���FLASH����ַ����	    
		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
		// �ڴ��ַ����
		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
		// �������ݵ�λ	
		DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
		// �ڴ����ݵ�λ
		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;	 
		// DMAģʽ��һ�λ���ѭ��ģʽ
		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
		//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  
		// ���ȼ�����	
		DMA_InitStructure.DMA_Priority = DMA_Priority_High;
		// ʹ���ڴ浽�ڴ�Ĵ���
		DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
		// ����DMAͨ��		   
		DMA_Init(DMA_CHANNEL, &DMA_InitStructure);
    //���DMA������������ɱ�־λ
    DMA_ClearFlag(DMA_FLAG_TC);
		// ʹ��DMA
		DMA_Cmd(DMA_CHANNEL,ENABLE);
}

/**
  * �ж�ָ�����ȵ���������Դ�Ƿ���ȫ��ȣ�
  * �����ȫ��ȷ���1��ֻҪ����һ�����ݲ���ȷ���0
  */
uint8_t Buffercmp(const uint32_t* pBuffer, 
                  uint32_t* pBuffer1, uint16_t BufferLength)
{
  /* ���ݳ��ȵݼ� */
  while(BufferLength--)
  {
    /* �ж���������Դ�Ƿ��Ӧ��� */
    if(*pBuffer != *pBuffer1)
    {
      /* ��Ӧ����Դ����������˳�������������0 */
      return 0;
    }
    /* ������������Դ�ĵ�ַָ�� */
    pBuffer++;
    pBuffer1++;
  }
  /* ����жϲ��Ҷ�Ӧ������� */
  return 1;  
}

//typedef struct
//{
//  uint32_t DMA_PeripheralBaseAddr;   // �����ַ
//  uint32_t DMA_MemoryBaseAddr;       // �洢����ַ
//  uint32_t DMA_DIR;                  // ���䷽��
//  uint32_t DMA_BufferSize;           // ������Ŀ
//  uint32_t DMA_PeripheralInc;        // �����ַ����ģʽ
//  uint32_t DMA_MemoryInc;            // �洢����ַ����ģʽ
//  uint32_t DMA_PeripheralDataSize;   // �������ݿ��
//  uint32_t DMA_MemoryDataSize;       // �洢�����ݿ��
//  uint32_t DMA_Mode;                 // ģʽѡ��
//  uint32_t DMA_Priority;             // ͨ�����ȼ�
//  uint32_t DMA_M2M;                  // �洢�����洢��ģʽ
//}DMA_InitTypeDef;

/*********************************************END OF FILE**********************/











// DMA �洢�������裨���ڣ����ݴ���ʵ��

#include "stm32f10x.h"
#include "bsp_usart_dma.h"
#include "bsp_led.h"

extern uint8_t SendBuff[SENDBUFF_SIZE];
static void Delay(__IO u32 nCount); 

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  uint16_t i;
  /* ��ʼ��USART */
  USART_Config(); 

  /* ����ʹ��DMAģʽ */
  USARTx_DMA_Config();
  
  /* ����RGB��ɫ�� */
  LED_GPIO_Config();

  //printf("\r\n USART1 DMA TX ���� \r\n");
  
  /*��佫Ҫ���͵�����*/
  for(i=0;i<SENDBUFF_SIZE;i++)
  {
    SendBuff[i]	 = 'P';
    
  }

  /*Ϊ��ʾDMA�������ж�CPU���ܴ����������飬����ʹ��DMA�������ݣ����ǳ���
  *��ʱ�����п��ܻᵼ�µ��Զ˴��ڵ������ֻῨ��������ҷɵ������
  *���DMA�����е�ѭ��ģʽ��Ϊ����ģʽ*/		
  
  /* USART1 �� DMA����TX���� */
  USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Tx, ENABLE);

  /* ��ʱCPU�ǿ��еģ����Ը����������� */  
  //����ͬʱ����LED
  while(1)
  {
    LED1_TOGGLE
    Delay(0xFFFFF);
  }
}

static void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/



















/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   I2C EEPROM(AT24C02)���ԣ�������Ϣͨ��USART1��ӡ�ڵ��Եĳ����ն�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_usart.h"
#include "./i2c/bsp_i2c_ee.h"
#include <string.h>

#define  EEP_Firstpage      0x00
uint8_t I2c_Buf_Write[256];
uint8_t I2c_Buf_Read[256];
uint8_t I2C_Test(void);

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{ 
  LED_GPIO_Config();
  
  LED_BLUE;
  /* ���ڳ�ʼ�� */
	USART_Config();
	
	printf("\r\n ����һ��I2C����(AT24C02)��д�������� \r\n");

	/* I2C �����(AT24C02)ʼ�� */
	I2C_EE_Init();

	printf("\r\n ����һ��I2C����(AT24C02)��д�������� \r\n");	
	 	 
  //EEPROM ��д����
	if(I2C_Test() ==1)
	{
			LED_GREEN;
	}
	else
	{
			LED_RED;
	}
  
  while (1)
  {      
  }
}

/**
  * @brief  I2C(AT24C02)��д����
  * @param  ��
  * @retval ��������1���쳣����0
  */
uint8_t I2C_Test(void)
{
	uint16_t i;

	printf("д�������\n\r");
    
	for ( i=0; i<=255; i++ ) //��仺��
  {   
    I2c_Buf_Write[i] = i;

    printf("0x%02X ", I2c_Buf_Write[i]);
    if(i%16 == 15)    
        printf("\n\r");    
   }

  //��I2c_Buf_Write��˳�����������д��EERPOM�� 
	I2C_EE_BufferWrite( I2c_Buf_Write, EEP_Firstpage, 256);
  
  EEPROM_INFO("\n\rд�ɹ�\n\r");
   
   EEPROM_INFO("\n\r����������\n\r");
  //��EEPROM��������˳�򱣳ֵ�I2c_Buf_Read��
	I2C_EE_BufferRead(I2c_Buf_Read, EEP_Firstpage, 256); 
   
  //��I2c_Buf_Read�е�����ͨ�����ڴ�ӡ
	for (i=0; i<256; i++)
	{	
		if(I2c_Buf_Read[i] != I2c_Buf_Write[i])
		{
			EEPROM_ERROR("0x%02X ", I2c_Buf_Read[i]);
			EEPROM_ERROR("����:I2C EEPROMд������������ݲ�һ��\n\r");
			return 0;
		}
    printf("0x%02X ", I2c_Buf_Read[i]);
    if(i%16 == 15)    
        printf("\n\r");
    
	}
  EEPROM_INFO("I2C(AT24C02)��д���Գɹ�\n\r");
  
  return 1;
}
/*********************************************END OF FILE**********************/





/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   AT24C02���ԣ����ģ��I2C��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h" 
#include "./i2c/bsp_i2c_ee.h"

 /**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  
    LED_GPIO_Config();
  
    LED_BLUE;

    /* ���ڳ�ʼ�� */
		USART_Config();

		printf("eeprom ���ģ��i2c�������� \r\n");		
  
    if(ee_Test() == 1)
  	{
			LED_GREEN;
    }
    else
    {
        LED_RED;
    }
    while(1);
}
/*********************************************END OF FILE**********************/









/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   I2C EEPROM(AT24C02)���ԣ��洢С��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./i2c/bsp_i2c_ee.h"
#include "./led/bsp_led.h"
#include <string.h>


uint8_t cal_flag = 0;
uint8_t k;

/*�洢С�������������飬��7��*/
long double double_buffer[7] = {0};
int int_bufffer[7] = {0};

#define DOUBLE_ADDR       10
#define LONGINT_ADDR      70

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{ 
  LED_GPIO_Config();

  /* ���ڳ�ʼ�� */
	USART_Config();
	
	printf("\r\n ����һ��EEPROM ��дС���ͳ�����ʵ�� \r\n");

	/* I2C �����(AT24C02)ʼ�� */
	I2C_EE_Init();	 	 
   

  		/*��ȡ���ݱ�־λ*/
    I2C_EE_BufferRead(&cal_flag, 0, 1);
  
    if( cal_flag != 0xCD )	/*����־����0xcd����ʾ֮ǰ����д������*/
    {      
        printf("\r\nû�м�⵽���ݱ�־��FLASHû�д洢���ݣ���������С��д��ʵ��\r\n");
        cal_flag =0xCD;
        
        /*д���־��0��ַ*/
        I2C_EE_BufferWrite(&cal_flag, 0, 1); 
        
        /*����Ҫд�������*/
        for( k=0; k<7; k++ )
        {
           double_buffer[k] = k +0.1;
           int_bufffer[k]=k*500+1 ;
        }

        /*д��С�����ݵ���ַ10*/
        I2C_EE_BufferWrite((void*)double_buffer,DOUBLE_ADDR, sizeof(double_buffer));
        /*д���������ݵ���ַ60*/
        I2C_EE_BufferWrite((void*)int_bufffer, LONGINT_ADDR, sizeof(int_bufffer));
              
        printf("��оƬд�����ݣ�");
        /*��ӡ������*/
        for( k=0; k<7; k++ )
        {
          printf("С��tx = %LF\r\n",double_buffer[k]);
          printf("����tx = %d\r\n",int_bufffer[k]);
        }
        
        printf("\r\n�븴λ�����壬�Զ�ȡ���ݽ��м���\r\n");      
		
    }    
    else
    {      
      	 printf("\r\n��⵽���ݱ�־\r\n");

				/*��ȡС������*/
        I2C_EE_BufferRead((void*)double_buffer, DOUBLE_ADDR, sizeof(double_buffer));
				
				/*��ȡ��������*/
        I2C_EE_BufferRead((void*)int_bufffer, LONGINT_ADDR, sizeof(int_bufffer));
	
			
				printf("\r\n��оƬ�������ݣ�\r\n");			
        for( k=0; k<7; k++ )
				{
					printf("С�� rx = %LF \r\n",double_buffer[k]);
					printf("���� rx = %d \r\n",int_bufffer[k]);				
				}
      
    }   

  
  while (1)
  {      
  }
}

/*********************************************END OF FILE**********************/












 /**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ���� 8M����flash���ԣ�����������Ϣͨ������1�ڵ��Եĳ����ն��д�ӡ����
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"
#include "./flash/bsp_spi_flash.h"


typedef enum { FAILED = 0, PASSED = !FAILED} TestStatus;

/* ��ȡ�������ĳ��� */
#define TxBufferSize1   (countof(TxBuffer1) - 1)
#define RxBufferSize1   (countof(TxBuffer1) - 1)
#define countof(a)      (sizeof(a) / sizeof(*(a)))
#define  BufferSize (countof(Tx_Buffer)-1)

#define  FLASH_WriteAddress     0x00000
#define  FLASH_ReadAddress      FLASH_WriteAddress
#define  FLASH_SectorToErase    FLASH_WriteAddress

     

/* ���ͻ�������ʼ�� */
uint8_t Tx_Buffer[] = "��л��ѡ��Ұ��stm32������\r\n";
uint8_t Rx_Buffer[BufferSize];

__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;
__IO TestStatus TransferStatus1 = FAILED;

// ����ԭ������
void Delay(__IO uint32_t nCount);
TestStatus Buffercmp(uint8_t* pBuffer1,uint8_t* pBuffer2, uint16_t BufferLength);

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{ 	
	LED_GPIO_Config();
	LED_BLUE;
	
	/* ���ô���Ϊ��115200 8-N-1 */
	USART_Config();
	printf("\r\n ����һ��8Mbyte����flash(W25Q64)ʵ�� \r\n");
	
	/* 8M����flash W25Q64��ʼ�� */
	SPI_FLASH_Init();
	
	/* ��ȡ Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();	
	Delay( 200 );
	
	/* ��ȡ SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();	
	printf("\r\n FlashID is 0x%X,\
	Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	
	/* ���� SPI Flash ID */
	if (FlashID == sFLASH_ID)
	{	
		printf("\r\n ��⵽����flash W25Q64 !\r\n");
		
		/* ������Ҫд��� SPI FLASH ������FLASHд��ǰҪ�Ȳ��� */
		// �������4K����һ����������������С��λ������
		SPI_FLASH_SectorErase(FLASH_SectorToErase);	 	 
		
		/* �����ͻ�����������д��flash�� */
		// ����дһҳ��һҳ�Ĵ�СΪ256���ֽ�
		SPI_FLASH_BufferWrite(Tx_Buffer, FLASH_WriteAddress, BufferSize);		
		printf("\r\n д�������Ϊ��%s \r\t", Tx_Buffer);
		
		/* ���ո�д������ݶ������ŵ����ջ������� */
		SPI_FLASH_BufferRead(Rx_Buffer, FLASH_ReadAddress, BufferSize);
		printf("\r\n ����������Ϊ��%s \r\n", Rx_Buffer);
		
		/* ���д�������������������Ƿ���� */
		TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
		
		if( PASSED == TransferStatus1 )
		{ 
			LED_GREEN;
			printf("\r\n 8M����flash(W25Q64)���Գɹ�!\n\r");
		}
		else
		{        
			LED_RED;
			printf("\r\n 8M����flash(W25Q64)����ʧ��!\n\r");
		}
	}// if (FlashID == sFLASH_ID)
	else// if (FlashID == sFLASH_ID)
	{ 
		LED_RED;
		printf("\r\n ��ȡ���� W25Q64 ID!\n\r");
	}
	
	while(1);  
}

/*
 * ��������Buffercmp
 * ����  ���Ƚ������������е������Ƿ����
 * ����  ��-pBuffer1     src������ָ��
 *         -pBuffer2     dst������ָ��
 *         -BufferLength ����������
 * ���  ����
 * ����  ��-PASSED pBuffer1 ����   pBuffer2
 *         -FAILED pBuffer1 ��ͬ�� pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
  while(BufferLength--)
  {
    if(*pBuffer1 != *pBuffer2)
    {
      return FAILED;
    }

    pBuffer1++;
    pBuffer2++;
  }
  return PASSED;
}

void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
/*********************************************END OF FILE**********************/










/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   W25Q64�洢С���������ķ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "./led/bsp_led.h"
#include "./usart/bsp_usart.h"
#include "./flash/bsp_spi_flash.h" 
 


//��ȡ��ID�洢λ��
__IO uint32_t DeviceID = 0;
__IO uint32_t FlashID = 0;

// ����ԭ������
void Delay(__IO uint32_t nCount);

/*
 * ��������main
 * ����  ��������
 * ����  ����
 * ���  ����
 */
int main(void)
{ 	
	uint8_t cal_flag = 0;
	uint8_t k;
	
	/*�洢С�������������飬��7��*/
	long double double_buffer[7] = {0};
	int int_bufffer[7] = {0};
	
	LED_GPIO_Config();
	LED_BLUE;
	
	/* ���ô���1Ϊ��115200 8-N-1 */
	USART_Config();
  
	printf("\r\n����һ��FLASH ��дС���ͳ�����ʵ�� \r\n");
	
	/* 16M����flash W25Q128��ʼ�� */
	SPI_FLASH_Init();
	
	/* ��ȡ Flash Device ID */
	DeviceID = SPI_FLASH_ReadDeviceID();
	
	Delay( 200 );
	
	/* ��ȡ SPI Flash ID */
	FlashID = SPI_FLASH_ReadID();
	
	printf("\r\nFlashID is 0x%X,  Manufacturer Device ID is 0x%X\r\n", FlashID, DeviceID);
	
	/* ���� SPI Flash ID */
	if (FlashID == sFLASH_ID) 
	{	
		LED_GREEN;
		
		printf("\r\n��⵽SPI FLASH W25Q64 !\r\n");
		
		/*��ȡ���ݱ�־λ*/
    SPI_FLASH_BufferRead(&cal_flag, SPI_FLASH_PageSize*0, 1);
    
		if( cal_flag == 0xCD )	/*����־����0xcd����ʾ֮ǰ����д������*/
    {
			  printf("\r\n��⵽���ݱ�־\r\n");

				/*��ȡС������*/
        SPI_FLASH_BufferRead((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
				
				/*��ȡ��������*/
        SPI_FLASH_BufferRead((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));
	
			
				printf("\r\n��оƬ�������ݣ�\r\n");			
        for( k=0; k<7; k++ )
				{
					printf("С�� rx = %LF \r\n",double_buffer[k]);
					printf("���� rx = %d \r\n",int_bufffer[k]);				
				}
    }    
    else
    {
      printf("\r\nû�м�⵽���ݱ�־��FLASHû�д洢���ݣ���������С��д��ʵ��\r\n");
			cal_flag =0xCD;
			/*��������*/
      SPI_FLASH_SectorErase(0);
			
			/*д���־����0ҳ*/
      SPI_FLASH_BufferWrite(&cal_flag, SPI_FLASH_PageSize*0, 1); 
      
			/*����Ҫд�������*/
      for( k=0; k<7; k++ )
			{
			   double_buffer[k] = k +0.1;
				 int_bufffer[k]=k*500+1 ;
			}

			/*д��С�����ݵ���һҳ*/
      SPI_FLASH_BufferWrite((void*)double_buffer, SPI_FLASH_PageSize*1, sizeof(double_buffer));
			/*д���������ݵ��ڶ�ҳ*/
      SPI_FLASH_BufferWrite((void*)int_bufffer, SPI_FLASH_PageSize*2, sizeof(int_bufffer));
       			
			printf("��оƬд�����ݣ�");
			/*��ӡ������*/
      for( k=0; k<7; k++ )
			{
        printf("С��tx = %LF\r\n",double_buffer[k]);
				printf("����tx = %d\r\n",int_bufffer[k]);
			}
			
			printf("\r\n�븴λ�����壬�Զ�ȡ���ݽ��м���\r\n");
    }   

	}// if (FlashID == sFLASH_ID)
	else
	{    
		LED_RED;
		printf("\r\n��ȡ���� W25Q64 ID!\n\r");
	}
	
	SPI_Flash_PowerDown();  
	while(1);  
}



void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


/*********************************************END OF FILE**********************/

















