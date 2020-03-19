## 简介
基于STM32F746使用FreeRTOS开发TouchGFX，学习图形界面设计，使用STM32CubeMX配置FreeRTOS和TouchGFX。


## 开发平台
硬件平台：STM32F746 Discovery Kit  
开发环境：MDK V5.28  
工程配置：STM32CubeMX V5.6  
界面设计：TouchGFX V4.13  
操作系统：FreeRTOS V9.0.0  


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
|  defaultTask |     4 * 512     | osPriorityNormal| TouchGFX运行 |  
|   userTask   |     4 * 128     | osPriorityNormal|    LD1闪烁   |  


## 注意
> **用户在STM32CubeMX生成的文件中添加代码要写在对应的`BEGIN END`行之间，防止重新生成代码后被清除掉**