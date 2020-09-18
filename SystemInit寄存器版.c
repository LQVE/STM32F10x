

static void SetSysClockTo72(void)
{
  __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/    
  /* Enable HSE */   //操作 CR 寄存器 16位 使能HSE  
  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
  /* Wait till HSE is ready and if Time out is reached exit */
  /*等待HSE就绪,并做超时处理*/
  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }  

//如果HSE启动成功,程序则继续往下执行
  if (HSEStatus == (uint32_t)0x01)
  {
    /* Enable Prefetch Buffer */
	/*闪存编程 使能预取值*/
    FLASH->ACR |= FLASH_ACR_PRFTBE;

    /* Flash 2 wait state */
	/* 等待两个时钟周期*/
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

    /* HCLK = SYSCLK=72M */
    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
    /* PCLK2 = HCLK=72M */
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    
    /* PCLK1 = HCLK =36M*/
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

   
    /*  PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
	/*改变锁相环倍频因子,可以实现超频*/
	/* 锁相环配置*/
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                        RCC_CFGR_PLLMULL));
    RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
    /* Enable PLL */
	/*配置CR使能锁相环*/
    RCC->CR |= RCC_CR_PLLON;

    /* Wait till PLL is ready */
	/*等待PLL稳定*/
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
    
    /* Select PLL as system clock source */
	/*选择PLL时钟作为系统时钟*/
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

    /* Wait till PLL is used as system clock source */
	/*等待PLLCLK切换为系统时钟*/
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
    {
    }
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock 
         configuration. User can add here some code to deal with this error */
	/*如果HSE启动失败 用户可以在这里添加处理错误的代码*/
  }
}