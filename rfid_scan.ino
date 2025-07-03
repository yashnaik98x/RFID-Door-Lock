#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN  10
byte readCard[4];

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println("Put your card");
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("Scanned PICC's UID:"));
  for (uint8_t i = 0; i < 4; i++) {
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
    Serial.print(" ");
  }
  Serial.println("");
  mfrc522.PICC_HaltA();
}
