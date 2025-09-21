<h1 align="center">In the name of GOD</h1>

# GAGHL_AVR_TASK_HANDLER

**A lightweight and portable millisecond tick timer library for AVR microcontrollers**

GAGHL_AVR_TASK_HANDLER is a simple, header-only C library designed to provide a reliable 1ms system tick using AVR hardware timers. It allows you to track time for tasks, implement delays, and create lightweight software timers without relying on an RTOS. The library supports Timer0, Timer1, Timer2 (and optionally Timer3/Timer4 on larger MCUs like ATmega2560) in CTC mode.

## 💡 Browse Online
You can explore this repository in a VS Code-like interface using [this link](https://github1s.com/GAGHL/GAGHL_AVR_TASK_HANDLER).

## 📦 Features

- ✅ 1ms tick generation using hardware timers
- ✅ Compatible with multiple AVR MCUs (ATmega16/32/2560, etc.)
- ✅ Support for Timer0, Timer1, Timer2 (and Timer3/Timer4 if available)
- ✅ Simple task timing functions:
  - Reset a timer
  - Check if a timeout has elapsed
- ✅ Thread-safe tick reading via atomic access
- ✅ Minimal and lightweight, suitable for bare-metal projects


## 📚 API Overview

| Function / Macro     | Parameters                                  | Description                                                          |
| -------------------- | ------------------------------------------- | -------------------------------------------------------------------- |
| `tick_timer_init()`  | `tick_timer_t timer`                        | Initialize a hardware timer to generate 1ms tick                     |
| `timer_gettick()`    | *(void)*                                    | Returns the current tick count (in milliseconds)                     |
| `task_timer_reset()` | `task_tick_t *task_timer`                   | Reset a software timer                                               |
| `is_task_elapsed()`  | `task_tick_t *task_timer, uint32_t timeout` | Returns `true` if the specified timeout has elapsed since last reset |

## 🚀 Getting Started

### 1. Add the files to your project

Copy these files into your AVR project:

- `GAGHL_AVR_TASK_HANDLER.c`
- `GAGHL_AVR_TASK_HANDLER.h`

### 2. Define `F_CPU`

In your project (before including headers), make sure to define CPU frequency:

```c
#define F_CPU 8000000UL  // or 16000000UL
```
### 3.Initialize a timer and use it
```c
#define F_CPU 8000000UL

#include <avr/io.h>
#include "GAGHL_AVR_TASK_HANDLER.h"

task_tick_t toggle_100ms = 0;
task_tick_t toggle_500ms = 1;

int main(void) {
    DDRA = 0x01;
    DDRB = 0x02;
    ticktimer_init(TIMER0);  // Initialize Timer0 for 1ms ticks
    
    task_timer_reset(&toggle_100ms);
    task_timer_reset(&toggle_500ms);
    
    while (1) {
        // Toggle PA0 every 100ms
        if (is_task_elapsed(&toggle_100ms, 100)) {
            PORTA ^= 0x01;
            task_timer_reset(&toggle_100ms);
        }
        
        // Toggle PB1 every 500ms
        if (is_task_elapsed(&toggle_500ms, 500)) {
            PORTB ^= 0x02;
            task_timer_reset(&toggle_500ms);
        }
    }
}

```
---

## 🔧 Requirements

- AVR microcontroller (e.g., ATmega32, ATmega16, ATmega2560)
- Timer3/Timer4 only available on larger MCUs like ATmega2560
- AVR-GCC or any compatible C toolchain

## 🛠️ TODO

- [ ] Configurable tick frequency
- [ ] Low-power mode support
- [ ] Optional 64-bit tick for extremely long uptime
- [ ] Add unit tests or simulation examples (e.g., with simavr or Proteus)



## 🤝 Contributing

Contributions are welcome!  
Whether it's bug fixes, feature suggestions, or improvements — your help is appreciated.

- Fork the repository
- Create a new branch (`git checkout -b feature/my-feature`)
- Commit your changes (`git commit -am 'Add new feature'`)
- Push to the branch (`git push origin feature/my-feature`)
- Open a Pull Request

If you’re using this library in your project, feel free to let me know — I’d love to check it out!

## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0).

You are free to:
- Share — copy and redistribute the material in any medium or format
- Adapt — remix, transform, and build upon the material

Under the following terms:
- **Attribution** — You must give appropriate credit to the author (GAGHL).
- **NonCommercial** — You may not use the material for commercial purposes without explicit permission.

For more information, see the full license: [https://creativecommons.org/licenses/by-nc/4.0/](https://creativecommons.org/licenses/by-nc/4.0/)

© 2025 GAGHL. All rights reserved.

## Author

Developed by [GAGHL](https://github.com/GAGHL)
