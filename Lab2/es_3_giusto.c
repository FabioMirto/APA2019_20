#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NOME_FILE1 "sequenze.txt"
#define NOME_FILE2 "testo.txt"
#define CHAR 5
#define MAX 20
#define RIGA 200
#define PAR 25

typedef struct {
    char sequenza[CHAR+1];
} dat;

typedef struct {
    char parola[PAR+1];
} test;


int main() {
    int i = 0, j, p, l, m = 0, num = 0, countWords = 0, len = 0;
    char riga[PAR+1], parola[PAR+1];
    test testo[RIGA];
    dat dati[MAX];
    FILE *fp1, *fp2;
    fp1 = fopen(NOME_FILE1, "r");
    fp2 = fopen(NOME_FILE2, "r");

    if (fp1 == NULL || fp2 == NULL) {
        printf("ERRORE NELL'APERTURA DEL FILE");
        EXIT_FAILURE;
    }

    fscanf(fp1, "%d", &num);
    for (i = 0; i < num; i++) {
        fscanf(fp1, "%s", dati[i].sequenza);
        len = strlen(dati[i].sequenza);
        for (l = 0; l < len; l++) {
            dati[i].sequenza[l] = tolower(dati[i].sequenza[l]);
        }
    }
    while (!feof(fp2)) {
        fscanf(fp2, "%s", testo[m].parola);
        for (int n = 0; n < strlen(testo[m].parola); n++) {
            testo[m].parola[n] = tolower(testo[m].parola[n]);
            if (ispunct(testo[m].parola[n]) != 0) {
                if (testo[m].parola[n] == '\'') {
                    i++;
                    testo[m].parola[n] = ' ';
                    sscanf(testo[m].parola, "%s%s", riga, parola);
                    strcpy(testo[m].parola, riga);
                    strcpy(testo[m + 1].parola, parola);
                    m++;
                }
                testo[m].parola[n] = ' ';
            }
            countWords++;
        }
        m++;
    }
    for (l = 0; l < num; l++) {
        p=0;
        for (j = 0; j < countWords; j++) {
                    if (strstr(testo[j].parola, dati[l].sequenza) != 0) {
                        if (p < 10) {
                            printf("la sequenza %s e' contenuta in %s (in posizione %d)\n", dati[l].sequenza,
                                   testo[j].parola,
                                   j + 1);
                            p++;

                        }
                    }
                }
            }
            fclose(fp1);
            fclose(fp2);
        return 0;
}
