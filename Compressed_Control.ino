const int start = 24;
const int select = 21;
const int A = 25;
const int B = 22;
const int L = 26;
const int R = 27;
const int D_U = 51;
const int D_R = 52;
const int D_D = 53;
const int D_L = 50;
const int Z = 44;
unsigned long iteration = 0;
unsigned long IT = 0;

const bool resetFlag = false;
const bool saveFlag = false;
const int downToSave = 0;

#include "instructions.h"
#include "routines.h"
#include "parsing.h"

const int LED = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(start,INPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  Serial.begin(9600);
  releaseButtons();
}

void loop() {
  if (resetFlag){
    Reset();
    exit(0);
  }
  if (saveFlag){
    Save();
    exit(0);
  }
  
  
  parseInsts(Instructions[IT],Delays[IT]);

  IT = IT+1;
  if (IT == halfInstructions)
  {
    digitalWrite(LED,LOW);
    releaseButtons();
    exit(0);
  }
}
