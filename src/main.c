/*学习如何读取一个按键的状态吧
 * */


#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f4xx_hal.h"

//仍然需要SysTick进行延时操作
void SysTick_Handler()
{
	HAL_IncTick();
}
int
main(int argc, char* argv[])
{

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	HAL_SYSTICK_Config(SystemCoreClock/1000);
	//配置A0为输入模式
	GPIO_InitTypeDef GPIO_InitStructure;
	//输入模式
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	//配置G6为输出模式
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pin = GPIO_PIN_6;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
	//先熄灭LED
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
	while (1)
    {
		//读取A0的状态是不是高电平
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
		{
			//如果A0是高电平，先延时20ms
			HAL_Delay(20);
			//A0还是高电平的话，就可以确定按钮的确按下了
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
			{
				//如果按下了就翻转LED的状态吧
				HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
				//A0一直为高电平的话，就等待，直到A0为低电平为止（等待按键释放）
				while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET);

			}
		}
    }

}
