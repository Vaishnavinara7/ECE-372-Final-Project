#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <MFRC522.h>
#include "rfid.h"
#include "spi.h"
#include "timer.h"
#include "matrix.h"
#include "lcd.h"
#include "switch.h"



// Global Variables
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          53         // Configurable, see typical pin layout above
#define PIN_NO          1542       // Pin number for the keypad

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
MFRC522::MIFARE_Key key;

typedef enum stateEnum{
    wait_press,
    bounce_low,
    wait_release,
    bounce_high
  } stateType;

volatile stateType state = wait_press;
volatile int runState = 0;

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

  MatrixInit();
  initLCD();
  initSwitchPB5();
  
  //init_rfid();
  setup();

  //Serial.print("working 1");
  Serial.flush();
  moveCursor(0, 0);
  writeString("          ");
  moveCursor(1, 0);
  writeString("          ");
 // moves the cursor to 0,0 position
  moveCursor(0, 0); 
  writeString("Press Button to");
  moveCursor(1, 0); // moves the cursor to 0,0 position
  writeString("Start");

  while(1){

  if (runState == 1){
    moveCursor(0, 0);
     writeString("                ");
     moveCursor(1, 0);
     writeString("                ");
  moveCursor(0, 0); // moves the cursor to 0,0 position
  writeString("Enter Code");
    
  int output_1 = -1;
  while(output_1<0){
  output_1 = ReadValue();
  delayMs(10);
  }
  moveCursor(0, 0); // moves the cursor to 0,0 position
  writeString("          ");
  moveCursor(0, 0);
  writeString("*");
  //Serial.print(output_1);
  //Serial.print(" number 1 \n");
  delayMs(1000);

  int output_2 = -1;
  while(output_2<0){
  output_2 = ReadValue();
  delayMs(10);
  }
  //Serial.print(output_2);
  //Serial.print(" number 2 \n");
  writeString("*");
  delayMs(1000);

  int output_3 = -1;
  while(output_3<0){
  output_3 = ReadValue();
  delayMs(10);
  }
  //Serial.print(output_3);
  //Serial.print(" number 3 \n");
  writeString("*");

  delayMs(1000);
  int output_4 = -1;
  while(output_4<0){
  output_4 = ReadValue();
  delayMs(10);
  }
      //Serial.print(output_4);
    //Serial.print(" number 4 \n");
    writeString("*");
  delayMs(1000);

 int inputNo = (output_1*1000) + (output_2*100) + (output_3 * 10) + output_4;
 if (inputNo == PIN_NO){
  //Serial.print(" Correct Pin, Start Key Copying \n");
  moveCursor(0, 0);
  writeString("          ");
  moveCursor(0, 0);
  writeString("PIN Correct");
    delayMs(1000);
  Serial.flush();


    cardno = readCardUID();
    if (cardno!=0){
      num = -1;
    moveCursor(0, 0);
     writeString("                ");
     moveCursor(1, 0);
     writeString("                ");
     moveCursor(0, 0);
     writeString("Card Has Been");
     moveCursor(1, 0);
     writeString("Read");
    }
    if(num == -1){
   

   delayMs(1000);
   Serial.flush();
   Serial.print("writing \n");
    moveCursor(0, 0);
     writeString("                ");
     moveCursor(1, 0);
     writeString("                ");
     moveCursor(0, 0);
     writeString("Time to write!");
     delayMs(1000);
     Serial.flush();
    Serial.print("writing \n");
    num = changeCardUID(cardno);
    }
    moveCursor(0, 0);
     writeString("                ");
     moveCursor(1, 0);
     writeString("                ");
 }
 else{
  moveCursor(0, 0);
  writeString("          ");
  moveCursor(0, 0);
  writeString("Incorrect");
  delayMs(2000);
    moveCursor(0, 0);
     writeString("                ");
     moveCursor(1, 0);
     writeString("                ");
 }

     runState = 0;
  moveCursor(0, 0); 
  writeString("Press Button to");
  moveCursor(1, 0); // moves the cursor to 0,0 position
  writeString("Start");
  }
         switch(state){
      case wait_press:
         break;
      case bounce_low:
        delayMs(1);
        state = wait_release;
        break;
      case wait_release:
        break;
      case bounce_high:
        delayMs(1);
        state = wait_press;
        break;
    }





  }


  return 0;

}

ISR(PCINT0_vect){  // External interrrupt 
    if(state == wait_press){
      state = bounce_low;
    }
    else if (state == wait_release){
        runState = 1;
      state = bounce_high;
    }

  }