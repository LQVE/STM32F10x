/**
  ******************************************************************************
  * @file    main.c
  * @author  LQVE
  * @version V1.0
  * @date    2020-09
  * @brief   
  ******************************************************************************
  * @attention
  *
	* ʹ��oxygenע�͹淶
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_systick.h"
#include "bsp_spi_flash.h"
#include "ff.h"

FATFS fs;
FIL fp;
const char wData[] = "�Ҳ������ö��꣡";
UINT bw;
char rData[] = "";
UINT br;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
uint8_t buffer[4096];
uint8_t writebuff[256];
int main(void)
{	
	
	LED_GPIO_Config();
	LED(1);
  /*��ʼ��USART */
  USART_Config();
	
	/* ����һ���ַ��� */
	Usart_SentStr( DEBUG_USARTx,"�ļ�ϵͳFATFS��ֲ\n");
	printf("FATFS\n");
	
	FRESULT res; 
	res = f_mount(&fs,"1:",1);
	printf("״̬f_mount res=%d",res);
	//��ʼ���ļ�ϵͳ
	if(res == FR_NO_FILESYSTEM)
	{
		f_mkfs("1:",0,0);
		printf("״̬f_mkfs res=%d",res);
		//��ʽ���� ��ȡ������ �����¹����ļ�ϵͳ
		res = f_mount(NULL,"1:",1);
		res = f_mount(&fs,"1:",1);
		printf("n f_mount res=%d",res);
	}
	
	//�����ļ�ϵͳд���ļ�
	res = f_open(&fp,"1:����һ���Ƚϳ��������ļ���.txt",FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
	printf("\r\n nf_open res = %d",res);
	if(res == FR_OK){
		res = f_write(&fp,wData,sizeof(wData),&bw);
		printf("\r\n nf_write res = %d",res);
		if(res == FR_OK){
			res = f_lseek(&fp,0);//�ض�λ�ļ�ָ�룻
			printf("\r\nn_F_seek = %d",res);
			res = f_read(&fp,rData,f_size(&fp),&br);
			if(res == FR_OK)
				printf("\r\n�ļ����ݣ�%s",rData);
			res = f_close(&fp);
		}
	}
	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/
