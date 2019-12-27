#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b);
int ****malloc4d(int z, int r, int t, int s);
int fZ(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);
int fR(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);
int fT(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);
int fS(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s);

int main() {
    clock_t start, end;
    double tempo;
    start=clock();
    int lenZ = 0, lenR = 0, lenT = 0, lenS = 0, lenTOT = 0;
    int ****Z,****R, ****T, ****S;
    int z = 17;
    int r = 20;
    int t = 15;
    int s = 19;

    Z = malloc4d(z, r, t, s);
    R = malloc4d(z, r, t, s);
    T = malloc4d(z, r, t, s);
    S = malloc4d(z, r, t, s);

    lenZ = fZ(Z, R, T, S, z, r, t, s);
    lenR = fR(Z, R, T, S, z, r, t, s);
    lenT = fT(Z, R, T, S, z, r, t, s);
    lenS = fS(Z, R, T, S, z, r, t, s);

    lenTOT = max(lenZ, (max(lenR, max(lenT, lenS))));

    printf("La collana di massima lunghezza è di %d gemme\n", lenTOT);

    end=clock();
    tempo=((double)(end-start))/CLOCKS_PER_SEC;
    printf("TEMPO DI ESECUZIONE IN SECONDI %.2f", tempo);
    return 0;
}

int ****malloc4d(int z, int r, int t, int s){
    int i, j, k, l, ****tmp;

    tmp = (int ****) malloc((z+1)*sizeof(int***));
    for (i=0; i<=z; i++) {
        tmp[i] = (int ***) malloc((r+1)*sizeof(int**));
        for (j=0; j<=r; j++) {
           tmp[i][j] = (int **) malloc((t+1)*sizeof(int*));
            for (k=0; k<=t; k++) {
                tmp[i][j][k] = (int *)calloc((s+1),sizeof(int));
                for(l=0; l<=s; l++){
                    tmp[i][j][k][l] = -1;
                }
            }
        }
    }
    return tmp;}

int fZ(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s) {
    if (z <= 0)
        return 0;
    if (Z[z][r][t][s] != -1)
        return Z[z][r][t][s];
    if(fZ(Z, R, T, S, z - 1, r, t, s) > fR(Z, R, T, S, z - 1, r, t, s))
        return Z[z][r][t][s] = 1 + (fZ(Z, R, T, S, z - 1, r, t, s));
    else
        return Z[z][r][t][s] = 1 + fR(Z, R, T, S, z - 1, r, t, s);
}

int fR(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s){
    if (r <= 0)
        return 0;
    if (R[z][r][t][s] != -1)
        return R[z][r][t][s];

    if(fS(Z, R, T, S, z, r-1, t, s) > fT(Z, R, T, S, z, r-1, t, s))
        return R[z][r][t][s] = 1 + (fS(Z, R, T, S, z, r-1, t, s));
    else
        return R[z][r][t][s] = 1 + fT(Z, R, T, S, z, r-1, t, s);
}

int fT(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s){
    if (t <= 0)
        return 0;
    if (T[z][r][t][s] != -1)
        return T[z][r][t][s];

    if(fZ(Z, R, T, S, z, r, t-1, s) > fR(Z, R, T, S, z, r, t-1, s))
        return T[z][r][t][s] = 1 + (fZ(Z, R, T, S, z, r, t-1, s));
    else
        return T[z][r][t][s] = 1 + fR(Z, R, T, S, z, r, t-1, s);
}

int fS(int ****Z, int ****R, int ****T, int ****S, int z, int r, int t, int s){
    if (s <= 0)
        return 0;
    if (S[z][r][t][s] != -1)
        return S[z][r][t][s];

    if(fS(Z, R, T, S, z, r, t, s-1) > fT(Z, R, T, S, z, r, t, s-1))
        return R[z][r][t][s] = 1 + (fS(Z, R, T, S, z, r, t, s-1));
    else
        return R[z][r][t][s] = 1 + fT(Z, R, T, S, z, r, t, s-1);
}

int max(int a, int b){
    if(a > b)
        return a;
    return b;
}
