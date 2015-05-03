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
// Wifi defines
//==========================================
    #include <SPI.h>
    #include <WiFi.h>
    
    char ssid[] = "yourNetwork";      //  your network SSID (name)
    char pass[] = "secretPassword";   // your network password
    int keyIndex = 0;            // your network key Index number (needed only for WEP)
    
    int status = WL_IDLE_STATUS;
    
    // Initialize the Wifi client library
    WiFiClient client;
    
    // server address:
    char server[] = "www.arduino.cc";
    //IPAddress server(64,131,82,241);
    
void setup()
{
	serialSetup();
	wifiSetup();
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

void wifiSetup()
{
	// check for the presence of the shield:
	if (WiFi.status() == WL_NO_SHIELD) {
		Serial.println("WiFi shield not present");
		// don't continue:
		while (true);
	}

	String fv = WiFi.firmwareVersion();
	if (fv != "1.1.0")
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
	// you're connected now, so print out the status:
	printWifiStatus();
}

void rfidSetup()
{
	//Initialize rfid serial
	rfid.begin(9600);
	Serial.println("RFID Ready");
}

String wifiMonitorRead()
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
	//Wifi server code
	if (DEBUG_MODE)
	{
		Serial.println("Finding tag key in my frige, key");
		Serial.println(tag_key);
	}
	String server_return_value;
	String request_base = "GET /latest.txt HTTP/1.1";
	if (DEBUG_MODE)
	{
		Serial.println("The HTTP request: ");
		Serial.println(request_base);
	}
	httpRequest(request_base);
	String server_return_value = wifiMonitorRead();
	if (DEBUG_MODE)
	{
		Serial.println("The server return value: ");
		Serial.println("server_return_value");
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
	//Wifi server code
	if (DEBUG_MODE)
	{
		Serial.println("Remove tag key from my frige, key:");
		Serial.println(key);
	}
	String server_return_value;
	String request_base = "GET /latest.txt HTTP/1.1";
	if (DEBUG_MODE)
	{
		Serial.println("The HTTP request: ");
		Serial.println(request_base);
	}
	httpRequest(request_base);
	String server_return_value = wifiMonitorRead();
	if (DEBUG_MODE)
	{
		Serial.println("The server return value: ");
		Serial.println("server_return_value");
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

bool addKeyToMyFridge(String key)
{
	//Wifi server code
	if (DEBUG_MODE)
	{
		Serial.println("Adding tag key in my frige...");
		Serial.println(key);
	}
	String server_return_value;
	String request_base = "GET /latest.txt HTTP/1.1";
	if (DEBUG_MODE)
	{
		Serial.println("The HTTP request: ");
		Serial.println(request_base);
	}
	httpRequest(request_base);
	String server_return_value = wifiMonitorRead();
	if (DEBUG_MODE)
	{
		Serial.println("The server return value: ");
		Serial.println("server_return_value");
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
	//Wifi server code
	if (DEBUG_MODE)
	{
		Serial.println("Finding tag key in data base...");
	}
	String server_return_value;
	String request_base = "GET /latest.txt HTTP/1.1";
	if (DEBUG_MODE)
	{
		Serial.println("The HTTP request: ");
		Serial.println(request_base);
	}
	httpRequest(request_base);
	String server_return_value = wifiMonitorRead();
	if (DEBUG_MODE)
	{
		Serial.println("The server return value: ");
		Serial.println("server_return_value");
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
// Wifi procedures
//==========================================

// this method makes a HTTP connection to the server:
void httpRequest(String request_base) {
	// close any connection before send a new request.
	// This will free the socket on the WiFi shield
	client.stop();

	// if there's a successful connection:
	if (client.connect(server, 80)) {
		Serial.println("connecting...");
		// send the HTTP PUT request:
		client.println(request_base);
		client.println("Host: www.arduino.cc");
		client.println("User-Agent: ArduinoWiFi/1.1");
		client.println("Connection: close");
		client.println();
	}
	else {
		// if you couldn't make a connection:
		Serial.println("connection failed");
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
