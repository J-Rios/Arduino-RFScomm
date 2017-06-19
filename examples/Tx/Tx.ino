#include <rfscomm.h>

#define P_TX      9    // Tx digital pin

#define MY_ID     0xA5 // Decimal value: 165 - One Byte, range (0-255) | (0x00-0xFF)
#define DEVICE_ID 0x1B // Decimal value: 27  - One Byte, range (0-255) | (0x00-0xFF)
#define CMD       0xFF // Decimal value: 255 - One Byte, range (0-255) | (0x00-0xFF)

RFSCOMM rf(MY_ID);

void setup()
{
    Serial.begin(9600);
    rf.config(P_TX, NO_USE, MAN_1200);
}

void loop()
{
    rf.send(DEVICE_ID, CMD);
    
    Serial.print("\nPackage sent:\n");
    Serial.print("My ID - 0x");
    Serial.print(MY_ID, HEX);
    Serial.print(" | Sent to device with ID - 0x");
    Serial.print(DEVICE_ID, HEX);
    Serial.print(" | CMD - 0x");
    Serial.print(CMD, HEX);
    Serial.print("\n");
    
    delay(1000);
}
