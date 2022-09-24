//include all necessary libraries needed
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "HX711.h" 


HX711 scale; //this is from the library 
//set the pin that recieves data from HX711
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
#define DOUT  D5
#define CLK  D6

float weight; //declare variable to hold reading
float calibration_factor = 419640;  //set the calibration factor


//set the wifi network that Esp8266 will connect to 
const char* ssid     = "Our4G"; //wifi ssid
const char* password = "baribario"; //wifi password

//set the api endpoint in which the data is sending to, the IP address is the address given to the device in which the server is
const String serverName = "http://192.168.100.240/weight_monitoring/conn.php"; 

void setup() {
  //set the baud rate
  Serial.begin(115200);

  //the followings are used to set up the sensor and HX711
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  
  //setup the connection to the wifi network 
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  scale.set_scale(calibration_factor); //Adjust to this calibration factor 
  weight = scale.get_units();  //gets the reading and store it in the variable
  
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
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
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 15 seconds
  delay(15000);  
}
