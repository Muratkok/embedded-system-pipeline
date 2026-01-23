/*
 * system_talks.h
 *
 *  Created on: Jan 24, 2026
 *      Author: murad
 */

#ifndef APP_SYSTEM_TALKS_H_
#define APP_SYSTEM_TALKS_H_

#include "iwdg_service.h"
#include "semphr.h"
#define EVENTFLAG_IMU (1U << 0)
#define EVENTFLAG_COMM (1U << 1)

typedef enum
{
	TASK_IMU,
	TASK_COMM,
	TASK_OTHER
} TaskType_t;

extern TaskType_t taskType;
extern void SystemTalks_Init(void);
extern void SystemTaskNotify(TaskType_t taskType);


#endif /* APP_SYSTEM_TALKS_H_ */
