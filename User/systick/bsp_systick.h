#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

//头文件core_cm3.h 中用到了 stm32f10x.h 的定义
//stm32f10x.h 需放在 core_cm3.h 前
#include "stm32f10x.h"
#include "core_cm3.h"

void SysTick_Delay_us(uint32_t us);
void SysTick_Delay_ms(uint32_t ms);




#endif /*__BSP_SYSTICK_H*/
