#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
inline void setBit(uint8_t bit){
    PORTB |= (bit << PB0);
}

void spi_xmit(uint8_t byte){
    PORTB &= ~(1 << PB0);
    for (uint8_t i = 0; i < 8; i++){
        setBit(((byte & 0x80) >> 7) & 0x01);
        byte <<= 1;
        PORTB |= (1 << PB1);
        _delay_us(8);
        PORTB &= ~(1 << PB1);
        _delay_us(1);
        PORTB &= ~(1 << PB0);
        _delay_us(7);
    }
    _delay_us(874);
}

void send_package(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4, uint8_t b5, uint8_t b6, uint8_t b7){
    spi_xmit(b0);
    spi_xmit(b1);
    spi_xmit(b2);
    spi_xmit(b3);
    spi_xmit(b4);
    spi_xmit(b5);
    spi_xmit(b6);
    spi_xmit(b7);
}
int main(void){
    // ACSR = (1 << ACD);
    DDRB |= (1 << PB0) | (1 << PB1);
    PORTB = 0x00;
    _delay_ms(500);
    send_package(0x74,0xBE,0xFE,0xFF,0xFF,0xFF,0x8F,0x7C);
    _delay_ms(100);
    send_package(0x34,0xFF,0xFE,0xFE,0xFE,0xFF,0xFA,0x3C);
    _delay_ms(10);
    send_package(0x74,0xBE,0xFE,0xFF,0xFF,0xFF,0x8F,0x7C);
    for (;;){
        _delay_ms(41);
        send_package(0x34, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xCF, 0x3C);
    }
}
