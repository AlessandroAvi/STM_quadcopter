# STM quadcopter

This repository contains the code that I am developing for the creation of a quadcopter controller. The idea is to use a nucleo STM32 F401RE as the drone controller in order to control correctly each ESC, the accelerometer/gyre and the transmission between user and STM.

This project is inspired by another STM quadcopter developed some years ago by Brokking [here](http://www.brokking.net/ymfc-32_main.html) the link to its webiste and [here](https://www.youtube.com/user/MacPuffdog) the link to his video tutorials.

# BOM

| **COMPONENT**           | **MODEL**                    | **N OF PIECES** | **COST €**| **LINK** |
| ----------------------- |:----------------------------:|:---------------:|:---------:| --------:|
| Microcontroller         | Nucelo STM32 F401RE          | 1               | 11.42     | [here](https://eu.mouser.com/ProductDetail/stmicroelectronics/nucleo-f401re/?qs=fK8dlpkaUMvGeToFJ6rzdA==&countrycode=DE&currencycode=EUR)
| Gyroscope/IMU           | MPU 6050                     | 1               | 2.70      | [here](https://www.ebay.it/itm/253105882143)
| ESC + motor + propeller | 10000 kV - A2212             | 4               | 26.23     | [here](https://it.aliexpress.com/item/4000443619541.html?spm=a2g0s.9042311.0.0.27424c4d62Gi67)
| Battery connector       | XT 60 male/female            | 1               | 2.42      | [here](https://it.aliexpress.com/item/33004745121.html?spm=a2g0s.9042311.0.0.27424c4dqASuNE)
| Lipo Battery            | 2200 mAh - 11.1 V - 3S - 30C | 1               | 20.99     | [here](https://www.amazon.it/gp/product/B08H861N2P/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)
| Battery charger         | 3S - B3 Pro                  | 1               | 4.15      | [here](https://it.aliexpress.com/item/4000917057193.html?spm=a2g0s.9042311.0.0.27424c4dGhvzAx)
| Bluetooth receiver      | HC-05                        | 1               | 3.05      | [here](https://it.aliexpress.com/item/1005001636656116.html?spm=a2g0s.9042311.0.0.27424c4d7co4l5)

Total cost up to now: 70.96 €

Just for initial prototyping I am controlling the drone actions with bluetooth. I am using an HC-05 bluetooth device connected to the STM and I send the control from an adroid app on my phone (arduino bluetooth controller). The app allows me to map to each button on the joystick a specific character.

# TO DO

- Include accelerometer in code
- Implement PID control to maintain the one axis prototype leveled even with perturbations
- Implement I2C communication for the gyro/IMU
- Implement computation of angle from gyro data/ signal processing
- Find a compatible/low cost/small radio controller(?) for future finished project ( NRF24L01 ?)
- Migrate all the code and project to a STM32 BluePill (STM32 F103) + custom PCB
- Create a controller with another STM32 BluePill + NRF24L01 (with antenna) + 2 batteries 18650 + 2 joysticks + custom PCB 

Future idea is to take the entire project and migrate it to a smaller microcontroller, for example the STM bluepill.

## COMPONENTS FOR FUTURE IMPLEMENTATION

| **COMPONENT**           | **MODEL**                    | **N OF PIECES** | **COST €**| **LINK** |
| ----------------------- |:----------------------------:|:---------------:|:---------:| --------:|
| STM blackpill           | STM32 F411                   | 2               | 6.68x2    | [here](https://it.aliexpress.com/item/32792513237.html?spm=a2g0s.9042311.0.0.74a34c4dBViBGv)
| ST link                 | -                            | 1               | 3.45      | [here](https://it.aliexpress.com/item/32792513237.html?spm=a2g0s.9042311.0.0.74a34c4dBViBGv)
| GPS                     | ??                           | 1               | ??        | [no link]()
| NRF24 tx + antenna      | NRF24L01                     | 2               | 1.85 x 2  | [here](https://it.aliexpress.com/item/32272725011.html?spm=a2g0s.9042311.0.0.74a34c4dBViBGv)
| FPV camera              | -                            | 1               | -         | [no link]()
| Display                 | TFT display screen 480x320   | 1               | 22.25     | [here](https://www.ebay.it/itm/253747582718)
| Joystick                | arduino joystick analog      | 2               | 0.52x2    | [here](https://it.aliexpress.com/item/32263199828.html?spm=a2g0s.9042311.0.0.74a34c4dBViBGv)
| PCB for tx cntrl        | -                            | 1               | -         | [no link]()
| PCB for flight cntrl    | -                            | 1               | -         | [no link]()
| Battery holder          | -                            | 1               | -         | [no link]()


# SITUATION UP TO NOW

<img src="https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Images/OneAxisPrototype1.jpg" width=70% height=70%>

<img src="https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Images/OneAxisPrototype2.jpg" width=70% height=70%>

<img src="https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Images/OneAxisPrototype.gif" width=70% height=70%>