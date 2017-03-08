# Build-you-own-weather-station
Workshop documentation on building your own nodeMCU based weatherstation

## Connect hardware on breadboard

<img src="https://github.com/bokse001/Build-you-own-weather-station/blob/master/images/nodemcu%20weatherstation_bb.jpg" alt="Connecting the hardware">

- DHT pin 1 to 3,3V
- DHT pin 2 to D4
- DHT pin 4 to GND
- Resistor to 3,3V and DHT pin 2

<img src="https://github.com/bokse001/Build-you-own-weather-station/blob/master/images/IDE.png" alt="Arduino IDE">
 
## Prepare your laptop for ESP development
1. Install the Arduino.cc IDE software and launch the IDE and allow firewall access
1. File > Preferences, check the “Display line numbers option“
1. Add the URL http://arduino.esp8266.com/stable/package_esp8266com_index.json to the “Addition Boards Manager URLs” field and press the “Ok” button
<img src="https://github.com/bokse001/Build-you-own-weather-station/blob/master/images/settings.png" alt="Settings">
1. Tools > Boards > Boards Manager, install the "esp8266" board package
<img src="https://github.com/bokse001/Build-you-own-weather-station/blob/master/images/boards.png" alt="Boards manager">
1. Sketch > Include Library > Manage Libraries, install the "DHT sensor library" and the "Adafruit Unified Sensor library" libraries
<img src="https://github.com/bokse001/Build-you-own-weather-station/blob/master/images/libraries.png" alt="Libraries">
1. Close and re-open Arduino IDE
1. Select the proper board from Tools->Board->Board ”nodeMCU 1.0 (ESP-12E Module)”

When Connectivity to the board does not work:
- Install the CP210x USB to UART driver and make sure you reboot your machine afterward (I suffered strange behaviors using the driver without rebooting) https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
- After rebooting open the Arduino IDE and select the proper board from Tools->Board->Board ”nodeMCU 1.0 (ESP-12E Module)”
<img src="https://github.com/bokse001/Build-you-own-weather-station/blob/master/images/examples.png" alt="Examples">


## Test your laptop and nodeMCU setup
- Load the example sketch “Blink” into the Arduino IDE from File->Examples->01 Basics->Blink
<img src="https://github.com/bokse001/Build-you-own-weather-station/blob/master/images/blink.png" alt="Examples">
- Try compiling it by pressing the Verify button
- When ok, connect the nodeMCU to your laptop:
	- 	Connect the nodeMCU with the USB cable
	- 	Via Tools -> Port, check if the correct COMxx port is selected
	- 	Upload the sketch by pressing the Upload button
	- 	Wait till the sketch is compiled and uploaded
- The blue led on the nodeMCU should now start blinking



## Test to see if the nodeMCU can measure temperature and humidity
- Load the example sketch “DHTtester” into the Arduino IDE from File->Examples->DHT sensor library->DHTtester
- Try compiling it by pressing the Verify button
- When ok:
	- 	Connect the nodeMCU with the USB cable
	- 	Via Tools -> Port, check if the correct COMxx port is selected
	- 	Upload the sketch by pressing the Upload button: 
	- 	Wait till the sketch is compiled and uploaded
	- 	Open the monitor Tools->Serial Monitor
- Message with the temperature and humidty should appear within the monitor


## Test to see if the nodeMCU can function as a web server
- Load the example sketch “AdvancedWebServer” into the Arduino IDE from File->Examples->ESP8266WebServer
- Find the line with the *ssid and change it to the ssid given to you in the workshop
- Find the line with the *password and change it to password given to you in the workshop
- Try compiling it by pressing the Verify button 
- When ok:
	- 	Connect the nodeMCU with the USB cable
	- 	Via Tools -> Port, check if the correct COMxx port is selected
	- 	Upload the sketch by pressing the Upload button 
	- 	Wait till the sketch is compiled and uploaded
	- 	Open the monitor
- A message should be displayed with “IP address: www.xxx.yyy.zzz”
- Now connect your laptop or mobile phone to the same network as the nodeMCU is connected to
- Open the page www.xxx.yyy.zzz, you should be able to see ESP8266 message and a graph


## Advanced Extra: combine the webserver and DHT sensor sketch to display the temperature and humidity from your laptop or mobile phone
- Open both the sketches “AdvancedWebServer” and “DHTtester” and find a way to combine the necessary code from DHTtester into the AdvancedWebServer examples.
- Do not forget to save it under a new name like “my_weatherstation”


## Testing the weather station
- Load the example sketch, provided to your during the workshop, “iot_innovatos_weerstation” into the Arduino IDE
- Find the line with the *ssid and change it to the ssid given to you in the workshop
- Find the line with the *password and change it to password given to you in the workshop
- Try compiling it by pressing the Verify button: 
- When ok:
	- 	Connect the nodeMCU with the USB cable
	- 	Via Tools -> Port, check if the correct COMxx port is selected
	- 	Upload the sketch by pressing the Upload button 
	- 	Wait till the sketch is compiled and uploaded
	- 	Open the monitor
- A message should be displayed with “IP address: www.xxx.yyy.zzz”
- Now connect your laptop or mobile phone to the same network as the nodeMCU is connected to
- Open the page www.xxx.yyy.zzz, you should be able to see the weatherstation temperature and humidty

