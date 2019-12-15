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

void stat_print(FILE *fp, stat_t *statp, int soglia){
    int i, len;
    fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    for(i = 0; i < len; i++){
        printf("%d %d %d %d %d %d\n", statp[i].hp, statp[i].mp, statp[i].atk,
                statp[i].def, statp[i].mag, statp[i].spr);
    }
}

void inv_read(FILE *fp, inv_t *invp){
    int i, len;
    fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    for(i = 0; i < len; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", invp[i].nome, invp[i].tipo,
               &invp[i].stat.hp, &invp[i].stat.mp, &invp[i].stat.atk,
               &invp[i].stat.def, &invp[i].stat.mag, &invp[i].stat.spr);
    }
}

void inv_print(FILE *fp, inv_t *invp){
    int i, len;
    fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    for(i = 0; i < len; i++){
        printf("%s %s %d %d %d %d %d %d\n", invp[i].nome, invp[i].tipo,
               invp[i].stat.hp, invp[i].stat.mp, invp[i].stat.atk,
               invp[i].stat.def, invp[i].stat.mag, invp[i].stat.spr);
    }
}

stat_t inv_getStat(inv_t *invp){
    int i, len;
    char k[LEN];
    FILE *fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    printf("Digita il nome di un oggetto per stampare le sua statistiche\n");
    scanf("%s", k);
    for(i = 0; i < len; i++) {
        if(strcmp(k, invp[i].nome) == 0){
            return invp[i].stat;
        }
    }
}