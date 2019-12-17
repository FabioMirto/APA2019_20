#include "pgList.h"
#include "equipArray.h"

struct pgList_s{
    pg_t pg;
    struct pgList_s *next;
};

pgList_t pgList_init() {
    pgList_t p = malloc(sizeof(*p));
    return p;
}

void pgList_free(pgList_t pgList){
        free(pgList->pg.equip);
        free(pgList->next);
    free(pgList);
}

pgList_t pgList_read(FILE *fp, pgList_t pgList){
    fp = fopen("pg.txt", "r");
    pg_t tmp;
    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", tmp.cod, tmp.nome, tmp.classe,
                 &tmp.b_stat.hp, &tmp.b_stat.mp, &tmp.b_stat.atk, &tmp.b_stat.def,
                 &tmp.b_stat.mag, &tmp.b_stat.spr) != EOF){
        pgList = listInsHead(pgList, tmp);
        pgList->pg.equip = malloc(sizeof(equipArray_t));
    }
    return pgList;
}

pgList_t newNode(pg_t val, pgList_t next) {
    pgList_t x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->pg = val;
        x->next = next;
    }
    return x;
}

pgList_t listInsHead (pgList_t h, pg_t val) {
    h = newNode(val,h);
    return h;
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    pgList_t x;
    for(x = pgList; x->next != NULL; x = x->next)
            pg_print(fp, &x->pg, invArray);
}

void pgList_insert(pgList_t pgList, pg_t pg){
    FILE *fp;
    invArray_t invArray;
    printf("Per aggiungere un nuovo personaggio inserire\n"
           "<codice> <nome> <classe> "
           "<hp> <mp> <atk> <def> <mag> <spr>\n"
           "Il codice deve essere nella forma PGXXXX dove X rappresenta"
           "una cifra nell'intervallo 0-9\n"
           "Il nome e la classe sono rappresentati privi di spazi (max 50 char)\n"
           "Tutti i campi sono separati da uno o più spazi\n");
    scanf("%s %s %s %d %d %d %d %d %d", pg.cod, pg.nome, pg.classe,
          &pg.b_stat.hp, &pg.b_stat.mp, &pg.b_stat.atk, &pg.b_stat.def,
          &pg.b_stat.mag, &pg.b_stat.spr);
    pgList = listInsHead(pgList, pg);
    printf("Personaggio aggiunto nella lista\n");
    pgList->pg.equip = malloc(sizeof(equipArray_t));
    pgList_print(fp, pgList, invArray);
}

pgList_t pgList_remove(pgList_t pgList, char* cod){
        pgList_t x, p;
        printf("Digita un codice per eliminare il personaggio relativo\ndalla lista\n");
        scanf("%s", cod);
        if (pgList == NULL)
            return NULL;
        for (x=pgList, p=NULL; x!=NULL; p=x, x=x->next) {
            if (strcmp(x->pg.cod, cod) == 0) {
                if (x==pgList)
                    pgList = x->next;
                else
                    p->next = x->next;
                free(x);
                break;
            }
        }
        return pgList;
}

pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    pgList_t x;
    for(x = pgList; x != NULL; x = x->next){
        if(strcmp(cod, x->pg.cod) == 0)
            return (pg_t*) &x->pg;
    }
}