#include "tiltaNucleus.h"

#include <stdio.h>

TiltaNucleus::TiltaNucleus(UART_HandleTypeDef *uart) {
    _uart = uart;
}

uint8_t TiltaNucleus::calculateChecksum(packet_t pkt) {
    uint8_t chk = 0;
    for(uint8_t i = 0; i < sizeof(packet_t) - 1; i++) {
        chk -= pkt.raw[i];
    }
    return chk;
}

void TiltaNucleus::sendPacket(packet_t pkt) {
    char buf[32] = {0};
    uint8_t bufPos = 0;

    pkt.checksum = calculateChecksum(pkt);

    bufPos += sprintf(buf + bufPos, ":");
    bufPos += sprintf(buf + bufPos, "%06lX", pkt.command);
    bufPos += sprintf(buf + bufPos, "%02X", pkt.unknown_maybePacketCounter);
    bufPos += sprintf(buf + bufPos, "%04X", pkt.focusValue);
    bufPos += sprintf(buf + bufPos, "%02X", pkt.checksum);
    bufPos += sprintf(buf + bufPos, "\r\n");


    printf("Sending command [%d]: %s", bufPos, buf);
    HAL_UART_Transmit(_uart, (uint8_t *)buf, bufPos, 10);
}

void TiltaNucleus::setPosition(uint16_t position) {
    if (position >= MAX_POSITION) {
        return;
    }

    packet_t pkt;
    pkt.command = CMD_FOCUS;
    pkt.unknown_maybePacketCounter = _packetCounter; // always increments by 5, idk
    pkt.focusValue = position;

    _packetCounter += 5;
    sendPacket(pkt);
}