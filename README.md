# Build-you-own-weather-station
Workshop documentation on building your own nodeMCU based weatherstation

## Connect hardware on breadboard

<img src="https://github.com/bokse001/Build-you-own-weather-station/blob/master/nodemcu%20weatherstation_bb.jpg" alt="Connecting the hardware">

- DHT pin 1 to 3,3V
- DHT pin 2 to D4
- DHT pin 4 to GND
- Resistor to 3,3V and DHT pin 2

 
## Prepare your laptop for ESP development
1. Install the Arduino.cc IDE software and launch the IDE and allow firewall access
1. File > Preferences, check the “Display line numbers option“
1. Add the URL http://arduino.esp8266.com/stable/package_esp8266com_index.json to the “Addition Boards Manager URLs” field and press the “Ok” button
1. Tools > Boards > Boards Manager, install the ESP8266 platform
1. Sketch > Include Library > Manage Libraries, install the Adafruit sensor and Adafruit Unified Sensor library library
1. Close Arduino IDE
1. (if needed) Install the CP210x USB to UART driver and make sure you reboot your machine afterward (I suffered strange behaviors using the driver without rebooting)
1. After rebooting open the Arduino IDE and select the proper board from Tools->Board->Board ”nodeMCU 1.0 (ESP-12E Module)”



## Test your laptop and nodeMCU setup
- Load the example sketch “blink” into the Arduino IDE
- Try compiling it by pressing the Verify button: 
- When ok:
	- 	Connect the nodeMCU with the USB cable
	- 	Via Tools > Port, check if there is a COMxx port selected
	- 	Upload the sketch by pressing the Upload button: 
	- 	Wait till the sketch is compiled and uploaded
- The blue led on the nodeMCU should now start blinking


## Test to see if the nodeMCU can measure temperature and humidity
- Load the example sketch “DHTtester” into the Arduino IDE
- Try compiling it by pressing the Verify button: 
- When ok:
	- 	Connect the nodeMCU with the USB cable
	- 	Via Tools > Port, check if there is a COMxx port selected
	- 	Upload the sketch by pressing the Upload button: 
	- 	Wait till the sketch is compiled and uploaded
	- 	Open the monitor
- Message with the temperature and humidty should appear within the monitor


## Test to see if the nodeMCU can function as a web server
- Load the example sketch “nodemcu_bmp_web” into the Arduino IDE
- Find the line with the *ssid and change it to the ssid given to you in the workshop
- Find the line with the *password and change it to password given to you in the workshop
- Try compiling it by pressing the Verify button: 
- When ok:
	- 	Connect the nodeMCU with the USB cable
	- 	Via Tools > Port, check if there is a COMxx port selected
	- 	Upload the sketch by pressing the Upload button: 
	- 	Wait till the sketch is compiled and uploaded
	- 	Open the monitor
- A message should be displayed with “IP address: www.xxx.yyy.zzz”
- Now connect your laptop or mobile phone to the same network as the nodeMCU is connected to
- Open the page www.xxx.yyy.zzz, you should be able to see ESP8266 message and a graph


## Advanced Extra: combine the webserver and DHT sensor sketch to display the temperature and humidity from your laptop or mobile phone
- Open both the sketches “nodemcu_bmp_web” and “DHTtester” and find a way to combine the necessary code from DHTtester into the nodemcu_bmp_web examples.
- Do not forget to save it under a new name like “my_weatherstation”


## Testing the weather station
- Load the example sketch, provided to your during the workshop, “iot_innovatos_weerstation” into the Arduino IDE
- Find the line with the *ssid and change it to the ssid given to you in the workshop
- Find the line with the *password and change it to password given to you in the workshop
- Try compiling it by pressing the Verify button: 
- When ok:
	- 	Connect the nodeMCU with the USB cable
	- 	Via Tools > Port, check if there is a COMxx port selected
	- 	Upload the sketch by pressing the Upload button: 
	- 	Wait till the sketch is compiled and uploaded
	- 	Open the monitor
- A message should be displayed with “IP address: www.xxx.yyy.zzz”
- Now connect your laptop or mobile phone to the same network as the nodeMCU is connected to
- Open the page www.xxx.yyy.zzz, you should be able to see the weatherstation temperature and humidty

