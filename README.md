# jalouOS
JalouOS is a little script running on a ESP8266 microcontroller. 
It has basicly two tasks: 
* controlling a NEMA-17 stepper driver 
* measuring the room temperature
* (sending current ip address to raspberry pi after boot)

JalouOS provides two endpoints: 
* POST / for do rotations
* GET /temperature for measure and return temperaure

## Hardware ToDO
* motor
* motor driver
* 433mhz funk 
* power outlet
* temperature 


## Wiring
ToDO


//powering the motor / motor driver using a relay would obviously make way more sense, but I wanted to learn how to use a 433mhz transmitter, so I realised powering the motor by controlling a power outlet with a 433mhz transmitter.

