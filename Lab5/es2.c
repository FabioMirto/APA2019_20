#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(FILE *fp, int nr, int nc);
void malloc2dP(int ***mp, int nr, int nc, FILE *fp);
void separa(int **mat, int nr, int nc, int *bianco, int *nero);
void free2d(int **m, int nr);

int main() {
    int **m, i, j, nr, nc;
    int *bianco, *nero;
    FILE *fp = fopen("mat.txt", "r");
    fscanf(fp, "%d %d", &nr, &nc);
    printf("%d %d\n", nr, nc);
   // m = malloc2dR(fp, nr, nc);
    malloc2dP(&m, nr, nc, fp);

    for(i = 0; i < nr; i++){
        for (j = 0; j < nc; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    bianco = calloc(1, sizeof(int));
    nero = calloc(1, sizeof(int));

    separa(m, nr, nc, bianco, nero);
    if((nr*nc) % 2 == 0) {
        printf("Caselle bianche\n");
        for (i = 0; i < ((nr * nc) / 2); i++) {
            printf("%d ", bianco[i]);
        }
        printf("\n");
        printf("Caselle nere\n");
        for (j = 0; j < (nr * nc) / 2; j++) {
            printf("%d ", nero[j]);
        }
    } else {
        printf("Caselle bianche\n");
        for (i = 0; i < ((nr * nc) / 2 + 1); i++) {
            printf("%d ", bianco[i]);
        }
        printf("\n");
        printf("Caselle nere\n");
        for (j = 0; j < (nr * nc) / 2; j++) {
            printf("%d ", nero[j]);
        }
    }
    
    free(bianco);
    free(nero);
    free2d(m, nr);

    return 0;
}
void malloc2dP(int ***mp, int nr, int nc, FILE *fp) {
    int i, j;
    int **m;
    m = malloc(nr*sizeof(int*));
    for (i=0; i<nr; i++) {
        m[i] = malloc(nc * sizeof(int));
    }
    for(i = 0; i < nr; i++){
        for (j = 0; j < nc; j++) {
            fscanf(fp, "%d", &m[i][j]);
        }
    }
    *mp = m;
}


int **malloc2dR(FILE *fp, int nr, int nc){
    int i;
    int **m;
    m = malloc(nr * sizeof(int*));
    for(i = 0; i < nr; i++){
        m[i] = malloc(nc * sizeof(int));
    }
    for(i = 0; i < nr; i++){
        for (int j = 0; j < nc; j++) {
            fscanf(fp, "%d", &m[i][j]);
        }
    }
    return m;
}

void separa(int **mat, int nr, int nc, int *bianco, int *nero){
    int b = 0, n = 0, somma = 0, countb = 0, countn = 0;
    int i, j;
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            somma = i + j;
            if(somma % 2 == 0){
                bianco[countb] = mat[i][j];
                countb++;
                if(countb == b){
                    b = b * 2;
                }
                    bianco = (int*) realloc(bianco, b * sizeof(int));
            } else if (somma % 2 != 0){
                nero[countn] = mat[i][j];
                countn++;
                if(countn == n){
                    n = n * 2;
                }
                   nero = (int*) realloc(nero, n * sizeof(int));
            }
        }
    }
}

void free2d(int **m, int nr) {
    int i;
    for (i=0; i<nr; i++) {
        free(m[i]);
    }
    free(m);
}
