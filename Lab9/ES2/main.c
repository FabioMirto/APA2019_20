#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "pgList.h"
#include "invArray.h"
#include "pg.h"

#define MAX 50

typedef enum {
    r_stampapg, r_stampainv, r_cercapg, r_aggiungipg, r_eliminapg, r_modificaeq, r_err, r_fine
} comandi_e;

void selezionaDati(pgList_t pgList, invArray_t invArray, comandi_e codiceComando);
comandi_e leggiComando(void);
void minuscolo(char parola[MAX]);

int main() {
    FILE *fp;
    pgList_t pgList = pgList_init();
    pgList = pgList_read(fp, pgList);
    invArray_t invArray = invArray_init();
    invArray = invArray_read(fp, invArray);
    selezionaDati(pgList, invArray, leggiComando());
    pgList_free(pgList);
    return 0;
}

comandi_e leggiComando(void){
    comandi_e c;
    char cmd[MAX];
    char tabella[r_fine][MAX] = {
           "stampa_pg", "stampa_inv", "cerca_pg",
           "aggiungi_pg", "elimina_pg", "modifica_eq"
    };
    printf("\t\t\t[COMANDO]\nstampa_pg stampa_inv cerca_pg\naggiungi_pg elimina_pg modifica_eq\n"
           "Fine per terminare\n");
    scanf("%s", cmd);
    minuscolo(cmd);
    c = r_stampapg;
    while (c < r_fine && strcmp(cmd, tabella[c]) != 0)
        c++;
    return (c);
}

void minuscolo(char parola[MAX]){
    int i, len;
    len = (int) strlen(parola);
    for(i = 0; i < len; i++){
        parola[i] = tolower(parola[i]);
    }
}

void selezionaDati(pgList_t pgList, invArray_t invArray, comandi_e codiceComando){
    int i = 0, j = 0, continua = 1;
    char cmd[7];
    FILE *fp;
    pg_t *pgp, pg;
    char code[6+1];
    while(continua){
        switch(codiceComando){
            case r_stampapg :
                pgList_print(fp, pgList, invArray);
                codiceComando = leggiComando();
                break;
            case r_stampainv :
                invArray_read(fp, invArray);
                invArray_print(fp, invArray);
                codiceComando = leggiComando();
                break;
            case r_cercapg :
                printf("Inserire codice personaggio: ");
                scanf("%s", code);
                pgp = pgList_searchByCode(pgList, code);
                if (pgp!=NULL) {
                    pg_print(fp, pgp, invArray);
                }
                codiceComando = leggiComando();
                break;
            case r_aggiungipg :
                pgList_insert(pgList, pg);
                codiceComando = leggiComando();
                break;
            case r_eliminapg :
                pgList = pgList_remove(pgList, code);
                pgList_print(fp, pgList, invArray);
                codiceComando = leggiComando();
                break;
            case r_modificaeq:
                printf("Inserire codice personaggio: ");
                scanf("%s", cmd);
                pgp = pgList_searchByCode(pgList, cmd);
                if (pgp!=NULL) {
                    pg_updateEquip(pgp, invArray);
                }
                pgList_print(fp, pgList, invArray);
                codiceComando = leggiComando();
                break;
            case r_fine :
                continua = 0;
                break;
            case r_err :
            default: printf("comando errato\n");
                break;
        }
    }
}
