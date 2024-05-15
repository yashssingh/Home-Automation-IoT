#define BLYNK_TEMPLATE_ID "TMPL3ZQ5GgAVg"
#define BLYNK_TEMPLATE_NAME "Test1"
#define BLYNK_AUTH_TOKEN "VNf-R8rrj1l5WAa2JlW1-M2Rck5kvcS4"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <Servo.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WiFiMulti.h>

// WiFi credentials
char ssid[] = "Crystal";
char pass[] = "yashyash11";

// Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;

// Telegram bot settings
String url = "https://api.telegram.org/ your bot ";
String chatId = "your id";

// DHT sensor settings
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Servo Motor settings
#define SERVO_PIN D3
Servo servoMotor;

// Relay Module settings
#define RELAY_PIN D1

// Virtual pins for Blynk
#define TEMP_HUMIDITY_PIN V0
#define LIGHT_BULB_PIN V1

// Function declaration
void sendTelegramMessage(String message);

void setup() {
  Serial.begin(115200);
  servoMotor.write(0);
  Blynk.begin(auth, ssid, pass);

  dht.begin();
  servoMotor.attach(SERVO_PIN);
  pinMode(RELAY_PIN, OUTPUT);
  sendTelegramMessage("Hey there ! We are connected to Wifi");
  // Initialize relay pin
  digitalWrite(RELAY_PIN, LOW); // Relay OFF
  
}

void loop() {
  Blynk.run();
  readTemperatureHumidity();
}

void readTemperatureHumidity() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.println();

  Blynk.virtualWrite(V6, temperature);
  Blynk.virtualWrite(V5, humidity); // Offset for humidity

  // Control Servo Motor based on humidity
  if (humidity > 45) 
  {
    servoMotor.write(90);
    sendTelegramMessage("Servo is ON since the humidity is above 45%"); // Send Telegram message
    // delay(2000);
    servoMotor.write(0);
    delay(2000);
  }
   else {
      servoMotor.write(0);
          sendTelegramMessage("Servo is OFF since the humidity is less than = to 45%"); // Send Telegram message

  }
}

// Blynk virtual pin handler for controlling the bulb
BLYNK_WRITE(LIGHT_BULB_PIN) {
  int state = param.asInt();
  if (state == 1) {
    digitalWrite(RELAY_PIN, HIGH);
    sendTelegramMessage("Bulb has been turned ON"); // Send Telegram message
 // Turn ON relay to light up the bulb
  } else {
    digitalWrite(RELAY_PIN, LOW); // Turn OFF relay
    sendTelegramMessage("Bulb has been turned OFF"); // Send Telegram message
  }
}

void connectWiFi() 
{
  // Connect to Wi-Fi
  Serial.begin(9600);
  delay(10);

  // Connect to Wi-Fi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");

}


  WiFiClientSecure client;

void sendTelegramMessage(String message) {
  connectWiFi();
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  https.begin(*client, url);
  https.addHeader("Content-Type", "application/json");
  String payload = "{\"chat_id\":\"";
  payload += chatId;
  payload += "\",\"text\":\"";
  payload += message;
  payload += "\"}";

  Serial.println(payload);
  int httpStatus = https.POST(payload);

  Serial.println(httpStatus);
  https.end();

}
