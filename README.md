# RFID-Based Door Lock System

This project demonstrates how to use an RFID module with an Arduino to create a secure door locking system. The system scans RFID tags and opens the lock only for authorized users.

## Features

- Scans RFID tags using MFRC522 module
- Controls a servo motor to lock/unlock the door
- Stores and verifies authorized RFID UIDs
- Provides LED and Serial output feedback

## Files

### `door_lock_rfid_code.ino`
This is the main code used to operate the RFID door locking system. It includes:
- Initialization of RFID module and servo
- UID authentication logic
- Servo control to simulate door locking/unlocking

### `rfid_scan.ino`
Use this sketch to scan RFID tags and retrieve their UIDs via the Serial Monitor. The UID can then be added to the list of authorized users in `door_lock_rfid_code.ino`.

## Hardware Required

- Arduino Uno (or compatible board)
- MFRC522 RFID reader
- RFID key tags/cards
- Servo motor (e.g., SG90)
- Jumper wires
- Breadboard
- Optional: LEDs for visual indication

## Wiring

| MFRC522 Pin | Arduino Pin |
|-------------|-------------|
| SDA         | D10         |
| SCK         | D13         |
| MOSI        | D11         |
| MISO        | D12         |
| IRQ         | Not connected |
| GND         | GND         |
| RST         | D9          |
| 3.3V        | 3.3V        |

Servo motor signal pin should be connected to D3 (or any PWM pin, depending on your code).

## Setup Instructions

1. Upload `rfid_scan.ino` to your Arduino.
2. Open Serial Monitor and scan your RFID tag.
3. Copy the UID printed on the Serial Monitor.
4. Paste this UID in the `authorizedUIDs` array in `door_lock_rfid_code.ino`.
5. Upload `door_lock_rfid_code.ino` to your Arduino.
6. Power the setup and scan your tag to see the door unlock.

## License

This project is open-source under the MIT License.

## Credits

Developed as a simple and practical IoT security solution using Arduino and RFID technology.

