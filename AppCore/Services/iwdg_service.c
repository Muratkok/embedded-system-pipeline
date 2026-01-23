/*
 * iwdg_service.c
 *
 *  Created on: Jan 24, 2026
 *      Author: murad
 */
#include "main.h"

IWDG_HandleTypeDef hiwdg;

void WatchDogInit(void)
{
	  hiwdg.Instance = IWDG;
	  hiwdg.Init.Prescaler = IWDG_PRESCALER_4;
	  hiwdg.Init.Reload = 4095;
	  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
	  {
	    Error_Handler();
	  }
}
void FeedWatchdog(void)
{
	HAL_IWDG_Refresh(&hiwdg);
	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
}
