#include <Adafruit_NeoPixel.h>

#define PIN 2	 // input pin Neopixel is attached to

#define NUMPIXELS      4 // number of neopixels in strip

//LED strip vars
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

//Photodiode vars
int LEDlights = 2;
int LightPen = A1;
int ValLight;
int LED_transistor = 8;

//Soil moisture vars
int pump_transistor = 10;
int moisture = 0;
int soil_output = A0;
int soil_input = A2;

void setup()
{
  
  pinMode(LED_transistor, OUTPUT);
  pinMode(LightPen, INPUT);
  pinMode(LEDlights, OUTPUT);
 
  pinMode(pump_transistor, OUTPUT);
  pinMode(soil_output,OUTPUT);
  pinMode(soil_input, INPUT);
  
  
  Serial.begin(9600);
  pixels.begin();
}

void loop()
{
  //Soil moisture code:://
  
  
  digitalWrite(soil_output, HIGH);  // Apply power to the soil moisture sensor
  delay(100); // Wait for 10 millisecond(s)
  moisture = analogRead(soil_input);
  digitalWrite(soil_output, LOW); //Turn off sensor
  Serial.print("Moisture: "); Serial.println(moisture);
  

  if (moisture < 200) {
    //First turn off led strip
    digitalWrite(LEDlights ,LOW);
    for (int i=0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 0, 0, 0);
    }
    pixels.show();
    
    //Then turn on pump
    analogWrite(pump_transistor, 255);
    delay(5000);
    analogWrite(pump_transistor, 0);
      }

 //Photodiode code:://
  
  setColor();
  for (int i=0; i < NUMPIXELS; i++) {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(redColor, greenColor, blueColor));

    // Delay for a period of time (in milliseconds).
    delay(100);
  }
  
  digitalWrite(LED_transistor, HIGH);
  ValLight = analogRead(LightPen);
  Serial.print("Light: "); Serial.println(ValLight);
  delay(100);
  
  if (ValLight < 250 ) {
    pixels.show();
  }
  else {
    digitalWrite(LEDlights ,LOW);
    for (int i=0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 0, 0, 0);
    }
    pixels.show();
  }
  delay(2000);
}

void setColor(){
  redColor = random(0, 255);
  greenColor = random(0,255);
  blueColor = random(0, 255);
}