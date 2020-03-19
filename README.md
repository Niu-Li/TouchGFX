## 简介
基于STM32F746开发TouchGFX


## 开发平台
硬件平台：STM32F746 Discovery Kit  
开发环境：MDK V5.28  
工程配置：STM32CubeMX V5.6  
界面设计：TouchGFX V4.13  
操作系统：RT-Thread Nano V3.1.3  


## 准备内容
1. STM32CubeMX版本不能低于V5.5，并且安装下载HAL库和TouchGFX包
2. TouchGFX必须升级到V4.13.0


## 配置功能
| **类型** | **状态** | **备注** |  
| :------: | :------: | :------: |
|   GPIO   |   开启   |   配置自定义引脚  |
|   CRC    |   开启   |    TouchGFX需求   |
|   DMA2D  |   开启   |    用于LCD显示    |
|   LTDC   |   开启   |     LCD控制       |
|   FMC    |   开启   |     存储扩展      |
|   SDRAM  |   开启   |    用于TouchGFX   |
|   TIM    |   TIM6   |    HAL系统时钟    |


## FreeRTOS任务
| **任务名称** | **堆栈大小** | **优先级** | **备注** |   
|   :-------:  |   :------:    |  :------:  |  :------: |
|      main    |   1024 * 4    | RT_THREAD_PRIORITY_MAX / 3 | TouchGFX |  
|      LED     |      128      |     8      |  LD1闪烁  |  
|     tidle    | IDLE_THREAD_STACK_SIZE | RT_THREAD_PRIORITY_MAX - 1 | 空闲线程 |  


## 注意
> **用户在STM32CubeMX生成的文件中添加代码要写在对应的`BEGIN END`行之间，防止重新生成代码后被清除掉**