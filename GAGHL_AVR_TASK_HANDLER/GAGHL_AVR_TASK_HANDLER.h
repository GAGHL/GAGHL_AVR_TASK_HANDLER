/*
 * GAGHL_AVR_TASK_HANDLER.h
 *
 * Created: 9/21/2025 2:47:45 PM
 *  Author: GAGHL
 */ 


#ifndef GAGHL_AVR_TASK_HANDLER_H_
#define GAGHL_AVR_TASK_HANDLER_H_

#include <stdint.h>
#include <stdbool.h>

#define s_to_ms(s)       ((uint32_t)((s) * 1000U))
#define min_to_ms(min)   ((uint32_t)((min) * 60000U))

typedef enum{
	TIMER0,
	TIMER1,
	TIMER2,
	TIMER3,
	TIMER4
} ticktimer_t;

extern volatile uint32_t t_1ms;

typedef uint32_t task;

void ticktimer_init(ticktimer_t ticktimer);

uint32_t HAL_GetTick(void);

static inline void task_timer_reset(task *timer) {
	*timer = HAL_GetTick();
}

static inline bool is_task_elapsed(task *timer, uint32_t timeout) {
	return ((uint32_t)(HAL_GetTick() - *timer) >= timeout);
}

#endif /* GAGHL_AVR_TASK_HANDLER_H_ */