#include <stdio.h>

void stampaCodifica (void *p, int size, int bigEndian);


int main (void) {
    float af;
    double ad;
    long double ald;
    char *c;
    int size_af, size_ad, size_ald;
    unsigned int i = 1;
    int bigEndian = 0;
    c = (char *) &i;
    if (*c == 1) {
        bigEndian = 0;
        printf("LITTLE ENDIAN\n");
    } else {
        bigEndian = 1;
        printf("BIG ENDIAN\n");
    }

    printf("Inserisci un numero: ");
    scanf("%Lf", &ald);
    af = (float) ald;
    ad = (double) ald;

    size_af = sizeof(af);
    size_ad = sizeof(ad);
    size_ald = sizeof(ald);

    printf("La dimensione espressa è:\n"
           "FLOAT = %d (in byte) %d (in bit)\n"
           "DOUBLE = %d (in byte) %d (in bit)\n"
           "LONG DOUBLE = %d (in byte) %d (in bit)\n", size_af, size_af*8, size_ad, size_ad*8, size_ald, size_ald*8);

    printf("****FLOAT****\n");
    printf("BIT SEGNO\n");
    stampaCodifica( (void*) &af, sizeof(af), bigEndian);
    printf("\n");
    printf("****DOUBLE****\n");
    printf("BIT SEGNO\n");
    stampaCodifica( (void*) &ad, sizeof(ad), bigEndian);
    printf("\n");
    printf("****LONG DOUBLE****\n");
    printf("BIT SEGNO\n");
    stampaCodifica( (void*) &ald, sizeof(ald), bigEndian);

    return 0;
}

void stampaCodifica (void *p, int size, int bigEndian) {
    int i, j;
    char *c = (char *) p;
    int cod[size * 8];
    if (bigEndian) {
        for (i = 0; i < size; i++) {
            for (j = 8; j > 0; j--) {
                printf("%d", (c[i] >> j) & 1);
                if (size == 4) {
                    if (i == 0 && j == 8) {
                        printf("\nBIT ESPONENTE\n");
                    }
                    if (i == 1 && j == 8) {
                        printf("\nBIT MANTISSA\n");
                    }
                }if(size == 8){
                        if (i == 0 && j == 8) {
                            printf("\nBIT ESPONENTE\n");
                        } if(i == 1 && j == 5){
                        printf("\nBIT MANTISSA\n");
                        }
                    } if(size == 16){
                        if (i ==  0 && j == 8) {
                            printf("\nBIT ESPONENTE\n");
                        } if(i ==  1 && j == 1){
                        printf("\nBIT MANTISSA\n");
                        }
                    }
            }
        }
    } else {
        for (i = size - 1; i >= 0; i--) {
            for (j = 7; j >= 0; j--) {
                printf("%d", (c[i] >> j) & 1);
                if (size == 4) {
                    if (i == size - 1 && j == 7) {
                        printf("\nBIT ESPONENTE\n");
                    } if(i == size - 2 && j == 7){
                        printf("\nBIT MANTISSA\n");
                    }
                } if(size == 8){
                    if (i == size - 1 && j == 7) {
                        printf("\nBIT ESPONENTE\n");
                    } if(i == size - 2 && j == 4){
                        printf("\nBIT MANTISSA\n");
                    }
                } if(size == 16){
                    if (i == size - 1 && j == 7) {
                        printf("\nBIT ESPONENTE\n");
                    } if(i == size - 2 && j == 0){
                        printf("\nBIT MANTISSA\n");
                    }
                }
            }
        }
    }
}
