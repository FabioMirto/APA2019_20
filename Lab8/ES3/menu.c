#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pg.h"
#include "menu.h"


comandi_e leggiComando(void){
    comandi_e c;
    char cmd[MAX];
    char tabella[r_fine][MAX] = {
            "new_pg", "delete_pg", "add_ob",
            "delete_ob", "stats", "print_ob", "search_ob", "print_pg"
    };
    printf("\t\t\t[COMANDO]\nNew_pg Delete_pg Add_ob Delete_ob\n"
           "Stats Print_ob Search_ob Print_pg\n"
           "Fine per terminare\n");
    scanf("%s", cmd);
    minuscolo(cmd);
    c = r_newpg;
    while (c < r_fine && strcmp(cmd, tabella[c]) != 0)
        c++;
    return (c);
}

void selezionaDati(tabPg_t *tabPg, tabInv_t *tabInv, comandi_e codiceComando){
    int i = 0, j = 0, continua = 1, scelta;
    char code[6+1], ob[MAX+1], nome[MAX + 1];
    pg_t tmp;
    while(continua){
        switch(codiceComando){
            case r_newpg :
                printf("Per aggiungere un nuovo personaggio inserire\n"
                       "<codice> <nome> <classe>"
                       "<hp> <mp> <atk> <def> <mag> <spr>\n"
                       "Il codice deve essere nella forma PGXXXX dove X rappresenta"
                       "una cifra nell'intervallo 0-9\n"
                       "Il nome e la classe sono rappresentati privi di spazi (max 50 char)\n"
                       "Tutti i campi sono separati da uno o più spazi\n");
                scanf("%s %s %s %d %d %d %d %d %d", tmp.codice, tmp.personaggio, tmp.classe, &tmp.stat.hp,
                      &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag, &tmp.stat.spr);
                tabPg->headPg = listInsHead(tabPg->headPg, tmp);
                printf("Personaggio aggiunto nella lista\n");
                printList(tabPg, NULL);
                codiceComando = leggiComando();
                break;
            case r_deletepg :
                printf("Inserire il codice di un personaggio per eliminarlo\n");
                scanf("%s", code);
                tabPg->headPg = listDelKey(tabPg->headPg, code);
                printf("Personaggio eliminato dalla lista\n");
                printList(tabPg, NULL);
                codiceComando = leggiComando();
                break;
            case r_addob:
                InsOb(tabPg, code, ob, tabInv);
                printList(tabPg, code);
                codiceComando = leggiComando();
                break;
            case r_deleteob :
                DelOb(tabPg, code, ob, tabInv);
                printList(tabPg, code);
                codiceComando = leggiComando();
                break;
            case r_statpg :
                calStat(tabPg, code);
                codiceComando = leggiComando();
                break;
            case r_stampainv :
                printInv(tabInv, nome);
                codiceComando = leggiComando();
                break;
            case r_cercainv :
                searchInv(tabInv, nome);
                codiceComando = leggiComando();
                break;
            case r_stamppg :
                printf("Inserire il codice di un personaggio per stamparlo\n");
                scanf("%s", code);
                printList(tabPg, code);
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
