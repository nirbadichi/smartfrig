#include <SoftwareSerial.h>

#define ADD_TAG_CODE "06008E6643AD"  //change this ID with your own card TAG
#define DEL_TAG_CODE "07003DE86DBF"  //change this ID with your own card TAG

SoftwareSerial rfid = SoftwareSerial(5, 6);
String msg;
String ID;  //string to store allowed cards

void setup()
{
	Serial.begin(9600);
	Serial.println("Serial Ready");

	rfid.begin(9600);
	Serial.println("RFID Ready");
}

char c;

void loop(){
	msg = "";
	rfid.flush();
	while (rfid.available()>0){
                // if (msg.length()==0){
                // Serial.println("start");
                //}
		c = rfid.read();
		msg += c;
            
		//Serial.println(msg);
		//Serial.println(msg.length());
	}
	msg = msg.substring(1, 13);
	if (msg.indexOf(ADD_TAG_CODE) >= 0) add();
	else if (msg.indexOf(DEL_TAG_CODE) >= 0) del();
	else if (msg.length()>10) verifica();
}

void add(){
	Serial.println("What TAG do you wanna grant access?: ");
	delay(500);
	rfid.flush();
	msg = "";
	while (msg.length()<13){
		while (rfid.available()>0){
			c = rfid.read();
			msg += c;
		}
	}
	if (ID.indexOf(msg) >= 0) {
		Serial.println("\nAccess already granted for this card.");
		msg = "";
	}
	else{
		Serial.print("Card: ");
		Serial.println(msg);
		ID += msg;
		ID += ",";
		//Serial.print("ID: ");
		// Serial.println(ID);
		Serial.println("Access granted for this card.");
	}

}

void del(){

	Serial.println("What TAG do you wanna deny access?: ");
	delay(500);
	rfid.flush();	
	msg = "";
	while (msg.length()<13){
		while (rfid.available()>0){
			c = rfid.read();
			msg += c;
		}
	}
	msg = msg.substring(1, 13);
	if (ID.indexOf(msg) >= 0){
		Serial.println(msg);
		Serial.println("TAG found. Access for this card denied.");
		//ID.replace(card,"");
		int pos = ID.indexOf(msg);
		msg = "";
		msg += ID.substring(0, pos);
		msg += ID.substring(pos + 15, ID.length());
		ID = "";
		ID += msg;
		//Serial.print("ID: ");
		//Serial.println(ID);
	}
	else Serial.println("\nTAG not found or already denied");
}

void verifica(){
	if (ID.indexOf(msg) >= 0) Serial.println("Access granted.");

	else Serial.println("Access denied.");
	delay(300);
}
