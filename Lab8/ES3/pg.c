#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "inventario.h"

nodoPg_t newNode(pg_t val, nodoPg_t next) {
    nodoPg_t x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

nodoPg_t listInsHead (nodoPg_t h, pg_t val) {
    h = newNode(val,h);
    return h;
}

void ListIn(tabPg_t *tabPg){
    FILE *fp = fopen("pg.txt", "r");;
    int i = 0;
    pg_t tmp;

    tabPg->headPg = NULL;

    while (fscanf(fp, "%s %s %s %d %d %d %d %d %d", tmp.codice, tmp.personaggio, tmp.classe, &tmp.stat.hp,
                  &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag, &tmp.stat.spr) != EOF) {
        tmp.equip.inUso = 0;
        tabPg->headPg = listInsHead(tabPg->headPg, tmp);
        i++;
        if(i == 1){
            tabPg->tailPg = tabPg->headPg;
        }
    }
    tabPg->nPg = i;
    fclose(fp);
}

nodoPg_t listDelKey(nodoPg_t h, char k[6+1]) {
    nodoPg_t x, p;
    if (h == NULL)
        return NULL;
    for (x=h, p=NULL; x!=NULL; p=x, x=x->next) {
        if (strcmp(x->val.codice, k) == 0) {
            if (x==h)
                h = x->next;
            else
                p->next = x->next;
            free(x);
            break;
        }
    }
    return h;
}

void InsOb(tabPg_t *tabPg, char k[6+1], char ob[MAX+1], tabInv_t *tabInv){
    nodoPg_t x;
    x = tabPg->headPg;
    printf("Inserire il codice del personaggio\n(formato PGXXXX dove X rappresenta"
           "una cifra nell'intervallo 0-9) \n");
    scanf("%s", k);
    int i, flag = 0;
    if(x->val.equip.inUso == 8){
        printf("Spazio esaurito\n");
        return;
    }
    for (x = tabPg->headPg; x != NULL && flag == 0; x = x->next) {
        if (strcmp(x->val.codice, k) == 0) {
            flag = 1;
        }
    }
    printIn(tabInv);
    if (flag) {
        printf("Digita il nome dell'oggetto da inserire\n");
        scanf("%s", ob);
        for (x = tabPg->headPg; x != NULL; x = x->next) {
            for (i = 0; i < tabInv->nInv; i++) {
                if (strcmp(ob, tabInv->vettInv[i].nome) == 0) {
                    /* strcpy(x->val.equip.vettEq[x->val.equip.inUso]->nome, tabInv->vettInv[i].nome);
                     strcpy(x->val.equip.vettEq[x->val.equip.inUso]->tipo, tabInv->vettInv[i].tipo);
                     x->val.equip.vettEq[x->val.equip.inUso]->stat.hp = tabInv->vettInv[i].stat.hp;
                     x->val.equip.vettEq[x->val.equip.inUso]->stat.mp = tabInv->vettInv[i].stat.mp;
                     x->val.equip.vettEq[x->val.equip.inUso]->stat.atk = tabInv->vettInv[i].stat.atk;
                     x->val.equip.vettEq[x->val.equip.inUso]->stat.def = tabInv->vettInv[i].stat.def;
                     x->val.equip.vettEq[x->val.equip.inUso]->stat.mag = tabInv->vettInv[i].stat.mag;
                     x->val.equip.vettEq[x->val.equip.inUso]->stat.spr = tabInv->vettInv[i].stat.spr;*/
                    x->val.equip.vettEq[x->val.equip.inUso] = &tabInv->vettInv[i];
                    x->val.equip.inUso++;

                }
            }
        }
    } else {
        printf("Codice non trovato\n");
        return;
    }
}

void DelOb(tabPg_t *tabPg, char k[6+1], char ob[MAX+1], tabInv_t *tabInv){
    nodoPg_t x;
    x = tabPg->headPg;
    int i, flag = 0;
    if(x->val.equip.inUso == 0){
        printf("Zaino vuoto\n");
        return;
    }
    printf("Inserire il codice del personaggio\n(formato PGXXXX dove X rappresenta"
           "una cifra nell'intervallo 0-9) \n");
    scanf("%s", k);
    printIn(tabInv);
    for (x = tabPg->headPg; x != NULL && flag == 0; x = x->next) {
        if (strcmp(x->val.codice, k) == 0) {
            flag = 1;
            if (flag) {
                printf("Digita il nome dell'oggetto da eliminare\n");
                scanf("%s", ob);
                for (x = tabPg->headPg; x != NULL; x = x->next) {
                    for (i = 0; i < 8; i++) {
                        if (strcmp(ob, x->val.equip.vettEq[i]->nome) == 0) {
                            strcpy(x->val.equip.vettEq[i]->nome, "");
                            strcpy(x->val.equip.vettEq[i]->tipo, "");
                            x->val.equip.vettEq[i]->stat.hp = 0;
                            x->val.equip.vettEq[i]->stat.mp = 0;
                            x->val.equip.vettEq[i]->stat.atk = 0;
                            x->val.equip.vettEq[i]->stat.def = 0;
                            x->val.equip.vettEq[i]->stat.mag = 0;
                            x->val.equip.vettEq[i]->stat.spr = 0;
                            x->val.equip.inUso--;
                            return;
                        }
                    }
                }
            }
        }
    }

    if(!flag){
        printf("Codice non trovato\n");
        return;
    }
}

void calStat(tabPg_t *tabPg, char k[6+1]){
    int i, flag = 0;
    nodoPg_t x;
    printf("Inserire il codice di un personaggio per calcolare le sue statistiche\n");
    scanf("%s", k);
    for (x = tabPg->headPg; x != NULL && flag == 0; x = x->next) {
        if (strcmp(x->val.codice, k) == 0) {
            flag = 1;
            if(x->val.equip.inUso == 0){
                printf("%s %s %s\n"
                       "HP = %d MP = %d ATK = %d  DEF = %d MAG = %d SPR = %d\n", x->val.codice,
                       x->val.personaggio, x->val.classe, x->val.stat.hp,
                       x->val.stat.mp, x->val.stat.atk,
                       x->val.stat.def, x->val.stat.mag, x->val.stat.spr);
            } else {
                for (i = 0; i < x->val.equip.inUso; i++) {
                    x->val.stat.hp += x->val.equip.vettEq[i]->stat.hp;
                    x->val.stat.mp += x->val.equip.vettEq[i]->stat.mp;
                    x->val.stat.atk += x->val.equip.vettEq[i]->stat.atk;
                    x->val.stat.def += x->val.equip.vettEq[i]->stat.def;
                    x->val.stat.mag += x->val.equip.vettEq[i]->stat.mag;
                    x->val.stat.spr += x->val.equip.vettEq[i]->stat.spr;
                    if (x->val.stat.hp < 0){
                        x->val.stat.hp = 0;
                    }if (x->val.stat.mp < 0){
                        x->val.stat.mp = 0;
                    }if (x->val.stat.atk < 0){
                        x->val.stat.atk = 0;
                    }if (x->val.stat.def < 0){
                        x->val.stat.def = 0;
                    }if (x->val.stat.mag < 0){
                        x->val.stat.mag = 0;
                    }if (x->val.stat.spr < 0){
                        x->val.stat.spr = 0;
                    }
                }
                printf("%s %s %s\n"
                       "HP = %d MP = %d ATK = %d  DEF = %d MAG = %d SPR = %d\n", x->val.codice,
                       x->val.personaggio, x->val.classe, x->val.stat.hp,
                       x->val.stat.mp, x->val.stat.atk,
                       x->val.stat.def, x->val.stat.mag, x->val.stat.spr);
            }
        }
    }
    if(!flag){
        printf("Codice non trovato!\n");
    }
}


void printList(tabPg_t *h, char k[6 + 1]) {
    nodoPg_t x;
    int i;
    if(k != NULL) {
        for (x = h->headPg; x != NULL; x = x->next) {
            if (strcmp(x->val.codice, k) == 0) {
                printf("%s %s %s %d %d %d %d %d %d\n", x->val.codice,
                       x->val.personaggio, x->val.classe,
                       x->val.stat.hp, x->val.stat.mp, x->val.stat.atk,
                       x->val.stat.def, x->val.stat.mag, x->val.stat.spr);
                if (x->val.equip.inUso != 0) {
                    for (i = 0; i < x->val.equip.inUso; i++) {
                        printf("%s %s %d %d %d %d %d %d\n", x->val.equip.vettEq[i]->nome,
                               x->val.equip.vettEq[i]->tipo, x->val.equip.vettEq[i]->stat.hp,
                               x->val.equip.vettEq[i]->stat.mp, x->val.equip.vettEq[i]->stat.atk,
                               x->val.equip.vettEq[i]->stat.def, x->val.equip.vettEq[i]->stat.mag,
                               x->val.equip.vettEq[i]->stat.spr);
                    }
                }
            }
        }
    } else {
        for (x = h->headPg; x != NULL; x = x->next) {
                printf("%s %s %s %d %d %d %d %d %d\n", x->val.codice,
                       x->val.personaggio, x->val.classe,
                       x->val.stat.hp, x->val.stat.mp, x->val.stat.atk,
                       x->val.stat.def, x->val.stat.mag, x->val.stat.spr);
                if (x->val.equip.inUso != 0) {
                    for (i = 0; i < x->val.equip.inUso; i++) {
                        printf("%s %s %d %d %d %d %d %d\n", x->val.equip.vettEq[i]->nome,
                               x->val.equip.vettEq[i]->tipo, x->val.equip.vettEq[i]->stat.hp,
                               x->val.equip.vettEq[i]->stat.mp, x->val.equip.vettEq[i]->stat.atk,
                               x->val.equip.vettEq[i]->stat.def, x->val.equip.vettEq[i]->stat.mag,
                               x->val.equip.vettEq[i]->stat.spr);
                    }
                }
            }
        }
    }


void minuscolo(char parola[MAX]){
    int i, len;
    len = (int) strlen(parola);
    for(i = 0; i < len; i++){
        parola[i] = tolower(parola[i]);
    }
}
