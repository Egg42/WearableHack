
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


#include <SPI.h>
#include <WiFi.h>


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

//*****************************************
//DECLARE INPUT OUT VARIABLES 
//**************************************
//varables in these arrays allow for interacting with D0-D12
//in the case of needing button states, you would set them from the inputs array

//in the case you need to set HIGH or LOW on an output, use the outputs array
//In case you need to READ the state of an input, use the inputs array
//ALL OF THESE 14 SIZE ARRAYS MAKE IT EASY TO USE i IN A FOR LOOP TO REFER TO (D0-D13)

int inputs[14];//inputs are buttons
int outputs[14];//outputs are like lights

//later there will be loops that set these pins (D0-D13) if your pin is true in isInput, then you will
//be set to input. these arrays should ALWAYS be the opposite of each other to ensure the pin setup is correct
boolean isInput[14] = {false,false,true,true,true,true,true,true,true,true,true,true,true, false};        //pin 13 (D13) is designated an output on
boolean isOutput[14] = {true,true,false,false,false,false,false,false,false,false,false,false,false,true};//Galileo itself. true on isOutput, false on isInput

int buttonState = 0;         // variable for reading the pushbutton status

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
  pinMode(2, INPUT);     
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 

  String fv = WiFi.firmwareVersion();
  if( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");
  
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
//  client.println("GET /search?q=arduino HTTP/1.1");
  client.println("POST / \"HEllo Doawg!\" HTTP/1.1");
  client.println("Host: www.google.com");
  //  client.println("Connection: close");
  //  client.println();
  }
}

void loop() {
  // if there are incoming bytes available 
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
    client.write("Hello Eric,  I am Player 1  \n");
    Serial.write(c);
  }
  buttonState = digitalRead(2);

  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(2, HIGH);  
    client.write("Hello Eric,  I am Player 1, I and PIN 2 is HIGH, Also LED-13 is GREEN\n");

  } 
  else {
    // turn LED off:
    digitalWrite(2, LOW); 
    client.write("Hello Eric,  I am Player 1, I and PIN 2 is LOW, Also LED-13 is DARK\n");
  }
  client.println("GET Hello Eric: Code EGGNOG!!!!!");

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();

    // do nothing forevermore:
    while(true);
  }
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





