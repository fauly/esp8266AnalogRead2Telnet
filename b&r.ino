#include <ESP8266WiFi.h>

const int numReadings = 1;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A0;

WiFiServer TelnetServer(23);
WiFiClient Telnet;

IPAddress ip (192,168,1,159);           //assigned ip address
IPAddress gateway (192,168,1,1);       //gateway of the network you're connected to
IPAddress subnet (255,255,255,0);      //subnet of the network your connected to

//IMPORTANT: use commas (,) and not full stops (.) to in the three addresses
//above,     and replace the SSID and password with your own when using the
//code


void handleTelnet() {
  if (TelnetServer.hasClient()) {
    if (!Telnet || !Telnet.connected()) {
      if (Telnet) Telnet.stop();
      Telnet = TelnetServer.available();
    } else {
      TelnetServer.available().stop();
    }
  }
}

void setup() {
  WiFi.config(ip, gateway, subnet);
  WiFi.begin("GodBless", "ThisMess");
  Serial.println();
  Serial.print("\nConnecting to: YOUR SSID ");
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  if (i == 21) {
      Serial.print("Could not connect to YOUR SSID");
     ESP.reset(); 
  }


  //start UART and the server
  Serial.begin(9600);
  TelnetServer.begin();
  TelnetServer.setNoDelay(true); 

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  
  Serial.print("Ready! Use 'telnet ");
  Serial.print(WiFi.localIP());
  Serial.println(" 23' to connect");
}

void loop() { 
  handleTelnet(); 

 // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  if (average > 190 && average < 195) {
    Telnet.println("Reading: 1");
  }
  else if(average > 225 && average < 235){
    Telnet.println("Reading: 2");
  }
  else if(average > 270 && average < 285){
    Telnet.println("Reading: 3");
  }
  else if(average > 360 && average < 380){
    Telnet.println("Reading: 4");
  }
  else if(average > 550 && average < 570){
    Telnet.println("Reading: 5");
  }
  else if(average > 160 && average < 170){
    Telnet.println("Reading: 6");
  }
  else if(average > 140 && average < 150){
    Telnet.println("Reading: 7");
  }
  else if(average > 116 && average < 125){
    Telnet.println("Reading: 8");
  }
  else if(average > 98 && average < 105){
    Telnet.println("Reading: 9");
  }
  else if(average > 85 && average < 98){
    Telnet.println("Reading: 10");
  }
  else if(average > 120 && average < 139){
    Telnet.println("Reading: Happy");
  }
  else if(average > 105 && average < 115){
    Telnet.println("Reading: Sad");
  }
  else{
  }
  delay(250); 
}
