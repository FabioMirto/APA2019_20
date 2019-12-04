#define MAX 50

typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct {
    char nome[MAX];
    char tipo[MAX];
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
    char codice[6+1];
    char personaggio[MAX + 1];
    char classe[MAX + 1];
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