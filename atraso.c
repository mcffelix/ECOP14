
void atraso_ms(unsigned int num) {
    volatile unsigned char j, k;
    for (int i = 0; i < num; i++) {
        for (j = 0; j < 41; j++) {
            for (k = 0; k < 3; k++);
        }

    }
}
