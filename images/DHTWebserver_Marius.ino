/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

const char *ssid = "<own ssid>";
const char *password = "<own pw>";

ESP8266WebServer server ( 80 );

const int led = 13;

int Temps[40];
int nPosition = 0;

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void handleRoot() {
	digitalWrite ( led, 1 );
	char temp[2000];
	int sec = millis() / 1000;
	int min = sec / 60;
	int hr = min / 60;
  char temperature[10]; 
  char humidity[10]; 
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // convert the float to astring
  dtostrf(h, 5, 2, humidity); 

  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // convert the float to astring
  dtostrf(t, 5, 2, temperature); 

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // store the last 40 Temperature values. 
  int intTemp = (int)t;
  Temps[nPosition] = intTemp;
  if (nPosition < 39) {
    nPosition += 1;
  } else {
    nPosition = 0;
  }

  Serial.print("Temperature(Float): ");
  Serial.print(t);
  Serial.println(" *C ");
  Serial.print("Temperature(String): ");
  Serial.println(temperature);
  Serial.print("Humidity(Float): ");
  Serial.print(h);
  Serial.println(" % ");
  Serial.print("Humidity(String): ");
  Serial.println(humidity);
   
	snprintf ( temp, 2000,

"<!DOCTYPE html>\
<html lang=\"en\">\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <meta charset=\"utf-8\">\
    <meta http-equiv=\"x-ua-compatible\" content=\"ie=edge\">\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
    <title>IoT Sensors</title>\
  <style>\
   body,html{\
      width:100\%;\
      max-height:100\%;\
      margin:0;\
      padding:0;\
    }\
  .container{\
    width:100\%;\
    max-height:100\%;\
  }\
  .header{\
    background:#0066a1;\
    color:#fff;\
    margin-bottom:36px;\
    text-align:center;\
  }\
  .header > img{\
    width:100\%;\
    margin:0;\
  }\
  .body-container{\
    width:100%;\
  }\
  .sensor{\
    margin-bottom:5\%;\
    position:relative;\
  }\
  img{\
    margin-left:5\%;\
    width:40\%;\
    height:auto;\
  }\
  span{\
    display:block;\
    position:absolute;\
    left:50\%;\
    top:8\%;\
    color:#0066a1;\
    font-size:5vw;\
  }\
  </style>\
  </head>\
  <body>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <div class=\"container\">\
    <div class=\"header\"><img src=\"http://iotweather.rash1981.com/img/innovatos.png\"></div>\
    <div class=\"body-container\">\
      <div class=\"sensor\">\
        <img src=\"http://iotweather.rash1981.com/img/temperature.gif\"><span>%s &#176;C</span>\
      </div>\
      <div class=\"sensor\">\
        <img src=\"http://iotweather.rash1981.com/img/humidity.gif\"><span>%s %%<span>\
      </div>\
    <img src=\"/test.svg\" />\
    </div>\      
    </div>\
    </div>\  
  </body>\
</html>",

		hr, min % 60, sec % 60, temperature, humidity
	);
	server.send ( 200, "text/html", temp );
	digitalWrite ( led, 0 );
}

void handleNotFound() {
	digitalWrite ( led, 1 );
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += server.uri();
	message += "\nMethod: ";
	message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
	message += "\nArguments: ";
	message += server.args();
	message += "\n";

	for ( uint8_t i = 0; i < server.args(); i++ ) {
		message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
	}

	server.send ( 404, "text/plain", message );
	digitalWrite ( led, 0 );
}

void setup ( void ) {
	pinMode ( led, OUTPUT );
	digitalWrite ( led, 0 );
	Serial.begin ( 115200 );
  delay ( 500 );
  Serial.println ( "" );
  Serial.print ( "Try Connect to " );
  Serial.println ( ssid );
	WiFi.begin ( ssid, password );
	Serial.println ( "" );

	// Wait for connection
	while ( WiFi.status() != WL_CONNECTED ) {
		delay ( 500 );
		Serial.print ( "." );
	}

	Serial.println ( "" );
	Serial.print ( "Connected to " );
	Serial.println ( ssid );
	Serial.print ( "IP address: " );
	Serial.println ( WiFi.localIP() );

	if ( MDNS.begin ( "esp8266" ) ) {
		Serial.println ( "MDNS responder started" );
	}

	server.on ( "/", handleRoot );
	server.on ( "/test.svg", drawGraph );
	server.on ( "/inline", []() {
		server.send ( 200, "text/plain", "this works as well" );
	} );
	server.onNotFound ( handleNotFound );
	server.begin();
	Serial.println ( "HTTP server started" );

   Serial.println("DHTxx test!");
   dht.begin();
}

void loop ( void ) {
	server.handleClient();
}

void drawGraph() {
	String out = "";
	char temp[100];
	out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"800\" height=\"250\">\n";
 	out += "<rect width=\"800\" height=\"250\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
 	out += "<g stroke=\"black\">\n";
 	int y = Temps[0];
 	for (int x = 1; x < 39; x+= 1) {
 		int y2 = Temps[x];
    if (nPosition == x) {
      y = 0;
    }
 		sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x * 20, 240 - (5*y), (x*20) + 20, 240 - (5*y2));
 		out += temp;
 		y = y2;
 	}
	out += "</g>\n</svg>\n";

	server.send ( 200, "image/svg+xml", out);
}
