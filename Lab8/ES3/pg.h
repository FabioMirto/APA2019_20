#include "inventario.h"

#define MAX 50

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

void  ListIn(tabPg_t *tabPg);
nodoPg_t newNode(pg_t val, nodoPg_t next);
nodoPg_t listInsHead (nodoPg_t h, pg_t val);
void DelOb(tabPg_t *tabPg, char k[6+1], char ob[MAX+1], tabInv_t *tabInv);
void InsOb(tabPg_t *tabPg, char k[6+1], char ob[MAX+1], tabInv_t *tabInv);
void minuscolo(char parola[MAX]);
nodoPg_t listDelKey(nodoPg_t h, char k[6+1]);
void calStat(tabPg_t *tabPg, char k[6+1]);
void printList(tabPg_t *h, char k[6 + 1]);