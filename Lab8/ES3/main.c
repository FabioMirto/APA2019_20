#include "menu.h"

int main() {
    tabPg_t tabPg;
    tabInv_t tabInv;
    ListIn(&tabPg);
    VectIn(&tabInv);

    selezionaDati(&tabPg, &tabInv, leggiComando());

    return 0;
}