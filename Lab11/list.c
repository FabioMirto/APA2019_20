#include "list.h"

struct titolo_s{
    char* titolo;
    data d;
    ora o;
    float valore;
    int numero;
};

struct titoli_s{
    titolo_t titolo;
    struct titoli_s* next;
};

titoli_t SortListIns(titoli_t h, titolo_t val){
    titoli_t x, p;
    if (h==NULL || h->titolo->titolo > val->titolo)
        return newNode(val, h);
    for (x=h->next, p=h;
         x!=NULL && h->titolo->titolo < val->titolo;
         p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}

titoli_t ListHead(titolo_t val, titoli_t h){
    h = newNode(val, h);
    return h;
}

titoli_t newNode(titolo_t val, titoli_t next){
    titoli_t x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->titolo = val;
        x->next = next;
    }
    return x;
}

titoli_t Listin(FILE *fp, titoli_t col){
    fp = fopen("F1.txt", "r");
    titolo_t tmp;
    int lenfile, len, i, j;
    char tit[20];
    tmp = malloc(sizeof(titolo_t));
    fscanf(fp, "%d ", &lenfile);
    for(i = 0; i < lenfile; i++){
        fscanf(fp, "%s %d ", tit, &len);
            for(j = 0; j < len; j++){
                fscanf(fp, "%d/%d/%d %d:%d %f %d ", &tmp[j].d.aaaa, &tmp[j].d.mm, &tmp[j].d.gg, &tmp[j].o.h,
                     &tmp[j].o.m, &tmp[j].valore, &tmp[j].numero);
                    tmp[j].titolo = strdup(tit);
            col = ListHead(&tmp[j], col);
        }
    }
    return col;
}
