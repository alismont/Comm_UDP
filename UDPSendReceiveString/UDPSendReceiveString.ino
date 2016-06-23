/*
  UDPSendReceive.pde:
  This sketch receives UDP message strings, prints them to the serial port
  and sends an "acknowledge" string back to the sender

  A Processing sketch is included at the end of file that can be used to send
  and received messages for testing with a computer.

  created 21 Aug 2010
  by Michael Margolis

  This code is in the public domain.
*/


#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include "Settimino.h"
#include <SD.h>
#include <Timer.h>
#include "TimerOne.h"

int pin2 = 2;
int pin13 = 13;
int pin52 = 52;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0x90, 0xA2, 0xDA, 0x0E, 0x05, 0xBD
};
IPAddress ip(192, 168, 1, 20);

unsigned int localPort = 3069;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back

int T[100], CptT[100];
bool TDN[100];

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;




//-------------------------------------------------------
void setup() {
  Serial.begin(9600);
  // start the Ethernet and UDP:
  Serial.println("Start");
  Ethernet.begin(mac, ip);
  Udp.begin(localPort);
  Serial.println(localPort);
  Serial.println("localPort");

  pinMode(pin2, INPUT);           // set pin to input
  digitalWrite(pin2, HIGH);
  pinMode(pin13, OUTPUT);

  Timer1.initialize(100000);         // initialize timer1
  Timer1.attachInterrupt(callback);

}
//---------------------------------------------------------
void loop() {

  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();

    for (int i = 0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }

    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.println("Contents:");
    Serial.println(packetBuffer);

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
    Serial.println(ReplyBuffer);
  }

  
  if (!digitalRead(pin2)) {
    CptT[1] = true;
  }
  else {
    T[1] =  0.0;
    TDN[1] =  0.0;
    CptT[1] = false;
  }
  if (T[1] >= 200) {
    TDN[1] =  1.0;
    T[1] = 200;
  }
    if (TDN[1] == 1) {

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write("Test Reponse");
    Udp.endPacket();
  }
}
//-----------------------------------------
void Tempo1() {

}

//--------------------------------------
void callback() {
  if (CptT[1]) {
    T[1] =  T[1] + 1.0;
  }
}
//----------------------------------------


