/***************************************************************************************/
/* Transmit RF-Secure packets with just one byte of data to a specific remote device   */
/* (DEVICE_ID) every second.                                                           */
/*                                                                                     */
/* This firmware is prepare to use it with "1.SingleByte_Rx" example.                  */
/***************************************************************************************/

#include <rfscomm.h>

/***************************************************************************************/

// I/O defines
#define P_TX         9 // Tx digital pin

// RF defines
#define MY_ID     0xA5 // Decimal value: 165 - One Byte, range (0-255) | (0x00-0xFF)
#define DEVICE_ID 0x1B // Decimal value:  27 - One Byte, range (0-255) | (0x00-0xFF)
#define DATA      0x12 // Decimal value:  18 - One Byte, range (0-255) | (0x00-0xFF)

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
    // Send and show packet content
    rf.send(DEVICE_ID, DATA);
    Serial.print("\nPackage sent:\n");
    Serial.print("[My ID: 0x"); Serial.print(MY_ID, HEX); Serial.print(" | ");
    Serial.print("To device with ID: 0x"); Serial.print(DEVICE_ID, HEX); Serial.print(" | ");
    Serial.print("Data: 0x"); Serial.print(DATA, HEX); Serial.print("\n");
    Serial.print("\n-------------------------------------------------------\n");
    delay(1000);
}

/***************************************************************************************/

