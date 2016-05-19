// This #include statement was automatically added by the Particle IDE.
#include "LiquidCrystal_I2C_Spark/LiquidCrystal_I2C_Spark.h"

// This #include statement was automatically added by the Particle IDE.
#include "neopixel/neopixel.h"

#define PIXEL_PIN D2
#define PIXEL_COUNT 64
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

LiquidCrystal_I2C *lcd;

const int buttonPin = 5;
int buttonState = 0;

void setup() {
  Serial.begin(115200);

  //initialize button pin
  pinMode(buttonPin, INPUT);

  Serial.println("Device starting...");
  Particle.subscribe("DidTheCubsWin", decideCubsStatus, MY_DEVICES);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pixelsOff();
  
  lcd = new LiquidCrystal_I2C(0x27, 16, 2);
  lcd->init();
  lcd->clear();
  
  //to test things out manually
  //const char *data = "Final: Brewers 4 Cubs 2. WP: MIL";
  //decideCubsStatus(data); //requires function to be modified to void decideCubsStatus(const char *data)
}

void writeGameScoreLCD(char team1 [20], char team2 [20], int score1, int score2) {
  lcd->backlight();
  lcd->setCursor(0,0);
  String outputTop =  String(String(team1) + " " + String(score1));
  String outputBottom = String(String(team2) + " " + String(score2));
  lcd->print(outputTop);
  lcd->setCursor(0,1);
  lcd->print(outputBottom);
}

void decideCubsStatus(const char *event, const char *data) {
  Serial.println("Calling function decideCubsStatus!");
  char team1 [20];
  char team2 [20];
  int score1;
  int score2;

  sscanf (data,"%*s %s %d %s %d",&team1,&score1,&team2,&score2);

  if (((strcmp(team1,"Cubs") == 0) && score1 > score2) || ((strcmp(team2,"Cubs") == 0) && score2 > score1)) {
    pixelsOff();
    cubsWin();
  } else {
    pixelsOff();
    cubsLose();
  }
  
  writeGameScoreLCD(team1, team2, score1, score2);
}

void loop() {
   buttonState = digitalRead(buttonPin);

   if (buttonState == HIGH) {
      pixelsOff();
      lcd->clear();
      lcd->noBacklight();
   }
}

void pixelsOff() {
    strip.setPixelColor(0, 0, 0, 0);
    strip.setPixelColor(1, 0, 0, 0);
    strip.setPixelColor(2, 0, 0, 0);
    strip.setPixelColor(3, 0, 0, 0);
    strip.setPixelColor(4, 0, 0, 0);
    strip.setPixelColor(5, 0, 0, 0);
    strip.setPixelColor(6, 0, 0, 0);
    strip.setPixelColor(7, 0, 0, 0);
    strip.setPixelColor(8, 0, 0, 0);
    strip.setPixelColor(9, 0, 0, 0);
    strip.setPixelColor(10, 0, 0, 0);
    strip.setPixelColor(11, 0, 0, 0);
    strip.setPixelColor(12, 0, 0, 0);
    strip.setPixelColor(13, 0, 0, 0);
    strip.setPixelColor(14, 0, 0, 0);
    strip.setPixelColor(15, 0, 0, 0);
    strip.setPixelColor(16, 0, 0, 0);
    strip.setPixelColor(17, 0, 0, 0);
    strip.setPixelColor(18, 0, 0, 0);
    strip.setPixelColor(19, 0, 0, 0);
    strip.setPixelColor(20, 0, 0, 0);
    strip.setPixelColor(21, 0, 0, 0);
    strip.setPixelColor(22, 0, 0, 0);
    strip.setPixelColor(23, 0, 0, 0);
    strip.setPixelColor(24, 0, 0, 0);
    strip.setPixelColor(25, 0, 0, 0);
    strip.setPixelColor(26, 0, 0, 0);
    strip.setPixelColor(27, 0, 0, 0);
    strip.setPixelColor(28, 0, 0, 0);
    strip.setPixelColor(29, 0, 0, 0);
    strip.setPixelColor(30, 0, 0, 0);
    strip.setPixelColor(31, 0, 0, 0);
    strip.setPixelColor(32, 0, 0, 0);
    strip.setPixelColor(33, 0, 0, 0);
    strip.setPixelColor(34, 0, 0, 0);
    strip.setPixelColor(35, 0, 0, 0);
    strip.setPixelColor(36, 0, 0, 0);
    strip.setPixelColor(37, 0, 0, 0);
    strip.setPixelColor(38, 0, 0, 0);
    strip.setPixelColor(39, 0, 0, 0);
    strip.setPixelColor(40, 0, 0, 0);
    strip.setPixelColor(41, 0, 0, 0);
    strip.setPixelColor(42, 0, 0, 0);
    strip.setPixelColor(43, 0, 0, 0);
    strip.setPixelColor(44, 0, 0, 0);
    strip.setPixelColor(45, 0, 0, 0);
    strip.setPixelColor(46, 0, 0, 0);
    strip.setPixelColor(47, 0, 0, 0);
    strip.setPixelColor(48, 0, 0, 0);
    strip.setPixelColor(49, 0, 0, 0);
    strip.setPixelColor(50, 0, 0, 0);
    strip.setPixelColor(51, 0, 0, 0);
    strip.setPixelColor(52, 0, 0, 0);
    strip.setPixelColor(53, 0, 0, 0);
    strip.setPixelColor(54, 0, 0, 0);
    strip.setPixelColor(55, 0, 0, 0);
    strip.setPixelColor(56, 0, 0, 0);
    strip.setPixelColor(57, 0, 0, 0);
    strip.setPixelColor(58, 0, 0, 0);
    strip.setPixelColor(59, 0, 0, 0);
    strip.setPixelColor(60, 0, 0, 0);
    strip.setPixelColor(61, 0, 0, 0);
    strip.setPixelColor(62, 0, 0, 0);
    strip.setPixelColor(63, 0, 0, 0);
    strip.setBrightness(30);
    strip.show();
}

void cubsWin() {
    strip.setPixelColor(0, 15, 90, 138);
    strip.setPixelColor(1, 15, 90, 138);
    strip.setPixelColor(2, 0, 0, 0);
    strip.setPixelColor(3, 15, 90, 138);
    strip.setPixelColor(4, 15, 90, 138);
    strip.setPixelColor(5, 0, 0, 0);
    strip.setPixelColor(6, 15, 90, 138);
    strip.setPixelColor(7, 15, 90, 138);
    strip.setPixelColor(8, 15, 90, 138);
    strip.setPixelColor(9, 15, 90, 138);
    strip.setPixelColor(10, 0, 0, 0);
    strip.setPixelColor(11, 15, 90, 138);
    strip.setPixelColor(12, 15, 90, 138);
    strip.setPixelColor(13, 0, 0, 0);
    strip.setPixelColor(14, 15, 90, 138);
    strip.setPixelColor(15, 15, 90, 138);
    strip.setPixelColor(16, 15, 90, 138);
    strip.setPixelColor(17, 15, 90, 138);
    strip.setPixelColor(18, 0, 0, 0);
    strip.setPixelColor(19, 15, 90, 138);
    strip.setPixelColor(20, 15, 90, 138);
    strip.setPixelColor(21, 0, 0, 0);
    strip.setPixelColor(22, 15, 90, 138);
    strip.setPixelColor(23, 15, 90, 138);
    strip.setPixelColor(24, 0, 0, 0);
    strip.setPixelColor(25, 15, 90, 138);
    strip.setPixelColor(26, 0, 0, 0);
    strip.setPixelColor(27, 15, 90, 138);
    strip.setPixelColor(28, 15, 90, 138);
    strip.setPixelColor(29, 0, 0, 0);
    strip.setPixelColor(30, 15, 90, 138);
    strip.setPixelColor(31, 0, 0, 0);
    strip.setPixelColor(32, 0, 0, 0);
    strip.setPixelColor(33, 15, 90, 138);
    strip.setPixelColor(34, 0, 0, 0);
    strip.setPixelColor(35, 15, 90, 138);
    strip.setPixelColor(36, 15, 90, 138);
    strip.setPixelColor(37, 0, 0, 0);
    strip.setPixelColor(38, 15, 90, 138);
    strip.setPixelColor(39, 0, 0, 0);
    strip.setPixelColor(40, 0, 0, 0);
    strip.setPixelColor(41, 15, 90, 138);
    strip.setPixelColor(42, 15, 90, 138);
    strip.setPixelColor(43, 15, 90, 138);
    strip.setPixelColor(44, 15, 90, 138);
    strip.setPixelColor(45, 15, 90, 138);
    strip.setPixelColor(46, 15, 90, 138);
    strip.setPixelColor(47, 0, 0, 0);
    strip.setPixelColor(48, 0, 0, 0);
    strip.setPixelColor(49, 15, 90, 138);
    strip.setPixelColor(50, 15, 90, 138);
    strip.setPixelColor(51, 0, 0, 0);
    strip.setPixelColor(52, 0, 0, 0);
    strip.setPixelColor(53, 15, 90, 138);
    strip.setPixelColor(54, 15, 90, 138);
    strip.setPixelColor(55, 0, 0, 0);
    strip.setPixelColor(56, 0, 0, 0);
    strip.setPixelColor(57, 15, 90, 138);
    strip.setPixelColor(58, 15, 90, 138);
    strip.setPixelColor(59, 0, 0, 0);
    strip.setPixelColor(60, 0, 0, 0);
    strip.setPixelColor(61, 15, 90, 138);
    strip.setPixelColor(62, 15, 90, 138);
    strip.setPixelColor(63, 0, 0, 0);
    strip.setBrightness(10);
    strip.show();
}

void cubsLose() {
    strip.setPixelColor(0, 0, 0, 0);
    strip.setPixelColor(1, 0, 0, 0);
    strip.setPixelColor(2, 255, 255, 255);
    strip.setPixelColor(3, 255, 255, 255);
    strip.setPixelColor(4, 0, 0, 0);
    strip.setPixelColor(5, 0, 0, 0);
    strip.setPixelColor(6, 0, 0, 0);
    strip.setPixelColor(7, 0, 0, 0);
    strip.setPixelColor(8, 0, 0, 0);
    strip.setPixelColor(9, 0, 0, 0);
    strip.setPixelColor(10, 255, 255, 255);
    strip.setPixelColor(11, 255, 255, 255);
    strip.setPixelColor(12, 0, 0, 0);
    strip.setPixelColor(13, 0, 0, 0);
    strip.setPixelColor(14, 0, 0, 0);
    strip.setPixelColor(15, 0, 0, 0);
    strip.setPixelColor(16, 0, 0, 0);
    strip.setPixelColor(17, 0, 0, 0);
    strip.setPixelColor(18, 255, 255, 255);
    strip.setPixelColor(19, 255, 255, 255);
    strip.setPixelColor(20, 0, 0, 0);
    strip.setPixelColor(21, 0, 0, 0);
    strip.setPixelColor(22, 0, 0, 0);
    strip.setPixelColor(23, 0, 0, 0);
    strip.setPixelColor(24, 0, 0, 0);
    strip.setPixelColor(25, 0, 0, 0);
    strip.setPixelColor(26, 255, 255, 255);
    strip.setPixelColor(27, 255, 255, 255);
    strip.setPixelColor(28, 0, 0, 0);
    strip.setPixelColor(29, 0, 0, 0);
    strip.setPixelColor(30, 0, 0, 0);
    strip.setPixelColor(31, 0, 0, 0);
    strip.setPixelColor(32, 0, 0, 0);
    strip.setPixelColor(33, 0, 0, 0);
    strip.setPixelColor(34, 255, 255, 255);
    strip.setPixelColor(35, 255, 255, 255);
    strip.setPixelColor(36, 0, 0, 0);
    strip.setPixelColor(37, 0, 0, 0);
    strip.setPixelColor(38, 0, 0, 0);
    strip.setPixelColor(39, 0, 0, 0);
    strip.setPixelColor(40, 0, 0, 0);
    strip.setPixelColor(41, 0, 0, 0);
    strip.setPixelColor(42, 255, 255, 255);
    strip.setPixelColor(43, 255, 255, 255);
    strip.setPixelColor(44, 0, 0, 0);
    strip.setPixelColor(45, 0, 0, 0);
    strip.setPixelColor(46, 0, 0, 0);
    strip.setPixelColor(47, 0, 0, 0);
    strip.setPixelColor(48, 0, 0, 0);
    strip.setPixelColor(49, 0, 0, 0);
    strip.setPixelColor(50, 255, 255, 255);
    strip.setPixelColor(51, 255, 255, 255);
    strip.setPixelColor(52, 255, 255, 255);
    strip.setPixelColor(53, 255, 255, 255);
    strip.setPixelColor(54, 0, 0, 0);
    strip.setPixelColor(55, 0, 0, 0);
    strip.setPixelColor(56, 0, 0, 0);
    strip.setPixelColor(57, 0, 0, 0);
    strip.setPixelColor(58, 255, 255, 255);
    strip.setPixelColor(59, 255, 255, 255);
    strip.setPixelColor(60, 255, 255, 255);
    strip.setPixelColor(61, 255, 255, 255);
    strip.setPixelColor(62, 0, 0, 0);
    strip.setPixelColor(63, 0, 0, 0);
    strip.setBrightness(10);
    strip.show();
}
