#include "stm32f10x.h"
//#include "string.h"
#include "bsp_led.h"
//#include "bsp_key.h"
//#include "bsp_rccclkconfig.h"
//#include "bsp_exti.h"
#include "bsp_systick.h"
//#include "bsp_usart.h"
//#include "bsp_dma_mtm.h"
#include "bsp_dma_mtp.h"

void LED_PMD(void){
		LED_R(ON);
		SysTick_Delay_ms(150);
		LED_R(OFF);
		SysTick_Delay_ms(150);
		LED_G(ON);
		SysTick_Delay_ms(150);
		LED_G(OFF);
		SysTick_Delay_ms(150);
		LED_B(ON);
		SysTick_Delay_ms(150);
		LED_B(OFF);
		SysTick_Delay_ms(150);
}

extern uint8_t SendBuff[SENDBUFF_SIZE];


int main(void){
	
	LED_GPIO_Config();
	LED(OFF);
	USART_Config();
  USARTx_DMA_Config();
	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
	
	for(uint16_t i=0;i<SENDBUFF_SIZE;i++){
		SendBuff[i] = 'P';
	}

	while(1){
		LED_PMD();
	}
  

	}
