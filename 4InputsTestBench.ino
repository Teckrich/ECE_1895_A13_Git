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
void correct(void);

// initialize constant global variables
// set pin numbers
const int encoderRED = 0;
const int encoderGREEN = 1;
const int encoderBLUE = 2;
const int encoder = 5;
const int fretRED = 10;
const int fretGREEN = 4;
const int fretBLUE = 3;
const int fret = 6;
const int joystick = 5;
const int joystickRED = 8;
const int switchit = 7;
const int switchitRED = 9;


// the setup function runs once when you press reset or power the board
void setup() {

  // initialize  outputs (LEDs)
  pinMode(encoderRED, OUTPUT);
  pinMode(encoderGREEN, OUTPUT);
  pinMode(encoderBLUE, OUTPUT);
  pinMode(fretRED, OUTPUT);
  pinMode(fretGREEN, OUTPUT);
  pinMode(fretBLUE, OUTPUT);
  pinMode(joystickRED, OUTPUT);
  pinMode(switchitRED, OUTPUT);

  // initialize input (pushbutton)
  pinMode(encoder, INPUT);
  pinMode(fret, INPUT);
  pinMode(switchit, INPUT);
}

// the loop function runs over and over again forever
void loop() {

  // choose an encoder
  int inputNum = random(4) + 1;

  // illuminate indicator LED
  if(inputNum == 1) digitalWrite(encoderBLUE,HIGH);
  else if(inputNum == 2) digitalWrite(fretBLUE,HIGH);
  else if(inputNum == 3) digitalWrite(joystickRED,HIGH);
  else if(inputNum == 4) digitalWrite(switchitRED,HIGH);

  // variable to store last state of switchit
  int switchitLast = digitalRead(switchit);

  for(int i = 0; i < 5000; i++){
    // start loop, poll every 1ms
    delay(1);

    // check for input, if no input, skip rest of loop and run again
    if((digitalRead(encoder) == HIGH) && (digitalRead(fret) == HIGH) && (digitalRead(switchit) == switchitLast) && (analogRead(joystick) > 500) && (analogRead(joystick) < 600)) {}

    // check for correct user input
    else if((digitalRead(encoder) == LOW) && (inputNum == 1)) {
      correct();
      break;
    }
    else if(digitalRead(fret) == LOW && (inputNum == 2)) {
      correct();
      break;
    }
    else if(analogRead(joystick) >= 600 || analogRead(joystick) <= 500 && (inputNum == 3)) {
      correct();
      break;
    }
    else if(digitalRead(switchit) != switchitLast && (inputNum == 4)) {
      correct();
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
  delay(1000);
}

// perform correct action response
void correct(void){
  deassertAllLEDs();
  blinkLED(encoderGREEN);
}

// wrong action response
void wrong(void){
  deassertAllLEDs();
  blinkLED(encoderRED);
}

// blink a given LED twice
void blinkLED(int LEDNUM) {
  // blink green LEDs
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
  digitalWrite(encoderRED,LOW);
  digitalWrite(encoderGREEN,LOW);
  digitalWrite(encoderBLUE,LOW);
  digitalWrite(fretRED,LOW);
  digitalWrite(fretGREEN,LOW);
  digitalWrite(fretBLUE,LOW);
  digitalWrite(joystickRED,LOW);
  digitalWrite(switchitRED,LOW);
}
