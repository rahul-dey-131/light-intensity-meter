// C++ code
// Light Intensity Measurement

#include <LiquidCrystal.h>	// Including the Liquid Crystal library to operate LCD

// Initializing Necessary Variables and Object
int redPin = 11, greenPin = 5, bluePin = 6;	// Variables for the RGB pins
LiquidCrystal LCD(10, 9, 7, 4, 3, 2);		// Object for the LCD Display

void setup()
{
  // Starting the Serial Monitor
  Serial.begin(9600);
  
  // Initializing Pins for the RGBs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Setting the LCD
  LCD.begin(16,2);
  LCD.setCursor(0,0);
  LCD.print("Light Intensity:");
}

void loop()
{
  // Getting Input from the LDR Sensor
  int ldrSensorValue;	// Variable for the LDR output value
  ldrSensorValue = analogRead(A0);
  
  // Controlling the LDR Sensor
  RGBController(ldrSensorValue);
  Serial.println(ldrSensorValue);
  
  // Displaying Intensity of the Light using LCD
  LCD.setCursor(0,1);
  LCD.print("                "); // Clearing previous text
  LCD.setCursor(0,1);
  LCD.print(luxConverter(ldrSensorValue));
  LCD.print(" Lux");
  
  delay(250);	// Pausing not to make the display jittery
}

// Initializing RGBController Function
void RGBController(int value) {
  int greenBrightness;	// Variable for green light intensity as it's not a casual PWM
  
  // Mapping the Lights According to the light Intensity
  if (value <= 146) {
  	analogWrite(redPin, map(value, 0, 146, 0, 255));
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  } 
  else if (value <= 294) {
   	analogWrite(redPin, 255);
    analogWrite(greenPin, map(value, 147, 294, 0, 63));
    analogWrite(bluePin, 0);
  }
  else if (value <= 440) {
   	analogWrite(redPin, 255);
    analogWrite(greenPin, map(value, 295, 440, 200, 255));
    analogWrite(bluePin, 0);
  }
  else if (value <= 586) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, map(value, 441, 586, 0, 255));
    analogWrite(bluePin, 0);
  }
  else if (value <= 732) {
   	analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, map(value, 587, 732, 0, 255));
  }
  else if (value <= 878) {
    analogWrite(redPin, 75);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, map(value, 733, 878, 127, 190));
  } 
  else {
    analogWrite(redPin, 38);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, map(value, 879, 1023, 191, 255));
  }
}

// Initializing luxConverter Function
float luxConverter(int ldrValue) {
  float voltage = ldrValue * (5 / 1023.0);	// Getting voltage drop according to the light intensity
  float resistanceLDR = (5.0 - voltage) * (4000 / voltage);	// Getting LDR Resistance
  float LUXValue = pow(50000.0 / resistanceLDR, 1.0 / 0.8);	// Converting to illuminance value
  return LUXValue;
}