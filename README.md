# STM quadcopter

This repository contains the code that I am developing teh creation of a quadcopter controller. The idea is to use a nucelo STM32 F401RE as the brain in order to control correctly the speed of the propellers, the acclerometer, the transmission, ecc.

This project is inspired by another STM quadcopter developed some years ago by Brokking [here](http://www.brokking.net/ymfc-32_main.html) the link to its webiste and here the [link](https://www.youtube.com/user/MacPuffdog) to his video tutorials.

Up to now the hardware that I used is:

- 1 x Nucelo STM32 F401RE: [Amazon link](https://www.amazon.com/NUCLEO-F401RE-Nucleo-64-Development-STM32F401RE-connectivity/dp/B07JYBPWN4)
- 1 x STM32 accelerometer shield IKS01A2: [no link]()
- 4 x (ESC + Brushless motor 1000kV + propellers) : [Aliexpress link](https://it.aliexpress.com/item/4000443619541.html?spm=a2g0s.9042311.0.0.27424c4dM7aEG2)
- 1 x  Battery connector male/female - XT60 : [Aliexpress link](https://it.aliexpress.com/item/33004745121.html?spm=a2g0s.9042311.0.0.27424c4dGhvzAx)
- 1 x lipo battery - 2200 mAh - 11.1V - 3S - 30C : [Aliexpress link](https://it.aliexpress.com/item/1005003134034389.html?spm=a2g0s.9042311.0.0.27424c4dGhvzAx)
- 1 x Battery lipo charger: [Aliexpress link](https://it.aliexpress.com/item/4000917057193.html?spm=a2g0s.9042311.0.0.27424c4dGhvzAx)



### TO DO

- Code for controlling easily PWM and brushless motor velocity

- Include accelerometer in code

- General idea of control of each propeller depending on angle/position of propeller

- Build hardware frame (3d print? / wood?)

- Organize well libraries from beginning

  
