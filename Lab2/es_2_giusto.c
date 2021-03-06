#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define CHAR 30
#define MAXD 1000

typedef enum{
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err
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
} dat;

comandi_e leggiComando (void);
void elencaData(dat dati[], int len);
void elencaCorsePartenza(dat dati[], int len);
void elencaCorseCapolinea(dat dati[], int len);
void elencaRitardo(dat dati[], int len);
void elencaRitardoTot(dat dati[], int len);
void minuscolo(char parola[CHAR]);

int main() {
    int i = 0, j, continua = 1, lenght = 0;
    FILE *fp = fopen("corse.txt", "r");
    if(fp == NULL){
        printf("ERRORE NELL'APERTURA DEL FILE");
        EXIT_FAILURE;
    }
    comandi_e codiceComando;
    dat dati[MAXD];
    while(fscanf(fp, "%d %s %s %d/%d/%d %s %s %d",&dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione,
                 &dati[i].gg, &dati[i].mm, &dati[i].aaaa, dati[i].oraPartenza, dati[i].oraArrivo, &dati[i].ritardo) != EOF){
        lenght++;
        i++;
    }
    for (j = 0; j < lenght; j++) {
        minuscolo(dati[j].destinazione);
        minuscolo(dati[j].partenza);
    }

fclose(fp);

while(continua) {
    codiceComando = leggiComando();
    switch (codiceComando) {
        case r_date: elencaData(dati, lenght);
            break;
        case r_partenza: elencaCorsePartenza(dati, lenght);
            break;
        case r_capolinea: elencaCorseCapolinea(dati, lenght);
            break;
        case r_ritardo: elencaRitardo(dati, lenght);
            break;
        case r_ritardo_tot: elencaRitardoTot(dati, lenght);
            break;
        case r_fine: (continua = 0);
            break;
        case r_err:
        default: printf("comando errato\n");
    }
   }
    return 0;
}

comandi_e leggiComando (void){
    comandi_e c;
    int len = 0;
    int i = 0;
    char cmd[MAX];
    char tabella[r_fine][MAX] = {
            "date", "partenza", "capolinea", "ritardo", "ritardo_tot"
    };
    printf("[COMANDO]\nDate Partenza Capolinea Ritardo Ritardo_tot\n"
           "Fine per terminare\n");
    scanf("%s", cmd);
    minuscolo(cmd);
    c = r_date;
    while (c<r_fine && strcmp(cmd,tabella[c])!=0)
        c++;
    return (c);
}

void elencaData(dat dati[], int len) {
            int g1, m1, a1, g2, m2, a2, i;
            printf("digita l'intervallo di date (con formato gg/mm/aaaa) per elencare le corse\n");
            scanf("%d/%d/%d %d/%d/%d", &g1, &m1, &a1, &g2, &m2, &a2);
            if (a1 < a2 || (a1 == a2 && m1 < m2) || (a1 == a2 && m1 == m2 && g1 < g2)) {
                for (i = 0; i < len; i++) {
                    if ((dati[i].aaaa < a2 || (dati[i].aaaa == a2 && dati[i].mm < m2) ||
                         (dati[i].aaaa == a2 && dati[i].mm == m2 && dati[i].gg < g2)) &&
                        (dati[i].aaaa > a1 || (dati[i].aaaa == a1 && dati[i].mm > m1) ||
                         (dati[i].aaaa == a1 && dati[i].mm == m1 && dati[i].gg > g1))) {
                        printf("%d %s %s %d/%d/%d %s %s %d\n", dati[i].codiceTratta, dati[i].partenza,
                               dati[i].destinazione,
                               dati[i].gg, dati[i].mm, dati[i].aaaa, dati[i].oraPartenza, dati[i].oraArrivo,
                               dati[i].ritardo);
                    }
                }
            } else {
                for (i = 0; i < len; i++) {
                    if ((dati[i].aaaa > a2 || (dati[i].aaaa == a2 && dati[i].mm > m2) ||
                         (dati[i].aaaa == a2 && dati[i].mm == m2 && dati[i].gg > g2)) &&
                        (dati[i].aaaa < a1 || (dati[i].aaaa == a1 && dati[i].mm < m1) ||
                         (dati[i].aaaa == a1 && dati[i].mm == m1 && dati[i].gg < g1))) {
                        printf("%d %s %s %d/%d/%d %s %s %d\n", dati[i].codiceTratta, dati[i].partenza,
                               dati[i].destinazione,
                               dati[i].gg, dati[i].mm, dati[i].aaaa, dati[i].oraPartenza, dati[i].oraArrivo,
                               dati[i].ritardo);
                    }
                }
            }
        }
void elencaCorsePartenza(dat dati[], int len) {
        char partenza[CHAR];
        int i;
        printf("digita una città di partenza per elencare tutte le corse partite da questa citta'");
        scanf("%s", partenza);
        minuscolo(partenza);
        for (i = 0; i < len; i++) {
            if (strcmp(partenza, dati[i].partenza) == 0) {
                printf("%d %s %s %d/%d/%d %s %s %d\n", dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione,
                       dati[i].gg, dati[i].mm, dati[i].aaaa, dati[i].oraPartenza, dati[i].oraArrivo, dati[i].ritardo);
            }
        }
    }

void elencaCorseCapolinea(dat dati[], int len) {
        char capolinea[CHAR];
        int i;
        printf("Digita una città di arrivo per elencare tutte le corse arrivate in questa citta'");
        scanf("%s", capolinea);
        minuscolo(capolinea);
        for (i = 0; i < len; i++) {
            if (strcmp(capolinea, dati[i].destinazione) == 0) {
                printf("%d %s %s %d/%d/%d %s %s %d\n", dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione,
                       dati[i].gg, dati[i].mm, dati[i].aaaa, dati[i].oraPartenza, dati[i].oraArrivo, dati[i].ritardo);
            }
        }
    }


void elencaRitardo(dat dati[], int len) {
        int i;
        printf("Le corse partite in ritardo sono:");
        for (i = 0; i < len; ++i) {
            if (dati[i].ritardo != 0) {
                printf("%d %s %s %d/%d/%d %s %s %d\n", dati[i].codiceTratta, dati[i].partenza, dati[i].destinazione,
                       dati[i].gg, dati[i].mm, dati[i].aaaa, dati[i].oraPartenza, dati[i].oraArrivo, dati[i].ritardo);
            }
        }
    }

void elencaRitardoTot(dat dati[], int len) {
        int i, ritardo_tot = 0, codiceTratta;
        printf("digita il codice di una tratta per sapere il ritardo complessivo su quella tratta");
        scanf("%d", &codiceTratta);
        for (i = 0; i < len; i++) {
            if (codiceTratta == dati[i].codiceTratta) {
                ritardo_tot += dati[i].ritardo;
            }
        }
        printf("Il ritardo totale è %d minuti\n", ritardo_tot);
    }

void minuscolo(char parola[CHAR]){
    int i, j, len;
    len = strlen(parola);
    for(i = 0; i < len; i++){
        parola[i] = tolower(parola[i]);
    }
}
