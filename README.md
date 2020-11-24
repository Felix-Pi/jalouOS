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
* motor ([amazon](https://www.amazon.de/gp/product/B015ST2U5A/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1))
* motor driver L298N ([amazon](https://www.amazon.de/gp/product/B00Q6WPVU0/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1))
* 433mhz funk ([amazon](https://www.amazon.de/gp/product/B071J2Z3YK/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1))
* power outlet([amazon](https://www.amazon.de/Brennenstuhl-Funkschalt-Set-Funksteckdosen-Innenbereich-Kindersicherung/dp/B073W52CS8/ref=sr_1_3?__mk_de_DE=ÅMÅŽÕÑ&crid=3SAK2QT1X6IBC&dchild=1&keywords=brennstuhl+funksteckdosenset&qid=1606205414&sprefix=Brennstuhl+fu%2Celectronics%2C246&sr=8-3))
* temperature ([amazon](https://www.amazon.de/gp/product/B00N1TSSD8/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1))


## Wiring
ToDO


//powering the motor / motor driver using a relay would obviously make way more sense, but I wanted to learn how to use a 433mhz transmitter, so I realised powering the motor by controlling a power outlet with a 433mhz transmitter.

