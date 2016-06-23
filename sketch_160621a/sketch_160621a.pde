/*
  Processing sketch to run with this example
 =====================================================
 
 // Processing UDP example to send and receive string data from Arduino
 // press any key to send the "Hello Arduino" message
 */
import processing.serial.*;

import hypermedia.net.*;

UDP udp;  // define the UDP object


//****************************************************************
void setup() {
  size(1000, 600);


  PFont font = createFont("arial", 20); // crée un objet de police texte


  udp = new UDP( this, 6000 );  // create a new datagram connection on port 6000
  udp.log( true );     // <-- printout the connection activity
  udp.listen( true );           // and wait for incoming message


  background(0);
  textSize(32);
  fill(255, 100, 100);
  text("TEST CONNECTION UDP ETHERNET", 380, 28);
}

//*********************************************
void draw()
{
}
//**********************************************
//---------------------------------------
void keyPressed() {
  String ip       = "192.168.1.20";  // the remote IP address
  int port        = 3069;    // the destination port

  udp.send("Hello World", ip, port );   // the message to send
  println("udp.send(Hello World, ip, port )");
}
//-------------------------------------------
//void receive( byte[] data ) {       // <-- default handler
  void receive( byte[] data, String ip, int port ) {  // <-- extended handler

  for (int i=0; i < data.length; i++)
    print(char(data[i]));
  println();
}