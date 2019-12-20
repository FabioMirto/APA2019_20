#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char gemma;
    int quantita;
} g;

int fZ(g *gem, char *sol, int i);
int fR(g *gem, char *sol, int i);
int fT(g *gem, char *sol, int i);
int fS(g *gem, char *sol, int i);

int main() {
    clock_t start, end;
    double tempo;
    start=clock();
    int i;
    char *sol, *sol1, *sol2, *sol3, val[4];
    int z = 19;
    int r = 14;
    int t = 5;
    int s = 11;
    int TOT = z+r+t+s;

    g gem[4] = {'Z', z, 'R', r, 'T', t, 'S', s, };

    sol = calloc(TOT, sizeof(char));
    fR(gem, sol, 0);
    printf("%s", sol);
    printf("\nTOTALE %lu\n", strlen(sol));

    gem[0].quantita = 19;
    gem[1].quantita = 14;
    gem[2].quantita = 5;
    gem[3].quantita = 11;
    sol1 = calloc(TOT, sizeof(char));
    fZ(gem, sol1, 0);
    printf("%s", sol1);
    printf("\nTOTALE %lu\n", strlen(sol1));

    gem[0].quantita = 19;
    gem[1].quantita = 14;
    gem[2].quantita = 5;
    gem[3].quantita = 11;
    sol2 = calloc(TOT, sizeof(char));
    fT(gem, sol2, 0);
    printf("%s", sol2);
    printf("\nTOTALE %lu\n", strlen(sol2));

    gem[0].quantita = 19;
    gem[1].quantita = 14;
    gem[2].quantita = 5;
    gem[3].quantita = 11;
    sol3 = calloc(TOT, sizeof(char));
    fS(gem, sol3, 0);
    printf("%s", sol3);
    printf("\nTOTALE %lu\n", strlen(sol3));

    end=clock();
    tempo=((double)(end-start))/CLOCKS_PER_SEC;
    printf("TEMPO DI ESECUZIONE IN SECONDI %.2f", tempo);
    return 0;
}

int fZ(g *gem, char *sol, int i){
    if(gem[0].quantita < 0)
        return 0;
    if(gem[0].quantita > 0) {
        sol[i] = gem[0].gemma;
        gem[0].quantita--;
        fZ(gem, sol, i + 1);
    }
    if(gem[1].quantita > 0) {
        sol[i] = gem[1].gemma;
        gem[1].quantita--;
        fR(gem, sol, i + 1);
    }
}

int fR(g *gem, char *sol, int i){
    if(gem[1].quantita < 0)
        return 0;
    if(gem[3].quantita > 0) {
        sol[i] = gem[3].gemma;
        gem[3].quantita--;
        fS(gem, sol, i + 1);
    }
    if(gem[2].quantita > 0) {
        sol[i] = gem[2].gemma;
        gem[2].quantita--;
        fT(gem, sol, i + 1);
    }
}

int fT(g *gem, char *sol, int i){
    if(gem[2].quantita < 0)
        return 0;
    if(gem[0].quantita > 0) {
        sol[i] = gem[0].gemma;
        gem[0].quantita--;
        fZ(gem, sol, i + 1);
    }
    if(gem[1].quantita > 0) {
        sol[i] = gem[1].gemma;
        gem[1].quantita--;
        fR(gem, sol, i + 1);
    }
}

int fS(g *gem, char *sol, int i){
    if(gem[3].quantita < 0)
        return 0;
    if(gem[3].quantita > 0) {
        sol[i] = gem[3].gemma;
        gem[3].quantita--;
        fS(gem, sol, i + 1);
    }
    if(gem[2].quantita > 0) {
        sol[i] = gem[2].gemma;
        gem[2].quantita--;
        fT(gem, sol, i + 1);
    }
}
