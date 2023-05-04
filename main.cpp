#include <Arduino.h>
#include <MFRC522.h>
#include <MFRC522Hack.h>
#include "rfid.h"
#include "spi.h"
#include "timer.h"



// Global Variables
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
MFRC522Hack mfrc522Hack(&mfrc522);
MFRC522::MIFARE_Key key;

// ---------------------------------------------------------------------- //
// Main Function
int main(void) {
int num = 0;
uint32_t cardno = 0;

  Serial.begin(9600);	
  sei();                // Enable global interrupts
  	// Initialize serial port
  SPI_MASTER_Init();

  
  initTimer0();
  
  initTimer1();
  initTimer4();
  
  //init_rfid();
  setup();

  //Serial.print("working 1");
  Serial.flush();

  while(1){
    Serial.flush();

    while (num == 0){
    cardno = readCardUID();
      Serial.print(cardno);
      Serial.print("\n");
    if (cardno!=0){
      num = -1;
      Serial.print(cardno);
      Serial.print("\n");
    }
   }

   delayMs(1999);
   Serial.flush();
   Serial.print("writing\n");
   Serial.flush();
      Serial.print(cardno);
      Serial.print("\n");

    while (num == -1){
   num = changeCardUID(cardno);
  }
  }
  return 0;

}