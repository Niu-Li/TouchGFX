/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-07-24     Tanek        the first version
 * 2018-11-12     Ernest Chen  modify copyright
 */
 
#include <stdint.h>
#include <rthw.h>
#include <rtthread.h>


// Updates the variable SystemCoreClock and must be called 
// whenever the core clock is changed during program execution.
extern void SystemClock_Config(void);

/* SysTick configuration */
static void rt_hw_systick_init(void)
{
#if defined (SOC_SERIES_STM32H7)
    HAL_SYSTICK_Config((HAL_RCCEx_GetD1SysClockFreq()) / RT_TICK_PER_SECOND);
#else
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / RT_TICK_PER_SECOND);
#endif
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)

#define RT_HEAP_SIZE    64  // Total Size : RT_HEAP_SIZE K
static uint8_t rt_heap[RT_HEAP_SIZE * 1024];    
RT_WEAK void *rt_heap_begin_get(void)
{
    return rt_heap;
}

RT_WEAK void *rt_heap_end_get(void)
{
    return (rt_heap + RT_HEAP_SIZE * 1024);
}
#endif

/**
 * This function will initial your board.
 */
RT_WEAK void rt_hw_board_init()
{
    /* HAL_Init() function is called at the beginning of the program */
    HAL_Init();
    
    /* enable interrupt */
    __set_PRIMASK(0);
    /* System clock initialization */
    SystemClock_Config();
    /* disable interrupt */
    __set_PRIMASK(1);
    
    /* System Tick Configuration */
    rt_hw_systick_init();

#if defined(RT_USING_USER_MAIN) && defined(RT_USING_HEAP)
    rt_system_heap_init(rt_heap_begin_get(), rt_heap_end_get());
#endif
    
    /* Call components board initial (use INIT_BOARD_EXPORT()) */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

void SysTick_Handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    
    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}
