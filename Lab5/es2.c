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

    for (i = 0; i < (nr+1+nc+1)/2 +1; i++) {
        printf("%d ", bianco[i]);
    }
    printf("\n");
    for (j = 0; j < (nr+1+nc+1)/2; j++) {
        printf("%d ", nero[j]);
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
    int b = 0, n = 0, somma = 0;
    int i, j;
    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            somma = i*nr + j;
            if(somma % 2 == 0){
                bianco[b] = mat[i][j];
                b++;
                    bianco = (int*) realloc(bianco, b * sizeof(int));
            } else if (somma % 2 != 0){
                nero[n] = mat[i][j];
                n++;
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
