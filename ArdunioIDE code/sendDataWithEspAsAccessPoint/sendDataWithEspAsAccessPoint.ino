//include all necessary libraries needed
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "HX711.h" 

//set ssid and password for wifi created by esp8266
const char* ssid     = "Weight monitoring system";
const char* password = "12345678";

//set the api endpoint in which the data is sending to, the IP address is the address given to the device in which the server is
const String serverName = "http://192.168.4.2/weight_monitoring/conn.php"; 

ESP8266WebServer server(80);

//set the pin that recieves data from HX711
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
#define DOUT  D5
#define CLK  D6

HX711 scale; //this is from the library 
float weight; //declare variable to hold reading
float calibration_factor = 419640;  //set the calibration factor

//this will be used to display the current sensor reading in json format when you try to check the ip of  esp which is http://192.168.4.1
void handleRoot() {
  String strVal = String(weight);
  Serial.println("Connected to server");
  server.send(200, "text/json", "{\"value\":\""+strVal+"\"}"); 
}

void setup() {
  //set the baud rate
  Serial.begin(115200);

  //the followings are used to set up the sensor and HX711
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading

  //create create wifi network
  WiFi.softAP(ssid, password);
  Serial.println("");

  delay(1000);
  
  server.on("/", handleRoot); //when you check the ip the functions handles it
  server.begin(); //start server

  //displays this on serial monitor after putting on server
  Serial.println("HTTP server started");
  Serial.print("Access Point-- ");
  Serial.print(ssid); Serial.println(" ...");
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP()); 
}

void loop() {
  scale.set_scale(calibration_factor); //Adjust to this calibration factor 
  weight = scale.get_units();  //gets the reading and store it in the variable
  
  WiFiClient client;
  HTTPClient http;
  
  String sendRequest = serverName + "?value=" + String(weight);  //concatenate the value with servername to send get request
  
  http.begin(client, sendRequest.c_str()); // Your Domain name with URL path or IP address with path
  
  int httpResponseCode = http.GET(); //send request
   
  //Shows the request sent in Serial Monitor
  Serial.print("sendRequest: ");
  Serial.println(sendRequest);
  
  //if request is sent successfully
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    String payload = http.getString(); //get response from request
    Serial.println(payload); //display response of request in serial monitor
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode); //prints error code is request is uncesseffull
  }

  Serial.println(" "); //empty line in serial monitor
  
  http.end();
  
  //Send an HTTP POST request every 15 seconds
  delay(15000); 
}
