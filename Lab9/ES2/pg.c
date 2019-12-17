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

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
    printf("%s %s %s ", pgp->cod, pgp->nome, pgp->classe);
    stat_print(fp, &pgp->b_stat, 1);
    if(pgp->equip != NULL)
        equipArray_print(fp, pgp->equip, invArray);
}

void pg_clean(pg_t *pgp, int len){
    int i;
    for(i = 0; i < len; i++){
        free(pgp[i].equip);
    }
    free(pgp);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    int index, cmd;
    char name[LEN];
    equipArray_t equipArray;
    FILE *fp;
    printf("Se vuoi aggiungere un equipaggiamento premi 1\naltrimenti premi 0\n");
    scanf("%d", &cmd);
    if(cmd) {
        invArray_print(fp, invArray);
        printf("Inserire il nome di un oggetto per aggiungerlo all'equipaggiamento\n");
        scanf("%s", name);
    } else {
        if(equipArray_print(fp, pgp->equip, invArray) != 0) {
            printf("Inserire il codice di un oggetto per rimuoverlo dall'equipaggiamento\n");
            scanf("%d", &index);
        }
    }
    equipArray_update(pgp->equip, invArray, index, cmd, name);
    if(pgp->equip != NULL)
        pgp->eq_stat = (inv_getStat(invArray_getByIndex(invArray, index), index));
    if(pgp->eq_stat.hp < 0){
        pgp->eq_stat.hp = 1;
    }
    if(pgp->eq_stat.mp < 0){
        pgp->eq_stat.mp = 1;
    }
    if(pgp->eq_stat.atk < 0){
        pgp->eq_stat.atk = 1;
    }
    if(pgp->eq_stat.def < 0){
        pgp->eq_stat.def = 1;
    }
    if(pgp->eq_stat.mag < 0){
        pgp->eq_stat.mag = 1;
    }
    if(pgp->eq_stat.spr < 0){
        pgp->eq_stat.spr = 1;
    }
}