#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char **scelte;
    int num_scelte;
} Livello;

int princ_molt(int pos, Livello *val, char **sol, int k, int count);

int main() {
    int i, j, k, total;
    char *sol;
    Livello *valor;
    FILE *fp = fopen("brani.txt", "r");

    fscanf(fp, "%d", &k);
    valor = malloc(k * sizeof(Livello));
    for(i = 0; i < k; i++){
            fscanf(fp, "%d", &valor[i].num_scelte);
        valor[i].scelte = malloc(valor[i].num_scelte * sizeof(char*));
        for (j = 0; j < valor[i].num_scelte; j++) {
            valor[i].scelte[j] = malloc(255 * sizeof(char*));
            fscanf(fp, "%s", valor[i].scelte[j]);
        }
    }

    sol = malloc(k * sizeof(char));

    printf("L'applicazione del principio di moltiplicazione da' le seguenti soluzioni: \n");
    total = princ_molt(0, valor, sol, k, 0);
    printf("e in totale sono %d \n", total);
    free(sol);
    for (i = 0; i < k; i++)
        free(valor[i].scelte);
    free(valor);

    return 0;
}

int princ_molt(int pos, Livello *val, char **sol, int k, int count) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++) {
            printf("%s\n", sol[i]);
        }
        printf("\n");
        return count+1;
    }
    for (i = 0; i < val[pos].num_scelte; i++) {
        sol[pos] =  val[pos].scelte[i];
        count = princ_molt(pos+1, val,  sol, k, count);
    }
    return count;
}
