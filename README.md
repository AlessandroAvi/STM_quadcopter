# STM quadcopter

This repository contains the code that I am developing for the creation of a quadcopter controller. The idea is to use a nucleo STM32 F401RE as the drone controller in order to control correctly each ESC, the accelerometer/gyre and the transmission between user and STM.

This project is inspired by another STM quadcopter developed some years ago by Brokking [here](http://www.brokking.net/ymfc-32_main.html) the link to its webiste and [here](https://www.youtube.com/user/MacPuffdog) the link to his video tutorials.

Up to now the hardware that I used is:

- 1 x Nucelo STM32 F401RE: [Amazon link](https://www.amazon.com/NUCLEO-F401RE-Nucleo-64-Development-STM32F401RE-connectivity/dp/B07JYBPWN4)
- 1 x Gyro/IMU sensor, mpu-6050: [Ebay link](https://www.ebay.it/itm/253105882143)
- 4 x (ESC + Brushless motor 1000kV + propellers) : [Aliexpress link](https://it.aliexpress.com/item/4000443619541.html?spm=a2g0s.9042311.0.0.27424c4dM7aEG2)
- 1 x  Battery connector male/female - XT60 : [Aliexpress link](https://it.aliexpress.com/item/33004745121.html?spm=a2g0s.9042311.0.0.27424c4dGhvzAx)
- 1 x lipo battery - 2200 mAh - 11.1V - 3S - 30C : [Aliexpress link](https://it.aliexpress.com/item/1005003134034389.html?spm=a2g0s.9042311.0.0.27424c4dGhvzAx)
- 1 x Battery lipo charger: [Aliexpress link](https://it.aliexpress.com/item/4000917057193.html?spm=a2g0s.9042311.0.0.27424c4dGhvzAx)
- 1 x drone frame f450: [no link]()

Just for initial prototyping I am controlling the drone actions with bluetooth. I am using an HC-05 bluetooth device connected to the STM and I send the control from an adroid app on my phone (arduino bluetooth controller). The app allows me to map to each control on the joystick a specific character that is sent when the button is touched.

### TO DO

- Include accelerometer in code
- Implement PID control to maintain the one axis prototype leveled even with perturbations
- Implement I2C communication for the gyro/IMU
- Implement computation of angle from gyro data/ signal processing
- Find a compatible/low cost/small radio controller(?) for future finished project

Future idea is to take the entire project and migrate it to a smaller microcontroller, for example the STM bluepill.

# SITUATION UP TO NOW

<img src="https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Images/OneAxisPrototype1.jpg" width=70% height=70%>

<img src="https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Images/OneAxisPrototype2.jpg" width=70% height=70%>

<img src="https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Images/OneAxisPrototype.gif" width=70% height=70%>
