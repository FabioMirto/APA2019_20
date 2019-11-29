#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char gemma;
    int quantita;
    int val;
} g;

typedef struct {
    int n;
} v;

int check(char car, int i, char *sol, int count, int max_rip);
int princ_molt(int pos, g gem[], char *sol, int k, int count, int val, int TOT, v va[], int max_rip);

int main() {
    clock_t start, end;
    double tempo;
    start=clock();
    v va[4] = {0,0,0,0};
    int count = 0, i, max_rip = 3, val = 0;
    char *sol;
    g gem[4] = {'Z', 8, 6, 'S', 5, 8, 'R', 1, 6, 'T', 10, 20};
    int TOT = 8+5+1+10;

    sol = calloc(TOT, sizeof(char));

    for (i = 1; i <= TOT; i++) {
        if(princ_molt(0, gem, sol, i, 0, val, 4, va, max_rip))
            printf("%s", sol);
        printf("\n");
    }
    printf("\nTOTALE %lu\nTOTALE VALORE %d\n", strlen(sol),
           va[0].n*gem[0].val + va[1].n*gem[1].val + va[2].n*gem[2].val + va[3].n*gem[3].val );
    end=clock();
    tempo=((double)(end-start))/CLOCKS_PER_SEC;
    printf("TEMPO DI ESECUZIONE IN SECONDI %.2f", tempo);
    return 0;
}

int princ_molt(int pos, g gem[], char *sol, int k, int count, int val, int TOT, v va[], int max_rip) {
    int i, flag = 0;
    if (pos >= k) {
            //val =va[0].n*gem[0].val + va[1].n*gem[1].val + va[2].n*gem[2].val + va[3].n*gem[3].val;

        return 1;
    }
    for (i = 0; i < TOT; i++) {
        if(pos == 0){
            if(gem[i].gemma == 'Z'){
                va[i].n += 1;
            } gem[i].quantita--;
            sol[pos] = gem[i].gemma;
            count++;
            princ_molt(pos + 1, gem, sol, k, count, val, TOT, va, max_rip);
            gem[i].quantita++;
        }
        if(gem[i].quantita > 0 && check(gem[i].gemma, pos - 1, sol, count, max_rip)){
            if(gem[i].gemma == 'Z'){
                va[i].n += 1;
            } gem[i].quantita--;
            sol[pos] = gem[i].gemma;
            count++;
            if(princ_molt(pos + 1, gem, sol, k, count, val, TOT, va, max_rip))
                flag = 1;
            gem[i].quantita++;
            if(flag)
                return 1;
        }
        count = 0;count++;
    }
    return 1;
}

int check(char car, int i, char *sol, int count, int max_rip){
    if(count > max_rip)
        return 0;
    return 1;
        if(n_z > n_s)
            return 0;
        return 1;
    if(sol[i] == 'Z' || sol[i] == 'T'){
        if(car == 'Z' || car == 'R')
            return 1;
        return 0;
    } else if(sol[i] == 'S' || sol[i] == 'R'){
        if(car ==  'S' || car == 'T')
            return 1;
        return 0;
        }
    return 0;
}
