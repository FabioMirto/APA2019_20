#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX 50

typedef enum{
    r_inserimentoa, r_inserimentob, r_ricerca, r_cancella, r_cancelladate, r_stampa, r_fine, r_err
} comandi_e;

typedef struct{
    char codice[6+1];
    char nome[MAX + 1];
    char cognome[MAX + 1];
    int gg;
    int mm;
    int aaaa;
    int dataInt;
    char via[MAX + 1];
    char citta[MAX + 1];
    int cap;
} Item ;

typedef struct node{
    Item *val;
    struct node *next;
}*link;

void minuscolo(char parola[MAX]);
comandi_e leggiComando (void);
Item *ListSearch(link h, char *code);
void printList(link h, int file);
Item *SortListDelDate(link *hp, int d1, int d2);
Item *SortListDel(link *hp,char codice[]);
Item *ListIn(FILE *fp, int file);
link SortListIns(link h,Item* val);
link newNode(link next,Item *val);
void selezionaDati(comandi_e codiceComando, link head);

int main() {
    link head = NULL;
    comandi_e codiceComando;
    codiceComando = leggiComando();
    selezionaDati(codiceComando, head);

return 0;
}

void selezionaDati(comandi_e codiceComando, link head){
    char codice[6];
    Item *tmp = NULL;
    int continua = 1, g1, m1, a1, g2, m2, a2, dataInt1, dataInt2, datatmp;
    FILE *fp;
    fp = fopen("item.txt", "r");
    assert(fp != NULL);
    while (continua) {
        switch (codiceComando) {
            case r_inserimentoa:
                printf("Inserisci"
                       "Codice Nome Cognome Data (nel formato gg/mm/aaaa) Via Città CAP\n");
                tmp = ListIn(fp, 0);
                head = SortListIns(head, tmp);
                printList(head, 0);
                codiceComando = leggiComando();
                break;
            case r_inserimentob:
                while(!feof(fp)){
                    tmp = ListIn(fp, 1);
                    head = SortListIns(head, tmp);
                }
                printList(head, 0);
                codiceComando = leggiComando();
                break;
            case r_ricerca:
                printf("Inserisci codice da cercare\n");
                scanf("%s", codice);
                tmp = ListSearch(head, codice);
                if(tmp != NULL)
                    printf("%s %s %s %d/%d/%d %s %s %d\n", tmp->codice,
                           tmp->nome, tmp->cognome,
                           tmp->gg, tmp->mm, tmp->aaaa,
                           tmp->via, tmp->citta, tmp->cap);
                codiceComando = leggiComando();
                break;
            case r_cancella:
                printf("Inserisci codice da eliminare\n");
                scanf("%s", codice);
                if(ListSearch(head,codice)!=NULL){
                    tmp = SortListDel(&head, codice);
                    printf("%s %s %s %d/%d/%d %s %s %d\n", tmp->codice,
                           tmp->nome, tmp->cognome,
                           tmp->gg, tmp->mm, tmp->aaaa,
                           tmp->via, tmp->citta, tmp->cap);
                }
                codiceComando = leggiComando();
                break;
            case r_cancelladate:
                printf("Inserisci due date nel formato gg/mm/aaaa\n");
                scanf("%d/%d/%d %d/%d/%d", &g1, &m1, &a1, &g2, &m2, &a2);
                dataInt1 = a1*10000 + m1 *100 + g1;
                dataInt2 = a2*10000 + m2 *100 + g2;
                if(dataInt1 > dataInt2){
                    datatmp = dataInt1;
                    dataInt1 = dataInt2;
                    dataInt2 = datatmp;
                }
                while (tmp != NULL){
                    tmp = SortListDelDate(&head, dataInt1, dataInt2);
                    if(tmp != NULL)
                        printf("%s %s %s %d/%d/%d %s %s %d\n", tmp->codice,
                               tmp->nome, tmp->cognome,
                               tmp->gg, tmp->mm, tmp->aaaa,
                               tmp->via, tmp->citta, tmp->cap);
                }
                codiceComando = leggiComando();
                break;
            case r_stampa:
                printList(head, 1);
                codiceComando = leggiComando();
                break;
            case r_fine:
                continua = 0;
                break;
            case r_err:
            default: printf("comando errato\n");
                break;
        }
    }
}

comandi_e leggiComando (void){
    comandi_e c;
    char cmd[MAX];
    char tabella[r_fine][MAX] = {
            "ins", "ins_file", "ricerca", "cancella_codice", "cancella_date", "stampa"
    };
    printf("\t\t\t\t\t\t[COMANDO]\nIns Ins_file Ricerca Cancella_codice Cancella_date Stampa\n"
           "Fine per terminare\n");
    scanf("%s", cmd);
    minuscolo(cmd);
    c = r_inserimentoa;
    while (c<r_fine && strcmp(cmd,tabella[c])!=0)
        c++;
    return (c);
}

void minuscolo(char parola[MAX]){
    int i, len;
    len = strlen(parola);
    for(i = 0; i < len; i++){
        parola[i] = tolower(parola[i]);
    }
}

Item *ListSearch(link h, char *code) {
    link x;
    for (x = h; x != NULL; x = x->next) {
        if (strcmp(x->val->codice, code) == 0)
            return x->val;
    }
    return NULL;
}

void printList(link h, int file){
    link x;
    FILE *fp1;
    if(file) {
        fp1 = fopen("stampa.txt", "w");
        assert(fp1 != NULL);
            fprintf(fp1, "LISTA:\n");
            for (x = h; x != NULL; x = x->next) {
                fprintf(fp1, "%s %s %s %d/%d/%d %s %s %d\n", x->val->codice, x->val->nome, x->val->cognome,
                        x->val->gg, x->val->mm, x->val->aaaa,
                        x->val->via, x->val->citta, x->val->cap);
            }
            fclose(fp1);
        } else {
            for (x = h; x != NULL; x = x->next) {
                printf("%s %s %s %d/%d/%d %s %s %d\n", x->val->codice, x->val->nome, x->val->cognome,
                       x->val->gg, x->val->mm, x->val->aaaa,
                       x->val->via, x->val->citta, x->val->cap);
            }
        }
}

Item* SortListDel(link *hp,char codice[]){
    link *xp,t;
    Item *val = NULL;
    for(xp = hp; (*xp) != NULL ;xp = &((*xp)->next)){
        if(strcmp((*xp)->val->codice, codice)==0){
            val = (*xp)->val;
            t = (*xp);
            (*xp) = (*xp)->next;
            free(t);
            break;
        }
    }
    return val;
}

Item* ListIn(FILE *fp, int file){
    Item *val;
    val = (Item *) malloc(sizeof(Item));
    if(file) {
        fscanf(fp, "%s %s %s %d/%d/%d %s %s %d\n", val->codice, val->nome, val->cognome,
               &val->gg, &val->mm, &val->aaaa, val->via, val->citta, &val->cap);
        val->dataInt = val->gg + val->mm * 100 + val->aaaa * 10000;
        return val;
    } else {
        scanf("%s %s %s %d/%d/%d %s %s %d", val->codice, val->nome, val->cognome,
               &val->gg, &val->mm, &val->aaaa, val->via, val->citta, &val->cap);
        val->dataInt = val->gg + val->mm * 100 + val->aaaa * 10000;
        return val;
    }
}

Item* SortListDelDate(link *hp, int d1, int d2){
    link *xp, t;
    Item *val = NULL;
    for(xp=hp;(*xp) != NULL;xp = &((*xp)->next)){
        if((((*xp)->val->dataInt)) < d2 && ((*xp)->val->dataInt) > d1){
            val = (*xp)->val;
            t = (*xp);
            (*xp) = (*xp)->next;
            free(t);
            break;
        }
    }
    return val;
}

link SortListIns(link h,Item* val){
    link x,p;
    if(h == NULL || h->val->dataInt > val->dataInt)
        return newNode(h,val);
    for(x = h->next, p = h;
    x != NULL && x->val->dataInt < val->dataInt;
    p=x, x = x->next);
    p->next = newNode(x,val);
    return h;
}

link newNode(link next,Item *val){
    link x;
    x = (link) malloc(sizeof(*x));
    if(x == NULL)
        return NULL;
    x->next = next;
    x->val = val;
    return x;
}
