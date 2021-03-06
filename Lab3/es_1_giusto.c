#include <stdio.h>
#include <ctype.h>

#define MAXR 50
#define NOME_FILE "mappa.txt"
#define true 1
#define false 0

int trovaBase(int mappa[MAXR][MAXR], int i, int j, int c);
int trovaAltezza(int mappa[MAXR][MAXR], int i, int j, int r);
void leggiMatrice(int M[MAXR][MAXR], int * nr, int * nc);
int riconosciRegione(int M[MAXR][MAXR], int nr, int nc, int r, int c,int* b, int* h);

int main() {
    int M[MAXR][MAXR];
    int r, c;
    int nr = 0, nc = 0, b = 0, h = 0;
    FILE *fp;
    fp = fopen(NOME_FILE, "r");
    if(fp == NULL){
        printf("ERRORE NELL'APERTURA FILE");
        return -1;
    }

   leggiMatrice(M, &nr, &nc);
    for(r = 0; r < nr; r++) {
        for (c = 0; c < nc; c++) {
        printf("%d ", M[r][c]);
        }
        printf("\n");
    }
    for(r = 0; r < nr; r++) {
        for (c = 0; c < nc; c++) {
            if(riconosciRegione(M, nr, nc, r, c, &b, &h) == true) {
                if (b * h != 1) {
                    printf("estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", r + 1, c + 1, b, h, b * h);
                } else {
                    break;
                }
            }
        }
    }
    fclose(fp);
    return 0;
}

void leggiMatrice(int M[MAXR][MAXR], int * nr, int * nc){
    FILE *fp;
    int i, j;
    fp = fopen(NOME_FILE, "r");
         fscanf(fp, "%d %d", nr, nc);
    for (i = 0; i < *nr; ++i) {
        for (j = 0; j < *nc; ++j) {
            fscanf(fp, "%d", &M[i][j]);
        }
    }
}

int trovaBase(int mappa[MAXR][MAXR], int i, int j, int c) {
    int k = 1, base = 1;
    c = c -1;
    while(k < c){
        if (mappa[i][j+k] != 0) {
            base++;
        } else{
            break;
        }
      k++;
    }
    return base;
}

int trovaAltezza(int mappa[MAXR][MAXR], int i, int j, int r) {
    int k = 1 , altezza = 1;
    r = r -1;
    while(k < r){
        if (mappa[i+k][j] != 0) {
            altezza++;
        } else {
            break;
        }
         k++;
    }
    return altezza;
}

int riconosciRegione(int M[MAXR][MAXR], int nr, int nc, int r, int c,int* b, int* h) {
    while(M[r][c] != 0){
        if((r == 0 && c == 0) ||
        ((r != 0 && c != 0) && (M[r - 1][c] == 0 && M[r][c - 1] == 0)) ||
        ((r == 0) &&  (M[r][c-1] == 0)) ||
        ((c == 0) &&  (M[r-1][c] == 0))){
            *b = trovaBase(M, r, c, nc);
            *h = trovaAltezza(M, r, c, nr);
                return true;
             } else {
                return false;
        }
    }
}
