#include <pic18f4520.h>
#include "bits.h"
#include "config.h"  
#include "io.h"
#include "so.h"
#include "delay.h"

//vetor para armazenar a conversão para o display
static const char valor[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D,
    0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C,
    0x39, 0x5E, 0x79, 0x71
};

//armazena qual é o display disponivel
static char display = 0;

// armazena o valor para cada display
static char v0, v1, v2, v3;

//armazena o valor completo a ser exibido nos diplays
int v = 4321;

void main() {
    //configuração dos pinos de controle para o SSD
    pinMode(DISP_1_PIN, OUTPUT);
    pinMode(DISP_2_PIN, OUTPUT);
    soInit();

    //Tempo de atraso para a multiplexação dos displays
    int tempo = 50;

    for (;;) {
        v0 = ((v / 1) % 10);
        v1 = ((v / 10) % 10);
        v2 = ((v / 100) % 10);
        v3 = ((v / 1000) % 10);

        //desliga TODOS os displays
        digitalWrite(DISP_1_PIN, LOW);
        digitalWrite(DISP_2_PIN, LOW);
    
        //desliga todos os leds
        soWrite(0x00);

        //liga APENAS um display por vez
        switch (display) {
            case 0:
                // Valor do display
                soWrite(valor[v0]);
                // Ligação do display
                digitalWrite(DISP_1_PIN, HIGH);
                //Próximo estado a ser executado
                display = 1;
                // Atraso para a multiplexação
                atraso(tempo);
                break;

            case 1:
                soWrite(valor[v1]);
                digitalWrite(DISP_2_PIN, HIGH);
                display = 0;
                atraso(tempo);
                break;

            default:
                display = 0;
                break;
        }
    }
}