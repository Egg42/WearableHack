
/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using a WiFi shield.
 
 This example is written for a network using WPA encryption. For 
 WEP or WPA, change the Wifi.begin() call accordingly.
 
 This example is written for a network using WPA encryption. For 
 WEP or WPA, change the Wifi.begin() call accordingly.
 
 Circuit:
 * WiFi shield attached
 
 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */
 
 #define ROCK 2
 #define PAPER 3
 #define SCISSORS 4
 #define LIZARD 5
 #define SPOCK 6

#include <SPI.h>
#include <WiFi.h>

int getGesture(){
  if(digitalRead(2)==HIGH){return ROCK;}
   if(digitalRead(3)==HIGH){return PAPER;}
    if(digitalRead(4)==HIGH){return SCISSORS;}
     if(digitalRead(5)==HIGH){return LIZARD;}
      if(digitalRead(6)==HIGH){return SPOCK;}
}

void checkButtonState(int inPin, int outPin = 13){
   int buttonState = 0;
  
    buttonState = digitalRead(inPin);
   if(buttonState == HIGH){
     switch(inPin){
        case ROCK:Serial.println("ROCK");break;
        case PAPER:Serial.println("PAPER");break;
        case SCISSORS:Serial.println("Scissors");break;
        case LIZARD:Serial.println("LIZARD");break;
        case SPOCK: Serial.println("SPOCK"); break;
     }
     delay(1000);
   digitalWrite(outPin,HIGH);
   } 
   else{
    digitalWrite(outPin,LOW); 
   }
}

//DECLARE GAME VARIABLES
int gameState = 0;
//when a button is pressed, we want to acknowledge the first one
//and put the button on cooldown.
const int buttonCD = 6;
//This character array is going to hold the current
//gesture as gained by the get Gesture function
int currentGesture = ROCK;

const int LEDw = 9, LEDy = 10, LEDr = 11, LEDg = 12, LEDo = 13;



//****************************************
//DECLARE CONNECTION INFO
//*****************************************

char ssid[] = "TeamAwesome"; //  your network SSID (name) //whoare you connecting to?
char pass[] = "teamawesome"; //  Your network password, hardcode i guess
int keyIndex = 0;            // your network key Index number (needed only for WEP)

//Initialize an IP adress object to have, this particular object will be used when you
//actually attempt to connect later
IPAddress server(192,168,1,2);  
int status = WL_IDLE_STATUS;

int PORT = 80;

//*****************************************
//DECLARE INPUT OUT VARIABLES 
//**************************************
//varables in these arrays allow for interacting with D0-D12
//in the case of needing button states, you would set them from the inputs array

//in the case you need to set HIGH or LOW on an output, use the outputs array
//In case you need to READ the state of an input, use the inputs array
//ALL OF THESE 14 SIZE ARRAYS MAKE IT EASY TO USE i IN A FOR LOOP TO REFER TO (D0-D13)

const int numPins = 14;
int inputs[numPins];//inputs are buttons
int outputs[numPins];//outputs are like lights

//later there will be loops that set these pins (D0-D13) if your pin is true in isInput, then you will
//be set to input. these arrays should ALWAYS be the opposite of each other to ensure the pin setup is correct
boolean isInput[numPins] = {false,false,true,true,true,true,true,true,true,true,false,false,false, false};        //pin 13 (D13) is designated an output on
boolean isOutput[numPins] = {false,false,false,false,false,false,false,false,false,false,true,true,true,true};//Galileo itself. true on isOutput, false on isInput

int buttonState = 0;  // variable for reading the pushbutton status

//Lastly, we will create an instance of WiFiClient to allow out
//Galileo to be the client of some Wifi Server
WiFiClient client;



//***********************************
//BEGIN setup
//***********************************

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  //Set all of the pin modes based on is output and is input
  for (int i=0;i<numPins;i++){//these pins are for INPUTS
     if(isInput[i]){
        pinMode(i,INPUT); 
     }
  }
  for(int c = 0; c < numPins; c++){//these pins are used for OUTPUTS
    if(isOutput[c]){
       pinMode(c,OUTPUT); 

    }
  }  
  
  //ERROR CHECKING IS HERE!!
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  //Check the firmware version
  String fv = WiFi.firmwareVersion();
  if( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");
  
  //TIME TO CONNECT*****************
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);
  
    // wait 10 seconds for connection:
    delay(10000);
  } 
  Serial.println("Connected to wifi");
  printWifiStatus();
  
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
  
  // Make a HTTP request:    
  client.println("GET /rps.php?p=5&t=rock HTTP/1.1");
  client.println("host: 192.168.1.2");
  client.println("Connection: close");
  client.println();
  }
}


//*************************************
//BEGIN LOOPS
//************************************
void loop() {
  // if there are incoming bytes available 
  // from the server, read them and print them:
  //currentGesture = getGesture();
  //delay(1000);            
  while (client.available()) {
    char c = client.read();
    client.write("Hello Eric,  I am Player 1  \n");
    Serial.write(c);
  }
  //client.println("GET Hello Eric: Code EGGNOG!!!!!");

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    //while(true);
  }
  
 checkButtonState(ROCK,13);
 checkButtonState(PAPER,13);
 checkButtonState(SCISSORS,13);
 checkButtonState(LIZARD,13);
 checkButtonState(SPOCK,13);
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}






