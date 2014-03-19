/*
 Rock Paper Scissors Lizzard Spock
 Glove Code
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 modified March 18th,2014
 by Max Bolling
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
const int ledPin =  13; // the number of the LED Test pin

char* Moves[] = {"Rock", //Array of Moves
"Paper",
"Scissors",
"Lizzard",
"Spock" };

String getMoves(int inputInt){ //Takes input numbers and converts to
  if(inputInt==4)return Moves[1];//Return Rock
  if(inputInt==3)return Moves[0];//Return Paper
  if(inputInt==7)return Moves[4];//Return Spoc
  if(inputInt==5)return Moves[2];//Return Scissors
    if(inputInt==6)return Moves[3];//Return Lizzard
 }
 
String checkButtonState(int inputPinNumber,int outputPinNumber,boolean canMove){//can be void when messanger is added
  int buttonState = 0;
  // read the state of the pushbutton value:
  buttonState = digitalRead(inputPinNumber);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
     return getMoves(inputPinNumber);//Put string messenger output here
     canMove = false;
     
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
  boolean moved == true;
  while(moved){
    checkButtonState(Pin1,ledPin,moved);
    checkButtonState(Pin2,ledPin,moved);
    checkButtonState(Pin3,ledPin,moved);
    checkButtonState(Pin4,ledPin,moved);
    checkButtonState(Pin5,ledPin,moved);
    checkButtonState(Pin6,ledPin,moved);
  }
}


