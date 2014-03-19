#include <SPI.h>
#include <WiFi.h>

//This function will send your player number and gesture to the server
void sendGesture(WiFiClient &client, int playernum, String gesture){
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


//DECLARE GAME VARIABLES
int gameState = 0;
//when a button is pressed, we want to acknowledge the first one
//and put the button on cooldown.
const int buttonCD = 6;
//This character array is going to hold the current
//gesture as gained by the get Gesture function



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
  
  // Send the gesture tot he server
  sendGesture(client, 9001, "ROCK");  
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






