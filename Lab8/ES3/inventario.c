#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "inventario.h"


void VectIn(tabInv_t *tabInv){
    int i;
    FILE *fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &tabInv->nInv);
    tabInv->vettInv = calloc(tabInv->nInv, sizeof(tabInv_t));
    for(i = 0; i < tabInv->nInv; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", tabInv->vettInv[i].nome,
               tabInv->vettInv[i].tipo, &tabInv->vettInv[i].stat.hp,
               &tabInv->vettInv[i].stat.mp, &tabInv->vettInv[i].stat.atk,
               &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag,
               &tabInv->vettInv[i].stat.spr);
    }
    fclose(fp);
}

void printInv(tabInv_t *tabInv, char *nome){
    int i;
    for (i = 0; i < tabInv->nInv; ++i) {
        if(strcmp(tabInv->vettInv[i].nome, nome) == 0)
            printf("%s %s %d %d %d %d %d %d\n", tabInv->vettInv[i].nome,
                          tabInv->vettInv[i].tipo, tabInv->vettInv[i].stat.hp,
                          tabInv->vettInv[i].stat.mp, tabInv->vettInv[i].stat.atk,
                          tabInv->vettInv[i].stat.def, tabInv->vettInv[i].stat.mag,
                          tabInv->vettInv[i].stat.spr);
    }
}

void printIn(tabInv_t *tabInv){
    int i;
    for (i = 0; i < tabInv->nInv; i++) {
            printf("%s %s %d %d %d %d %d %d\n", tabInv->vettInv[i].nome,
                   tabInv->vettInv[i].tipo, tabInv->vettInv[i].stat.hp,
                   tabInv->vettInv[i].stat.mp, tabInv->vettInv[i].stat.atk,
                   tabInv->vettInv[i].stat.def, tabInv->vettInv[i].stat.mag,
                   tabInv->vettInv[i].stat.spr);
    }
}

void searchInv(tabInv_t *tabInv, char *nome){
    int i;
    for (i = 0; i < tabInv->nInv; ++i) {
        if(strcmp(tabInv->vettInv[i].nome, nome) == 0)
            printf("Equipaggiamento presente nell'inventario\n");
    }
}