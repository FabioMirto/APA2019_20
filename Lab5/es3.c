#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define CHAR 30

typedef enum{
   r_date, r_partenza, r_capolinea, r_codicetratta, r_ricerca, r_lettura, r_stampa, r_fine, r_err
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
    int len;
} dat;

comandi_e leggiComando (void);
void minuscolo(char parola[CHAR]);
void selezionaDati(comandi_e codiceComando, dat *dati, int lenght, FILE *fp);
void ricercaLineare(dat dati[], int lenght, char par[30]);
int ricercaDicotomica(dat dati[], int lenght, char par[30]);
void stampaPuntatore(dat **dati1, int lenght);
void ordinamento(dat **dati1, int i, int j);
dat *leggiFile(int *len, dat *dati);

int main() {
    int m = 0, i, lenght, stamp = 0, verifica = 0;
    FILE *fp = fopen("corse.txt", "r");
    FILE *fp1;
    FILE *fp2;
    if(fp == NULL){
        printf("ERRORE NELL'APERTURA DEL FILE");
        EXIT_FAILURE;
    }
    comandi_e codiceComando;
    dat *dati = leggiFile(&lenght, NULL);

    selezionaDati(codiceComando, dati, lenght, fp1);

    return 0;
}
void selezionaDati(comandi_e codiceComando, dat *dati, int lenght, FILE *fp){
    int i = 0, j = 0, l = 0, r = lenght - 1, k = 0, continua = 1, ricerca = 0, m;
    int dataInt[lenght];
    int stamp = 0;
    char par[30];

    dat **date, **partenza, **destinazione, **codice_tratta;

    date = malloc(lenght * sizeof(dat*));
    partenza = malloc(lenght * sizeof(dat*));
    destinazione = malloc(lenght * sizeof(dat*));
    codice_tratta = malloc(lenght * sizeof(dat*));

    for (i = 0; i < lenght; i++) {
        partenza[i] = destinazione[i] = codice_tratta[i] = date[i] = &dati[i];
    }
    while(continua) {
        codiceComando = leggiComando();
        switch (codiceComando) {
            case r_stampa:
                printf("per stampare i contenuti del log\n"
                       "premere 1 per stampare su video\n"
                       "premere 0 per stampare su file\n");
                scanf("%d", &stamp);
                if(stamp == 0){
                    fp = fopen("log.txt", "w");
                    for (k = 0; k < lenght; k++) {
                        fprintf(fp, "%d %s %s %d/%d/%d %s %s %d\n",dati[k].codiceTratta, dati[k].partenza, dati[k].destinazione,
                                dati[k].gg, dati[k].mm, dati[k].aaaa, dati[k].oraPartenza, dati[k].oraArrivo, dati[k].ritardo);
                    }
                } else {
                    for (k = 0; k < lenght; k++) {
                        printf( "%d %s %s %d/%d/%d %s %s %d\n",dati[k].codiceTratta, dati[k].partenza, dati[k].destinazione,
                                dati[k].gg, dati[k].mm, dati[k].aaaa, dati[k].oraPartenza, dati[k].oraArrivo, dati[k].ritardo);
                        printf("%d\n", dati[k].dataInt);
                    }
                }
                break;
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
            case r_lettura :
                if (dati != NULL)
                    free(dati);
                dati = leggiFile(&lenght, dati);
                for(m = 0; m < lenght; m++){
                    printf( "%d %s %s %d/%d/%d %s %s %d\n", dati[m].codiceTratta, dati[m].partenza, dati[m].destinazione,
                            dati[m].gg, dati[m].mm, dati[m].aaaa, dati[m].oraPartenza, dati[m].oraArrivo, dati[m].ritardo);
                }
                selezionaDati(codiceComando, dati, lenght, fp);
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
            "date", "partenza", "capolinea", "codice_tratta", "ricerca", "lettura", "stampa"
    };
    printf("\t\t\t\t\t\t[COMANDO]\nStampa Date Partenza Capolinea Codice_Tratta Ricerca Lettura\n"
           "Fine per terminare\n");
    scanf("%s", cmd);
    minuscolo(cmd);
    c = r_date;
    while (c<r_fine && strcmp(cmd,tabella[c])!=0)
        c++;
    return (c);
}

void minuscolo(char parola[CHAR]){
    int i, len;
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

void stampaPuntatore(dat **dati1, int lenght){
    int i;
    for(i = 0; i < lenght; i++){
        printf( "%d %s %s %d/%d/%d %s %s %d\n", dati1[i]->codiceTratta, dati1[i]->partenza, dati1[i]->destinazione,
                dati1[i]->gg, dati1[i]->mm, dati1[i]->aaaa, dati1[i]->oraPartenza, dati1[i]->oraArrivo, dati1[i]->ritardo);
    }
}

dat *leggiFile(int *len, dat *dati) {

    FILE *fp;
    char name[20];
    dat d_temp;
    int n = 1, i = 0;
    printf("Inserire nome file:");
    scanf("%s", name);

    fp = fopen(name, "r");

    dati = malloc(n * sizeof(dat));

    while (fscanf(fp, "%d %s %s %d/%d/%d %s %s %d",&d_temp.codiceTratta, d_temp.partenza, d_temp.destinazione,
                  &d_temp.gg, &d_temp.mm, &d_temp.aaaa, d_temp.oraPartenza, d_temp.oraArrivo, &d_temp.ritardo) != EOF) {
        d_temp.dataInt = d_temp.aaaa*10000 + d_temp.mm * 100 + d_temp.gg;
        minuscolo(d_temp.partenza);
        minuscolo(d_temp.destinazione);
        if (i == n) {
            n = 2 * n;
            dati = realloc(dati, n * sizeof(dat));
        }
        dati[i++] = d_temp;
    }
    *len = i;
    fclose(fp);
    return dati;
}

void ordinamento(dat **dati1, int i, int j){
    dat *temp;
    temp = dati1[j];
    dati1[j] = dati1[j+1];
    dati1[j+1] = temp;
}
