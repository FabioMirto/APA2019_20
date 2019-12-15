#include "equipArray.h"

struct equipArray_s{
    int inUso;
    invArray_t inv;
};

equipArray_t equipArray_init(){
    equipArray_t equipArray = (equipArray_t) calloc(EQUIP_SLOT, sizeof(struct equipArray_s));
    equipArray->inv = calloc(EQUIP_SLOT, sizeof(invArray_t));
    return equipArray;
}

void equipArray_free(equipArray_t equipArray){
    free(equipArray);
}

int equipArray_inUse(equipArray_t equipArray){
    int i;
    for(i = 0; i < EQUIP_SLOT; i++){
       if(equipArray[i].inUso == 0)
           return i;
    }
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i, len;
    fp = fopen("inventario.txt", "r");
    fscanf(fp, "%d", &len);
    printf("Inventario\n");
    invArray_print(fp, invArray);
}

equipArray_t equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int i, len, index;
    equipArray = equipArray_init();
    if(equipArray->inUso == 8){
        printf("Spazio esaurito\n");
        return NULL;
    }
    equipArray->inv = (invArray_t) invArray_getByIndex(invArray, index);
    equipArray->inUso++;
    return equipArray;
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    int i;
    if(equipArray->inUso != 0) {
        for (i = 0; i < EQUIP_SLOT; i++) {
        }
    }
}
