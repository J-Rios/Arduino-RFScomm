#include "rfscomm.h"

/*******************************/

RFSCOMM::RFSCOMM(uint8_t my_id)
{
    _my_id = my_id;
    _src_id = 0;
    _dev_id = 0;
    _cmd = 0;
    _waiting_rx = 1;
}

/*******************************/

void RFSCOMM::config(uint8_t tx_pin, uint8_t rx_pin, uint8_t rf_bauds)
{
    aes256_init(key, &_key_context);
    
    //man.workAround1MhzTinyCore(); //add this in order for transmitter to work with 1Mhz Attiny85/84

    if(tx_pin == NO_USE)
        man.setupReceive(rx_pin, rf_bauds);
    else if (rx_pin == NO_USE)
        man.setupTransmit(tx_pin, rf_bauds);
    else
        man.setup(tx_pin, rx_pin, rf_bauds);
}

/*******************************/

void RFSCOMM::send(uint8_t dest_id, uint8_t data)
{
    _tx_package[0] = _my_id;
    _tx_package[1] = dest_id;
    _tx_package[2] = data;
    aes256_enc(_tx_package, &_key_context);
    man.transmitArray(AES_BLOCK_SIZE, _tx_package);
}

/*******************************/

uint8_t RFSCOMM::receive()
{
    uint8_t result = 0;
    unsigned long initTime = millis();

    if(_waiting_rx)
    {
        man.beginReceiveArray(AES_BLOCK_SIZE, _rx_package);
        _waiting_rx = 0;
    }
        
    while((millis() - initTime) < RX_TIMEOUT)
    {
        if(man.receiveComplete())
        {
            aes256_dec(_rx_package, &_key_context);
            _src_id = _rx_package[0];
            _dev_id = _rx_package[1];
            _cmd = _rx_package[2];
            man.beginReceiveArray(AES_BLOCK_SIZE, _rx_package);
            result = 1;
        }
        // For future: Add some kind of low power delay here that not interfer with the rx timer in manchester lib...
    }
    
    return result;
}

uint8_t RFSCOMM::rx_src_id()
{
    return _src_id;
}

uint8_t RFSCOMM::rx_dev_id()
{
    return _dev_id;
}

uint8_t RFSCOMM::rx_cmd()
{
    return _cmd;
}
