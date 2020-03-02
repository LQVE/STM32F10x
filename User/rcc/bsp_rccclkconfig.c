#include "bsp_rccclkconfig.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x){
	ErrorStatus HSEstatus;
	
	//��д ��RCC�Ĵ�����λ�� ���ϵ��ʱ��
	RCC_DeInit();
	
	//ʹ��HSE
	RCC_HSEConfig(RCC_HSE_ON);
	
	/* �ȴ�HSE����������ʱ���� */
	HSEstatus = RCC_WaitForHSEStartUp();
	
	if( HSEstatus==SUCCESS ){
		//ʹ��Ԥȡָ
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//���������ȴ�����
		FLASH_SetLatency(FLASH_Latency_2);
		
		//���������������ߵķ�Ƶ����
		// 1.AHB����ʱ�� HCLK  72M
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		// 2.APB1����ʱ�� PCLK1 ���32M
		RCC_PCLK1Config(RCC_HCLK_Div2);
		// 3.APB2����ʱ�� PCLK2 72M
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//�������໷ Ĭ��PLLCLK = HSE * 9 = 72 MHz   HSE*n ʵ�ֳ�Ƶ
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
		//ʹ��PLL
    RCC_PLLCmd(ENABLE);
		/* Wait till PLL is ready */
	  /*�ȴ�PLL�ȶ�*/
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY==RESET));
			
		/*����ϵͳʱ����Դ ����*/
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		/*�����Ƿ�ɹ�*/
		while(RCC_GetSYSCLKSource()!=0x08);
		
	}
	else{
	/*     ���SHE����ʧ�� ��������Ӵ��������*/
		
	}
}

void MCO_GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode =  GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void HSI_SetSysClk(uint32_t RCC_PLLMul_x){
	__IO uint32_t HSIstatus = 0;
	
	//��д ��RCC�Ĵ�����λ�� ���ϵ��ʱ��
	RCC_DeInit();
	
	//ʹ��HSI
	RCC_HSICmd(ENABLE);
	
	/* �ȴ�HSEI����������ʱ���� */
	HSIstatus = RCC->CR & RCC_CR_HSIRDY;
	
	if( HSIstatus==RCC_CR_HSIRDY ){
		//ʹ��Ԥȡָ
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//���������ȴ�����
		FLASH_SetLatency(FLASH_Latency_2);
		
		//���������������ߵķ�Ƶ����
		// 1.AHB����ʱ�� HCLK  72M
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		// 2.APB1����ʱ�� PCLK1 ���32M
		RCC_PCLK1Config(RCC_HCLK_Div2);
		// 3.APB2����ʱ�� PCLK2 72M
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//�������໷ Ĭ��PLLCLK = HSE * 9 = 72 MHz   HSE*n ʵ�ֳ�Ƶ
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x);
		//ʹ��PLL
    RCC_PLLCmd(ENABLE);
		/* Wait till PLL is ready */
	  /*�ȴ�PLL�ȶ�*/
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY==RESET));
			
		/*����ϵͳʱ����Դ ����*/
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		/*�����Ƿ�ɹ�*/
		while(RCC_GetSYSCLKSource()!=0x08);
		
	}
	else{
	/*     ���SHI����ʧ�� ��������Ӵ��������*/
		
	}
}
