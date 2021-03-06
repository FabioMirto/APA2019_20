#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define CHAR 30
#define MAXD 1000

typedef enum{
    r_date, r_partenza, r_capolinea, r_codicetratta, r_ricerca, r_fine, r_err
} comandi_e;

typedef struct{
    int codiceTratta;
    char partenza[CHAR];
    char destinazione[CHAR];
    int gg;
    int mm;
    int aaaa;
    char oraPartenza[CHAR];
    char oraArrivo[CHAR];
    int ritardo;
    int dataInt;
} dat;

comandi_e leggiComando (void);
void minuscolo(char parola[CHAR]);
void selezionaDati(comandi_e codiceComando, dat *dati, int lenght);
int ricercaLineare(dat dati[], int lenght, char par[30]);
int ricercaDicotomica(dat dati[], int lenght, char par[30]);


int main() {
    int i = 0, j, lenght = 0, stamp = 0;
    FILE *fp = fopen("corse.txt", "r");
    FILE *fp1 = fopen("log.txt", "w");
    if(fp == NULL){
        printf("ERRORE NELL'APERTURA DEL FILE");
        EXIT_FAILURE;
    }
    comandi_e codiceComando;
    dat dati[MAXD];
    while(fscanf(fp, "%d %s %s %d/%d/%d %s %s %d",&dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione,
                 &dati[i].gg, &dati[i].mm, &dati[i].aaaa, dati[i].oraPartenza, dati[i].oraArrivo, &dati[i].ritardo) != EOF){
        dati[i].dataInt = dati[i].aaaa * 10000 + dati[i].mm * 100 + dati[i].gg; //da sistemare
        lenght++;
        i++;
    }
    for (j = 0; j < lenght; j++) {
        minuscolo(dati[j].destinazione);
        minuscolo(dati[j].partenza);
    }
    printf("per stampare i contenuti del log\n"
           "premere 1 per stampare su video\n"
           "premere 0 per stampare su file\n");
    scanf("%d", &stamp);
    if(stamp == 0){
        for (int k = 0; k < lenght; k++) {
            fprintf(fp1, "%d %s %s %d/%d/%d %s %s %d\n",dati[k].codiceTratta, dati[k].partenza, dati[k].destinazione,
                    dati[k].gg, dati[k].mm, dati[k].aaaa, dati[k].oraPartenza, dati[k].oraArrivo, dati[k].ritardo);
        }
    } else {
        for (int k = 0; k < lenght; k++) {
            printf( "%d %s %s %d/%d/%d %s %s %d\n",dati[k].codiceTratta, dati[k].partenza, dati[k].destinazione,
                    dati[k].gg, dati[k].mm, dati[k].aaaa, dati[k].oraPartenza, dati[k].oraArrivo, dati[k].ritardo);
        }
    }


    fclose(fp);
    fclose(fp1);

    selezionaDati(codiceComando, dati, lenght);

    return 0;
}
void selezionaDati(comandi_e codiceComando, dat *dati, int lenght){
    int i = 0, j = 0, l = 0, r = lenght - 1, k = 0, continua = 1, ricerca, m;
    int dataInt[lenght];
    int temp;
    char tempt[30], par[30];
    while(continua) {
        codiceComando = leggiComando();
        switch (codiceComando) {
            case r_date:
                for (k = 0; k < lenght; k++) {
                    dati[k].dataInt = dati[k].aaaa * 10000 + dati[k].mm * 100 + dati[k].gg;
                }
                for (i = l; i < r; i++) {
                    for (j = l; j < r - i + l; j++) {
                        if (dati[j].dataInt > dati[j+1].dataInt) {
                            temp = dati[j].dataInt;
                            dati[j].dataInt = dati[j+1].dataInt;
                            dati[j+1].dataInt = temp;
                        } else if (dataInt[j] == dataInt[j + 1]) {
                            if (strcmp(dati[j].oraPartenza, dati[j + 1].oraPartenza) > 0) {
                                strcpy(tempt, dati[j].oraPartenza);
                                strcpy(dati[j].oraPartenza, dati[j + 1].oraPartenza);
                                strcpy(dati[j + 1].oraPartenza, tempt);
                            }
                        }

                    }
                }
                for (k = 0; k < lenght; k++) {
                    printf( "%d %s %s %d %s %s %d\n",dati[k].codiceTratta, dati[k].partenza, dati[k].destinazione,
                            dati[k].dataInt, dati[k].oraPartenza, dati[k].oraArrivo, dati[k].ritardo);
                }
                break;
            case r_partenza:
                ricerca = 1;
                for (i = l; i < r; i++) {
                    for (j = l; j < r - i + l; j++) {
                        if (strcmp(dati[j].partenza, dati[j + 1].partenza) > 0) {
                            strcpy(tempt, dati[j].partenza);
                            strcpy(dati[j].partenza, dati[j + 1].partenza);
                            strcpy(dati[j + 1].partenza, tempt);
                        }
                    }
                }
                for (k = 0; k < lenght; k++) {
                    printf( "%d %s %s %d/%d/%d %s %s %d\n",dati[k].codiceTratta, dati[k].partenza, dati[k].destinazione,
                            dati[k].gg, dati[k].mm, dati[k].aaaa, dati[k].oraPartenza, dati[k].oraArrivo, dati[k].ritardo);
                }
                break;
            case r_capolinea:
                ricerca = 0;
                for (i = l; i < r; i++) {
                    for (j = l; j < r - i + l; j++) {
                        if (strcmp(dati[j].destinazione, dati[j + 1].destinazione) > 0) {
                            strcpy(tempt, dati[j].destinazione);
                            strcpy(dati[j].destinazione, dati[j + 1].destinazione);
                            strcpy(dati[j + 1].destinazione, tempt);
                        }
                    }
                }
                for (k = 0; k < lenght; k++) {
                    printf( "%d %s %s %d/%d/%d %s %s %d\n",dati[k].codiceTratta, dati[k].partenza, dati[k].destinazione,
                            dati[k].gg, dati[k].mm, dati[k].aaaa, dati[k].oraPartenza, dati[k].oraArrivo, dati[k].ritardo);
                }
                break;
            case r_codicetratta:
                ricerca = 0;
                for (i = l; i < r; i++) {
                    for (j = l; j < r - i + l; j++) {
                        if (dati[j].codiceTratta > dati[j + 1].codiceTratta) {
                            temp = dati[j].codiceTratta;
                            dati[j].codiceTratta = dati[j + 1].codiceTratta;
                            dati[j + 1].codiceTratta = temp;
                        }
                    }
                }
                for (k = 0; k < lenght; k++) {
                    printf( "%d %s %s %d/%d/%d %s %s %d\n",dati[k].codiceTratta, dati[k].partenza, dati[k].destinazione,
                            dati[k].gg, dati[k].mm, dati[k].aaaa, dati[k].oraPartenza, dati[k].oraArrivo, dati[k].ritardo);
                }
                break;
            case r_ricerca:
                printf("Inserisci una stazione di partenza per la ricerca\n");
                scanf("%s", par);
                minuscolo(par);
                if(ricerca == 0){
                    m = ricercaLineare(dati, lenght, par);
                } else{
                    m = ricercaDicotomica(dati, lenght, par);
                }
                if(m != -1){
                    printf( "%d %s %s %d/%d/%d %s %s %d\n",dati[m].codiceTratta, dati[m].partenza, dati[m].destinazione,
                            dati[m].gg, dati[m].mm, dati[m].aaaa, dati[m].oraPartenza, dati[m].oraArrivo, dati[m].ritardo);
                } else{
                    printf("Stazione di partenza non trovata\n");
                }
                break;
            case r_fine: (continua = 0);
                break;
            case r_err:
            default: printf("comando errato\n");
        }
    }
}

comandi_e leggiComando (void){
    comandi_e c;
    int len = 0;
    int i = 0;
    char cmd[MAX];
    char tabella[r_fine][MAX] = {
            "date", "partenza", "capolinea", "codice_tratta", "ricerca"
    };
    printf("[COMANDO]\nDate Partenza Capolinea Codice_Tratta Ricerca\n"
           "Fine per terminare\n");
    scanf("%s", cmd);
    minuscolo(cmd);
    c = r_date;
    while (c<r_fine && strcmp(cmd,tabella[c])!=0)
        c++;
    return (c);
}

void minuscolo(char parola[CHAR]){
    int i, j, len;
    len = strlen(parola);
    for(i = 0; i < len; i++){
        parola[i] = tolower(parola[i]);
    }
}

int ricercaLineare(dat dati[], int lenght, char par[30]){
    int i = 0, r = lenght - 1;
    for(i = 0; i < r; i++){
        if(strcmp(dati[i].partenza, par) == 0){
            return i;
        }
    }
    return -1;
}

int ricercaDicotomica(dat dati[], int lenght, char par[30]){
    int i = 0, r = lenght - 1;
    int m;
    while(i <= r){
        m = (i+r)/2;
        if(strcmp(dati[m].partenza, par) == 0){
            return m;
        } else if(strcmp(dati[m].partenza, par) < 0){
            i = m + 1;
        } else {
            r = m - 1;
        }
    }
    return -1;
}
