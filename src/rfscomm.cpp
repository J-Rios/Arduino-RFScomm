#include "rfscomm.h"

/***************************************************************************************/

RFSCOMM::RFSCOMM(uint8_t my_id)
{
    _my_id = my_id;
    _src_id = 0;
    _dev_id = 0;
    _data_length = 0;
    memset(_data, '\0', AES_BLOCK_SIZE-3);
    _waiting_rx = 1;
}

/***************************************************************************************/

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

/***************************************************************************************/

void RFSCOMM::send(uint8_t dest_id, uint8_t data)
{
    uint8_t data_length = 1;

    _tx_package[0] = _my_id;
    _tx_package[1] = dest_id;
    _tx_package[2] = data_length;
    _tx_package[3] = data;

    aes256_enc(_tx_package, &_key_context);
    man.transmitArray(AES_BLOCK_SIZE, _tx_package);
}

void RFSCOMM::send(uint8_t dest_id, uint8_t cmd, uint8_t val)
{
    uint8_t data_length = 2;

    _tx_package[0] = _my_id;
    _tx_package[1] = dest_id;
    _tx_package[2] = data_length;
    _tx_package[3] = cmd;
    _tx_package[4] = val;

    aes256_enc(_tx_package, &_key_context);
    man.transmitArray(AES_BLOCK_SIZE, _tx_package);
}

void RFSCOMM::send(uint8_t dest_id, uint8_t* data, uint8_t data_length)
{
    if(data_length != 0)
    {
        if(data_length > AES_BLOCK_SIZE-3)
        {
            data_length = AES_BLOCK_SIZE-3;
            data[data_length-1] = '\0';
        }

        _tx_package[0] = _my_id;
        _tx_package[1] = dest_id;
        _tx_package[2] = data_length;
        for(int i = 3; i < data_length+3; i++)
            _tx_package[i] = data[i-3];

        aes256_enc(_tx_package, &_key_context);
        man.transmitArray(AES_BLOCK_SIZE, _tx_package);
    }
}

/***************************************************************************************/

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
            _data_length = _rx_package[2];
            for (int i = 0; i < _data_length; i++)
            	_data[i] = _rx_package[i+3];
            man.beginReceiveArray(AES_BLOCK_SIZE, _rx_package);
            result = 1;
        }
        // For future: Add some kind of low power delay here that not interfer with the rx timer in manchester lib...
    }
    
    return result;
}

/***************************************************************************************/

uint8_t RFSCOMM::rx_src_id()
{
    return _src_id;
}

uint8_t RFSCOMM::rx_dev_id()
{
    return _dev_id;
}

uint8_t RFSCOMM::rx_data_length()
{
    return _data_length;
}

uint8_t* RFSCOMM::rx_data()
{
    return _data;
}
