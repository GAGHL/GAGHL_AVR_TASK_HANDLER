/*
 * GAGHL_AVR_TASK_HANDLER.h
 *
 * Created: 9/21/2025 2:47:45 PM
 *  Author: GAGHL
 */ 


#ifndef GAGHL_AVR_TASK_HANDLER_H_
#define GAGHL_AVR_TASK_HANDLER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>
#include <stdint.h>
#include <stdbool.h>

#define s_to_ms(s)       ((uint32_t)((s) * 1000U))
#define min_to_ms(min)   ((uint32_t)((min) * 60000U))

typedef enum{
	TIMER0,
	TIMER1,
	TIMER2,
#ifdef OCR3A
	TIMER3,
#endif
#ifdef OCR4A
	TIMER4,
#endif
#ifdef OCR5A
	TIMER5
#endif
} tick_timer_t;

extern volatile uint32_t t_1ms;

typedef uint32_t task_tick_t;

uint32_t timer_gettick(void);

void tick_timer_init(tick_timer_t timer);

static inline void task_timer_reset(task_tick_t *task_timer) {
	*task_timer = timer_gettick();
}

static inline bool is_task_elapsed(task_tick_t *task_timer, uint32_t timeout) {
	return ((uint32_t)(timer_gettick() - *task_timer) >= timeout);
}

#endif /* GAGHL_AVR_TASK_HANDLER_H_ */