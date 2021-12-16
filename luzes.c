#include "config.h"
#include "pic18f4520.h"
#include "bits.h"
#include "keypad.h"
#include "lcd.h"
#include "rgb.h"

void Luzes(void){
    volatile int i;
    float t;
    unsigned int tecla;
    kpInit();
    lcdInit();
    rgbInit();
    TRISD = 0x00;  
    PORTD = 0x00; 
    
    for(;;){
        kpDebounce();
    if(kpRead() != tecla){
        tecla = kpRead();
        if(kpReadKey() == 'U'){
            rgbColor(1);
            turnOn(1);
            lcdCommand(0x80);
            lcdString("Luz do quarto");
            lcdCommand(0xC0);
            lcdString("ON");
        }
        if(kpReadKey() == 'L'){
            lcdCommand(0x01);
            rgbColor(2);
            turnOn(2);
            lcdCommand(0x80);
            lcdString("Luz da sala");
            lcdCommand(0xC0);
            lcdString("ON");
        }
        if(kpReadKey() == 'D'){
            lcdCommand(0x01);
            rgbColor(4);
            turnOn(4);
            lcdCommand(0x80);
            lcdString("Luz da cozinha");
            lcdCommand(0xC0);
            lcdString("ON");
        }
        if(kpReadKey() == 'A'){
            lcdCommand(0x01);
            for(i=0; i<7; i++){
                bitClr(PORTD, i);
            }
            lcdCommand(0x80);
            lcdString("Luzes");
            lcdCommand(0xC0);
            lcdString("OFF");
        }
        if(kpReadKey() == 'B'){
            lcdCommand(0x01);
            for(i=0; i<7; i++){
                bitSet(PORTD, i);
            }
            lcdCommand(0x80);
            lcdString("Luzes");
            lcdCommand(0xC0);
            lcdString("ON");
            }
        if (kpReadKey() == 'X') {
                lcdCommand(0x01);
                lcdString("Luzes alternando");
                bitSet(PORTD, 0);
                for (t = 0; t < 5000; t++);
                bitClr(PORTD, 0);
                bitSet(PORTD, 1);
                for (t = 0; t < 5000; t++);
                bitClr(PORTD, 1);
                bitSet(PORTD, 2);
                for (t = 0; t < 5000; t++);
                bitClr(PORTD, 2);
                bitSet(PORTD, 3);
                for (t = 0; t < 5000; t++);
                bitClr(PORTD, 3);
        }
    }
    }
}
  

            
            
            
        
    
