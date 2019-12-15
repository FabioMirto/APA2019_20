#include "invArray.h"
#include "inv.h"

struct invArray_s{
    char nome[LEN];
    char tipo[LEN];
    stat_t stat;
};

invArray_t invArray_init(){
    int i, len, j;
    FILE *fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    invArray_t invArray = (invArray_t) calloc(len, sizeof(struct invArray_s));
        return invArray;
}

void invArray_free(invArray_t invArray){
    free(invArray);
}

void invArray_read(FILE *fp, invArray_t invArray){
    int i, len, j;
    fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    //invArray = invArray_init();
    for(i = 0; i < len; i++){
        fscanf(fp, "%s %s %d %d %d %d %d %d", invArray[i].nome, invArray[i].tipo,
               &invArray[i].stat.hp, &invArray[i].stat.mp, &invArray[i].stat.atk,
               &invArray[i].stat.def, &invArray[i].stat.mag, &invArray[i].stat.spr);
    }

}

void invArray_print(FILE *fp, invArray_t invArray){
    int i, len;
    fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    for(i = 0; i < len; i++){
        printf("[%d] %s %s %d %d %d %d %d %d\n", i, invArray[i].nome, invArray[i].tipo,
               invArray[i].stat.hp, invArray[i].stat.mp, invArray[i].stat.atk,
               invArray[i].stat.def, invArray[i].stat.mag, invArray[i].stat.spr);
    }
}

void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    int i, len;
    fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    printf("Inserire l'indice di un oggetto per stamparlo\n");
    scanf("%d", &index);
    for(i = 0; i < len; i++){
        if(index == i)
        printf("[%d] %s %s %d %d %d %d %d %d\n", i, invArray[i].nome, invArray[i].tipo,
               invArray[i].stat.hp, invArray[i].stat.mp, invArray[i].stat.atk,
               invArray[i].stat.def, invArray[i].stat.mag, invArray[i].stat.spr);
    }
}

inv_t *invArray_getByIndex(invArray_t invArray, int index){
    int i, len;
    FILE *fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    printf("Inserire l'indice di un oggetto per ritornare il puntatore\n");
    scanf("%d", &index);
    for(i = 0; i < len; i++){
        if(index == i)
            return (inv_t *) &invArray[i];
    }
}

int invArray_searchByName(invArray_t invArray, char *name){
    int i, len;
    inv_t *inv;
    FILE *fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    if(name == NULL) {
        printf("Inserire il nome di un oggetto per ritornare l'indice\n");
        scanf("%s", name);
    }
    for(i = 0; i < len; i++){
        if(strcmp(name, invArray[i].nome) == 0)
            return i;
    }
}