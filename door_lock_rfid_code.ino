#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
String UID = "93 40 3A 1A"; // The authorized card's UID
byte lock = 0;  // 0 means locked, 1 means unlocked

Servo servo;
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  servo.attach(3);

  // Set the initial lock state
  if (lock == 0) {
    servo.write(160);  // Door starts locked
    Serial.println("Door is locked");
  } else {
    servo.write(70);  // Door starts unlocked
    Serial.println("Door is unlocked");
  }

  Serial.println("Ready to scan. Please place your card.");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) {
    delay(500);  // Wait before checking for a card again
    return;  // No new card, exit loop
  }

  if (!rfid.PICC_ReadCardSerial()) {
    delay(500);  // Wait before reading the card again
    return;  // No card read, exit loop
  }

  Serial.println("Card detected! Scanning...");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }
  ID.toUpperCase();
  Serial.print("Scanned UID: ");
  Serial.println(ID);

  // Check if the scanned UID matches the authorized UID
  if (ID.substring(1) == UID) {
    if (lock == 0) {
      // If door is locked, unlock it
      servo.write(70);  // Move servo to unlock position
      Serial.println("Door is unlocked");
      lock = 1;  // Update the state to unlocked
    } else {
      // If door is unlocked, lock it
      servo.write(160);  // Move servo to lock position
      Serial.println("Door is locked");
      lock = 0;  // Update the state to locked
    }
    delay(1500);  // Wait before allowing another scan
  } else {
    Serial.println("Wrong card!");
    delay(1500);  // Delay to prevent multiple scans
  }
}
