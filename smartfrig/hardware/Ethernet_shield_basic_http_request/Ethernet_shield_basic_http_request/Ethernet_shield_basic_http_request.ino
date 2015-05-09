#include <SoftwareSerial.h>
//==========================================
// General defines
//==========================================
#define DEBUG_MODE 1

//==========================================
// RFID defines
//==========================================
#define TAG_START_INDEX 1
#define TAG_END_INDEX 13
#define TAG_LEGAL_LENGTH 13
SoftwareSerial rfid = SoftwareSerial(5, 6);

//==========================================
// ethernet defines
//==========================================

#include <SPI.h>
#include <Ethernet.h>

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
	0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x04 };
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192, 168, 56, 177);

// initialize the library instance:
EthernetClient client;

char server[] = "a7he2uhi7b.database.windows.net.1433";

unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 60 * 1000;  // delay between updates, in milliseconds


void setup()
{
	serialSetup();
	ethernetSetup();
	rfidSetup();
}


void loop()
{
    rfidMonitorRead();
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
    if (Ethernet.begin(mac)==0)
    {
        Serial.println("Failed to configure Ethernet using DHCP");
        Ethernet.begin(mac,ip);
    };
    delay(1000);
    Serial.println("Ethernet Ready");
	// start the Ethernet connection using a fixed IP address and DNS server:
	//Ethernet.begin(mac, ip, myDns);
	// print the Ethernet board/shield's IP address:
	//Serial.print("My IP address: ");
	//Serial.println(Ethernet.localIP());
}

void rfidSetup()
{
	//Initialize rfid serial
	rfid.begin(9600);
	Serial.println("RFID Ready");
}

String ethernetMonitorRead()
{
	// if there's incoming data from the net connection.
	// send it out the serial port.  This is for debugging
	// purposes only:
	String string_buffer = "";
	while (client.available()) {
		char char_buffer = client.read();
		string_buffer += char_buffer;
	}
	if (DEBUG_MODE)
	{
		Serial.println("Data that was read from the server: ");
		Serial.println(string_buffer);
	}

	// if there's no net connection, but there was one last time
	// through the loop, then stop the client:
	if (!client.connected() && lastConnected) {
		Serial.println();
		Serial.println("disconnecting.");
		client.stop();
	}
        // store the state of the connection for next time through
	// the loop:
	lastConnected = client.connected();

	return string_buffer;

}

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
		if (DEBUG_MODE)
		{
			Serial.println("Data that was read from the RFID: ");
			Serial.println(string_buffer.substring(TAG_START_INDEX, TAG_END_INDEX));
		}
		readTag(string_buffer.substring(TAG_START_INDEX, TAG_END_INDEX));
	}
	string_buffer = "";
}

bool findTagKeyInMyFridge(String tag_key)
{
	//ethernet server code
	if (DEBUG_MODE)
	{
		Serial.println("Finding tag key in my frige, key");
		Serial.println(tag_key);
	}
	String server_return_value;
	String request_base = "GET find tag key in my fridge";
	if (DEBUG_MODE)
	{
		Serial.println("The HTTP request: ");
		Serial.println(request_base);
	}
	if (!client.connected())
	{
		httpRequest(request_base);
	}	
	 server_return_value = "temp value";//ethernetMonitorRead();
	if (DEBUG_MODE)
	{
		Serial.println("The server return value: ");
		Serial.println(server_return_value);
	}
	if (server_return_value) // need to update condition based on retrun value from server
	{
		if (DEBUG_MODE)
		{
			Serial.println("Finding tag key in my frige... return true");
		}
		return true;
	}
	if (DEBUG_MODE)
	{
		Serial.println("Finding tag key in my frige... return false");
	}
	return false;
}


bool removeKeyFromMyFridge(String key)
{
	//ethernet server code
	if (DEBUG_MODE)
	{
		Serial.println("Remove tag key from my frige, key:");
		Serial.println(key);
	}
	String server_return_value;
	String request_base = "GET remove key fridge";
	if (DEBUG_MODE)
	{
		Serial.println("The HTTP request: ");
		Serial.println(request_base);
	}
	if (!client.connected())
	{
		//httpRequest(request_base);
	}
	server_return_value = "";//ethernetMonitorRead();
	if (DEBUG_MODE)
	{
		Serial.println("The server return value: ");
		Serial.println(server_return_value);
	}
	if (server_return_value != "") // need to update condition based on retrun value from server
	{
		if (DEBUG_MODE)
		{
			Serial.println("Removing tag key in my frige... return true");
		}
		return true;
	}
	if (DEBUG_MODE)
	{
		Serial.println("Removing tag key in my frige... return false");
	}
	return false;
}

bool addKeyToMyFridge(String key)
{
	//ethernet server code
	if (DEBUG_MODE)
	{
		Serial.println("Adding tag key in my frige...");
		Serial.println(key);
	}
	String server_return_value;
	String request_base = "GET add to my fridge";
	if (DEBUG_MODE)
	{
		Serial.println("The HTTP request: ");
		Serial.println(request_base);
	}
	if (!client.connected())
	{
		//httpRequest(request_base);
	}
               server_return_value = "temp value";//ethernetMonitorRead();
	if (DEBUG_MODE)
	{
		Serial.println("The server return value: ");
		Serial.println(server_return_value);
	}
	if (server_return_value) // need to update condition based on retrun value from server
	{
		if (DEBUG_MODE)
		{
			Serial.println("Removing tag key in my frige... return true");
		}
		return true;
	}
	if (DEBUG_MODE)
	{
		Serial.println("Removing tag key in my frige... return false");
	}
	return false;
}

bool findKeyInDataBase(String key)
{
	//ethernet server code
	if (DEBUG_MODE)
	{
		Serial.println("Finding tag key in data base...");
	}
	String server_return_value;
	String request_base = "GET find in data base";
	if (DEBUG_MODE)
	{
		Serial.println("The HTTP request: ");
		Serial.println(request_base);
	}
	if (!client.connected())
	{
		//httpRequest(request_base);
	}
	 server_return_value = "temp value";//ethernetMonitorRead();
	if (DEBUG_MODE)
	{
		Serial.println("The server return value: ");
		Serial.println(server_return_value);
	}
	if (server_return_value) // need to update condition based on retrun value from server
	{
		if (DEBUG_MODE)
		{
			Serial.println("Finding tag key in data base... return true");
		}
		return true;
	}
	if (DEBUG_MODE)
	{
		Serial.println("Finding tag key in my frige... return false");
	}
	return false;
}

void readTag(String rfid_key)
{
	void* record;
	if (findTagKeyInMyFridge(rfid_key))
	{
		if (removeKeyFromMyFridge(rfid_key))
		{
			Serial.println("Removed tag key from my frige... Success");
		}
		else
		{
			Serial.println("Removed tag key from my frige... Fail");
		}
	}
	else
	{
		if (findKeyInDataBase(rfid_key))
		{
			if (addKeyToMyFridge(rfid_key))
			{
				Serial.println("Add tag key to my frige... Success");
			}
			else
			{
				Serial.println("Add tag key to my frige... Fail");
			}
		}
		else
		{
			Serial.println("Tag key was not found in data base");
		}
	}
	delay(500);
}



//==========================================
// ethernet procedures
//==========================================

// this method makes a HTTP connection to the server:
void httpRequest(String request_base)
{
    Serial.println("connecting...");
    // if there's a successful connection:
    if (client.connect(server, 80)) 
    {
        Serial.println("connected");
        client.println("GET /search?q=arduino HTTP/1.1");
        client.println("a7he2uhi7b.database.windows.net.1433");
        client.println();
	// send the HTTP PUT request:
	//client.println(request_base);
	//client.println("Host: www.arduino.cc");
	//client.println("User-Agent: Arduinoethernet/1.1");
	//client.println("Connection: close");
	//client.println();
    }
    else 
    {
	// if you couldn't make a connection:
	Serial.println("connection failed");
	Serial.println("disconnecting.");
	client.stop();
    }
}
