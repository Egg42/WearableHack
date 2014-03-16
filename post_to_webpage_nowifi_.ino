
#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0x90,0xA2,0xDA,0x00,0x55,0x8D};  //Replace with your Ethernet shield MAC
EthernetClient client;

void setup()
{
Serial.begin(9600);
Ethernet.begin(mac);
delay(1000);
Serial.println("connecting...");
}

void loop(){
String data;
data+="";
data+="data=12.7%2C0%2C50"; // Use HTML encoding for comma's
data+="&submit=Submit"; // Submitting data

if (client.connect("www.your-website.com",80)) {
Serial.println("connected");
client.println("POST /pageThatTakesPostData.php HTTP/1.1");
client.println("Host: www.your-website.com");
client.println("Content-Type: application/x-www-form-urlencoded");
client.println("Connection: close");
client.print("Content-Length: ");
client.println(data.length());
client.println();
client.print(data);
client.println();

//Prints your post request out for debugging
Serial.println("POST /pageThatTakesPostData.php HTTP/1.1");
Serial.println("Host: www.your-website.com");
Serial.println("Content-Type: application/x-www-form-urlencoded");
Serial.println("Connection: close");
Serial.print("Content-Length: ");
Serial.println(data.length());
Serial.println();
Serial.print(data);
Serial.println();
}
delay(2000);

if (client.connected()) {
Serial.println();
Serial.println("disconnecting.");
client.stop();
}

}
