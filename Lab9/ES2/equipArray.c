#include "equipArray.h"

struct equipArray_s{
    int inUso;
    int inv[EQUIP_SLOT];
};

equipArray_t equipArray_init(){
    equipArray_t equipArray = malloc(sizeof(equipArray_t));
    for(int i = 0; i < EQUIP_SLOT; i++){
            equipArray->inv[i] = -1;
    }
    equipArray->inUso = 0;
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

int equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray) {
    int i;
    if (equipArray->inUso == 0) {
        return 0;
    }
    printf("Oggetti equipaggiati:\n");
    for (i = 0; i < equipArray->inUso; i++)
        invArray_printByIndex(fp, invArray, equipArray->inv[i], i);
}

equipArray_t equipArray_update(equipArray_t equipArray, invArray_t invArray, int index, int cmd, char *name){
    FILE *fp;
    if(cmd) {
        if (equipArray->inUso == EQUIP_SLOT) {
            printf("Spazio esaurito!\n");
            EXIT_FAILURE;
        } else {
            index = invArray_searchByName(invArray, name);
            if(index != -1) {
                equipArray->inv[equipArray->inUso] = index;
                equipArray->inUso++;
            }
        } return equipArray;
    } else {
        if (equipArray->inUso == 0) {
            printf("Equipaggiamento vuoto!\n");
            EXIT_FAILURE;
        } else {
            equipArray->inv[index] = -1;
            equipArray->inUso--;
    }
            return equipArray;
    }
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    int i;
    if(equipArray->inUso != 0) {
        for (i = 0; i < EQUIP_SLOT; i++) {
        }
    }
}
