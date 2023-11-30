/*
 * scheduler.h
 *
 *  Created on: Nov 29, 2023
 *      Author: K21
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"

#define SCH_MAX_TASKS 40
#define NO_TASK_ID 0

typedef struct {
	// Pointer to the task (must be a 'void (void)' function)
	void (*pTask) (void);
	// Delay (ticks) until the function will (next) be run
	uint32_t Delay;
	// Interval (ticks) between subsequent runs.
	uint32_t Period;
	// Incremented (by scheduler) when task is due to execute
	uint8_t RunMe;
	//This is a hint to solve the question below.
	uint32_t TaskID;
}sTask;


void SCH_Init(void);

unsigned char SCH_Delete_Task(int TASK_INDEX);

unsigned char SCH_Add_Task( void (*pFunction)() , unsigned int DELAY, unsigned int PERIOD);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);


#endif /* INC_SCHEDULER_H_ */
