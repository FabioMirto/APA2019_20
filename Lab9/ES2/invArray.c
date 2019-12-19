#include "invArray.h"
#include "equipArray.h"
#include "pg.h"

struct invArray_s {
    inv_t *vettInv;
    int nInv;
    int maxInv;
};

invArray_t invArray_init() {
    invArray_t invArray = malloc(sizeof(*invArray));
    invArray->maxInv = 0;
    invArray->nInv = 0;
    return invArray;
}

void invArray_free(invArray_t invArray){
    free(invArray);
}

invArray_t invArray_read(FILE *fp, invArray_t invArray) {
    int i = 0;
    char nome[LEN], tipo[LEN];
    fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &invArray->nInv);
    invArray->vettInv = malloc(invArray->nInv * sizeof(inv_t));
    while (fscanf(fp, "%s %s %d %d %d %d %d %d", nome, tipo,
                  &invArray->vettInv[i].stat.hp, &invArray->vettInv[i].stat.mp, &invArray->vettInv[i].stat.atk,
                  &invArray->vettInv[i].stat.def, &invArray->vettInv[i].stat.mag, &invArray->vettInv[i].stat.spr) != EOF){
        invArray->vettInv[i].nome = strdup(nome);
        invArray->vettInv[i].tipo = strdup(tipo);
        i++;
    }

    return invArray;
}

void invArray_print(FILE *fp, invArray_t invArray){
    int i, len;
    for(i = 0; i < invArray->nInv; i++){
        printf("[%d] %s %s %d %d %d %d %d %d\n", i, invArray->vettInv[i].nome, invArray->vettInv[i].tipo,
               invArray->vettInv[i].stat.hp, invArray->vettInv[i].stat.mp, invArray->vettInv[i].stat.atk,
               invArray->vettInv[i].stat.def, invArray->vettInv[i].stat.mag, invArray->vettInv[i].stat.spr);
    }
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index, int i) {
    inv_print(fp, &invArray->vettInv[index], i);
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    int i, len;
    if(invArray->vettInv == NULL)
        invArray->vettInv = malloc(sizeof(inv_t));
    for(i = 0; i < invArray->nInv; i++){
        if(index == i)
            return &invArray->vettInv[i];
    }
}

int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    for(i = 0; i < invArray->nInv; i++){
        if(strcmp(name, invArray->vettInv[i].nome) == 0)
            return i;
    }
}