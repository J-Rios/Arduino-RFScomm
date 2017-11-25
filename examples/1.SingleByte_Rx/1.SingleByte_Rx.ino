/***************************************************************************************/
/* Receive RF-Secure packets and check if any of them is for this receiver device      */
/* (MY_ID) if so, check if the packet has just one byte of data and show it.           */
/*                                                                                     */
/* This firmware is prepare to use it with "1.SingleByte_Tx" example.                  */
/***************************************************************************************/

#include <rfscomm.h>

/***************************************************************************************/

// I/O defines
#define P_RX       4 // RF Rx digital pin
#define P_LED     13 // LED pin

// RF defines
#define MY_ID   0x1B // Decimal value: 27 - One Byte, range (0-255) | (0x00-0xFF)

/***************************************************************************************/

// RF Object
RFSCOMM rf(MY_ID);

/***************************************************************************************/

// Main Setup function
void setup()
{
    // Init Serial and RF object
    Serial.begin(9600);
    rf.config(NO_USE, P_RX, MAN_1200);

    Serial.print("\nSystem with ID 0x"); Serial.print(MY_ID, HEX); Serial.print(", configured to receive\n");
    Serial.print("\n-------------------------------------------------------\n");
}

// Main Loop function
void loop()
{
    uint8_t src_id, dev_id, data_length;
    uint8_t* data;

    // If any packet received
    if(rf.receive())
    {
        // Get the packet content
        src_id = rf.rx_src_id();
        dev_id = rf.rx_dev_id();
        data_length = rf.rx_data_length();
        data = rf.rx_data();

        // Notify and show packet content
        Serial.print("\nPackage received:\n");
        Serial.print("[From device with ID: 0x"); Serial.print(src_id, HEX); Serial.print(" | ");
        Serial.print("To device with ID: 0x"); Serial.print(dev_id, HEX); Serial.print(" | ");
        Serial.print("Data ("); Serial.print(data_length); Serial.print(" bytes): ");
        for(int i = 0; i < data_length; i++)
        {
            Serial.print("0x"); Serial.print(data[i], HEX); Serial.print(" ");
        }
        Serial.print("]\n\n");

        if(dev_id == MY_ID)
        {
            if(data_length == 1)
            {
                Serial.print("Expected data from device [0x"); Serial.print(src_id, HEX); Serial.print("] has been received.\n");
				Serial.print("Data received: 0x"); Serial.print(data[0], HEX); Serial.println();
            }
            else
                Serial.print("Unexpected data received. More than one byte of data received.\n");
        }

        Serial.print("\n-------------------------------------------------------\n");
    }
}

/***************************************************************************************/

