#include "adc.h"
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "keypad.h"
#include "serial1.h"
#include "bits.h"
#include "pic18f4520.h"
#include "pwm.h"
#include "bits.h"
#include "serial.h"
#include "ds1307.h"
#include "i2c.h"
#include "cooler.h"
#include "luzes.h"
#include "placasolar.h"

void main(void) {
    char casos;
    unsigned int tecla;
    int time;
    kpInit();
    
    char logo[48] = {
        0x01, 0x03, 0x03, 0x0E, 0x1C, 0x18, 0x08, 0x08, //0,0
        0x11, 0x1F, 0x00, 0x01, 0x1F, 0x12, 0x14, 0x1F, //0,1
        0x10, 0x18, 0x18, 0x0E, 0x07, 0x03, 0x02, 0x02, //0,2
        0x08, 0x18, 0x1C, 0x0E, 0x03, 0x03, 0x01, 0x00, //1,0
        0x12, 0x14, 0x1F, 0x08, 0x00, 0x1F, 0x11, 0x00, //1,1
        0x02, 0x03, 0x07, 0x0E, 0x18, 0x18, 0x10, 0x00 //1,2
    };
    lcdInit();
    int i;
    lcdCommand(0x40); //Configura para a primeira posição de memória
    //Envia cada uma das linhas em ordem
    for (i = 0; i < 48; i++) {
        lcdChar(logo[i]);
    }
    lcdCommand(0x80);
    lcdChar(0);
    lcdChar(1);
    lcdChar(2);
    lcdCommand(0xC0);
    lcdChar(3);
    lcdChar(4);
    lcdChar(5);
    
    lcdPosition(0,8);
    lcdString("CASA");
    lcdPosition(1,4);
    lcdString("INTELIGENTE");
    
    for (;;) {
        kpDebounce();
        if (kpRead() != tecla) {
            tecla = kpRead();
            if (kpReadKey() == 'U') {
                Luzes();
            }
            if (kpReadKey() == 'L') {
                PrincipalPlaca();
            }
            if (kpReadKey() == 'D') {
                PrincipalCooler();
            }
        }
    }
}



















