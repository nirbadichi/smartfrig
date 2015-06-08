#include <emulatetag.h>
#include <llcp.h>
#include <mac_link.h>
#include <PN532.h>
#include <PN532Interface.h>
#include <PN532_debug.h>
#include <snep.h>

#include <Due.h>
#include <MifareClassic.h>
#include <MifareUltralight.h>
#include <Ndef.h>
#include <NdefMessage.h>
#include <NdefRecord.h>
#include <NfcAdapter.h>
#include <NfcDriver.h>
#include <NfcTag.h>



#include <PN532_SPI.h>



#if 0
#include <SPI.h>
#include <PN532_SPI.h>



PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);
#else

#include <Wire.h>
#include <PN532_I2C.h>



PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
#endif


void setup() {
      Serial.begin(9600);
      Serial.println("NDEF Writer");
      nfc.begin();
}

void loop() {
    Serial.println("\nPlace a formatted Mifare Classic NFC tag on the reader.");
    if (nfc.tagPresent()) {
        NdefMessage message = NdefMessage();
        message.addUriRecord("http://arduino.cc");

        bool success = nfc.write(message);
        if (success) {
          Serial.println("Success. Try reading this tag with your phone.");        
        } else {
          Serial.println("Write failed.");
        }
    }
    delay(5000);
}
