**README**

This repository contains code for an IoT project implemented on an ESP8266 microcontroller, enabling various functionalities such as monitoring temperature and humidity, controlling a servo motor and a relay module, and communicating with a Telegram bot for notifications.

### Features:
- **Temperature and Humidity Monitoring:** Utilizes a DHT11 sensor to measure temperature and humidity levels.
- **Servo Motor Control:** Controls a servo motor based on humidity levels. When humidity exceeds 45%, the servo motor is activated to a certain position.
- **Bulb Control:** Controls a relay module to turn a bulb on or off via Blynk app.
- **Telegram Notification:** Sends notifications to a Telegram bot regarding the status of the system, including WiFi connection status, servo motor activation, and bulb status.

### Dependencies:
- [Blynk](https://github.com/blynkkk/blynk-library): Library for IoT development platform.
- [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library): Library for DHT sensors.
- [Servo Library](https://github.com/arduino-libraries/Servo): Library for servo motor control.
- [ESP8266HTTPClient](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient): Library for making HTTP requests.
- [WiFiClientSecureBearSSL](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi/src/BearSSL): Library for secure WiFi client.

### Setup:
1. Clone or download the repository.
2. Open the Arduino IDE and install the required libraries mentioned above.
3. Connect the ESP8266 microcontroller to the appropriate pins according to the defined pin configurations in the code.
4. Customize the WiFi credentials, Blynk authentication token, Telegram bot settings, and other parameters as needed.
5. Upload the code to the ESP8266 microcontroller.
6. Monitor the system via the Blynk app and receive notifications on the Telegram bot.

### Usage:
- Access the Blynk app to monitor temperature and humidity, control the bulb, and receive notifications.
- Receive Telegram notifications regarding WiFi connection status, servo motor activation, and bulb status.

### Note:
- Ensure proper connections and configurations to avoid any malfunctioning of the system.
- Customize the code according to specific requirements and hardware configurations.
- Refer to the respective library documentation for detailed information on usage and functionalities.

### Contributors:
- [Yash Singh] 
