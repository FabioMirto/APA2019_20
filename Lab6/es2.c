#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

typedef enum{
    r_insertion_a, r_insertion_b, r_search, r_deletecode, r_deletedate, r_print, r_fine, r_err
} comandi_e;

typedef struct{
    char codice[6];
    char nome[MAX];
    char cognome[MAX];
    int gg;
    int mm;
    int aaaa;
    char via[MAX];
    char citta[MAX];
    int cap;
    int dataInt;
} Item;

typedef struct node *link;

struct node {
    Item val;
    link next;
};


comandi_e leggiComando (void);
void minuscolo(char parola[MAX]);
link SortListIns(link h, Item val);
link newNode(Item val, link next);
Item LISTsearch(link l, char *code);
Item ITEMnull();
link SortListDel(link h, char *code);
void LISTprint(link l, FILE *fp, Item t);

int main() {
    int continua = 1;
    char s[200], code[51];
    Item *t;
    link h, l, p;
    FILE *fp = fopen("item.txt", "r");
    if(fp == NULL){
        printf("ERRORE!");
    }
    comandi_e codiceComando;
    h = malloc(sizeof (struct node));
    t = malloc(20 * sizeof (struct node));
    while(continua){
        codiceComando = leggiComando();
        switch(codiceComando){
            case r_insertion_a:
                printf("inserisci nuovo elemento ");
                scanf("%s %s %s %d/%d/%d %s %s %d", t->codice, t->nome, t->cognome, &t->gg, &t->mm, &t->aaaa, t->via, t->citta, &t->cap);
                t->dataInt = t->aaaa * 10000 + t->mm * 100 + t->gg;
                printf("%s %s %s %d/%d/%d %s %s %d\n", t->codice, t->nome, t->cognome, t->gg, t->mm, t->aaaa, t->via, t->citta, t->cap);
                if(t->dataInt != 0){
                    SortListIns(h, *t);
                }
                break;
            case r_insertion_b:
                fscanf(fp, "%s %s %s %d/%d/%d %s %s %d", t->codice, t->nome, t->cognome, &t->gg, &t->mm, &t->aaaa, t->via, t->citta, &t->cap);
                t->dataInt = t->aaaa * 10000 + t->mm * 100 + t->gg;
                printf("%s %s %s %d/%d/%d %s %s %d\n", t->codice, t->nome, t->cognome, t->gg, t->mm, t->aaaa, t->via, t->citta, t->cap);
                if(t->dataInt != 0){
                    SortListIns(h, *t);
                }
                break;
            case r_search:
                printf("Inserisci codice da cercare ");
                scanf("%s", code);
                *t = LISTsearch(h, code);
                if(t->dataInt != 0){
                    printf("%s %s %s %d/%d/%d %s %s %d\n", t->codice, t->nome, t->cognome, t->gg, t->mm, t->aaaa, t->via, t->citta, t->cap);
                }
                break;
            case r_deletecode:
                printf("Inserisci codice da cancellare dalla lista\n");
                scanf("%s", code);
                SortListDel(h, code);
                LISTprint(l, fp, *t);
                break;
            case r_deletedate:
                break;
            case r_print:
                break;
            case r_fine: (continua = 0);
                break;
            case r_err:
            default: printf("comando errato\n");
        }
    }
    LISTprint(l, fp, *t);
    return 0;
}

comandi_e leggiComando (void){
    comandi_e c;
    int len = 0;
    int i = 0;
    char cmd[MAX];
    char tabella[r_fine][MAX] = {
            "video", "file", "ricerca", "cancella_codice", "cancella_date", "stampa"
    };
    printf("[COMANDO]\nvideo, file, ricerca, cancella_codice, cancella_date, stampa\n"
           "Fine per terminare\n");
    scanf("%s", cmd);
    minuscolo(cmd);
    c = r_insertion_a;
    while (c<r_fine && strcmp(cmd,tabella[c])!=0)
        c++;
    return (c);
}

void minuscolo(char parola[MAX]){
    int i, j, len;
    len = strlen(parola);
    for(i = 0; i < len; i++){
        parola[i] = tolower(parola[i]);
    }
}


link SortListIns(link h, Item val) {
    link x, p;
    if (h==NULL || h->next > val.dataInt)
        return newNode(val, h);
    for (x=h->next, p=h; x!=NULL && val.dataInt < x->val.dataInt;
         p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}

link newNode(Item val, link next) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

Item LISTsearch(link l, char *code){
    link x;
    for(x = l; x != NULL && strcmp(code, x->val.codice); x = x->next);
    if(x != NULL)
        return x->val;
    return ITEMnull();
}

Item ITEMnull(){
    Item tmp;
    tmp.dataInt = -1;
    return tmp;
}

link SortListDel(link h, char *code) {
    link x, p;
    if (h == NULL)
        return NULL;
    for (x=h, p=NULL; x!=NULL && code != x->val.codice; p=x, x=x->next) {
        if (code == x->val.codice){
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

void LISTprint(link l, FILE *fp, Item t){
    link x;
    for(x = l; x != NULL; x = x->next){
        printf("%s %s %s %02d/%02d/%04d %s %s %d\n", t.codice, t.nome, t.cognome, t.gg, t.mm,
                t.aaaa, t.via, t.citta, t.cap);
    }
}
