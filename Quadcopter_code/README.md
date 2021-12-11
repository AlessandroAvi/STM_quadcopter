# Quadcopter code

This file contains informations about the code developed for teh flight controller.

This is the pin table for the STM32 blackpill F411CEU

| **STM PIN**             |**FLIGHT CONTROLLER ROLE**| **DEVICE PIN**       | 
| ----------------------- |:------------------------:| -------------------- |
| PA2                     | USART 2 TX               | PC USB               | 
| PA3                     | USART 2 RX               | PC USB               | 
| PA6                     | TIM3 CH1 - PWM - FR fan  | FR ESC white cable   | 
| PA7                     | TIM3 CH2 - PWM - FL fan  | FL ESC white cable   | 
| PB0                     | TIM3 CH3 - PWM - RR fan  | RR ESC white cable   | 
| PB1                     | TIM3 CH4 - PWM - RL fan  | RL ESC white cable   | 
| PA11                    | USART 6 TX               | HC-05 RX pin         | 
| PA12                    | USART 6 RX               | HC-05 TX pin         | 
| GND                     | HC-05 GND                | HC-05 GND pin        | 
| 5V                      | HC-05 VDD                | HC-05 VDD pin        | 
| GND                     | 4 ESC GND                | ESC GND - black cable| 
