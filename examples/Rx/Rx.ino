#include <rfscomm.h>

#define P_RX      4    // Rx digital pin

#define MY_ID     0x1B // Decimal value: 27  - One Byte, range (0-255) | (0x00-0xFF)
#define CMD       0xFF // Decimal value: 255 - One Byte, range (0-255) | (0x00-0xFF)

RFSCOMM rf(MY_ID);

void setup()
{
    Serial.begin(9600);
    rf.config(NO_USE, P_RX, MAN_1200);
}

void loop()
{
    uint8_t src_id, dev_id, cmd;
    
    if(rf.receive())
    {
        src_id = rf.rx_src_id();
        dev_id = rf.rx_dev_id();
        cmd = rf.rx_cmd();

        Serial.print("\nPackage received:\n");
        Serial.print("My ID: 0x");
        Serial.print(MY_ID, HEX);
        Serial.print(" | From device with ID - 0x");
        Serial.print(dev_id, HEX);
        Serial.print(" | CMD - 0x");
        Serial.print(cmd, HEX);
        Serial.print("\n");

        if(dev_id == MY_ID)
        {
            if(cmd == CMD)
            {
                Serial.print("Expected command from device [0x");
                Serial.print(src_id, HEX);
                Serial.print("] has been received\n");
            }
        }

        Serial.print("\n");
    }
}

