#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

//ͷ�ļ�core_cm3.h ���õ��� stm32f10x.h �Ķ���
//stm32f10x.h ����� core_cm3.h ǰ
#include "stm32f10x.h"
#include "core_cm3.h"

void SysTick_Delay_us(uint32_t us);
void SysTick_Delay_ms(uint32_t ms);




#endif /*__BSP_SYSTICK_H*/
