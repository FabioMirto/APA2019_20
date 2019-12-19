#include "inv.h"

void stat_read(FILE *fp, stat_t *statp){
    fp = fopen("inventario.txt", "r");
    int len, i;
    char trash[LEN];
    fscanf(fp, "%d", &len);
    inv_t *inv = calloc(len, sizeof(inv_t));
        for(i = 0; i < len; i++){
            fscanf(fp, "%s %s %d %d %d %d %d %d", trash, trash,
                    &statp[i].hp,&statp[i].mp,&statp[i].atk,&statp[i].def,&statp[i].mag,&statp[i].spr);
        }
}

void stat_print_pg(FILE *fp, stat_t *statp, int soglia) {
    if(statp->hp < 0)
        printf("1 ");
    else
        printf("%d ", statp->hp);

    if(statp->mp < 0)
        printf("1 ");
    else
        printf("%d ", statp->mp);

    if(statp->atk < 0)
        printf("1 ");
    else
        printf("%d ", statp->atk);

    if(statp->def < 0)
        printf("1 ");
    else
        printf("%d ", statp->def);

    if(statp->mag < 0)
        printf("1 ");
    else
        printf("%d ", statp->mag);

    if(statp->spr < 0)
        printf("1 ");
    else
        printf("%d\n", statp->spr);
}

void stat_print(FILE *fp, stat_t *statp, int soglia){
    printf("%d %d %d %d %d %d\n", statp->hp, statp->mp, statp->atk, statp->def, statp->mag, statp->spr);
}

void inv_read(FILE *fp, inv_t *invp){
    int i, len;
    char nome[LEN], tipo[LEN];
    fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    for(i = 0; i < len; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", nome, tipo,
               &invp[i].stat.hp, &invp[i].stat.mp, &invp[i].stat.atk,
               &invp[i].stat.def, &invp[i].stat.mag, &invp[i].stat.spr);
        invp[i].nome = strdup(nome);
        invp[i].tipo = strdup(tipo);
    }
}

void inv_print(FILE *fp, inv_t *invp, int i) {
    printf("[%d] %s  %s ", i, invp->nome, invp->tipo);
    stat_print(fp, &invp->stat, 1);
}

stat_t inv_getStat(inv_t *invp, int k){
    int i, len;
    FILE *fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    for(i = 0; i < len; i++) {
        if(k == i){
            return invp->stat;
        }
    }
}