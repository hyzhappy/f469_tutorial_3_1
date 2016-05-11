/*ѧϰ��ζ�ȡһ��������״̬��
 * */


#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f4xx_hal.h"

//��Ȼ��ҪSysTick������ʱ����
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
	//����A0Ϊ����ģʽ
	GPIO_InitTypeDef GPIO_InitStructure;
	//����ģʽ
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pin = GPIO_PIN_0;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pin = GPIO_PIN_6;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
	//��Ϩ��LED
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_6, GPIO_PIN_SET);
	while (1)
    {
		//��ȡA0��״̬�ǲ��Ǹߵ�ƽ
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
		{
			//���A0�Ǹߵ�ƽ������ʱ20ms
			HAL_Delay(20);
			//A0���Ǹߵ�ƽ�Ļ����Ϳ���ȷ����ť��ȷ������
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
			{
				//��������˾ͷ�תLED��״̬��
				HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
				//A0һֱΪ�ߵ�ƽ�Ļ����͵ȴ���ֱ��A0Ϊ�͵�ƽΪֹ���ȴ������ͷţ�
				while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET);

			}
		}
    }

}
