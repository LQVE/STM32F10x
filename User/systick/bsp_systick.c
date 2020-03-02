#include "bsp_systick.h"

#if 0
static __INLINE uint32_t SysTick_Config(uint32_t ticks)
{ 
	//tick ��ֵ�Ƿ����2^24
  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */
  //��ʼ��reload�Ĵ�����ֵ                                                      
  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
	//�������ȼ�,��λȫд1 ���ȼ����
  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M3 System Interrupts */
	//��ʼ��count��ֵΪ0
  SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
	
	//����ʱ��Ϊ72Mhz
	//ʹ���ж�
	//ʹ��systick
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
