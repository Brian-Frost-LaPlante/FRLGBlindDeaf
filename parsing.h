void oneButton(int pin, bool isOn) {
  if (isOn) {
    pinMode(pin,OUTPUT);
    digitalWrite(pin,LOW);
  }
  else {
    pinMode(pin,INPUT);
  }
}

void releaseButtons() {
  // Do this after every command
  oneButton(D_L,0);
  oneButton(D_D,0);
  oneButton(D_R,0);
  oneButton(D_U,0);
  oneButton(R,0);
  oneButton(L,0);
  oneButton(B,0);
  oneButton(A,0);
  oneButton(Z,0);
  oneButton(select,0);
  oneButton(start,0);
  delay(40);
}


void doInst(int inst) {
  // After being turned from nibble to number, gets performed here
  // A   = 0000, B  = 0001, S  = 0010, D_U = 0011, D_D = 0100, D_L = 0101
  // D_R = 0110, UB = 0111, DB = 1000, LB  = 1001, RB  = 1010, W   = 1011

  switch (inst) {
  case 0: // A
    oneButton(A,1);
  iteration = iteration+1;
    Serial.println("INPUT " + String(iteration)+ ": A");
    break;
  case 1: // B
    oneButton(B,1);
      iteration = iteration+1;
    Serial.println("INPUT " + String(iteration)+ ": B");
    break;
  case 2: // S
    oneButton(start,1);
      iteration = iteration+1;
    Serial.println("INPUT " + String(iteration)+ ": START");
    break;
  case 3: // D_U
    oneButton(D_U,1);
      iteration = iteration+1;
    Serial.println("INPUT " + String(iteration)+ ": UP");
    break;
  case 4: // D_D
    oneButton(D_D,1);
      iteration = iteration+1;
    Serial.println("INPUT " + String(iteration)+ ": DOWN");
    break;
  case 5: // D_L
    oneButton(D_L,1);
      iteration = iteration+1;
    Serial.println("INPUT " + String(iteration)+ ": LEFT");
    break;
  case 6: // D_R
    oneButton(D_R,1);
      iteration = iteration+1;
    Serial.println("INPUT " + String(iteration)+ ": RIGHT");
    break;
  case 7: // UB
    oneButton(D_U,1);
    oneButton(B,1);
          iteration = iteration+1;
    Serial.println("INPUT " + String(iteration)+ ": UP+B");
    break;
  case 8: // DB
    oneButton(D_D,1);
    oneButton(B,1);
          iteration = iteration+1;
    Serial.println("INPUT " + String(iteration)+ ": DOWN+B");
    break;
  case 9: // LB
    oneButton(D_L,1);
    oneButton(B,1);
          iteration = iteration+1;
    Serial.println("INPUT " + String(iteration)+ ": LEFT+B");
    break;
  case 10: // RB
    oneButton(D_R,1);
    oneButton(B,1);      
    iteration = iteration+1;
    Serial.println("INPUT " + String(iteration)+ ": RIGHT+B");
    break;
  case 11: // W
    // Here, we do nothing!
    break;
  }
}

void parseInstsStd(byte inst, unsigned long holdTime) {
  // This maps the instructions to a pinout.
  // read bits one by one.
  int inst1 = bitRead(inst,0) + 2*bitRead(inst,1) + 4*bitRead(inst,2) + 8*bitRead(inst,3);

  int inst2 = bitRead(inst,4) + 2*bitRead(inst,5) + 4*bitRead(inst,6) + 8*bitRead(inst,7);

  unsigned int delay1 = bitRead(holdTime,0) + 2*bitRead(holdTime,1) + 4*bitRead(holdTime,2) 
                    + 8*bitRead(holdTime,3) + 16*bitRead(holdTime,4) + 32*bitRead(holdTime,5) 
                    + 64*bitRead(holdTime,6) + 128*bitRead(holdTime,7) + 256*bitRead(holdTime,8) 
                    + 512*bitRead(holdTime,9) + 1024*bitRead(holdTime,10) + 2048*bitRead(holdTime,11) 
                    + 4096*bitRead(holdTime,12) + 8192*bitRead(holdTime,13) + 16384*bitRead(holdTime,14) 
                    + 32768*bitRead(holdTime,15);

  unsigned int delay2 = bitRead(holdTime,16) + 2*bitRead(holdTime,17) + 4*bitRead(holdTime,18) 
                    + 8*bitRead(holdTime,19) + 16*bitRead(holdTime,20) + 32*bitRead(holdTime,21) 
                    + 64*bitRead(holdTime,22) + 128*bitRead(holdTime,23) + 256*bitRead(holdTime,24) 
                    + 512*bitRead(holdTime,25) + 1024*bitRead(holdTime,26) + 2048*bitRead(holdTime,27) 
                    + 4096*bitRead(holdTime,28) + 8192*bitRead(holdTime,29) + 16384*bitRead(holdTime,30) 
                    + 32768*bitRead(holdTime,31);

  // before each instruction, do a button release
  // then instruction based on number, followed by delay
  releaseButtons();
  doInst(inst1);
  delay(delay1);
  releaseButtons();
  doInst(inst2);
  delay(delay2);
}

void walkCycle(){
  int iteration = 0;
  Serial.println("Walk Cycle");
  while (iteration < halfWalk){
    
    parseInstsStd(WalkCycle[iteration],WalkCycleDelays[iteration]);
    iteration = iteration+1;
  }
}

void intro(){
  int iteration = 0;
  Serial.println("Walk Cycle");
  while (iteration < halfIntro){
    
    parseInstsStd(Intro[iteration],IntroDelays[iteration]);
    iteration = iteration+1;
  }
}

void emberCycle(){
  int embernumber = 0;
  int iteration = 0;
  Serial.println("Ember Cycle");
  while (embernumber<17) {
    Serial.println(embernumber);
    while (iteration < halfEmber){
      parseInstsStd(Ember[iteration],EmberDelays[iteration]);
      iteration = iteration+1;
    }
    iteration = 0;
  embernumber = embernumber+1;
  }
}

void growlCycle(unsigned int numCycles){
  int growlnumber = 0;
  int iteration = 0;
  Serial.println("Growl Cycle");
  while (growlnumber<numCycles) {
    Serial.println(growlnumber);
    while (iteration < halfGrowl){
      parseInstsStd(Growl[iteration],GrowlDelays[iteration]);
      iteration = iteration+1;
    }
    iteration = 0;
  growlnumber = growlnumber+1;
  }
}

void dougCycle1(){
  int dougnumber = 0;
  int iteration = 0;
  while (dougnumber<49) { // Doug Cycle 1 happens 49 times
    Serial.println("Doug  Cycle 1\n");
    Serial.println(dougnumber);
    while (iteration < halfDoug1){
      parseInstsStd(Doug1[iteration],Doug1Delays[iteration]);
      iteration = iteration+1;
    }
  growlCycle(30); // End of each doug 1 cycle is 30 growl cycles
  iteration = 0;
  dougnumber = dougnumber+1;
  }
}

void dougCycle2(){
  int dougnumber = 0;
  int iteration = 0;
  while (dougnumber<2) { // Doug Cycle 2 happens twice each time
    Serial.println("Doug  Cycle 2\n");
    Serial.println(dougnumber);
    while (iteration < halfDoug2){
      parseInstsStd(Doug2[iteration],Doug2Delays[iteration]);
      iteration = iteration+1;
    }
  growlCycle(35); // End of each doug 2 cycle is 35 growl cycles
  iteration = 0;
  dougnumber = dougnumber+1;
  }
}

void dougCycle3(){
  int dougnumber = 0;
  int iteration = 0;
  while (dougnumber<90) { // Doug Cycle 3 happens NINETY times
    Serial.println("Doug  Cycle 3\n");
    Serial.println(dougnumber);
    while (iteration < halfDoug3){
      parseInstsStd(Doug3[iteration],Doug3Delays[iteration]);
      iteration = iteration+1;
    }
  growlCycle(36); // End of each doug 3 cycle is 36 growl cycles
  iteration = 0;
  dougnumber = dougnumber+1;
  }
}

void dougCycle4(){
  int dougnumber = 0;
  int iteration = 0;
  while (dougnumber<159) { // Doug Cycle 4 happens ONE HUNDRED AND FIFTY NINE times
    Serial.println("Doug  Cycle 4\n");
    Serial.println(dougnumber);
    while (iteration < halfDoug4){
      parseInstsStd(Doug4[iteration],Doug4Delays[iteration]);
      iteration = iteration+1;
    }
  growlCycle(41); // End of each doug 4 cycle is 41 growl cycles
  iteration = 0;
  dougnumber = dougnumber+1;
  }
}

void abmash(int ab, unsigned int numCycles, unsigned int presstime){
  // ab = 0,1
  int n = 0;
  while (n < numCycles){
    releaseButtons();
    doInst(ab);
    delay(presstime);
  }
}

void walkmash(int udlr, unsigned int numCycles){
  // udlr = 3456 
  int n = 0;
  while (n < numCycles){
    releaseButtons();
    doInst(udlr);
    delay(84);
    releaseButtons();
    doInst(11); //w
    delay(267);
  }
}

void parseInsts(byte inst, unsigned long holdTime) {
  // This maps the instructions to a pinout.
  // read bits one by one.
  // ORDER: start select A B L R D_U D_R D_D D_L
  int inst1 = bitRead(inst,0) + 2*bitRead(inst,1) + 4*bitRead(inst,2) + 8*bitRead(inst,3);

  int inst2 = bitRead(inst,4) + 2*bitRead(inst,5) + 4*bitRead(inst,6) + 8*bitRead(inst,7);

  unsigned int delay1 = bitRead(holdTime,0) + 2*bitRead(holdTime,1) + 4*bitRead(holdTime,2) 
                    + 8*bitRead(holdTime,3) + 16*bitRead(holdTime,4) + 32*bitRead(holdTime,5) 
                    + 64*bitRead(holdTime,6) + 128*bitRead(holdTime,7) + 256*bitRead(holdTime,8) 
                    + 512*bitRead(holdTime,9) + 1024*bitRead(holdTime,10) + 2048*bitRead(holdTime,11) 
                    + 4096*bitRead(holdTime,12) + 8192*bitRead(holdTime,13) + 16384*bitRead(holdTime,14) 
                    + 32768*bitRead(holdTime,15);

  unsigned int delay2 = bitRead(holdTime,16) + 2*bitRead(holdTime,17) + 4*bitRead(holdTime,18) 
                    + 8*bitRead(holdTime,19) + 16*bitRead(holdTime,20) + 32*bitRead(holdTime,21) 
                    + 64*bitRead(holdTime,22) + 128*bitRead(holdTime,23) + 256*bitRead(holdTime,24) 
                    + 512*bitRead(holdTime,25) + 1024*bitRead(holdTime,26) + 2048*bitRead(holdTime,27) 
                    + 4096*bitRead(holdTime,28) + 8192*bitRead(holdTime,29) + 16384*bitRead(holdTime,30) 
                    + 32768*bitRead(holdTime,31);

  // Involved cycles
  if ((inst1 == 0)&&(inst2==12)) { // walk
    walkCycle();
  }
  else if ((inst1 == 1)&&(inst2==12)) { // ember
    emberCycle();
  }
  else if ((inst1 == 2)&&(inst2==12)) { // growl
    growlCycle(delay1);
  }
  else if ((inst1 == 3)&&(inst2==12)) { // doug1
    dougCycle1();
  }
  else if ((inst1 == 4)&&(inst2==12)) { // doug2
    dougCycle2();
  }
  else if ((inst1 == 5)&&(inst2==12)) { // doug3
    dougCycle3();
  }
  else if ((inst1 == 6)&&(inst2==12)) { // doug4
    dougCycle4();
  }
  else if ((inst1 == 8)&&(inst2==12)) { // intro, 7 is skipped in case I throw in "Doug 5"
    intro();
  }

  // "button-mash" cycles
  else if ((inst1 == 0)&&(inst2==14)) { // amash
    abmash(0,delay1,delay2);
  }
  else if ((inst1 == 1)&&(inst2==14)) { // bmash
    abmash(1,delay1,delay2);
  }
  else if ((inst1 == 2)&&(inst2==14)) { // walkup
    walkmash(3,delay1);
  }
  else if ((inst1 == 3)&&(inst2==14)) { // walkdown
    walkmash(4,delay1);
  }
  else if ((inst1 == 4)&&(inst2==14)) { // walkleft
    walkmash(5,delay1);
  }
  else if ((inst1 == 5)&&(inst2==14)) { // walkright
    walkmash(6,delay1);
  }


  else {
  // before each instruction, do a button release
  // then instruction based on number, followed by delay
  releaseButtons();
  doInst(inst1);
  delay(delay1);
  releaseButtons();
  doInst(inst2);
  delay(delay2);
  }
}


void Reset() {
     releaseButtons();
    delay(2000);
    // This is a sequence of commands that resets the game
    oneButton(Z,true);
    delay(2000);
    releaseButtons();
    delay(2000);
    oneButton(A,true);
    delay(2000);
    releaseButtons();
    delay(2000);
    oneButton(D_L,true);
    delay(2000);
    releaseButtons();
    delay(2000);
    oneButton(A,true);
    delay(2000);
    releaseButtons();
    delay(2000);
    oneButton(A,true);
    delay(2000);
    releaseButtons();
    delay(2000);
}

void Save() {
     releaseButtons();
    delay(2000);
    // This is a sequence of commands that saves the game
    oneButton(start,true);
    delay(2000);
    int downNum = 0;
    while (downNum < downToSave){
      releaseButtons();
      delay(2000);
      oneButton(D_D,true);
      delay(40);
      downNum = downNum+1;
    }
    releaseButtons();
    delay(2000);
    oneButton(A,true);
    delay(2000);
    releaseButtons();
    delay(2000);
    oneButton(A,true);
    delay(2000);
    releaseButtons();
    delay(2000);
    oneButton(A,true);
    delay(2000);
    releaseButtons();
    delay(20000);
    oneButton(B,true);
    delay(2000);
    releaseButtons();
    delay(2000);
    oneButton(B,true);
    delay(2000);
    releaseButtons();
    delay(2000);
    oneButton(B,true);
    delay(2000);
    releaseButtons();
}
