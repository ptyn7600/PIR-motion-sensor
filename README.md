# PIR Motion Sensor with Arduino
This is a class mini project at Miami University to introduce to other classmates about one chip that they can use in their further final project.


## Introduction
Passive Infrared (PIR) Motion Sensor is commonly used in many applications, such as automatic doors, security alarm system, etc. This project uses motion sensor HC-SR501 and interface it with the Atmega328P on the Ardunio. The code is in C language, and avr-gcc toolchain is used to compile the code. 

## Table of Content
* [How The HC-SR501 works](#how-the-hc-sr501-works)
* [Parts used in the project](#parts-used-in-the-project)
* [Datasheet](#datasheet)
* 

## How The HC-SR501 works
HC-SR501 works based on sensing the infared radiation from the objects. Any object that has a temperature above absolute zero kelvin will emit the infared radition. Therefore, HC-SR501 works with most objects in our life. HC-SR501 has two parts: the Fresnel lens and the pyroelectric sensor. <br/>
<p align="center">
  <img 
    width="300"
    src="Images/PIR-motion.jpg"
  >
</p>
The Fresnel lens help to focus the infared radiation into the pyroelectric sensor. If we look closer, the pyroelectric sensor has two rectangle infared sensor electrodes. One will produce the positive output voltage and one will produce the negative output voltage. Those two electrodes are wired up so that they will give the difference between two output voltages. Using two electrodes instead of one because we want to track the change in the radiation level, not the ambient level. <br/><br/>
<p align="center">
  <img 
    width="300"
    src="Images/Pyroelectric-Sensor.gif"
  >
</p>

## Parts used in the project
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

## Characterization the Sensor

## Coding 
Here is the commnad line that you can run to execute the code. Note: I have 13 as my COM for my arduino USB port.
```
$ python compile_script.py 13
```

## Contributor
* [Tra Yen Nhu Phan](https://github.com/ptyn7600)
