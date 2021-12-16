#include "pwm.h"
#include "serial.h"
#include <pic18f4520.h>
#include "bits.h"
#include "lcd.h"
#include "serial.h"
#include "ds1307.h"
#include "i2c.h"
#include "adc.h"

#define L_ON 0x0F
#define L_OFF 0x08
#define L_CLR 0x01
#define L_L1 0x80
#define L_L2 0xC0

char temp, l1,l2, h1, h2, t1, t2, j, k, l;
int i, x;

void ConfiguraLimiteInferior(char temp) {
    if (temp == 'a') {
        serial_tx_str(" Digite L2:\r\n");
        l2 = serial_rx(4000);
        lcdPosition(0, 14);
        lcdChar(l2);
        serial_tx(l2);
    }
    if (temp == 'b') {
        serial_tx_str(" Digite L1:\r\n");
        l1 = serial_rx(4000);
        lcdPosition(0, 13);
        lcdChar(l1);
        serial_tx(l1);
    }
}
void ConfiguraLimiteSuperior(char temp) {
    if (temp == 'c') {
        serial_tx_str(" Digite H2:\r\n");
        h2 = serial_rx(4000);
        lcdPosition(0, 9);
        lcdChar(h2);
        serial_tx(h2);
    }
    if (temp == 'd') {
        serial_tx_str(" Digite H1:\r\n");
        h1 = serial_rx(4000);
        lcdPosition(0, 8);
        lcdChar(h1);
        serial_tx(h1);
    }
    if (temp == 'e') {
        serial_tx_str(" Digite T2:\r\n");
        t2 = serial_rx(4000);
        lcdPosition(0, 4);
        lcdChar(t2);
        serial_tx(t2);
    }
    if (temp == 'f') {
        serial_tx_str(" Digite T1:\r\n");
        t1 = serial_rx(4000);
        lcdPosition(0, 3);
        lcdChar(t1);
        serial_tx(t1);
    }
}
void AtualizaTemperatura(void) {
    while (t1 > h1) {
            while (t2 > h2) {
            t2--;
            lcdPosition(0, 4);
            lcdChar(t2);
            serial_tx(t2);
        }
        t1--;
        lcdPosition(0, 3);
        lcdChar(t1);
        serial_tx(t1);
        for (x = 100; x >= 0; x--) {
            if (x > 0) {
                pwmSet(100);
            } else {
                pwmSet(0);
            }
            lcdPosition(1, 7);
            lcdChar((x / 10) % 10 + 48);
            lcdChar(x % 10 + 48);
            x--;
        }
    }
}
void PrincipalCooler(void){
    char l,h,t=0,temp,i,x;
    TRISA = 0xC3;
    TRISB = 0x03;
    TRISC = 0x01;
    TRISD = 0x00;
    TRISE = 0x00;
    ADCON1 = 0x06;
    lcdInit();
    pwmInit();
    pwmFrequency(2000);
    serial_init();
    TRISCbits.TRISC7 = 1; //RX
    TRISCbits.TRISC6 = 0; //TX
    PORTB = 0;
    lcdPosition(0,12);
    lcdChar('L');
    lcdChar('b');
    lcdChar('a');
    lcdPosition(0,7);
    lcdChar('H');
    lcdChar('d');
    lcdChar('c');
    lcdPosition(0,2);
    lcdChar('T');
    lcdChar('f');
    lcdChar('e');
    lcdPosition(1,0);
    lcdString("Ajuste: ");
    for(;;){
        serial_tx_str(" Digite:\r\n");
        temp = serial_rx(2000);
        serial_rx(temp);
        ConfiguraLimiteInferior(temp);
        ConfiguraLimiteSuperior(temp);
        AtualizaTemperatura();
    } 
}