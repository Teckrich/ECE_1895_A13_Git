#include <avr/interrupt.h>
#include <avr/io.h>

ISR (INT0_vect);
volatile short buttonDown = 0;
short count = 0;

void setup() {

  pinMode(8, OUTPUT);  

  DDRD  &= ~(1 << PD2); // set pd2 as input
  PORTD |= (1 << PD2);  // pin pd2 pull-up enabled 
  
  EICRA |= (1<< ISC00); // ISC01 & ISC00 set to 01 -> enables interrupt on rising or falling edge
  EICRA &= ~(1 << ISC01); 

  EIMSK |= (1 << INT0); // Turn on INT0 interrupt
  sei();                // "Enables interrupts by setting the global interrupt mask"

  loop();
}

// Interrupt handler is triggered when button is depressed or unpressed
ISR (INT0_vect) {
  
  uint8_t temp = PIND & (1 << PD2); // get value from pin PD2

  if (temp) { // if button is not pressed (pulled-up high = 1)
    buttonDown = 0;
  } else { // button pressed (shorted to ground = 0)
    buttonDown = 1; // set button to 0
  }
}

void loop() {
  while (buttonDown) {
    
    count = 0;

    digitalWrite(8, HIGH);    // turn the LED on (HIGH is the voltage level)
    // poll button in 10ms increments for a total of 1s so that the LED turns off 'instantly'
    for (count = 0; count < 101; count++) { 
      if (buttonDown) {
        delay(10);
      }
      else {count = 101;} 
    }
    digitalWrite(8, LOW);     // turn the LED off by making the voltage LOW
    // poll button in 10ms increments for a total of 1s so that the LED turns on 'instantly'
    for (count = 0; count < 101; count++) { 
      if (buttonDown) {
        delay(10);
      }
      else {count = 101;} 
    }
  }        
}
