/***************************************************************************************/
/* Transmit RF-Secure packets with multiples bytes (array) of data in each packet, to  */
/* a specific remote device (DEVICE_ID) every second.                                  */
/*                                                                                     */
/* This firmware is prepare to use it with "3.MultipleBytes_Rx" example.               */
/***************************************************************************************/

#include <rfscomm.h>

/***************************************************************************************/

// I/O defines
#define P_TX                       9 // RF Tx digital pin

// RF defines
#define MY_ID                   0xA5 // Decimal value: 165 - One Byte, range (0-255) | (0x00-0xFF)
#define DEVICE_ID               0x1B // Decimal value:  27 - One Byte, range (0-255) | (0x00-0xFF)

// Maximum data bytes to send
// AES-256 has a max data lenght of 16 bytes, and internally, the packet frame to send uses 3 bytes 
// with source ID, destiny ID and data_length fields, so make sure to not send more than 13 bytes.
#define MAX_DATA_LENGTH           13 // Maximum data bytes to send
    
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
    // Prepare data array to send (string with null termination character '\0' to ensure strlen() get correct string length)
    // Make sure to not send more than 13 bytes (MAX_DATA_LENGTH). Bytes over 13 will be lost in transmission.
    // Here we send a non-fixed size array, but you can use a fixed sized array "data[MAX_DATA_LENGTH]".
    uint8_t* data = "What's up\0"; // Data string
    //static uint8_t data[MAX_DATA_LENGTH] = "What's up\0"; // Data string
    uint8_t data_length = strlen(data)+1; // Data length (12 data bytes + 1 null terminating '\0' byte)
    
    // Send the packet
    rf.send(DEVICE_ID, data, data_length);
    Serial.print("\nPackage sent:\n");
    Serial.print("[My ID: 0x"); Serial.print(MY_ID, HEX); Serial.print(" | ");
    Serial.print("To device with ID: 0x"); Serial.print(DEVICE_ID, HEX); Serial.print(" | ");
    Serial.print("Data ("); Serial.print(data_length); Serial.print(" bytes): ");
    Serial.print((const char*)data); Serial.print("]\n");
    Serial.print("\n-------------------------------------------------------\n");
    delay(1000);
}

/***************************************************************************************/

