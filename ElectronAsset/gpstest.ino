// Getting the library
#include "MQTT/MQTT.h"
#include "AssetTracker/AssetTracker.h"
#include "LiquidCrystal_I2C_Spark/LiquidCrystal_I2C_Spark.h"
#include "SparkJson/SparkJson.h"

// Set whether you want the device to publish data to the internet by default here.
// 1 will Particle.publish AND Serial.print, 0 will just Serial.print
// Extremely useful for saving data while developing close enough to have a cable plugged in.
// You can also change this remotely using the Particle.function "tmode" defined in setup()
int transmittingData = 1;

// Used to keep track of the last time we published data
long lastPublish = 0;

// How many minutes between publishes? 10+ recommended for long-time continuous publishing!
int delayMinutes = 1;

// Creating an AssetTracker named 't' for us to reference
AssetTracker t = AssetTracker();

// A FuelGauge named 'fuel' for checking on the battery state
FuelGauge fuel;

LiquidCrystal_I2C *lcd;
String latlon;

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "USERNAME"
#define AIO_PASSWORD    "PASSWORD"

void callback(char* topic, byte* payload, unsigned int length);

MQTT client(AIO_SERVER, AIO_SERVERPORT, callback);

// recieve message
void callback(char* topic, byte* payload, unsigned int length) {
   //implement this later
}

void writetoLCD(String latlon) {
  lcd->backlight();
  lcd->setCursor(0,0);
  //String outputTop =  String(lat);
  lcd->print(latlon);
  String outputBottom = String("TEST");
  lcd->setCursor(0,1);
  lcd->print(outputBottom);
}

// setup() and loop() are both required. setup() runs once when the device starts
// and is used for registering functions and variables and initializing things
void setup() {
    // Opens up a Serial port so you can listen over USB
    Serial.begin(9600);
    
    // Sets up all the necessary AssetTracker bits
    t.begin();
    
    // Enable the GPS module. Defaults to off to save power. 
    // Takes 1.5s or so because of delays.
    t.gpsOn();
    
    // These three functions are useful for remote diagnostics. Read more below.
    //Particle.function("tmode", transmitMode);
    //Particle.function("batt", batteryStatus);
    //Particle.function("gps", gpsPublish);
    
    //lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    //lcd->init();
    //lcd->clear();
    
    Serial.println("Connecting to aio...");
    client.connect("sparkclient", AIO_USERNAME, AIO_PASSWORD);
}

// loop() runs continuously
void loop() {
    // You'll need to run this every loop to capture the GPS output
    t.updateGPS();

    //String pubAccel = String::format("%d,%d,%d",t.readX(),t.readY(),t.readZ());
    //Serial.println(pubAccel);
    //Particle.publish("A", pubAccel, 60, PRIVATE);
        
    // Dumps the full NMEA sentence to serial in case you're curious
    // Serial.println(t.preNMEA());
        
    // GPS requires a "fix" on the satellites to give good data,
    // so we should only publish data if there's a fix
    if(t.gpsFix()){
        // Only publish if we're in transmittingData mode 1;
        if(transmittingData){
            if (client.isConnected()) {
               // read the value from the sensor:
               latlon = t.readLatLon();
     
               const char MOISTURE_FEED[] PROGMEM = AIO_USERNAME "/feeds/temperature/json";
               
               //create our json payload as {"meaning":"moisture","value":sensorvalue}
               StaticJsonBuffer<300> pubJsonBuffer;
               JsonObject& pubJson = pubJsonBuffer.createObject();
               
               int comma = latlon.indexOf(",");
               String lat = latlon.substring(0,comma);
               char latChar[10];
               char lonChar[10];
               lat.toCharArray(latChar, 10);
               String lon = latlon.substring(comma+1);
               lon.toCharArray(lonChar, 10);
            
               pubJson["value"] = "10";
               pubJson["lat"] = latChar;
               pubJson["lon"] = lonChar;
               pubJson["ele"] = "0";
               char message_buff[200];
               pubJson.printTo(message_buff, sizeof(message_buff));
               
               Serial.println(latChar);
               Serial.println(lonChar);
     
               //WORKAROUND - convert the int value to a char, and post using that
               //char str[80];
               //strcpy(str,"10,");
               //strcat(str,latlon);
               //strcat(str,",10");
               //const char* payload = strcat("10,", latlon);
               //payload = strcat(payload,",10");

               Serial.println("Pushing data to Adafruit.io...");
               //Serial.println(MOISTURE_FEED);
               //Serial.println(message_buff);
               client.publish(MOISTURE_FEED,message_buff);
     
               //go into deep sleep for 60 seconds
               //System.sleep(SLEEP_MODE_DEEP, 60);
			   //System.sleep(SLEEP_MODE_DEEP, 10);
            }
        } else {
            Serial.println("Transmitting data is off...");
        }
    }
}

// Allows you to remotely change whether a device is publishing to the cloud
// or is only reporting data over Serial. Saves data when using only Serial!
// Change the default at the top of the code.
int transmitMode(String command){
    transmittingData = atoi(command);
    return 1;
}

// Actively ask for a GPS reading if you're impatient. Only publishes if there's
// a GPS fix, otherwise returns '0'
int gpsPublish(String command){
    if(t.gpsFix()){ 
        Particle.publish("G", t.readLatLon(), 60, PRIVATE);
        
        // uncomment next line if you want a manual publish to reset delay counter
        // lastPublish = millis();
        return 1;
    }
    else { return 0; }
}

// Lets you remotely check the battery status by calling the function "batt"
// Triggers a publish with the info (so subscribe or watch the dashboard)
// and also returns a '1' if there's >10% battery left and a '0' if below
int batteryStatus(String command){
    // Publish the battery voltage and percentage of battery remaining
    // if you want to be really efficient, just report one of these
    // the String::format("%f.2") part gives us a string to publish,
    // but with only 2 decimal points to save space
    Particle.publish("B", 
          "v:" + String::format("%.2f",fuel.getVCell()) + 
          ",c:" + String::format("%.2f",fuel.getSoC()),
          60, PRIVATE
    );
    // if there's more than 10% of the battery left, then return 1
    if(fuel.getSoC()>10){ return 1;} 
    // if you're running out of battery, return 0
    else { return 0;}
}
