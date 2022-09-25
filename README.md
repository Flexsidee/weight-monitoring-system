# WEB BASED WEIGHT MONITORING SYSTEM

The followings were used in making this project;
- Esp8266: This is a microcontroller with wifi module, its used to create access point and to send the data gotten to the  backend
- Load Cell: This the sensor used to meaure the weights.
- HX711: This is used to amplify the signal coming from the load cell.
- Arduino IDE: This is the ide used to write code into the microcontroller.
- Xampp: Apache server used for php and mysql, used to save and fetch data.
- DataTable: A jquery client used to make tables better

How to Use Project
- Connect the load call to HX711
- connect hx711 to esp8266
- upload the script used to caliberate the sensor and note it down, the script can be found in 
- upload the main script that send the data reading to api in the sever that saves to the database 
- use the device in which the server (xampp) is installed on to connect to the wifi from esp "Weight Monitoring System" and password='12345678'
- check ip address of the device to see if its 192.168.4.2, if not manually set ip of the device
- switch of Firewall on the syste.
- go to main page on the xampp server to view recently added record, 'http://192.168.4.2/weight_monitoring/'

