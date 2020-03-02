#include "bsp_rccclkconfig.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x){
	ErrorStatus HSEstatus;
	
	//重写 把RCC寄存器复位成 刚上电的时候
	RCC_DeInit();
	
	//使能HSE
	RCC_HSEConfig(RCC_HSE_ON);
	
	/* 等待HSE就绪并做超时处理 */
	HSEstatus = RCC_WaitForHSEStartUp();
	
	if( HSEstatus==SUCCESS ){
		//使能预取指
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//设置两个等待周期
		FLASH_SetLatency(FLASH_Latency_2);
		
		//以下配置三个总线的分频因子
		// 1.AHB总线时钟 HCLK  72M
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		// 2.APB1总线时钟 PCLK1 最大32M
		RCC_PCLK1Config(RCC_HCLK_Div2);
		// 3.APB2总线时钟 PCLK2 72M
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//配置锁相环 默认PLLCLK = HSE * 9 = 72 MHz   HSE*n 实现超频
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
		//使能PLL
    RCC_PLLCmd(ENABLE);
		/* Wait till PLL is ready */
	  /*等待PLL稳定*/
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY==RESET));
			
		/*配置系统时钟来源 三个*/
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		/*配置是否成功*/
		while(RCC_GetSYSCLKSource()!=0x08);
		
	}
	else{
	/*     如果SHE启动失败 在这里添加错误处理代码*/
		
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
	
	//重写 把RCC寄存器复位成 刚上电的时候
	RCC_DeInit();
	
	//使能HSI
	RCC_HSICmd(ENABLE);
	
	/* 等待HSEI就绪并做超时处理 */
	HSIstatus = RCC->CR & RCC_CR_HSIRDY;
	
	if( HSIstatus==RCC_CR_HSIRDY ){
		//使能预取指
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
		//设置两个等待周期
		FLASH_SetLatency(FLASH_Latency_2);
		
		//以下配置三个总线的分频因子
		// 1.AHB总线时钟 HCLK  72M
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		// 2.APB1总线时钟 PCLK1 最大32M
		RCC_PCLK1Config(RCC_HCLK_Div2);
		// 3.APB2总线时钟 PCLK2 72M
		RCC_PCLK2Config(RCC_HCLK_Div1);
		
		//配置锁相环 默认PLLCLK = HSE * 9 = 72 MHz   HSE*n 实现超频
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x);
		//使能PLL
    RCC_PLLCmd(ENABLE);
		/* Wait till PLL is ready */
	  /*等待PLL稳定*/
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY==RESET));
			
		/*配置系统时钟来源 三个*/
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		/*配置是否成功*/
		while(RCC_GetSYSCLKSource()!=0x08);
		
	}
	else{
	/*     如果SHI启动失败 在这里添加错误处理代码*/
		
	}
}
