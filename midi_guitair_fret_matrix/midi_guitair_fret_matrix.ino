#define NUM_STRINGS 4
#define NUM_FRETS 8
#define VELOCITY 80
#define noteON 144
#define noteOFF 128 

char *notes[]  = {"F","F#","G","G#","A","A#","B","C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
int stringOffsets[] = {0,5,10,15,19,25};
int stringPins[] = {3,4,5,6,7,8};
int fretPins[] = {9,10,11,12,13,14,15,16};
int currentNote[NUM_STRINGS];

void setup() {
  // put your setup code here, to run once:

//Initialize read pins
  for (int i=0; i< NUM_FRETS; i++){
    pinMode(fretPins[i], INPUT);
  }
  
// Initialize write pins?
  for (int i=0; i< NUM_STRINGS; i++){
    pinMode(stringPins[i], OUTPUT);
    digitalWrite(stringPins[i], LOW);
    currentNote[i]=0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  //Scan Strings: We will scan down the neck string my string and set
  // the note as the highest detected fret
  // Currently setting the note after each string instead of after all strings
  for (int i=0; i < NUM_STRINGS; i++){
    
    //Turn String High
    digitalWrite(stringPins[i], HIGH);
    //Set current note to zero
    int newNote=0;
    
    for (int k=0; k < NUM_FRETS; k++){
      if (digitalRead(fretPins[k]) == HIGH){
        newNote=k+1;
        }
    }

   //Turn String Low
   digitalWrite(stringPins[i], LOW);
   if (newNote != currentNote[i]){
      MIDImessage(noteOFF, currentNote[i]+stringOffsets[i], VELOCITY);
      if (newNote != 0){
        MIDImessage(noteON, newNote+stringOffsets[i], VELOCITY);
      }
      currentNote[i] = newNote;
   }
  }
}


void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}

