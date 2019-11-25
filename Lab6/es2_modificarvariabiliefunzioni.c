#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

link newNode(Item *val, link next);
void minuscolo(char parola[MAX]);
comandi_e leggiComando (void);
Item *ListSearch(link h, char *code);
void StampaLista(link h);
Item* Elimina2(link *hp, int d1, int d2);
Item* Elimina(link *hp,char codice[]);
void StampaItem(Item* pi);
Item* Valori(FILE *fp);
link Inserimento(link h,Item* val);
link NewNode(link next,Item *val);

int main() {
    link head = NULL;
    struct Item *val;
    comandi_e codiceComando;
    codiceComando = leggiComando();
    char codice[6];
    link x;
    Item *match = NULL, *tmp = val;
    int continua = 1, g1, m1, a1, g2, m2, a2, dataInt1, dataInt2, datatmp;
    FILE *fp1, *fp;
    fp = fopen("item.txt", "r");
    val = (Item*) malloc(sizeof(Item));
    while (continua) {
        switch (codiceComando) {
            case r_inserimentoa:
                head = Inserimento(head, match);
                StampaLista(head);
                codiceComando = leggiComando();
                break;
            case r_inserimentob:
                while(!feof(fp)){
                    match=Valori(fp);
                    head=Inserimento(head,match);
                }
                StampaLista(head);
                codiceComando = leggiComando();
                break;
            case r_ricerca:
                printf("Inserisci codice da cercare");
                scanf("%s", codice);
                match=ListSearch(head,codice);
                if(match!=NULL)
                    StampaItem(match);
                codiceComando = leggiComando();
                break;
            case r_cancella:
                printf("Inserisci codice da eliminare");
                scanf("%s", codice);
                if(ListSearch(head,codice)!=NULL){
                    match=Elimina(&head,codice);
                    StampaItem(match);
                }
                codiceComando = leggiComando();
                break;
            case r_cancelladate:
                printf("inserisci due date nel formato gg/mm/aaaa");
                scanf("%d/%d/%d %d/%d/%d", &g1, &m1, &a1, &g2, &m2, &a2);
                dataInt1 = a1*10000 + m1 *100 + g1;
                dataInt2 = a2*10000 + m2 *100 + g2;
                if(dataInt1 > dataInt2){
                    datatmp = dataInt1;
                    dataInt1 = dataInt2;
                    dataInt2 = datatmp;
                }
                do{
                    match=Elimina2(&head,dataInt1,dataInt2);
                    if(match!=NULL)
                        StampaItem(match);
                }while (match!=NULL);
                codiceComando = leggiComando();
                break;
            case r_stampa:
                printf("LISTA:\n");
                StampaLista(head);
                codiceComando = leggiComando();
                break;
            case r_err:
                break;
            case r_fine:
                continua = 0;
                break;
        }
    }
return 0;
}

comandi_e leggiComando (void){
    comandi_e c;
    char cmd[MAX];
    char tabella[r_fine][MAX] = {
            "inserimento", "file", "ricerca", "cancella", "cancella_date", "stampa"
    };
    printf("[COMANDO]\ninserimento file ricerca cancella cancella_date stampa\n"
           "Fine per terminare\n");
    scanf("%s", cmd);
    minuscolo(cmd);
    c = r_inserimentoa;
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

link newNode(Item *val, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

link SortListIns(link h, Item *val) {
    link x, p;
    int k = val->dataInt;
    if (h==NULL || (h->val->dataInt) < k)
        return newNode(val, h);
    for (x=h->next, p=h;
         x!=NULL && (x->val->dataInt > k);
         p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}

link SortListDelDate(link h, int data1, int data2) {
    link x, p;
    if (h == NULL)
        return NULL;
    for (x=h, p=NULL; x!=NULL && (data1 <= x->val->dataInt) && (x->val->dataInt <= data2); p=x, x=x->next) {
        if((data1 == x->val->dataInt) && (x->val->dataInt == data2)){
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

Item *ListIns(Item *val, int file) {
    Item tmp;
    FILE *fp;
    if (file) {
        fp = fopen("item.txt", "r");
            while (fscanf(fp, "%s %s %s %d/%d/%d %s %s %d\n", val->codice,val->nome, val->cognome,
                          &val->gg, &val->mm, &val->aaaa, val->via,
                          val->citta, &val->cap) != EOF) {
                val->dataInt = val->aaaa * 10000 + val->mm * 100 + val->gg;
            }
        return val;
    } else {
        scanf("%s %s %s %d/%d/%d %s %s %d", tmp.codice, tmp.nome, tmp.cognome, &tmp.gg, &tmp.mm, &tmp.aaaa, tmp.via, tmp.citta, &tmp.cap);
        tmp.dataInt = tmp.aaaa * 10000 + tmp.mm * 100 + tmp.gg;
    return val;
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

link SortListDel(link h, char *codice) {
    link x, p;
    if (h == NULL)
        return NULL;
    for (x=h, p=NULL; x!=NULL && (strcmp(codice, x->val->codice) >= 0); p=x, x=x->next) {
        if((x->val->codice == codice)){
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

void StampaLista(link h){
    link x;
    if(h==NULL)
        fprintf(stderr,"Lista vuota\n");
    for(x=h;x!=NULL;x=x->next){
        fprintf(stdout,"%s %s %s %d/%d/%d %s %s %d\n",x->val->codice,x->val->nome,x->val->cognome,
                x->val->gg, x->val->mm, x->val->aaaa,
                x->val->via,x->val->citta,x->val->cap);
    }
}
Item* Elimina(link *hp,char codice[]){
    link *xp,t;
    Item *val=NULL;
    for(xp=hp;(*xp)!=NULL;xp=&((*xp)->next)){
        if(strcmp((*xp)->val->codice, codice)==0){
            val=(*xp)->val;
            t=(*xp);
            (*xp)=(*xp)->next;
            free(t);
            break;
        }
    }
    return val;
}
Item* Valori(FILE *fp){
    Item *val;
    val=(Item*)malloc(sizeof(Item));
    fscanf(fp, "%s %s %s %d/%d/%d %s %s %d\n",val->codice,val->nome,val->cognome,&val->gg, &val->mm, &val->aaaa, val->via,val->citta,&val->cap);
    val->dataInt = val->gg + val->mm*100 + val->aaaa * 10000;
    return val;
}
Item* Elimina2(link *hp, int d1, int d2){
    link *xp,t;
    Item *val=NULL;
    for(xp=hp;(*xp)!=NULL;xp=&((*xp)->next)){
        if((((*xp)->val->dataInt))<d2 && ((*xp)->val->dataInt)>d1){
            val=(*xp)->val;
            t=(*xp);
            (*xp)=(*xp)->next;
            free(t);
            break;
        }
    }
    return val;
}

void StampaItem(Item* pi){
    if(pi==NULL)
        fprintf(stderr,"Null\n");
    else
        fprintf(stdout,"%s %s %s %d/%d/%d %s %s %d\n",pi->codice,pi->nome,pi->cognome,pi->gg, pi->mm, pi->aaaa, pi->via,pi->citta,pi->cap);
}

link Inserimento(link h,Item* val){
    link x,p;
    if(h==NULL || (h->val->dataInt)>(val->dataInt))
        return NewNode(h,val);
    for(x=h->next,p=h;x!=NULL && (x->val->dataInt)<(val->dataInt);p=x,x=x->next);
    p->next=NewNode(x,val);
    return h;
}

link NewNode(link next,Item *val){
    link x;
    x=(link)malloc(sizeof(*x));
    if(x==NULL)
        fprintf(stderr,"Errore malloc");
    x->next=next;
    x->val=val;
    return x;
}
