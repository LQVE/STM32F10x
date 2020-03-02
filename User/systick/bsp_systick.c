#include "bsp_systick.h"

#if 0
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
	//tick 的值是否大于2^24
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */
  //初始化reload寄存器的值                                                      
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
	//配置优先级,四位全写1 优先级最低
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M3 System Interrupts */
	//初始化count的值为0
  SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
	
	//配置时钟为72Mhz
	//使能中断
	//使能systick
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
                   SysTick_CTRL_TICKINT_Msk   | 
                   SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
  return (0);                                                  /* Function successful */
}

#endif

void SysTick_Delay_us(uint32_t us)
{
	uint32_t i;
	SysTick_Config(72);
	for(i=0;i<us;i++){
		while( !((SysTick->CTRL) & (1<<16)) );
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_ms(uint32_t ms)
{
	uint32_t i;
	SysTick_Config(72000);
	for(i=0;i<ms;i++){
		while( !((SysTick->CTRL) & (1<<16)) );
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
