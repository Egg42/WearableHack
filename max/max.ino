/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */

// constants won't change. They're used here to 
// set pin numbers:
const int Pin1 = 3;     // the number of the pushbutton pin
const int Pin2 = 4;
const int Pin3 = 5;
const int Pin4 = 6;
const int Pin5 = 7;
const int Pin6 = 8;
const int ledPin =  13; // the number of the LED pin
// variables will change:

void checkButtonState(int inputPinNumber,int outputPinNumber){
  int buttonState = 0;
  // read the state of the pushbutton value:
  buttonState = digitalRead(inputPinNumber);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(outputPinNumber, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(outputPinNumber, LOW);
  }
}

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);  
  // initialize the pushbutton pin as an input:
  pinMode(Pin1, INPUT);  
  pinMode(Pin2, INPUT);  
  pinMode(Pin3, INPUT);  
  pinMode(Pin4, INPUT);    
  pinMode(Pin5, INPUT);    
  pinMode(Pin6, INPUT);  
}

void loop(){
checkButtonState(Pin1,ledPin);
checkButtonState(Pin2,ledPin);
checkButtonState(Pin3,ledPin);
checkButtonState(Pin4,ledPin);
checkButtonState(Pin5,ledPin);
checkButtonState(Pin6,ledPin);
}

