#ifndef RFID_H
#define RFID_H
#include <MFRC522.h>

extern MFRC522 mfrc522;


//void init_rfid();
//int read_rfid(int*);
//int write_rfid(int*);

void setup();
uint32_t uidToCardNum(MFRC522 mf);
int isCardPresent();
uint32_t readCardUID();
int changeCardUID(uint32_t cardno);



#endif