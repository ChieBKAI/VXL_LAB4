/*
 * scheduler.c
 *
 *  Created on: Nov 29, 2023
 *      Author: K21
 */

#include "scheduler.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];
unsigned int current_index_task = 0;

unsigned char SCH_Delete_Task(int TASK_INDEX) {
	if (SCH_tasks_G[TASK_INDEX].pTask == 0) {
		return 0;
	} else {
		SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
		SCH_tasks_G[TASK_INDEX].Delay = 0;
		SCH_tasks_G[TASK_INDEX].Period = 0;
		SCH_tasks_G[TASK_INDEX].RunMe = 0;
		SCH_tasks_G[TASK_INDEX].TaskID = 0;
		return 1;
	}
}

void SCH_Init(void) {
	for (int i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_Delete_Task(i);
	}
	current_index_task = 0;
}

unsigned char SCH_Add_Task( void (*pFunction)() , unsigned int DELAY, unsigned int PERIOD) {
	if (current_index_task < SCH_MAX_TASKS) {
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period = PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;
		SCH_tasks_G[current_index_task].TaskID = current_index_task;
		current_index_task++;
		return current_index_task - 1;
	}
	return SCH_MAX_TASKS;
}

void SCH_Update(void) {
	for (int i = 0; i < current_index_task; i++) {
		if (SCH_tasks_G[i].Delay > 0) {
			SCH_tasks_G[i].Delay--;
		}else {
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe += 1;
		}
	}
}

void SCH_Dispatch_Tasks(void) {
	for (int i = 0; i < current_index_task; i++) {
		if (SCH_tasks_G[i].RunMe > 0) {
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();
		}
	}
}

