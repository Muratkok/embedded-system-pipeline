/*
 * system_talks.c
 *
 *  Created on: Jan 24, 2026
 *      Author: murad
 */
#include "main.h"
#include "cmsis_os2.h"
#include "system_talks.h"
#include "imu_talks.h"
#include "iwdg_service.h"


#ifdef IWDG_ENABLE

TaskType_t taskType;
// Monitor task handle
osThreadId_t systemMonitorTaskHandle;

// Task health flags
static osEventFlagsId_t systemEventFlags;

// Notify callback
void SystemTaskNotify(TaskType_t taskType)
{
    switch(taskType) {
        case TASK_IMU:
        	osEventFlagsSet(systemEventFlags, EVENTFLAG_IMU);
            break;
        case TASK_COMM:
        	osEventFlagsSet(systemEventFlags, EVENTFLAG_COMM);
            break;
        default:
            break;
    }
}

// Monitor task
static void SystemMonitorTask(void *arg)
{
    for(;;)
    {
        uint32_t flags = osEventFlagsWait(systemEventFlags, EVENTFLAG_IMU | EVENTFLAG_COMM,
        								 osFlagsWaitAll | osFlagsNoClear, osKernelGetTickFreq());
        if ((flags & (EVENTFLAG_IMU | EVENTFLAG_COMM)) == (EVENTFLAG_IMU | EVENTFLAG_COMM))
        {
        	//clear flags
        	osEventFlagsClear(systemEventFlags, EVENTFLAG_IMU | EVENTFLAG_COMM);
        	FeedWatchdog();
		}
    }
}

void SystemTalks_Init(void)
{
    const osThreadAttr_t monitorTaskAttr = {
        .name = "SystemMonitor",
        .priority = osPriorityNormal,
        .stack_size = 512
    };
    WatchDogInit();
    systemEventFlags = osEventFlagsNew(NULL);
    systemMonitorTaskHandle = osThreadNew(SystemMonitorTask, NULL, &monitorTaskAttr);
}
#endif
