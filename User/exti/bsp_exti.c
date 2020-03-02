#include "bsp_exti.h"

/*
1.初始化要连接到EXTI的GPIO
2.初始化EXTI用于产生中断/或事件
3.初始化NVIC.用于处理中断
4.编写中断服务函数 stm32f10x_it.c
5.main函数
*/

static void EXTI_NVIC_Config(void){/*此函数用于初始化NVIC*/
	NVIC_InitTypeDef NVIC_InitStruct;
	//优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//配置中断源
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn; //EXTI9_5_IRQn,EXTI15_10_IRQn 
	//配置主优先级
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	//配置子优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	//使能 开总中断
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	//配置中断源
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn; //EXTI9_5_IRQn,EXTI15_10_IRQn 
	
	NVIC_Init(&NVIC_InitStruct);
}


void EXTI_Config(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
	//配置中断优先级
	EXTI_NVIC_Config();
	//初始化GPIO
	
	GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY1_INT_GPIO_PORT,&GPIO_InitStruct);	
	
	GPIO_InitStruct.GPIO_Pin = KEY2_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY2_INT_GPIO_PORT,&GPIO_InitStruct);
	
	//初始化EXTI  Selects the GPIO pin used as EXTI Line.
	//打开EXTI的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
	//初始化EXTI结构体
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_Mode =  EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line = EXTI_Line13;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
}
