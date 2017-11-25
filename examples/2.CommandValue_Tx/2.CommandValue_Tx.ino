/***************************************************************************************/
/* Transmit RF-Secure packets to wireless control a device (DEVICE_ID) and remote turn */
/* ON/OFF a LED by sending a specific command and value every second.                  */
/*                                                                                     */
/* This firmware is prepare to use it with "2.CommandValue_Rx" example.                */
/***************************************************************************************/

#include <rfscomm.h>

/***************************************************************************************/

// I/O defines
#define P_TX         9 // RF Tx digital pin

// RF defines
#define MY_ID     0xA5 // Decimal value: 165 - One Byte, range (0-255) | (0x00-0xFF)
#define DEVICE_ID 0x1B // Decimal value:  27 - One Byte, range (0-255) | (0x00-0xFF)
#define CMD_LED   0x25 // Decimal value:  37 - One Byte, range (0-255) | (0x00-0xFF)
#define VAL_OFF   0x00 // Decimal value:   0 - One Byte, range (0-255) | (0x00-0xFF)
#define VAL_ON    0xFF // Decimal value: 255 - One Byte, range (0-255) | (0x00-0xFF)

/***************************************************************************************/

// RF Object
RFSCOMM rf(MY_ID);

/***************************************************************************************/

// Main Setup function
void setup()
{
    // Init Serial and RF object
    Serial.begin(9600);
    rf.config(P_TX, NO_USE, MAN_1200);
    
    Serial.print("\nSystem with ID 0x"); Serial.print(MY_ID, HEX); Serial.print(", configured to transmit\n");
    Serial.print("\n-------------------------------------------------------\n");
}

// Main Loop function
void loop()
{
    // Send a LED-ON and show packet content
    rf.send(DEVICE_ID, CMD_LED, VAL_ON);
    Serial.print("\nPackage sent:\n");
    Serial.print("[My ID: 0x"); Serial.print(MY_ID, HEX); Serial.print(" | ");
    Serial.print("To device with ID: 0x"); Serial.print(DEVICE_ID, HEX); Serial.print(" | ");
    Serial.print("Command: 0x"); Serial.print(CMD_LED, HEX); Serial.print(" (LED) | ");
    Serial.print("Value: 0x"); Serial.print(VAL_ON, HEX); Serial.print(" (ON)]\n");
    Serial.print("\n-------------------------------------------------------\n");
    delay(1000);

    // Send a LED-OFF and show packet content
    rf.send(DEVICE_ID, CMD_LED, VAL_OFF);
    Serial.print("\nPackage sent:\n");
    Serial.print("[My ID: 0x"); Serial.print(MY_ID, HEX); Serial.print(" | ");
    Serial.print("To device with ID: 0x"); Serial.print(DEVICE_ID, HEX); Serial.print(" | ");
    Serial.print("Command: 0x"); Serial.print(CMD_LED, HEX); Serial.print(" (LED) | ");
    Serial.print("Value: 0x"); Serial.print(VAL_OFF, HEX); Serial.print(" (OFF)]\n");
    Serial.print("\n-------------------------------------------------------\n");
    delay(1000);
}

/***************************************************************************************/
