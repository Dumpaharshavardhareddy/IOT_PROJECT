#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>

#define POTENTIOMETER_PIN 2
#define BUZZER_PIN 9
#define RED_PIN 10
#define GREEN_PIN 11
#define BLUE_PIN 12

const int threshold = 3000;

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Move this function up
void showColor(int r, int g, int b) {
  analogWrite(RED_PIN, 255 - r);   // For common cathode
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN, 255 - b);
}

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Wire.begin(47, 48);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Initializing...");
  delay(1500);
}

void loop() {
  int sensorValue = analogRead(POTENTIOMETER_PIN);
  float temperature = map(sensorValue, 0, 4095, 0, 100);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  if (sensorValue > threshold) {
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("ALERT: HIGH TEMP");
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Status: NORMAL ");
  }

  // RGB LED cycle
  showColor(255, 0, 0); // Red
  delay(1000);
  showColor(0, 255, 0); // Green
  delay(1000);
  showColor(0, 0, 255); // Blue
  delay(1000);
}
