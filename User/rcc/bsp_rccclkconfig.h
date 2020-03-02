#ifndef __BSP_RCCCLKCONFIG_H

#define __BSP_RCCCLKCONFIG_H


#include "stm32f10x.h"

void HSE_SetSysClk(uint32_t RCC_PLLMul_x);
//声明函数 搞丢分号 出现莫名其妙的error
void MCO_GPIO_Config(void);
void HSI_SetSysClk(uint32_t RCC_PLLMul_x);

#endif /*__BSP_RCCCLKCONFIG_H*/

