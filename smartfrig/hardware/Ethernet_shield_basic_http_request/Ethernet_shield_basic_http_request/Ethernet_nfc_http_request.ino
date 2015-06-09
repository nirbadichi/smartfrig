#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

//==========================================
// NFC defines
//==========================================
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

//==========================================
// General defines
//==========================================
#define DEBUG_MODE 1

//==========================================
// RFID defines
//==========================================
/*#define TAG_START_INDEX 1
#define TAG_END_INDEX 13
#define TAG_LEGAL_LENGTH 13
SoftwareSerial rfid = SoftwareSerial(5, 6);
*/
//==========================================
// ethernet defines
//==========================================


// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x04 };
// Azure Mobile Service address
// You can find this in your service dashboard
const char *server = "fringnfc.azure-mobile.net";

// Azure Mobile Service Application Key
// You can find this key in the 'Manage Keys' menu on the dashboard
const char *ams_key = "YsKiJgEvswUtPyOcSxkHiXPyvkJkgv25";
  
char buffer[64];

const char *frig_id = "1";
 
/*
** Send an HTTP POST request to the Azure Mobile Service data API
*/

// initialize the library instance:
EthernetClient client;

boolean lastConnected = false;                 // state of the connection last time through the main loop

void setup()
{
	serialSetup();
	ethernetSetup();
	//rfidSetup();
        nfcSetup();
}


void loop()
{
    //rfidMonitorRead();
    nfcMonitorRead();
}

void serialSetup()
{
    //Initialize serial
    Serial.begin(9600);
    Serial.println("Serial Ready");
}

void ethernetSetup()
{
  // give the ethernet module time to boot up:
  delay(1000); 
 
  Serial.println("Ethernet Setup");
 
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Ethernet failed");
    for (;;) ;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
}

/*
void rfidSetup()
{
	//Initialize rfid serial
	rfid.begin(9600);
	Serial.println("RFID Ready");
}
*/

void nfcSetup()
{
    //Initialize nfc serial
    nfc.begin();
    Serial.println("NDEF Reader");
}
/*
void rfidMonitorRead()
{
	String string_buffer = "";
	char char_buffer;
	rfid.flush();
	while (rfid.available()>0){
		char_buffer = rfid.read();
		string_buffer += char_buffer;
		//Serial.println(string_buffer);
		//Serial.println(string_buffer.length());
	}
	if (string_buffer.length() > TAG_LEGAL_LENGTH)
	{
		if (DEBUG_MODE){
			Serial.println("Data that was read from the RFID: ");
			Serial.println(string_buffer.substring(TAG_START_INDEX, TAG_END_INDEX));
		}
		readTag(string_buffer.substring(TAG_START_INDEX, TAG_END_INDEX));
	}
	string_buffer = "";
}
*/

void nfcMonitorRead()
{
  if (DEBUG_MODE){
      Serial.println("\nScan a NFC tag\n");
  }
  if (nfc.tagPresent()){
      NfcTag tag = nfc.read();
      if (tag.hasNdefMessage()){ // every tag won't have a message
          String payloadAsString = "";
          NdefMessage message = tag.getNdefMessage();
          int recordCount = message.getRecordCount();
          for (int i = 0; i < recordCount; i++){      
              NdefMessage message = tag.getNdefMessage();
              NdefRecord record = message.getRecord(i);
              int payloadLength = record.getPayloadLength();
              byte payload[payloadLength];
              record.getPayload(payload);
              for (int c = 0; c < payloadLength; c++) {
                  payloadAsString += (char)payload[c];
              }
              if (DEBUG_MODE)
              {
                  Serial.println(payloadAsString);
              }
          }
          readTag(payloadAsString);
      }    
  }
  delay(3000);
}

/*
** Send an HTTP POST request to the Azure Mobile Service data API
*/
 
void sendRequest(String value)
{
  Serial.println("\nconnecting...");
 
  if (client.connect(server, 80)) {
 
    Serial.print("sending ");
    Serial.println(value);
    
    // GET URI 
    sprintf(buffer, "POST /api/Arduino?itemId=%s&frigId=%s HTTP/1.1", value.c_str(),frig_id);
    client.println(buffer);
 
    // Host header
    sprintf(buffer, "Host: %s", server);
    client.println(buffer);
 
    // Azure Mobile Services application key
    sprintf(buffer, "X-ZUMO-APPLICATION: %s", ams_key);
    client.println(buffer);
 
    // JSON content type
    client.println("Content-Type: application/json");
  
    // Content length
    client.print("Content-Length: ");
    client.println(strlen(buffer));
 
    // End of headers
    client.println();
 
    // Request body
    client.println(buffer);
    
  } else {
    Serial.println("connection failed");
  }
}


/*
** Wait for response
*/
 
void waitResponse()
{
  while (!client.available()) {
    if (!client.connected()) {
      return;
    }
  }
}

/*
** Read the response and dump to serial
*/
 
void readResponse()
{
  //bool print = true;
  Serial.println("Data that was read from the server: ");
  while (client.available()) {
    char c = client.read();
    // Print only until the first carriage return
    //if (c == '\n')
     // print = false;
    //if (print)
      Serial.print(c);
  }
}

 
/*
** Close the connection
*/

void endRequest()
{
  client.stop();
}

void readTag(String rfid_key)
{
    sendRequest(rfid_key);
    waitResponse();
    if (DEBUG_MODE){
        readResponse();
    }
    endRequest();
    delay(1000);
}
