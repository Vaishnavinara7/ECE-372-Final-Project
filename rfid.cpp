
#include "rfid.h"
#include "spi.h"
#include <Arduino.h>
#include <MFRC522.h>
#include <MFRC522Hack.h>

/*void init_rfid() {
    

    //spi.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delayMs(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
    
}

int read_rfid(int* num_ret) {
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        Serial.print("no card\n");
      return 0;
    }

    // Select one of the cards
    else if ( ! mfrc522.PICC_ReadCardSerial()) {
        Serial.flush();
        Serial.print("m");
      return 0;
    }

    // Dump debug info about the card; PICC_HaltA() is automatically called
    // UID
    int num = 0;
    Serial.print(F("Card UID:"));
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      num = num + mfrc522.uid.uidByte[i];
      Serial.print(mfrc522.uid.uidByte[i]);
      num_ret[i] = mfrc522.uid.uidByte[i];
    } 
     Serial.println("\n");
     Serial.println(num);
    return(num);

}

int write_rfid(int* num_ret) {
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        Serial.print("no card\n");
      return -1;
    }

    // Select one of the cards
    else if ( ! mfrc522.PICC_ReadCardSerial()) {
        Serial.flush();
        Serial.print("M");
      return -1;
    }

    // Dump debug info about the card; PICC_HaltA() is automatically called
    // UID
    //int num = 0;
    Serial.print(F("Writing card\n"));
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      mfrc522.uid.uidByte[i] = num_ret[i];
      Serial.print(num_ret[i]);
      
    } 
    Serial.print(F("Task Complete\n"));
    return(1);

}
*/

#include <spi.h>
#include <MFRC522.h>

#define BYTE(sht, in)  (in & ((uint32_t)0xFF<<(8*sht)))>>(8*sht)

MFRC522::MIFARE_Key key;
void setup() {
  mfrc522.PCD_Init();  // Init MFRC522 card
  mfrc522.PCD_DumpVersionToSerial();
  Serial.print("\n");
  Serial.flush();

  for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

}


uint32_t uidToCardNum(MFRC522 mf) {
  uint32_t cardNum = 0;
  for (byte i = 0; i < mf.uid.size; i++) {
    cardNum |= ((uint32_t)mf.uid.uidByte[i]) << (8 * i);
    Serial.println(cardNum, HEX);
  }
  return cardNum;
}

int isCardPresent() {
  int timeout = 0;
  Serial.print("INFO> Bring your card closer to the sensing area.");

  while ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delayMs(500);
    timeout++;
    if (timeout % 2 == 0) {
      Serial.print(".");
    }

    if (timeout > 20) {
      Serial.println("TimeOut!");
      return -1;
    }
  }

  return 0;
}

uint32_t readCardUID() {
  if (isCardPresent() < 0) 
  return 0;

  uint32_t cardno = uidToCardNum(mfrc522);
  Serial.println();
  Serial.print("* Card No.: ");
  Serial.print(cardno);

  Serial.print(F("* Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  return cardno;
}

int changeCardUID(uint32_t cardno) {



  delay(100);
  //Serial.println(Serial.available());

    if (isCardPresent() < 0) {
        return -1;  
    }

    else{

    
      Serial.print("\nINFO> prepare to write new card number:");
      Serial.print(cardno);
      Serial.print("\n");

      byte newUid[] = { BYTE(0, cardno),
                        BYTE(1, cardno),
                        BYTE(2, cardno),
                        BYTE(3, cardno)
                      };
      for (int i = 0; i < 4; i++) {
        Serial.println(newUid[i], HEX);
      }

      if ( mfrc522Hack.MIFARE_SetUid(newUid,(byte)4, key, true) ) {
        Serial.println(F("\nINFO> Change new card number done."));
      }

     return 1; 
    }
  }
  



