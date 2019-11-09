#include <stdio.h>
#include <string.h>

#define MAX 50
#define NOME_FILE "mappa.txt"

typedef struct {
    int x, y, b, h, Area;
} val;

int trovaBase(int mappa[MAX][MAX], int i, int j, int c);
int trovaAltezza(int mappa[MAX][MAX], int i, int j, int r);

int main() {
    int mappa[MAX][MAX];
    int r, c, i, j,  base, altezza, maxbase = 0, maxaltezza = 0, area = 0, maxarea = 0;
    val valori[10];
    FILE *fp;
    fp = fopen(NOME_FILE, "r");
    if(fp == NULL){
        printf("ERRORE NELL'APERTURA FILE");
        return -1;
    }

    fscanf(fp, "%d %d", &r, &c);

    for(i = 0; i < r; i++){
        for(j = 0; j < c; j++){
            fscanf(fp, "%d", &mappa[i][j]);

        }
    }
    for(i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            if (mappa[i][j] != 0) {
                base = trovaBase(mappa, i, j, c);
                altezza = trovaAltezza(mappa, i, j, r);
                area = base * altezza;
            } if(base > maxbase){
                maxbase = base;
                valori[0].x = i + 1;
                valori[0].y = j + 1;
                valori[0].b = maxbase;
                valori[0].h = altezza;
                valori[0].Area = area;
            } if(altezza>maxaltezza){
                maxaltezza = altezza;
                valori[1].x = i + 1;
                valori[1].y = j + 1;
                valori[1].b = base;
                valori[1].h = maxaltezza;
                valori[1].Area = area;
            } if(area>maxarea){
                maxarea = area;
                valori[2].x = i + 1;
                valori[2].y = j + 1;
                valori[2].b = base;
                valori[2].h = altezza;
                valori[2].Area = maxarea;
            }
        }
    }
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", valori[0].x,valori[0].y, valori[0].b, valori[0].h, valori[0].Area);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", valori[1].x,valori[1].y, valori[1].b, valori[1].h, valori[1].Area);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", valori[2].x,valori[2].y, valori[2].b, valori[2].h, valori[2].Area);

    fclose(fp);
    return 0;
}


int trovaBase(int mappa[MAX][MAX], int i, int j, int c) {
    int k = 1, base = 1;
    c = c - 1;
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
int trovaAltezza(int mappa[MAX][MAX], int i, int j, int r) {
    int k = 1 , altezza = 1;
    r = r - 1;
    while(k < r){
        if (mappa[i+k][j] != 0) {
            altezza++;
        } else{
            break;
        }
        k++;
    }

    return altezza;
}
