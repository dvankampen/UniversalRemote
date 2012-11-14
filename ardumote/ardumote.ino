/*
 * Ardumote sketch
 *
 * TODO: Write description
 *
 */

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUDP.h>

#include <avr/pgmspace.h> // for progmem, for LED MIME images
#define P(name)   static const prog_uchar name[] PROGMEM  // declare a static string

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] =  { 192,168,1,9 };

const int MAX_PAGENAME_LEN = 8;  // max characters in page name 
char buffer[MAX_PAGENAME_LEN+1]; // additional character for terminating null

EthernetServer server(80);
EthernetClient client;

EthernetUDP Udp;

int receivedCommands = 0;

int localPort = 56000;
int packetSize = 0;
// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

void setup()
{
  Serial.begin(115200);
  Ethernet.begin(mac, ip);
  server.begin();
  Udp.begin(localPort);
  delay(1000);
  Serial.println(F("Ready"));
}

void loop()
{

  client = server.available();
  if (client) {
    int type = 0;
    while (client.connected()) {
      if (client.available()) {
        // GET, POST, or HEAD
        memset(buffer,0, sizeof(buffer)); // clear the buffer
        if(client.readBytesUntil('/', buffer,MAX_PAGENAME_LEN)){ 
          if(strcmp(buffer, "GET ") == 0 )
            type = 1;
          else if(strcmp(buffer,"POST ") == 0)
            type = 2;
          // look for the page name
          memset(buffer,0, sizeof(buffer)); // clear the buffer
          if(client.readBytesUntil( '/', buffer,MAX_PAGENAME_LEN )) 
          {
            if (strcasecmp(buffer, "home") == 0) 
              showHome();
            else if (strcasecmp(buffer, "lcd") == 0) 
              showLCD();
            else if (strcasecmp(buffer, "tv") == 0) 
              showTV();
            else if (strcasecmp(buffer, "receiver") == 0) 
              showReceiver();
            else if (strcasecmp(buffer, "cable") == 0) 
              showCable();
            else if (strcasecmp(buffer, "status") == 0) 
              showStatus();
            else if(strcasecmp(buffer, "analog") == 0)
              showAnalog();
            else if(strcasecmp(buffer, "digital") == 0)
              showDigital();
            else if(strcmp(buffer, "change")== 0)
              showChange(type == 2);
            else
              unknownPage(buffer);
          }
        }
        break;
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
  
  packetSize = Udp.parsePacket();
  if (packetSize) {
    Udp.read(packetBuffer, packetSize);
    receivedCommands++;
  } // else, no packet received
}




void printP(const prog_uchar *str)
{
  // copy data out of program memory into local storage, write out in
  // chunks of 32 bytes to avoid extra short TCP/IP packets
  // from webduino library Copyright 2009 Ben Combee, Ran Talbott
  uint8_t buffer[32];
  size_t bufferEnd = 0;

  while (buffer[bufferEnd++] = pgm_read_byte(str++))
  {
    if (bufferEnd == 32)
    {
      client.write(buffer, 32);
      bufferEnd = 0;
    }
  }

  // write out everything left but trailing NUL
  if (bufferEnd > 1)
    client.write(buffer, bufferEnd - 1);
}
