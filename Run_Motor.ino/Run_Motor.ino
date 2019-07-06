// (c) Michael Schoeffler 2017, http://www.mschoeffler.de
#include <HX711_ADC.h> // https://github.com/olkal/HX711_ADC
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // LiquidCrystal_I2C library

//Initialize the pins for the motor
#define ENABLE 5
#define DIRA 3
#define DIRB 4

HX711_ADC LoadCell(6, 7); // parameters: dt pin, sck pin<span data-mce-type="bookmark" style="display: inline-block; width: 0px; overflow: hidden; line-height: 0;" class="mce_SELRES_start"></span>
LiquidCrystal_I2C lcd(0x27,16,2); // 0x27 is the i2c address of the LCM1602 IIC v1 module (might differ)
void setup() {
  //---set pin direction for motors
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  Serial.begin(9600); //Set the baud rate of the serial monitor
  //Calibrate the Load Cell and LCD
  LoadCell.begin(); // start connection to HX711
  LoadCell.start(2000); // load cells gets 2000ms of time to stabilize
  LoadCell.setCalFactor(435); // calibration factor for load cell => strongly dependent on your individual setup
  lcd.begin(); // begins connection to the LCD module
  lcd.backlight(); // turns on the backlight
}

void loop() {
  LoadCell.update(); // retrieves data from the load cell
  float i = LoadCell.getData(); // get output value
  lcd.setCursor(0, 0); // set cursor to first row
  lcd.print("Weight[g]:"); // print out to LCD
  lcd.setCursor(0, 1); // set cursor to secon row
  lcd.print(i);
  if (i > 181) { // weight is greater than 13g
   digitalWrite(ENABLE, HIGH); // Any value between 0 and 255
   digitalWrite(DIRA, LOW);
   digitalWrite(DIRB, HIGH); 
  } else {
   digitalWrite(ENABLE, LOW); // Any value between 0 and 255
   digitalWrite(DIRA, HIGH);
   digitalWrite(DIRB, LOW);
  }
}
