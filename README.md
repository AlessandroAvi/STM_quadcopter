# STM quadcopter

STILL WORK IN PROGRESS

This repository contains the code that I am developing for the creation of a quadcopter controller. The idea is to use a nucleo STM32 F401RE as the drone controller in order to control correctly each ESC, the accelerometer/gyre and the transmission between user and STM.

This project is inspired by another STM quadcopter developed some years ago by Brokking [here](http://www.brokking.net/ymfc-32_main.html) the link to its webiste and [here](https://www.youtube.com/user/MacPuffdog) the link to his video tutorials.

# BOM

| **COMPONENT**           | **MODEL**                    | **N OF PIECES** | **COST €**| **LINK** |
| ----------------------- |:----------------------------:|:---------------:|:---------:| --------:|
| Microcontroller         | STM32 F411                   | 1               | 6.68      | [here](https://it.aliexpress.com/item/32792513237.html?spm=a2g0s.9042311.0.0.74a34c4dBViBGv)
| ST link                 | -                            | 1               | 3.45      | [here](https://it.aliexpress.com/item/32792513237.html?spm=a2g0s.9042311.0.0.74a34c4dBViBGv)
| ESC + motor + propeller | 10000 kV - A2212             | 4               | 26.23     | [here](https://it.aliexpress.com/item/4000443619541.html?spm=a2g0s.9042311.0.0.27424c4d62Gi67)
| Battery connector       | XT 60 male/female            | 1               | 2.42      | [here](https://it.aliexpress.com/item/33004745121.html?spm=a2g0s.9042311.0.0.27424c4dqASuNE)
| Lipo Battery            | 2200 mAh - 11.1 V - 3S - 30C | 1               | 20.99     | [here](https://www.amazon.it/gp/product/B08H861N2P/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)
| Battery charger         | 3S - B3 Pro                  | 1               | 4.15      | [here](https://it.aliexpress.com/item/4000917057193.html?spm=a2g0s.9042311.0.0.27424c4dGhvzAx)
| Gyroscope/IMU           | MPU 6050                     | 1               | 2.70      | [here](https://www.ebay.it/itm/253105882143)
| NRF24 tx + antenna      | NRF24L01                     | 1               | 1.85      | [here](https://it.aliexpress.com/item/32272725011.html?spm=a2g0s.9042311.0.0.74a34c4dBViBGv)
| FPV camera              | OV2640 2MP                   | 1               | 4.74      | [here](https://it.aliexpress.com/item/33046344720.html?spm=a2g0s.9042311.0.0.34784c4d8o1aSF)
| Bluetooth receiver      | HC-05                        | 1               | 3.05      | [here](https://it.aliexpress.com/item/1005001636656116.html?spm=a2g0s.9042311.0.0.27424c4d7co4l5)
| GPS                     | GY-NEO6MV2                   | 1               | 2.97      | [here](https://it.aliexpress.com/item/1005001635722164.html?spm=a2g0o.productlist.0.0.2cda6cbasI9OK1&algo_pvid=14b9cbef-8043-4b47-ab6c-e60a8ce52c07&aem_p4p_detail=202112100019011915512198914790005598781&algo_exp_id=14b9cbef-8043-4b47-ab6c-e60a8ce52c07-2&pdp_ext_f=%7B%22sku_id%22%3A%2212000017044837230%22%7D)
| PCB for flight cntrl    | -                            | 1               | -         | [no link]()

Total cost up to now: 79.23 €

Just for initial prototyping I am controlling the drone actions with bluetooth. I am using an HC-05 bluetooth device connected to the STM and I send the control from an adroid app on my phone (arduino bluetooth controller). The app allows me to map to each button on the joystick a specific character. Future implementatios is to use a radio transmitter made with another STM that uses an NRF module.

Tutorials for the complementary filter and kalman filter at [here](https://www.youtube.com/watch?v=BUW2OdAtzBw).
A very nice tool that shows real time signal coming from the COM port [serial oscilloscope](https://x-io.co.uk/serial-oscilloscope/)

# TO DO

- Implement computation of angle from gyro data/ signal processing
- Tune correctly PD/PID
- Migrate all the code and project to a STM32 Blackpill (STM32 F10F411) + custom PCB
- create 3d model of frame + print

Useful link for sensor fusion between gyro and accelerometer with kalman filter 
 [here](https://www.telesens.co/2017/05/02/sensor-fusion-part-3-implementation-of-gyro-accel-sensor-fusion/)


# SITUATION UP TO NOW

<img src="https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Images/OneAxisPrototype1.jpg" width=70% height=70%>

<img src="https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Images/OneAxisPrototype2.jpg" width=70% height=70%>

<img src="https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Images/OneAxisPrototype.gif" width=70% height=70%>

<img src="https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Images/frame_mounted.jpg" width=70% height=70%>

<img src="https://github.com/AlessandroAvi/STM_quadcopter/blob/main/Images/drone.jpg" width=70% height=70%>