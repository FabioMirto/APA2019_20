#include <stdio.h>
#include <stdlib.h>

#define MAX 255

typedef struct {
    char **scelte;
    int num_scelte;
} canz;

int genPlaylist(int pos, canz *val, char **sol, int k, int count);

int main() {
    int i, j, k, total;
    char *sol;
    canz *canzoni;
    FILE *fp = fopen("brani.txt", "r");

    fscanf(fp, "%d", &k);
    canzoni = malloc(k * sizeof(canz));
    for(i = 0; i < k; i++){
            fscanf(fp, "%d", &canzoni[i].num_scelte);
        canzoni[i].scelte = malloc(canzoni[i].num_scelte * sizeof(char*));
        for (j = 0; j < canzoni[i].num_scelte; j++) {
            canzoni[i].scelte[j] = malloc(MAX * sizeof(char *));
            fscanf(fp, "%s", canzoni[i].scelte[j]);
        }
    }

    sol = malloc(k * sizeof(char));

    printf("Tutte le possibile playlist sono: \n");
    total = genPlaylist(0, canzoni, sol, k, 0);
    printf("e in totale sono %d \n", total);
    free(sol);
    for (i = 0; i < k; i++)
        free(canzoni[i].scelte);
    free(canzoni);

    return 0;
}

int genPlaylist(int pos, canz *val, char **sol, int k, int count) {
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
        count = genPlaylist(pos+1, val,  sol, k, count);
    }
    return count;
}
