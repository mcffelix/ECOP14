#include "adc.h"
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "serial1.h"
#include "bits.h"
#include "pic18f4520.h"
#include "pwm.h"

int ValorAD = 0;
float time;

void Serial(void) {
    ValorAD = adcRead(0);
    serialSend('I');
    serialSend(':');
    serialSend(' ');
    serialSend((ValorAD / 1000) % 10 + '0');
    serialSend((ValorAD / 100) % 10 + '0');
    serialSend((ValorAD / 10) % 10 + '0');
    serialSend((ValorAD / 1) % 10 + '0');
    serialSend('\n');
}
void MostraLcd(void) {
    ValorAD = adcRead(0);
    lcdCommand(0x80);
    lcdString("Wh/area: ");
    lcdChar((ValorAD / 1000) % 10 + 48);
    lcdChar((ValorAD / 100) % 10 + 48);
    lcdChar((ValorAD / 10) % 10 + 48);
    lcdChar(ValorAD % 10 + 48);
    if(ValorAD<=100){
        lcdCommand(0xC0);
        lcdString("Baixa incidencia");
        pwmSet(50);
    }
    else if(ValorAD>=600){
        lcdCommand(0xC0);
        lcdString("Alta incidencia");
        pwmSet(0);
    }
    else{
        lcdCommand(0xC0);
        lcdString("Media incidencia");
        pwmSet(0);
    }
}
void PrincipalPlaca(void){
    char slot;
    pwmFrequency(2000);
    pwmInit();
    adcInit();
    lcdInit();
    timerInit();
    serialInit(); 
    lcdCommand(0x01);
    for(;;) {
        timerReset(5000);
        switch(slot){
            case 0:
                Serial();
                slot = 1;
                break;
            case 1:
                MostraLcd();
                slot = 0;
                break;
            default:
                slot=0;
                break;
        }
        timerWait();
    }
}


