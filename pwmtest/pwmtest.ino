/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  PWM test - this will drive 16 PWMs in a 'wave'

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815

  These displays use I2C to communicate, 2 pins are required to  
  interface. For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#define PWMMAX 1000
char *notes[]  = {"F","F#","G","G#","A","A#","B","C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

int currentnote = 0;
int currentnote2 = 0;
int currentnote3=0;
int currentnote4=0;
int currentnote5=0;
 int velocity = 60;//velocity of MIDI notes, must be between 0 and 127
 //higher velocity usually makes MIDI instruments louder
 
 int noteON = 144;//144 = 10010000 in binary, note on command
 int noteOFF = 128;//128 = 10000000 in binary, note off command

byte pins = 3;

int pwm_value;
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);



void setup() {
  Serial.begin(115200);
  Serial.println("16 channel PWM test!");

  // if you want to really speed stuff up, you can go into 'fast 400khz I2C' mode
  // some i2c devices dont like this so much so if you're sharing the bus, watch
  // out for this!
  //alpha4.begin(0x70);
  
  pwm.begin();
  //1600 is max
  //tune so that %50 duty give 512us pulse
  pwm.setPWMFreq(1000);  // This is the maximum PWM frequency
    
  // save I2C bitrate
  uint8_t twbrbackup = TWBR;
  // must be changed after calling Wire.begin() (inside pwm.begin())
  TWBR = 12; // upgrade to 400KHz!
  
  for (int pwmnum=0; pwmnum<16; pwmnum++){
    pwm.setPWM(pwmnum, 0, 250*pwmnum+10);
  }
  
   pinMode(3, INPUT);
   pinMode(4, INPUT);
   pinMode(5, INPUT);
   pinMode(6, INPUT);
   pinMode(7, INPUT);
}


void writedisplay(int value){
  String  out=String(value);
  alpha4.writeDigitAscii(3,out[3]);
  alpha4.writeDigitAscii(2,out[2]);
  alpha4.writeDigitAscii(1,out[1]);
  alpha4.writeDigitAscii(0,out[0]);
  
  alpha4.writeDisplay();
}

void loop() {

  // Drive each PWM in a 'wave'
//  for (uint16_t i=0; i<4096; i += 8) {
//    for (uint8_t pwmnum=0; pwmnum < 16; pwmnum++) {
//      pwm.setPWM(pwmnum, 0, (i + (4096/16)*pwmnum) % 4096 );
//    }

  pwm_value = pulseIn(3, HIGH, 5000);
  //Serial.println(pwm_value);
  writedisplay(pwm_value);


  int pwmchannel=(float(pwm_value)/float(PWMMAX))*16;
  int note=pwmchannel+40;
   
  if (pwmchannel!=currentnote){
  
    MIDImessage(noteOFF, 50-currentnote, velocity);//turn note off
    currentnote=pwmchannel;
    if (pwmchannel!=0){
     MIDImessage(noteON, 50-currentnote, velocity);//turn note on
    }
  }

  //Serial.println(pwmchannel);
  //Serial.println(notes[pwmchannel]);


  pwm_value = pulseIn(4, HIGH, 5000);
  //Serial.println(pwm_value);
  writedisplay(pwm_value);


  pwmchannel=(float(pwm_value)/float(PWMMAX))*16;
  note=pwmchannel+28;
   
  if (pwmchannel!=currentnote2){
  
    MIDImessage(noteOFF, 55-currentnote2, velocity);//turn note off
    currentnote2=pwmchannel;
    if (pwmchannel!=0){
     MIDImessage(noteON, 55-currentnote2, velocity);//turn note on
    }
  }

  //Serial.println(pwmchannel);
  //Serial.println(notes[pwmchannel]);

  pwm_value = pulseIn(5, HIGH, 5000);
  //Serial.println(pwm_value);
  writedisplay(pwm_value);


  pwmchannel=(float(pwm_value)/float(PWMMAX))*16;
  note=pwmchannel+28;
   
  if (pwmchannel!=currentnote3){
  
    MIDImessage(noteOFF, 60-currentnote3, velocity);//turn note off
    currentnote3=pwmchannel;
    if (pwmchannel!=0){
     MIDImessage(noteON, 60-currentnote3, velocity);//turn note on
    }
  }


//##################
  pwm_value = pulseIn(6, HIGH, 5000);
  //Serial.println(pwm_value);
  writedisplay(pwm_value);


  pwmchannel=(float(pwm_value)/float(PWMMAX))*16;
  note=pwmchannel+28;
   
  if (pwmchannel!=currentnote4){
  
    MIDImessage(noteOFF, 65-currentnote4, velocity);//turn note off
    currentnote4=pwmchannel;
    if (pwmchannel!=0){
     MIDImessage(noteON, 65-currentnote4, velocity);//turn note on
    }
  }


//###############################
  pwm_value = pulseIn(7, HIGH, 5000);
  //Serial.println(pwm_value);
  writedisplay(pwm_value);


  pwmchannel=(float(pwm_value)/float(PWMMAX))*16;
  note=pwmchannel+28;
   
  if (pwmchannel!=currentnote5){
  
    MIDImessage(noteOFF, 69-currentnote5, velocity);//turn note off
    currentnote5=pwmchannel;
    if (pwmchannel!=0){
     MIDImessage(noteON, 69-currentnote5, velocity);//turn note on
    }
  }







  
  ///delay(10);
  }


//send MIDI message
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}

