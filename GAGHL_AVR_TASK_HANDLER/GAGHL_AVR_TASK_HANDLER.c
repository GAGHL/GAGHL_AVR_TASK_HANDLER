/*
 * GAGHL_AVR_TASK_HANDLER.c
 *
 * Created: 9/21/2025 2:47:30 PM
 *  Author: GAGHL
 */ 

#include "GAGHL_AVR_TASK_HANDLER.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

#ifndef F_CPU
	#define F_CPU 8000000UL
#endif

volatile uint32_t t_1ms = 0;

static inline void timer0_init(void) {
	#if defined(TCCR0A)
		// Timer0: CTC mode, prescaler = 64
		TCCR0A = (1 << WGM01);
		TCCR0B = ((1 << CS01) | (1 << CS00));
				
		#if F_CPU == 8000000UL
			OCR0A = 124; // 1ms tick: 8MHz  / 64 / 125 = 1ms
		#elif F_CPU == 16000000UL
			OCR0A = 249; // 1ms tick: 16MHz / 64 / 250 = 1ms
		#else
			#error "Unsupported F_CPU for 1ms Tick!"
		#endif
				
		TIMSK0 |= (1 << OCIE0A); // Enable Timer0 CTC Interrupt
	#elif defined(TCCR0)
		// Timer0: CTC mode, prescaler = 64
		TCCR0 = ((1 << WGM01) | (1 << CS01) | (1 << CS00));
				
		#if F_CPU == 8000000UL
			OCR0 = 124; // 1ms tick: 8MHz  / 64 / 125 = 1ms
		#elif F_CPU == 16000000UL
			OCR0 = 249; // 1ms tick: 16MHz / 64 / 250 = 1ms
		#else
			#error "Unsupported F_CPU for 1ms Tick!"
		#endif
				
		TIMSK |= (1 << OCIE0); // Enable Timer0 CTC Interrupt
	#endif
}

static inline void timer1_init(void) {
	#if defined(TCCR1B)
		// Timer1: CTC mode, prescaler = 64
		TCCR1A = 0x00;
		TCCR1B = ((1 << WGM12) | (1 << CS11) | (1 << CS10));
				
		#if F_CPU == 8000000UL
			OCR1A = 124; // 1ms tick: 8MHz  / 64 / 125 = 1ms
		#elif F_CPU == 16000000UL
			OCR1A = 249; // 1ms tick: 16MHz / 64 / 250 = 1ms
		#else
			#error "Unsupported F_CPU for 1ms Tick!"
		#endif
				
		#if defined(TIMSK1)
			TIMSK1 |= (1 << OCIE1A); // Enable Timer1 CTC Interrupt
		#elif defined(TIMSK)	
			TIMSK |= (1 << OCIE1A); // Enable Timer1 CTC Interrupt
		#endif
	#endif
}

static inline void timer2_init(void) {
	#if defined(TCCR2B)
		// Timer2: CTC mode, prescaler = 64
		TCCR2A = (1 << WGM21);
		TCCR2B = (1 << CS22);
				
		#if F_CPU == 8000000UL
			OCR2A = 124; // 1ms tick: 8MHz  / 64 / 125 = 1ms
		#elif F_CPU == 16000000UL
			OCR2A = 249; // 1ms tick: 16MHz / 64 / 250 = 1ms
		#else
			#error "Unsupported F_CPU for 1ms Tick!"
		#endif
				
		TIMSK2 |= (1 << OCIE2A); // Enable Timer2 CTC Interrupt
	#elif defined(TCCR2)
		// Timer2: CTC mode, prescaler = 64
		TCCR2 = ((1 << WGM21) | (1 << CS22));
				
		#if F_CPU == 8000000UL
			OCR2 = 124; // 1ms tick: 8MHz  / 64 / 125 = 1ms
		#elif F_CPU == 16000000UL
			OCR2 = 249; // 1ms tick: 16MHz / 64 / 250 = 1ms
		#else
			#error "Unsupported F_CPU for 1ms Tick!"
		#endif
				
		TIMSK |= (1 << OCIE2); // Enable Timer2 CTC Interrupt
	#endif
}

static inline void timer3_init(void) {
	#ifdef TCCR3B
		// Timer3: CTC mode, prescaler = 64
		TCCR3A = 0x00;
		TCCR3B = ((1 << WGM32) | (1 << CS31) | (1 << CS30));
			
		#if F_CPU == 8000000UL
			OCR3A = 124; // 1ms tick: 8MHz  / 64 / 125 = 1ms
		#elif F_CPU == 16000000UL
			OCR3A = 249; // 1ms tick: 16MHz / 64 / 250 = 1ms
		#else
			#error "Unsupported F_CPU for 1ms Tick!"
		#endif
			
		TIMSK3 |= (1 << OCIE3A); // Enable Timer3 CTC Interrupt
	#endif
}

static inline void timer4_init(void) {
	#ifdef TCCR4B
		// Timer4: CTC mode, prescaler = 64
		TCCR4A = 0x00;
		TCCR4B = ((1 << WGM42) | (1 << CS41) | (1 << CS40));
			
		#if F_CPU == 8000000UL
			OCR4A = 124; // 1ms tick: 8MHz  / 64 / 125 = 1ms
		#elif F_CPU == 16000000UL
			OCR4A = 249; // 1ms tick: 16MHz / 64 / 250 = 1ms
		#else
			#error "Unsupported F_CPU for 1ms Tick!"
		#endif
			
		TIMSK4 |= (1 << OCIE4A); // Enable Timer4 CTC Interrupt
	#endif
}

void ticktimer_init(ticktimer_t ticktimer){
	
	cli();
	
	switch(ticktimer){
		
		case TIMER0:
			timer0_init();
		break;
		
		case TIMER1:
			timer1_init();
		break;
		
		case TIMER2:
			timer2_init();
		break;
		
		case TIMER3:
			timer3_init();
		break;
		
		case TIMER4:
			timer4_init();
		break;
		
	}
	
	sei();
}

#if defined(TIMER0_COMPA_vect)
	ISR(TIMER0_COMPA_vect) {
		t_1ms++;
	}
#elif defined(TIMER0_COMP_vect)
	ISR(TIMER0_COMP_vect) {
		t_1ms++;
	}
#endif

#if defined(TIMER1_COMPA_vect)
	ISR(TIMER1_COMPA_vect) {
		t_1ms++;
	}
#endif

#if defined(TIMER2_COMPA_vect)
	ISR(TIMER2_COMPA_vect) {
		t_1ms++;
	}
#elif defined(TIMER2_COMP_vect)
	ISR(TIMER2_COMP_vect) {
		t_1ms++;
	}
#endif

#if defined(TIMER3_COMPA_vect)
	ISR(TIMER3_COMPA_vect) {
		t_1ms++;
	}
#endif

#if defined(TIMER4_COMPA_vect)
	ISR(TIMER4_COMPA_vect) {
		t_1ms++;
	}
#endif


uint32_t timer_gettick(void) {
	uint32_t tick;
	
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { tick = t_1ms; }
	
	return tick;
}
