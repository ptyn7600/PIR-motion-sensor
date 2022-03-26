# PIR Motion Sensor with Arduino
This is a class mini project at Miami University to introduce to other classmates about one chip that they can use in their further final project.


## Introduction
Passive Infrared (PIR) Motion Sensor is commonly used in many applications, such as automatic doors, security alarm system, etc. This project uses motion sensor HC-SR501 and interface it with the Atmega328P on the Ardunio. The code is in C language, and avr-gcc toolchain is used to compile the code. 

## Table of Content
* [How The HC-SR501 works](#how-the-hc-sr501-works)
* [Modules used in the project](#modules-used-in-the-project)
* [Datasheet](#datasheet)
* 

## How The HC-SR501 works
HC-SR501 has two parts: the Fresnel sensor and the pyroelectric sensor. (Images/PIR-motion.jpg)
## Modules used in the project
* Arduino Uno 
* An USB cable
* A mini breadboard
* A PIR Motion Sensor HC-SR501
* A LED
* A 220k resistor
* Wires

## Wiring Instruction

## Datasheet
Here is the datasheet of [HC-SR501](PIR-datasheet.pdf)

## Demonstration
This is a demo Youtube video to show how the sensor will work: [PIR Motion Sensor Demo](https://youtu.be/V0tJ8MuLAaM)

## Technologies

## Coding 
Here is the commnad line that you can run to execute the code. Note: I have 13 as my COM for my arduino USB port.
```
$ python compile_script.py 13
```

## Contributor
* [Tra Yen Nhu Phan](https://github.com/ptyn7600)
