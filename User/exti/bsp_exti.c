#include "bsp_exti.h"

/*
1.��ʼ��Ҫ���ӵ�EXTI��GPIO
2.��ʼ��EXTI���ڲ����ж�/���¼�
3.��ʼ��NVIC.���ڴ����ж�
4.��д�жϷ����� stm32f10x_it.c
5.main����
*/

static void EXTI_NVIC_Config(void){/*�˺������ڳ�ʼ��NVIC*/
	NVIC_InitTypeDef NVIC_InitStruct;
	//���ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//�����ж�Դ
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn; //EXTI9_5_IRQn,EXTI15_10_IRQn 
	//���������ȼ�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	//���������ȼ�
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	//ʹ�� �����ж�
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
	
	//�����ж�Դ
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn; //EXTI9_5_IRQn,EXTI15_10_IRQn 
	
	NVIC_Init(&NVIC_InitStruct);
}


void EXTI_Config(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
	//�����ж����ȼ�
	EXTI_NVIC_Config();
	//��ʼ��GPIO
	
	GPIO_InitStruct.GPIO_Pin = KEY1_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY1_INT_GPIO_PORT,&GPIO_InitStruct);	
	
	GPIO_InitStruct.GPIO_Pin = KEY2_INT_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY2_INT_GPIO_PORT,&GPIO_InitStruct);
	
	//��ʼ��EXTI  Selects the GPIO pin used as EXTI Line.
	//��EXTI��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource13);
	//��ʼ��EXTI�ṹ��
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
