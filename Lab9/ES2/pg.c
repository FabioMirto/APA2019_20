#include "invArray.h"
#include "pg.h"

pg_t *pg_init(){
    FILE *fp = fopen("pg.txt", "r");
    int i = 0, n = 1, tra;
    char trash[LEN];
    pg_t *pgp;
    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", trash, trash, trash,
                 &tra, &tra, &tra, &tra,
                 &tra, &tra) == 9){
        i++;
    }
    pgp = malloc(i * sizeof(pg_t));
    equipArray_init();
    return pgp;
}


int pg_read(FILE *fp, pg_t *pgp){
    fp = fopen("pg.txt", "r");
    int i = 0, n = 1;
    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", pgp[i].cod, pgp[i].nome, pgp[i].classe,
                 &pgp[i].b_stat.hp, &pgp[i].b_stat.mp, &pgp[i].b_stat.atk, &pgp[i].b_stat.def,
                 &pgp[i].b_stat.mag, &pgp[i].b_stat.spr) == 9){
        i++;
    }
    return i;
}

void pg_print(FILE *fp, pg_t pgp, invArray_t invArray, int len){
    int i;
        printf("%s %s %s %d %d %d %d %d %d\n", pgp.cod, pgp.nome, pgp.classe,
               pgp.b_stat.hp, pgp.b_stat.mp, pgp.b_stat.atk, pgp.b_stat.def,
               pgp.b_stat.mag, pgp.b_stat.spr);

}

void pg_clean(pg_t *pgp, int len){
    int i;
    for(i = 0; i < len; i++){
        free(pgp[i].equip);
    }
    free(pgp);
}

pg_t *pg_updateEquip(pg_t *pgp, invArray_t invArray){
    pgp = pg_init();
    pgp->equip =  equipArray_update(pgp->equip, invArray);
    return pgp;
}