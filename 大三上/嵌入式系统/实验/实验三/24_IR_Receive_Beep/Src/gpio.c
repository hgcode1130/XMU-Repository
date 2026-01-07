#include "gpio.h"

void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* 使能所有需要用到的GPIO端口的时钟 */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();

    /* 1. 配置 PF15 为外部中断引脚 (用于红外接收器信号输入) */
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING; // 配置为上升沿和下降沿都触发中断
    GPIO_InitStruct.Pull = GPIO_NOPULL;                 // 无上下拉
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    /* 配置 EXTI 中断线 15_10 */
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 2, 2);
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);


    /* 2. 配置 PG6 为推挽输出引脚 (用于LED状态指示) */
    // 程序启动时，先将LED引脚置于低电平（熄灭状态）
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_RESET);
    
    GPIO_InitStruct.Pin = GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // 推挽输出模式
    GPIO_InitStruct.Pull = GPIO_NOPULL;           // 无上下拉
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // 低速模式即可
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
}