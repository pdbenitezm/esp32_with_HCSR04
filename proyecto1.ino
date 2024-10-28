//pantalla lcd
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#define LCD_WIDTH 135
#define LCD_HEIGHT 240
#define LCD_MOSI 23
#define LCD_SCLK 18
#define LCD_CS 15
#define LCD_DC 2
#define LCD_RST 4
#define LCD_BLK 32
Adafruit_ST7789 lcd = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);

//modulo ultrasonico
const int trigPin = 12;
const int echoPin = 13;
//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;
float distanceInch;
//escala de medicion para una distancia de 1.0m (100cm) (1 led= 12.5 cm)
float mLED_1 = 12.5;
float mLED_2 = 25;
float mLED_3 = 37.5;
float mLED_4 = 50;
float mLED_5 = 62.5;
float mLED_6 = 75;
float mLED_7 = 87.5;
float mLED_8 = 100;

//for ESP32 Microcontrollers (controlador 595)
int latchPin = 21;
int clockPin = 26;
int dataPin = 22;
byte leds = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  Serial.begin(115200);
  lcd.init(LCD_WIDTH, LCD_HEIGHT);
  lcd.setRotation(3);
  lcd.fillScreen(ST77XX_BLACK);
  delay(500);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distanceCm = duration * SOUND_SPEED / 2;

  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  /////////////////////////////////////////////////
  lcd.fillScreen(ST77XX_BLACK);
  lcd.setTextSize(6);
  lcd.setCursor(0, 0);  // Establece el cursor al inicio
  Serial.println(distanceCm);
  //lcd.print("distance(cm): ");
  lcd.println(distanceCm);
  leds = 0;

  //condicionales
  if (distanceCm <= mLED_1) {
    leds |= 0b00000001;
  }
  if (distanceCm >= mLED_1) {
    leds |= 0b00000001;
  }
  if (distanceCm >= mLED_2) {

    leds |= 0b00000011;
  }
  if (distanceCm >= mLED_3) {

    leds |= 0b00000111;
  }
  if (distanceCm >= mLED_4) {

    leds |= 0b00001111;
  }
  if (distanceCm >= mLED_5) {

    leds |= 0b00011111;
  }
  if (distanceCm >= mLED_6) {

    leds |= 0b00111111;
  }
  if (distanceCm >= mLED_7) {

    leds |= 0b01111111;
  }
  if (distanceCm == mLED_8) {

    leds |= 0b11111111;
  }
  if (distanceCm > mLED_8) {

    leds |= 0b11111111;
  }
  updateShiftRegister();
  delay(250);
}

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}