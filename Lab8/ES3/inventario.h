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

void VectIn(tabInv_t *tabInv);
void printInv(tabInv_t *tabInv, char *nome);
void searchInv(tabInv_t *tabInv, char *nome);
void printIn(tabInv_t *tabInv);