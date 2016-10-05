

char* notecolors[] = {'(115, 211, 109)','(115, 211, 109)','(115, 211, 109)','(115, 211, 109)','(83, 145, 238)','(98, 111, 223)','(251, 70, 106)','(228, 251, 70)','(142, 147, 179)','(193, 125, 196)','(83, 145, 238)','(105, 216, 143)'};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i=0; i<12; i++){
    Serial.println(notecolors[i]);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
