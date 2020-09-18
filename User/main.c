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
	* 使用oxygen注释规范
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
const char wData[] = "我不做大哥好多年！";
UINT bw;
char rData[] = "";
UINT br;

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
uint8_t buffer[4096];
uint8_t writebuff[256];
int main(void)
{	
	
	LED_GPIO_Config();
	LED(1);
  /*初始化USART */
  USART_Config();
	
	/* 发送一个字符串 */
	Usart_SentStr( DEBUG_USARTx,"文件系统FATFS移植\n");
	printf("FATFS\n");
	
	FRESULT res; 
	res = f_mount(&fs,"1:",1);
	printf("状态f_mount res=%d",res);
	//初始化文件系统
	if(res == FR_NO_FILESYSTEM)
	{
		f_mkfs("1:",0,0);
		printf("状态f_mkfs res=%d",res);
		//格式化后 先取消挂载 在重新挂载文件系统
		res = f_mount(NULL,"1:",1);
		res = f_mount(&fs,"1:",1);
		printf("n f_mount res=%d",res);
	}
	
	//利用文件系统写入文件
	res = f_open(&fp,"1:这是一个比较长的中文文件名.txt",FA_OPEN_ALWAYS|FA_WRITE|FA_READ);
	printf("\r\n nf_open res = %d",res);
	if(res == FR_OK){
		res = f_write(&fp,wData,sizeof(wData),&bw);
		printf("\r\n nf_write res = %d",res);
		if(res == FR_OK){
			res = f_lseek(&fp,0);//重定位文件指针；
			printf("\r\nn_F_seek = %d",res);
			res = f_read(&fp,rData,f_size(&fp),&br);
			if(res == FR_OK)
				printf("\r\n文件内容：%s",rData);
			res = f_close(&fp);
		}
	}
	
  while(1)
	{	
		
	}	
}
/*********************************************END OF FILE**********************/
