#include "MQTT/MQTT.h"

int sensorPin = A0;    // set the input pin for the moisture sensor

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "USERNAME
#define AIO_PASSWORD    "PASSWORD"

void callback(char* topic, byte* payload, unsigned int length);

MQTT client(AIO_SERVER, AIO_SERVERPORT, callback);

// recieve message
void callback(char* topic, byte* payload, unsigned int length) {
   //implement this later
}

void setup() {
  Serial.begin(9600);
  
  Serial.println("Connecting to aio...");
  client.connect("sparkclient", AIO_USERNAME, AIO_PASSWORD);
}

void loop() {
  // publish/subscribe
  if (client.isConnected()) {
     int sensorValue = 0;  // variable to store the value coming from the sensor
     
     // read the value from the sensor:
     Serial.println("Reading sensor value...");
     sensorValue = analogRead(sensorPin);
     
     Serial.println(sensorValue);
     
     Serial.println("Attempting to publish a reading...");
     
     const char MOISTURE_FEED[] PROGMEM = AIO_USERNAME "/feeds/moisture";
     
     //having issue sending int values to adafruit.io. not sure if it's the mqtt library of adafruit.io
     //client.publish("rayterrill/feeds/moisture",(uint8_t *)&sensorValue,10);
     //client.publish("rayterrill/feeds/moisture",(uint8_t *)&sensorValue, sizeof(sensorValue));
     
     //WORKAROUND - convert the int value to a char, and post using that
     char payload[12];
     ltoa(sensorValue, payload, 10);
    
     client.publish(MOISTURE_FEED,payload);
     
     //go into deep sleep for 60 seconds
     System.sleep(SLEEP_MODE_DEEP, 60);
  }
}
