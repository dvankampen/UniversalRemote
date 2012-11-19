/*
 * Ardumote sketch
 *
 * TODO: Write description
 *
 */

#include <pins_arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Flash.h>
#include <SD.h>
#include <TinyWebServer.h>

#include <avr/pgmspace.h> // for progmem, for LED MIME images
#define P(name)   static const prog_uchar name[] PROGMEM  // declare a static string

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] =  { 192,168,1,9 };

// pin 4 is the SPI select pin for the SDcard
const int SD_CS = 4;

// pin 10 is the SPI select pin for the Ethernet
const int ETHER_CS = 10;

/*********************************************/
boolean has_filesystem = true;
Sd2Card card;
SdVolume volume;
SdFile root;
SdFile file;

const int MAX_PAGENAME_LEN = 8;  // max characters in page name 
char buffer[MAX_PAGENAME_LEN+1]; // additional character for terminating null

EthernetServer server(80);
EthernetClient client;

// The LED attached to PIN 22 on an Arduino board.
const int LEDPIN = 22;

// The initial state of the LED
int ledState = LOW;

void setLedEnabled(boolean state) {
  ledState = state;
  digitalWrite(LEDPIN, ledState);
}

boolean index_handler(TinyWebServer& web_server);

void send_file_name(TinyWebServer& web_server, const char* filename) {
  if (!filename) {
    web_server.send_error_code(404);
    web_server << F("Could not parse URL");
  } else {
    TinyWebServer::MimeType mime_type
      = TinyWebServer::get_mime_type_from_filename(filename);
    web_server.send_error_code(200);
    web_server.send_content_type(mime_type);
    web_server.end_headers();
    if (file.open(&root, filename, O_READ)) {
      Serial << F("Read file "); Serial.println(filename);
      web_server.send_file(file);
      file.close();
    } else {
      web_server << F("Could not find file: ") << filename << "\n";
    }
  }
}

TinyWebServer::PathHandler handlers[] = {
  {"/upload/" "*", TinyWebServer::PUT, &TinyWebPutHandler::put_handler },
  {"/tv/",TinyWebServer::GET, &tv_command_handler },
  {"/receiver/",TinyWebServer::GET, &receiver_command_handler },
  {"/cable/",TinyWebServer::GET, &cable_command_handler },
  {"/", TinyWebServer::GET, &index_handler },
  {NULL},
};

const char* headers[] = {
  "Content-Length",
  NULL
};

boolean file_handler(TinyWebServer& web_server) {
  char* filename = TinyWebServer::get_file_from_path(web_server.get_path());
  send_file_name(web_server, filename);
  free(filename);
  return true;
}

boolean learner_handler(TinyWebServer& web_server) {}

boolean tv_command_handler(TinyWebServer& web_server) {
  send_file_name(web_server, "TV.HTM");
  if (client.available()) {
    char ch = (char)client.read();
    if (ch == '0') {
      setLedEnabled(false);
    } else if (ch == '1') {
      setLedEnabled(true);
    }
  }
}

boolean cable_command_handler(TinyWebServer& web_server) {
  send_file_name(web_server, "CABLE.HTM");
  
  Client& client = web_server.get_client();
  if (client.available()) {
    char ch = (char)client.read();
    if (ch == '0') {
      setLedEnabled(false);
    } else if (ch == '1') {
      setLedEnabled(true);
    }
  }
}

boolean receiver_command_handler(TinyWebServer& web_server) {
  send_file_name(web_server, "RECEIVER.HTM");
  if (client.available()) {
    char ch = (char)client.read();
    if (ch == '0') {
      setLedEnabled(false);
    } else if (ch == '1') {
      setLedEnabled(true);
    }
  }
}

boolean index_handler(TinyWebServer& web_server) {
  send_file_name(web_server, "INDEX.HTM");
  return true;
}

void file_uploader_handler(TinyWebServer& web_server,
                           TinyWebPutHandler::PutAction action,
                           char* buffer, int size) {
  static uint32_t start_time;

  switch (action) {
  case TinyWebPutHandler::START:
    start_time = millis();
    if (!file.isOpen()) {
      // File is not opened, create it. First obtain the desired name
      // from the request path.
      char* fname = web_server.get_file_from_path(web_server.get_path());
      if (fname) {
        Serial << "Creating " << fname << "\n";
        file.open(&root, fname, O_CREAT | O_WRITE | O_TRUNC);
        free(fname);
      }
    }
    break;

  case TinyWebPutHandler::WRITE:
    if (file.isOpen()) {
      file.write(buffer, size);
    }
    break;

  case TinyWebPutHandler::END:
    file.sync();
    Serial << "Wrote " << file.fileSize() << " bytes in "
           << millis() - start_time << " millis\n";
    file.close();
  }
}

boolean has_ip_address = false;
TinyWebServer web = TinyWebServer(handlers, headers);

const char* ip_to_str(const uint8_t* ipAddr)
{
  static char buf[16];
  sprintf(buf, "%d.%d.%d.%d\0", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
  return buf;
}

EthernetUDP Udp;

int receivedCommands = 0;

int localPort = 56000;
int packetSize = 0;
// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

void setup()
{
  Serial.begin(115200);
  Serial << F("Free RAM: ") << FreeRam() << "\n";

  pinMode(SS_PIN, OUTPUT);	// set the SS pin as an output
                                // (necessary to keep the board as
                                // master and not SPI slave)
  digitalWrite(SS_PIN, HIGH);	// and ensure SS is high

  // Ensure we are in a consistent state after power-up or a reset
  // button These pins are standard for the Arduino w5100 Rev 3
  // ethernet board They may need to be re-jigged for different boards
  pinMode(ETHER_CS, OUTPUT);	// Set the CS pin as an output
  digitalWrite(ETHER_CS, HIGH);	// Turn off the W5100 chip! (wait for
                                // configuration)
  pinMode(SD_CS, OUTPUT);	// Set the SDcard CS pin as an output
  digitalWrite(SD_CS, HIGH);	// Turn off the SD card! (wait for
                                // configuration)
                                
  Ethernet.begin(mac, ip);
  // initialize the SD card.
  Serial << F("Setting up SD card...\n");
  // pass over the speed and Chip select for the SD card
  if (!card.init(SPI_FULL_SPEED, SD_CS)) {
    Serial << F("card failed\n");
    has_filesystem = false;
  }
  // initialize a FAT volume.
  if (!volume.init(&card)) {
    Serial << F("vol.init failed!\n");
    has_filesystem = false;
  }
  if (!root.openRoot(&volume)) {
    Serial << F("openRoot failed");
    has_filesystem = false;
  }

  if (has_filesystem) {
    // Assign our function to `upload_handler_fn'.
    TinyWebPutHandler::put_handler_fn = file_uploader_handler;
  }

  // Start the web server.
  Serial << F("Web server starting...\n");
  web.begin();

  Serial << F("Ready to accept HTTP requests.\n\n");
  Udp.begin(localPort);
  delay(1000);
}

void loop()
{

  web.process();
  
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
