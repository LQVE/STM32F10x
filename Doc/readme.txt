

/***********************************************************************/
void LED_PMD(void){
		LED_R(ON);
		SysTick_Delay_ms(50);
		LED_R(OFF);
		SysTick_Delay_ms(50);
		LED_G(ON);
		SysTick_Delay_ms(50);
		LED_G(OFF);
		SysTick_Delay_ms(50);
		LED_B(ON);
		SysTick_Delay_ms(50);
		LED_B(OFF);
		SysTick_Delay_ms(50);
}

int main(void){
	LED_GPIO_Config();
	int i=3;
	for(;i>0;i--){
		LED_PMD();


	}
//	//EXTI_Config();
//	
//	while(1){
//		LED_G(ON);
//		SysTick_Delay_ms(1000);
//		LED_G(OFF);
//		SysTick_Delay_ms(1000);
//	}
	
	uint8_t ch;
	USART_Config();
	printf("****************************\n");
	printf("欢迎使用野火STM32开发板\n");
	printf("请输入数字指令1~7\n");
	printf("****************************\n");
	while(1){
	//Usart_SendByte(DEBUG_USARTx,10);
	//Usart_SendHalfWord(DEBUG_USARTx,0x4156);
	//uint8_t a[10] = {12,56,41,78,89,78,75,98,65,78};
	//Usart_SentByteArray(DEBUG_USARTx,a,10);
	//Usart_SentStr(DEBUG_USARTx,"是谁,送你来到我身边,是谁,在敲打我窗\n");
		
		
	/* 勾选 use microLIB*/
  
  //putchar('p');
	//SysTick_Delay_ms(1000);
	 
		
		ch = getchar();
		printf("RECIVE：%c\n",ch);
		switch(ch){
		case('1'):LED_R(ON);SysTick_Delay_ms(300);LED_R(OFF);break;
		case('2'):LED_G(ON);SysTick_Delay_ms(300);LED_G(OFF);break;
		case('3'):LED_B(ON);SysTick_Delay_ms(300);LED_B(OFF);break;
		case('4'):LED_R(ON);LED_G(ON);SysTick_Delay_ms(300);LED_R(OFF);LED_G(OFF);break;
		case('5'):LED_R(ON);LED_B(ON);SysTick_Delay_ms(300);LED_R(OFF);LED_B(OFF);break;
		case('6'):LED_B(ON);LED_G(ON);SysTick_Delay_ms(300);LED_B(OFF);LED_G(OFF);break;
		case('7'):LED_R(ON);LED_G(ON);LED_B(ON);SysTick_Delay_ms(300);LED_R(OFF);LED_G(OFF);LED_B(OFF);break;
		case('8'):
			int i;
			for(i=0;i<10;i++)
			{LED_PMD();}break;
		default:
			printf("****************************\n");
			printf("欢迎使用野火STM32开发板\n");
			printf("请输入数字指令1~7\n");
			printf("****************************\n");
			printf("ch = %c\n",ch);
			break;
	}
}
	}
	
/*************************************************************************************/

#define BUFFER_SIZE                      32


extern const uint32_t aSRC_Const_Buffer[BUFFER_SIZE];
extern uint32_t aDST_Buffer[BUFFER_SIZE];


int main(void){
	uint8_t status = 0;
	LED_GPIO_Config();
	LED(OFF);
	LED(ON);
	SysTick_Delay_ms(500);
	LED(OFF);
	MtM_DMA_Config();
	//检测传输是否完成
	while(DMA_GetFlagStatus(MTM_DMA_FLAG_TC)==RESET)
	//status = Buffercmp(aSRC_Const_Buffer,aDST_Buffer,BUFFER_SIZE);
	if (status==0){
		LED_R(ON);
	}
	else{
		LED_G(ON);
	}
	while(1){

	}
/******************************************************************************************/
