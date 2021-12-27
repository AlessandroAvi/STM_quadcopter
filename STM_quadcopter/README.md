# STM quadcopter

This repo contains the code developed for the flight controller. In this README.md file the explanation of the general idea of the code can be found.


## Explanation of the motors

The quadcopter is equipped with 4 brushless motors of 1000 KV. These are mopre than enough for making the frame lift and fly the vehicle. For the control of the motors speed a PWM signal is required. In this project it has been decided to not use directly a receiver for the control of the PWM, but rather generate the signal from the microcontroller depenging on the command received. From the datasheet is specified that the motors require a PWM signal at 50-60 Hz and the PWM signal should change in between the values of 1 ms for lowest speed and 2 ms for highest speed. If the motors are connected to a new device for the first time is good practice to teach them the throttle ranege that is going to be used. For doing this follow the [instructions](https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Docs/datasheet_ESC.pdf) at page 3. In this project the source clock is of 84 MHz, the Timer 3 is used for the PWM signal with, prescaler = 70-1, ARR=20000-1 wich creates a PWM signal at 60 Hz. This set up allows me to have a resolution in between 1 ms and 2 ms of 1200 steps. 



## Explanation of MPU6050 

[Useful video tutorial](https://www.youtube.com/watch?v=RZd6XDx5VXo&t=0s)

The quadcopter is equipped with a MPU6050 board cwhich contains a gyroscope and an acceelrometer. The usage of these 2 sensors is more than enought for having a precise estimation of the pitch and roll angles that allows the drone to balance itself. In the code two methods of sensor fusion are develoepd, which are a bsic complementary filtering and a kalmann filter. 

The sensor fusion is required because the sensors taken alone are not reliable and subject to specific problems. The accelerometer is very sensible to noise and its values can be used for the computation of an angle only in the case the system is still with low vibrations. An accelerometer is reliable at low frequencies. On the other hand the gyroscope is able to give a precise measure of the angular rate, this means that in order to obtain an angle an integration is required. Since the raw measure is subject to noise and bias, the integration of the raw data will mose ptobably output an angle that is also subject to drift. The gyroscope is reliable at high frequencies. 

In order to get the best of both worlds it's a good idea to fuse the measuraments with eother a kalmann filter or a complementary filter. 

### Complementary filter

[Useful video tutorial](https://www.youtube.com/watch?v=BUW2OdAtzBw)

### Kalmann filter

[Useful video tutorial](https://www.youtube.com/watch?v=hQUkiC5o0JI)


### Explanation of NRF24 tx/rx data streaming



### Explanation of FPV camera



