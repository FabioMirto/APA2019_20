#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

typedef enum {
    r_newpg, r_deletepg, r_addob, r_deleteob, r_statpg, r_err, r_fine
} comandi_e;

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct {
    char *nome;
    char *tipo;
    stat_t stat;
} inv_t;

typedef struct {
    int inUso;
    inv_t *vettEq[8];
} tabEquip_t;

typedef struct {
    inv_t *vettInv;
    int nInv;
    int maxInv;
} tabInv_t;

typedef struct{
    char *codice;
    char *personaggio;
    char *classe;
    tabEquip_t equip;
    stat_t stat;
} pg_t;

typedef struct node{
    pg_t val;
    struct node *next;
}*nodoPg_t;

typedef struct {
    nodoPg_t headPg;
    nodoPg_t tailPg;
    int nPg;
} tabPg_t;

nodoPg_t newNode(pg_t val, nodoPg_t next);
void  ListIn(tabPg_t *tabPg);
void VectIn(tabInv_t *tabInv);
nodoPg_t listInsHead (nodoPg_t h, pg_t val);
void printList(tabPg_t *h);
void DelOb(tabPg_t *tabPg, char k[6+1], char ob[MAX+1], tabInv_t *tabInv);
void InsOb(tabPg_t *tabPg, char k[6+1], char ob[MAX+1], tabInv_t *tabInv);
void selezionaDati(tabPg_t *tabPg, tabInv_t *tabInv, comandi_e codiceComando);
comandi_e leggiComando(void);
void minuscolo(char parola[MAX]);
nodoPg_t listDelKey(nodoPg_t h, char k[6+1]);
void calStat(tabPg_t *tabPg, char k[6+1]);

int main() {
    tabPg_t tabPg;
    tabInv_t tabInv;
    ListIn(&tabPg);
    VectIn(&tabInv);

    selezionaDati(&tabPg, &tabInv, leggiComando());

    return 0;
}

comandi_e leggiComando(void){
        comandi_e c;
        char cmd[MAX];
        char tabella[r_fine][MAX] = {
                "new_pg", "delete_pg", "add_ob",
                "delete_ob", "stats"
        };
        printf("\t\t\t\t\t\t[COMANDO]\nNew_pg Delete_pg Add_ob Delete_ob Stats\n"
               "Fine per terminare\n");
        scanf("%s", cmd);
        minuscolo(cmd);
        c = r_newpg;
        while (c<r_fine && strcmp(cmd,tabella[c])!=0)
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

void selezionaDati(tabPg_t *tabPg, tabInv_t *tabInv, comandi_e codiceComando){
    int i = 0, j = 0, continua = 1, scelta;
    char code[6+1], ob[MAX+1];
    char cod[6+1], name[MAX], tipo[MAX];
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
                scanf("%s %s %s %d %d %d %d %d %d", cod, name, tipo, &tmp.stat.hp,
                      &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag, &tmp.stat.spr);
                tmp.codice = strdup(cod);
                tmp.personaggio = strdup(name);
                tmp.classe = strdup(tipo);
                tabPg->headPg = listInsHead(tabPg->headPg, tmp);
                printf("Personaggio aggiunto nella lista\n");
                printList(tabPg);
                codiceComando = leggiComando();
                break;
            case r_deletepg :
                printf("Inserire il codice di un personaggio per eliminarlo\n");
                scanf("%s", code);
                tabPg->headPg = listDelKey(tabPg->headPg, code);
                printf("Personaggio eliminato dalla lista\n");
                printList(tabPg);
                codiceComando = leggiComando();
                break;
            case r_addob:
                InsOb(tabPg, code, ob, tabInv);
                codiceComando = leggiComando();
                break;
            case r_deleteob :
                DelOb(tabPg, code, ob, tabInv);
                codiceComando = leggiComando();
                break;
            case r_statpg :
                calStat(tabPg, code);
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
    char codice[6+1], personaggio[MAX+1], classe[MAX+1];
    tabPg->headPg = NULL;

    while (fscanf(fp, "%s %s %s %d %d %d %d %d %d", codice, personaggio, classe, &tmp.stat.hp,
                  &tmp.stat.mp, &tmp.stat.atk, &tmp.stat.def, &tmp.stat.mag, &tmp.stat.spr) != EOF) {
        tmp.equip.inUso = 0;
        tmp.codice = strdup(codice);
        tmp.personaggio = strdup(personaggio);
        tmp.classe = strdup(classe);
        tabPg->headPg = listInsHead(tabPg->headPg, tmp);
        i++;
        if(i == 1){
            tabPg->tailPg = tabPg->headPg;
        }
    }
    tabPg->nPg = i;
    fclose(fp);
}

void printList(tabPg_t *h){
    tabPg_t *x;
    int i;
    for (x = h; x->headPg->next != NULL; x->headPg = x->headPg->next) {
            printf("%s %s %s %d %d %d %d %d %d\n", x->headPg->val.codice,
                   x->headPg->val.personaggio, x->headPg->val.classe,
                   x->headPg->val.stat.hp,  x->headPg->val.stat.mp,  x->headPg->val.stat.atk,
                   x->headPg->val.stat.def,  x->headPg->val.stat.mag, x->headPg->val.stat.spr);
           /* if(x->headPg->val.equip.inUso != 0){
                for (i = 0; i < x->headPg->val.equip.inUso; i++) {
                    printf("%s %s %d %d %d %d %d %d\n", x->headPg->val.equip.vettEq[i]->nome,
                           x->headPg->val.equip.vettEq[i]->tipo, x->headPg->val.equip.vettEq[i]->stat.hp,
                           x->headPg->val.equip.vettEq[i]->stat.mp, x->headPg->val.equip.vettEq[i]->stat.atk,
                           x->headPg->val.equip.vettEq[i]->stat.def, x->headPg->val.equip.vettEq[i]->stat.mag,
                           x->headPg->val.equip.vettEq[i]->stat.spr);
                }
            }*/
    }
}

void VectIn(tabInv_t *tabInv){
    int i;
    char nome[MAX+1], tipo[MAX+1];
    FILE *fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &tabInv->nInv);
    tabInv->vettInv = (inv_t *) calloc(tabInv->nInv, sizeof(inv_t));
    for(i = 0; i < tabInv->nInv; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", nome,
               tipo, &tabInv->vettInv[i].stat.hp,
               &tabInv->vettInv[i].stat.mp, &tabInv->vettInv[i].stat.atk,
               &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag,
               &tabInv->vettInv[i].stat.spr);
        tabInv->vettInv[i].nome = strdup(nome);
        tabInv->vettInv[i].tipo = strdup(tipo);
    }
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
    printf("Inserire il codice del personaggio\n(formato PGXXXX dove X rappresenta"
           "una cifra nell'intervallo 0-9) \n");
    scanf("%s", k);
    int i, flag = 0;
    if(x->val.equip.inUso == 0){
        printf("Zaino vuoto\n");
        return;
    }
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
                printf("%s %s %s "
                       "%d %d %d %d %d %d\n", x->val.codice,
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
                }
                    printf("%s %s %s ", x->val.codice, x->val.personaggio, x->val.classe);
                    if (x->val.stat.hp < 0)
                        printf("1 ");
                    else
                        printf("%d ", x->val.stat.hp);

                    if (x->val.stat.mp < 0)
                        printf("1 ");
                    else
                        printf("%d ", x->val.stat.mp);

                    if (x->val.stat.atk < 0)
                        printf("1 ");
                    else
                        printf("%d ", x->val.stat.atk);

                    if (x->val.stat.def < 0)
                        printf("1 ");
                    else
                        printf("%d ", x->val.stat.def);

                    if (x->val.stat.mag < 0)
                        printf("1 ");
                    else
                        printf("%d ", x->val.stat.mag);

                    if (x->val.stat.spr < 0)
                        printf("1\n");
                    else
                        printf("%d\n", x->val.stat.spr);
            }
        }
    }
    if(!flag){
        printf("Codice non trovato!\n");
    }
}

