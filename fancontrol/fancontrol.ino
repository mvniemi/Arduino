// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to
#define DHTPIN2 3
#define DHTPIN3 4

#define RELAYPIN1 8
#define RELAYPIN2 9

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT s1(DHTPIN, DHTTYPE);
DHT s2(DHTPIN2,DHTTYPE);
DHT s3(DHTPIN3,DHTTYPE);

int potPin = 3;
int val=0;
float diffMin=999;
float diffMax=0;
float diffAvg=0;
float diff=0;
int count=1;


double dewPointFast(double celsius, double humidity)
{
 double a = 17.271;
 double b = 237.7;
 double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
 double Td = (b * temp) / (a - temp);
 return Td;
}

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  s1.begin();
  s2.begin();
  s3.begin();
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);

  

 //setup display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)\

  //Show test image buffer from hardware
  //display.display();
  //delay(2);
  //display.clearDisplay();
}

void loop() {
  // Wait a few seconds between measurements.
  //Set to minute values
  //Long measure time takes care of switching too fast
  delay(500);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h1 = s1.readHumidity();
  // Read temperature as Celsius (the default)
  float t1 = s1.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f1 = s1.readTemperature(true);

  
  float h2 = s2.readHumidity();
  // Read temperature as Celsius (the default)
  float t2 = s2.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f2 = s2.readTemperature(true);

  float h3 = s3.readHumidity();
  // Read temperature as Celsius (the default)
  float t3 = s3.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f3 = s3.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  //Check both
  if (isnan(h1) || isnan(t1) || isnan(f1)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (isnan(h2) || isnan(t2) || isnan(f2)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif1 = s1.computeHeatIndex(f1, h1);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic1 = s1.computeHeatIndex(t1, h1, false);
  double inDp= dewPointFast(t1,h1);
//
  // Compute heat index in Fahrenheit (the default)
  float hif2 = s2.computeHeatIndex(f2, h2);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic2 = s2.computeHeatIndex(t2, h2, false);
  double outDp= dewPointFast(t2,h2);


  // Compute heat index in Fahrenheit (the default)
  float hif3 = s3.computeHeatIndex(f3, h3);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic3 = s3.computeHeatIndex(t3, h3, false);
  double inDp1= dewPointFast(t3,h3);

//Code for driving display here
//
//what to display?
//Sensor values/ Status
//Differnetial
//Vent stats
//Failures
  float* pa[]={&h1,&h2,&h3};
  float* h1pointer = &h1;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.print("Dewpt 1:");
  display.println(*pa[0]);
  display.print("Dewpt 2:");
  display.println(*pa[1]);
  display.print("Dewpt 3:");
  display.println(*pa[2]);

  
  display.print("Diff: ");
  diff=h1-h3;
  display.println(diff);
  
  if (diff>diffMax){
    diffMax=diff;
  }
  if (diff<diffMin){
    diffMin=diff;
  }
  diffAvg=(diffAvg*count+diff)/(count+1);
  count++;

  display.print("Avgdiff= ");
  display.println(diffAvg);
  display.print("Max= ");
  display.println(diffMax);
  display.print("Min= ");
  display.println(diffMin);
  display.println(log(count));
  display.display();

  
 //Logic for ventilate
 //If outside is lower by 1C then vent
  if(inDp>(outDp+1)){
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
  }
  else{
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
  }
}



