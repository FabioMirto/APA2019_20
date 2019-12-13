#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pg.h"


void VectIn(tabInv_t *tabInv){
    int i;
    char nome[MAX+1], tipo[MAX+1];
    FILE *fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &tabInv->nInv);
    tabInv->vettInv = (inv_t *) calloc(tabInv->nInv, sizeof(inv_t));
    for(i = 0; i < tabInv->nInv; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", nome,
               tipo, &tabInv->vettInv[i].stat.hp,
               &tabInv->vettInv[i].stat.mp, &tabInv->vettInv[i].stat.atk,
               &tabInv->vettInv[i].stat.def, &tabInv->vettInv[i].stat.mag,
               &tabInv->vettInv[i].stat.spr);
        tabInv->vettInv[i].nome = strdup(nome);
        tabInv->vettInv[i].tipo = strdup(tipo);
    }
    fclose(fp);
}

void printInv(tabInv_t *tabInv, char *nome){
    int i;
    printf("Digita il nome di un equipaggiamento per stamparlo\n");
    scanf("%s", nome);
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
    printf("Ricerca di equipaggiamento per nome\n");
    scanf("%s", nome);
    for (i = 0; i < tabInv->nInv; ++i) {
        if(strcmp(tabInv->vettInv[i].nome, nome) == 0)
            printf("Equipaggiamento presente nell'inventario\n");
    }
}