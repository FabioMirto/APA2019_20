#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX 20
#define CHAR 30
#define MAXD 1000

typedef enum{
    r_date, r_partenza, r_capolinea, r_codicetratta, r_ricerca, r_stampa, r_fine, r_err,
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
void ricercaLineare(dat dati[], int lenght, char par[30]);
int ricercaDicotomica(dat dati[], int lenght, char par[30]);
void stampaPuntatore(dat **dati1, int lenght);
void ordinamento(dat **dati1, int i, int j);


int main() {
    int i = 0, j, lenght = 0, stamp = 0;
    FILE *fp = fopen("corse.txt", "r");
    assert(fp != NULL);
    comandi_e codiceComando;
    dat dati[MAXD];
    while(fscanf(fp, "%d %s %s %d/%d/%d %s %s %d",&dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione,
                 &dati[i].gg, &dati[i].mm, &dati[i].aaaa, dati[i].oraPartenza, dati[i].oraArrivo, &dati[i].ritardo) != EOF){
        dati[i].dataInt = dati[i].aaaa * 10000 + dati[i].mm * 100 + dati[i].gg;
        minuscolo(dati[i].destinazione);
        minuscolo(dati[i].partenza);
        lenght++;
        i++;
    }

    fclose(fp);

    selezionaDati(codiceComando, dati, lenght);

    return 0;
}
void selezionaDati(comandi_e codiceComando, dat *dati, int lenght){
    int i = 0, j = 0, l = 0, r = lenght - 1, k = 0, stamp, continua = 1, ricerca, m;
    int dataInt[lenght];
        char par[30];
    FILE *fp1;
    dat *date[lenght], *partenza[lenght], *destinazione[lenght], *codice_tratta[lenght];
    for (i = 0; i < lenght; i++) {
        partenza[i] = destinazione[i] = codice_tratta[i] = date[i] = &dati[i];
    }
    while(continua) {
        codiceComando = leggiComando();
        switch (codiceComando) {
            case r_date:
                for (k = 0; k < lenght; k++) {
                    date[k]->dataInt = dati[k].aaaa * 10000 + dati[k].mm * 100 + dati[k].gg;
                }
                for (i = l; i < r; i++) {
                    for (j = l; j < r - i + l; j++) {
                        if (date[j]->dataInt > date[j+1]->dataInt) {
                            ordinamento(date, i, j);
                        } else if (dataInt[j] == dataInt[j + 1]) {
                            if (strcmp(date[j]->oraPartenza, date[j + 1]->oraPartenza) > 0) {
                                ordinamento(date, i, j);
                            }
                        }

                    }
                }
                stampaPuntatore(date, lenght);
                break;
            case r_partenza:
                ricerca = 1;
                for (i = l; i < r; i++) {
                    for (j = l; j < r - i + l; j++) {
                        if (strcmp(partenza[j]->partenza, partenza[j + 1]->partenza) > 0) {
                            ordinamento(partenza, i, j);
                        }
                    }
                }
                stampaPuntatore(partenza, lenght);
                break;
            case r_capolinea:
                ricerca = 0;
                for (i = l; i < r; i++) {
                    for (j = l; j < r - i + l; j++) {
                        if (strcmp(destinazione[j]->destinazione, destinazione[j + 1]->destinazione) > 0) {
                            ordinamento(destinazione, i, j);
                        }
                    }
                }
                stampaPuntatore(destinazione, lenght);
                break;
            case r_codicetratta:
                ricerca = 0;
                for (i = l; i < r; i++) {
                    for (j = l; j < r - i + l; j++) {
                        if (codice_tratta[j]->codiceTratta > codice_tratta[j + 1]->codiceTratta) {
                            ordinamento(codice_tratta, i, j);
                        }
                    }
                }
                stampaPuntatore(codice_tratta, lenght);
                break;
            case r_ricerca:
                printf("Inserisci una stazione di partenza per la ricerca\n");
                scanf("%s", par);
                minuscolo(par);
                if(ricerca == 0){
                    ricercaLineare(dati, lenght, par);
                } else {
                   m = ricercaDicotomica(dati, lenght, par);
                    if(m != -1){
                        printf( "%d %s %s %d/%d/%d %s %s %d\n",dati[m].codiceTratta, dati[m].partenza, dati[m].destinazione,
                                dati[m].gg, dati[m].mm, dati[m].aaaa, dati[m].oraPartenza, dati[m].oraArrivo, dati[m].ritardo);
                    } else{
                        printf("Stazione di partenza non trovata\n");
                    }
                }

                break;
            case r_stampa:
                printf("per stampare i contenuti del log\n"
                       "premere 1 per stampare su video\n"
                       "premere 0 per stampare su file\n");
                scanf("%d", &stamp);
                if(stamp == 0){
                    fp1 = fopen("log.txt", "w");
                    assert(fp1 != NULL);
                    for (k = 0; k < lenght; k++) {
                        fprintf(fp1, "%d %s %s %d/%d/%d %s %s %d\n",dati[k].codiceTratta, dati[k].partenza, dati[k].destinazione,
                                dati[k].gg, dati[k].mm, dati[k].aaaa, dati[k].oraPartenza, dati[k].oraArrivo, dati[k].ritardo);
                    }
                    fclose(fp1);
                } else {
                    for (k = 0; k < lenght; k++) {
                        printf( "%d %s %s %d/%d/%d %s %s %d\n",dati[k].codiceTratta, dati[k].partenza, dati[k].destinazione,
                                dati[k].gg, dati[k].mm, dati[k].aaaa, dati[k].oraPartenza, dati[k].oraArrivo, dati[k].ritardo);
                    }
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
    char cmd[MAX];
    char tabella[r_fine][MAX] = {
            "date", "partenza", "capolinea", "codice_tratta", "ricerca", "stampa"
    };
    printf("[COMANDO]\nStampa Date Partenza Capolinea Codice_Tratta Ricerca\n"
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

void ricercaLineare(dat dati[], int lenght, char par[30]){
    int i = 0, r = lenght - 1;
    for(i = 0; i < r; i++){
        if(strncmp(dati[i].partenza, par, strlen(par)) == 0){
            printf( "%d %s %s %d/%d/%d %s %s %d\n",dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione,
                    dati[i].gg, dati[i].mm, dati[i].aaaa, dati[i].oraPartenza, dati[i].oraArrivo, dati[i].ritardo);
        }
    }
}

int ricercaDicotomica(dat dati[], int lenght, char par[30]){
    int i = 0, r = lenght - 1;
    int m;
    while(i <= r){
        m = (i+r)/2;
        if(strncmp(dati[m].partenza, par, strlen(par)) == 0){
          return m;
        } else if(strncmp(dati[m].partenza, par, strlen(par)) < 0){
            i = m + 1;
        } else {
            r = m - 1;
        }
    }
}

void stampaPuntatore(dat **dati1, int lenght){
    int i;
    for(i = 0; i < lenght; i++){
        printf( "%d %s %s %d/%d/%d %s %s %d\n",dati1[i]->codiceTratta, dati1[i]->partenza, dati1[i]->destinazione,
                dati1[i]->gg, dati1[i]->mm, dati1[i]->aaaa, dati1[i]->oraPartenza, dati1[i]->oraArrivo, dati1[i]->ritardo);
    }
}

void ordinamento(dat **dati1, int i, int j){
    dat *temp;
    temp = dati1[j];
    dati1[j] = dati1[j+1];
    dati1[j+1] = temp;
}
