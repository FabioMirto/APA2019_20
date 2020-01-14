#include "list.h"

int main() {
    FILE *fp;
    titoli_t col = NULL;
    col = Listin(fp, col);
    free(col);
    return 0;
}
