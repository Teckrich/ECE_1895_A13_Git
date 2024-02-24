/*
  Adam Nichols
  Prof. Dickerson
  ECE 1895 - Junior Design
  10 February 2024

  LED Blink Single:

  Blink a single LED lamp while a pushbutton is pressed.
*/

// function prototypes
void blinkLED(int LEDNUM);
void deassertAllLEDs(void);
void TuneItCorrect(void);
void FretItCorrect(void);
void wrong(void);

// initialize constant global variables
// set pin numbers
const int actionRED = 14;
const int encoderGREEN = 13;
const int encoder1BLUE = 8;
const int encoder2BLUE = 9;
const int encoder3BLUE = 10;
const int encoder4BLUE = 11;
const int encoder1 = 0;
const int encoder2 = 1;
const int encoder3 = 2;
const int encoder4 = 3;

const int fretGREEN = 31;
const int fret1BLUE = 21;
const int fret2BLUE = 22;
const int fret3BLUE = 23;
const int fret4BLUE = 12;
const int fret1 = 15;
const int fret2 = 16;
const int fret3 = 17;
const int fret4 = 18;

const int joystick = 0;
const int joystickRED = 25;

const int switchit = 27;
const int switchitRED = 26;

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize  outputs (LEDs)
  pinMode(actionRED, OUTPUT);
  pinMode(encoderGREEN, OUTPUT);
  pinMode(encoder1BLUE, OUTPUT);
  pinMode(encoder2BLUE, OUTPUT);
  pinMode(encoder3BLUE, OUTPUT);
  pinMode(encoder4BLUE, OUTPUT);
  pinMode(fret1BLUE, OUTPUT);
  pinMode(fret2BLUE, OUTPUT);
  pinMode(fret3BLUE, OUTPUT);
  pinMode(fret4BLUE, OUTPUT);
  pinMode(fretGREEN, OUTPUT);
  pinMode(joystickRED, OUTPUT);
  pinMode(switchitRED, OUTPUT);

  // initialize input (pushbutton)
  pinMode(encoder1, INPUT);
  pinMode(encoder2, INPUT);
  pinMode(encoder3, INPUT);
  pinMode(encoder4, INPUT);
  pinMode(fret1, INPUT);
  pinMode(fret2, INPUT);
  pinMode(fret3, INPUT);
  pinMode(fret4, INPUT);
  pinMode(joystick, INPUT);
  pinMode(switchit, INPUT);

  
  // seed random generator, user twist first encoder to generate random seed
  int seed = 0;
  digitalWrite(encoder1BLUE,HIGH);
  while(1) {
    seed += 1;
    if(digitalRead(encoder1) == LOW) break;
  }
  digitalWrite(encoder1BLUE,LOW);
  randomSeed(seed);
  delay(1000);
}

// the loop function runs over and over again forever
void loop() {
  
  // wait a little bit before starting
  delay(500);
  
  // choose an encoder1
  int inputNum = random(9) + 1;

  // illuminate indicator LED
  if(inputNum == 1) digitalWrite(encoder1BLUE,HIGH);
  else if(inputNum == 2) digitalWrite(encoder2BLUE,HIGH);
  else if(inputNum == 3) digitalWrite(encoder3BLUE,HIGH);
  else if(inputNum == 4) digitalWrite(encoder4BLUE,HIGH);
  else if(inputNum == 5) digitalWrite(fret1BLUE,HIGH);
  else if(inputNum == 6) digitalWrite(fret2BLUE,HIGH);
  else if(inputNum == 7) digitalWrite(fret3BLUE,HIGH);
  else if(inputNum == 8) digitalWrite(fret4BLUE,HIGH);
  else if(inputNum == 9) digitalWrite(joystickRED,HIGH);
  else if(inputNum == 10) digitalWrite(switchitRED,HIGH);

  // variable to store last state of switchit
  int switchitLast = digitalRead(switchit);

  for(int i = 0; i < 5000; i++){
    // start loop, poll every 1ms
    delay(1);

    // check for input, if no input, skip rest of loop and run again
    if((digitalRead(encoder1) == HIGH) && (digitalRead(encoder2) == HIGH) && (digitalRead(encoder3) == HIGH) && (digitalRead(encoder4) == HIGH)
        && (digitalRead(fret1) == HIGH) && (digitalRead(fret2) == HIGH) && (digitalRead(fret3) == HIGH) && (digitalRead(fret4) == HIGH)
        && (digitalRead(switchit) == switchitLast)) {} //&& (analogRead(joystick) > 500) && (analogRead(joystick) < 600)){}

    // check for correct user input
    else if((digitalRead(encoder1) == LOW) && (inputNum == 1)) {
      TuneItCorrect();
      break;
    }  
    else if((digitalRead(encoder2) == LOW) && (inputNum == 2)) {
      TuneItCorrect();
      break;
    }
    else if((digitalRead(encoder3) == LOW) && (inputNum == 3)) {
      TuneItCorrect();
      break;
    }
    else if((digitalRead(encoder4) == LOW) && (inputNum == 4)) {
      TuneItCorrect();
      break;
    }
    // check for correct user input
    else if((digitalRead(fret1) == LOW) && (inputNum == 5)) {
      FretItCorrect();
      break;
    }  
    else if((digitalRead(fret2) == LOW) && (inputNum == 6)) {
      FretItCorrect();
      break;
    }
    else if((digitalRead(fret3) == LOW) && (inputNum == 7)) {
      FretItCorrect();
      break;
    }
    else if((digitalRead(fret4) == LOW) && (inputNum == 8)) {
      FretItCorrect();
      break;
    }
    
    else if(analogRead(joystick) >= 600 || analogRead(joystick) <= 500 && (inputNum == 9)) {
      blinkLED(joystickRED);
      break;
    }
    else if(digitalRead(switchit) != switchitLast && (inputNum == 10)) {
      blinkLED(switchitRED);
      break;
    }
    else{
      wrong();
      break;
    }


    // user ran out of time, end
    if(i == 4999){
      wrong();
      break;
    }
  }

  // wait a little before restarting
  delay(500);
}

// perform correct action response
void TuneItCorrect(void){
  deassertAllLEDs();
  blinkLED(encoderGREEN);
}

// perform correct action response
void FretItCorrect(void){
  deassertAllLEDs();
  blinkLED(fretGREEN);
}

// wrong action response
void wrong(void){
  deassertAllLEDs();
  blinkLED(actionRED);
}

// blink a given LED twice
void blinkLED(int LEDNUM) {
  // blink LEDs
  digitalWrite(LEDNUM,HIGH);
  delay(500);
  digitalWrite(LEDNUM,LOW);
  delay(500);
  digitalWrite(LEDNUM,HIGH);
  delay(500);
  digitalWrite(LEDNUM,LOW);
  delay(500);
}

// turn off all LEDs
void deassertAllLEDs(void) {
  // turn off all LEDs
  digitalWrite(actionRED,LOW);
  digitalWrite(encoderGREEN,LOW);
  digitalWrite(encoder1BLUE,LOW);
  digitalWrite(encoder2BLUE,LOW);
  digitalWrite(encoder3BLUE,LOW);
  digitalWrite(encoder4BLUE,LOW);
  digitalWrite(fretGREEN,LOW);
  digitalWrite(fret1BLUE,LOW);
  digitalWrite(fret2BLUE,LOW);
  digitalWrite(fret3BLUE,LOW);
  digitalWrite(fret4BLUE,LOW);
  digitalWrite(joystickRED,LOW);
  digitalWrite(switchitRED,LOW);
}
