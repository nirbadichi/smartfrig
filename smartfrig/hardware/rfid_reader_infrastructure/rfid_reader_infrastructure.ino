#include <SoftwareSerial.h>

#define TAG_LEGAL_LENGTH 13
#define TAG_START_INDEX 1
#define TAG_END_INDEX 13

SoftwareSerial rfid = SoftwareSerial(5, 6);

void setup()
{
	Serial.begin(9600);
	Serial.println("Serial Ready");

	rfid.begin(9600);
	Serial.println("RFID Ready");
}



void loop()
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
		readTag(string_buffer.substring(TAG_START_INDEX, TAG_END_INDEX));
	}
	string_buffer = "";

}



bool findTagKeyInMyFridge(String tag_key)
{
	//Wifi server code
}


void removeKeyFromMyFridge(String key)
{
	//Wifi server code
}

bool addKeyToMyFridge(String key)
{
	//Wifi server code
}

bool findKeyInDataBase(String key)
{
	//Wifi server code
}

void readTag(String rfid_key)
{
	void* record;
	if (findTagKeyInMyFridge(rfid_key))
	{
		removeKeyFromMyFridge(rfid_key);
	}
	else
	{
		if (findKeyInDataBase(rfid_key))
		{
			addKeyToMyFridge(rfid_key);
		}
		else
		{
			//Tag doesn't exist in base
		}
	}
	delay(500);
}
