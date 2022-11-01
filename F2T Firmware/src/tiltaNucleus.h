#include <stdint.h>
#include "usart.h"

class TiltaNucleus {

    const uint32_t CMD_FOCUS = 0x010601;
    const unsigned MAX_POSITION = 10000;
    
    typedef union {
        struct __attribute__((__packed__)) {
            uint32_t command : 24;
            uint8_t unknown_maybePacketCounter;
            uint16_t focusValue;
            uint8_t checksum;
        };
        uint8_t raw[7];
    } packet_t;

    public:
    TiltaNucleus(UART_HandleTypeDef *uart);
    void setPosition(uint16_t position);

    private:
    void sendPacket(packet_t pkt);
    uint8_t calculateChecksum(packet_t pkt);

    uint8_t _packetCounter = 0;
    UART_HandleTypeDef *_uart;
};