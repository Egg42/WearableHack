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
 modified March 19th
 by Michial Green II & MAx Bolling (CCC)
 
 http://www.arduino.cc/en/Tutorial/Button
 */


#include <SPI.h>
#include <WiFi.h>

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

//This function will send your player number and gesture to the server
void sendGesture(WiFiClient &client, int playernum, String gesture){
  
  IPAddress server(192,168,1,2);
  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {    
    Serial.println("connected to server");
  }
    String get = "Get /rps.php?p=";
           get += playernum;
           get += "&p=";
           get += gesture;
           get += " HTTP/1.1";
    Serial.println(get);
    Serial.println("host: 192.168.1.2");
    Serial.println("Connection: close");
    Serial.println();
    client.println("GET /rps.php?p=5&t=rock HTTP/1.1");
    client.println("host: 192.168.1.2");
    client.println("Connection: close");
    client.println();
}
//****************************************
//DECLARE CONNECTION INFO
//*****************************************

char ssid[] = "TeamAwesome"; //  your network SSID (name) //whoare you connecting to? TeamAwesome
char pass[] = "teamawesome"; //  Your network password, hardcode i guess, teamawesome
int keyIndex = 0;            // your network key Index number (needed only for WEP)

//Initialize an IP adress object to have, this particular object will be used when you
//actually attempt to connect later
IPAddress server(192,168,1,2);  
int status = WL_IDLE_STATUS;

int PORT = 80;
//Lastly, we will create an instance of WiFiClient to allow out
//Galileo to be the client of some Wifi Server
WiFiClient client;
//if you are actually in range of the raspberry pie, and want to connect
//use IP address: 192.168.1.2
//but if you connect over the web use 
//ip address 50.184.225.93
int player = 1;


// constants won't change. They're used here to 
// set pin numbers:

const int Pin1 = 2;     // the number of the pushbutton pin
const int Pin2 = 3;
const int Pin3 = 4;
const int Pin4 = 5;
const int Pin5 = 6;
const int Pin6 = 7;    //pin6 is irrelevant
const int ledPin =  13; // the number of the LED Test pin
boolean standby = true;

char* Moves[] = {"Rock", //Array of Moves
"Paper",
"Scissors",
"Lizzard",
"Spock" };

String getMoves(int inputInt){ //Takes input numbers and converts to
  if(inputInt==2)return Moves[0];//Return Rock
  if(inputInt==3)return Moves[1];//Return Paper and QUICKLY LOOPS!!!!!!!
  if(inputInt==4)return Moves[2];//Return Scissors WORKS
  if(inputInt==5)return Moves[3];//Return Lizard
  if(inputInt==6)return Moves[4];//Return Spock MISS
  if(inputInt==7)return Moves[4];
  else return "_";
 }
 
String checkButtonState(int inputPinNumber){//can be void when messanger is added
  int buttonState = 0;
  // read the state of the pushbutton value:
  buttonState = digitalRead(inputPinNumber);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:  
     Serial.println("Deteced Gesture:");
     Serial.println(getMoves(inputPinNumber));    
     return getMoves(inputPinNumber);//Put string messenger output here
  } 
}


void setup() {
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
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
  
  // initialize the pushbutton pin as an input:
  pinMode(Pin1, INPUT);  
  pinMode(Pin2, INPUT);  
  pinMode(Pin3, INPUT);  
  pinMode(Pin4, INPUT);    
  pinMode(Pin5, INPUT);    
  pinMode(Pin6, INPUT);  
  
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
  
  
  
}

void loop(){
 if(standby){
  delay(3000);
  // Serial.println("STANDBY CHECK:");
 if (checkButtonState(Pin1)== "Rock"){
  Serial.println("Detected Rock waiting for input");
  delay(4000);
  standby = false;
 }
}
else{
  Serial.println("ELSE CHECK:");
  String gesture = "";
  gesture += checkButtonState(Pin1);
  gesture += checkButtonState(Pin2);
  gesture += checkButtonState(Pin3);
  gesture += checkButtonState(Pin4);
  gesture += checkButtonState(Pin5);
  gesture += checkButtonState(Pin6);
  Serial.print("Sending Gesture :");
  Serial.println(gesture);
  sendGesture(client, player, gesture);
  standby = true;
}
}



