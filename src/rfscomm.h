#ifndef RFSCOMM_h
    #define RFSCOMM_h
  
    #include "utility/AVR_Crypto_Lib_aes/aes.h"
    #include "utility/Manchester_Lib/manchester.h"

    #define AES_KEY_SIZE    32  // AES-256 encryption Key size (32 bytes - 256 bits)
    #define AES_BLOCK_SIZE  16  // AES-256 encryption Data block size (16 bytes - 128 bits)
    #define RX_TIMEOUT      100 // Reception waiting time
    #define NO_USE          255 // No use value for Tx or Rx pins

    const uint8_t key[AES_KEY_SIZE] =
    {
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,
        18,19,20,21,22,23,24,25,26,27,28,29,30,31
    };
  
    class RFSCOMM
    {
        public:
            RFSCOMM(uint8_t my_id);
            void config(uint8_t _tx_pin, uint8_t _rx_pin, uint8_t rf_bauds);
            void send(uint8_t dest_id, uint8_t data);
            uint8_t receive();
            uint8_t rx_src_id();
            uint8_t rx_dev_id();
            uint8_t rx_cmd();
            
        private:
            uint8_t _my_id;
            uint8_t _src_id, _dev_id, _cmd;
            uint8_t _rx_package[AES_BLOCK_SIZE];
            uint8_t _tx_package[AES_BLOCK_SIZE];
            aes256_ctx_t _key_context;
            uint8_t _waiting_rx;
    };
  
#endif
