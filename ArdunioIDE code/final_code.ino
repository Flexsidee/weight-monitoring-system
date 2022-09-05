#include "HX711.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


const char *ssid = "Weight Monitoring Server";
const char *password = "12345678";

//IPAddress local_ip(192,168,4,100);
//IPAddress gateway(192,168,4,1);
//IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

#define SERVER_IP "http://192.168.1.100"


static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
#define DOUT  D5
#define CLK  D6
float weight;
float calibration_factor = 419640; 

HX711 scale;


void setup(){  
  Serial.begin(115200);
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0
  long zero_factor = scale.read_average(); //Get a baseline reading
  
  Serial.println();
  Serial.print("Configuring access point...");
  
  WiFi.softAP(ssid, password);
//  WiFi.softAPConfig(local_ip, gateway, subnet);

  delay(1000);

  server.on("/data", handle_OnConnect);
  server.on("/", handle_OnConnect);
  server.begin();
  Serial.println("HTTP server started");
  Serial.print("Access Point-- ");
  Serial.print(ssid); Serial.println(" ...");
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP()); 
}
 
void loop(){
  server.handleClient();
  
  scale.set_scale(calibration_factor); //Adjust to this calibration factor 
  weight = scale.get_units(); 
  delay(2000);
  
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" KG");

  update_server();
  Serial.println();
}

void handle_OnConnect() {
  String strVal = String(weight);
  Serial.println("Connected to server");
  server.send(200, "text/json", "{\"value\":\""+strVal+"\"}"); 
}

void update_server(){
    WiFiClient client;
    HTTPClient http;
    String strVal = String(weight);
    http.begin(client,SERVER_IP);
    http.addHeader("Content-Type", "application/json");
    Serial.print("[HTTP] POST...\n");
    int httpCode = http.POST("{\"hello\":\"world\"}");
    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();  
  }