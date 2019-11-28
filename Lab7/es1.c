#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char car;
    int value;
} g;

int check(char car, int i, char *sol);
int princ_molt(int pos, g gem[], char *sol, int k, int count, char *val, int TOT);

int main() {
    clock_t start, end;
    double tempo;
    start=clock();
    int count = 0;
    char *sol, val[4];
    int z = 19;
    int s = 5;
    int r = 6;
    int t = 8;
    int TOT = s+z+r+t;

    g gem[4] = {'Z', z, 'S', s, 'R', r, 'T', t};

    sol = calloc(TOT, sizeof(char));

    for (int i = 0; i < TOT; ++i) {
        princ_molt(0, gem, sol, i, 0, val, 4);
    }

    printf("TOTALE %lu\n", strlen(sol));
    end=clock();
    tempo=((double)(end-start))/CLOCKS_PER_SEC;
    printf("TEMPO DI ESECUZIONE IN SECONDI %.2f", tempo);
    return 0;
}

int princ_molt(int pos, g gem[], char *sol, int k, int count, char *val, int TOT) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; ++i) {
                printf("%c", sol[i]);
        }
        return count + 1;
    }
    for (i = 0; i < TOT; i++) {
        if(pos == 0){
            sol[pos] = gem[i].car;
            gem[i].value--;
            count = princ_molt(pos + 1, gem, sol, k, count, val, TOT);
            gem[i].value++;
        }
        if(gem[i].value > 0 && check(gem[i].car, pos - 1, sol) == 1){
            sol[pos] = gem[i].car;
            gem[i].value--;
            count = princ_molt(pos + 1, gem, sol, k, count, val, TOT);
            gem[i].value++;
        }
    }
    return count;
}

int check(char car, int i, char *sol){
            if(sol[i] == 'Z'){
                if(car == 'Z' || car == 'R')
                    return 1;
                return 0;
            } else if(sol[i] == 'S'){
                if(car ==  'S' || car == 'T')
                    return 1;

                return 0;
            } else if(sol[i] == 'R'){
                if(car == 'S' || car == 'T')
                    return 1;

                return 0;
            } else if(sol[i] == 'T'){
                if(car == 'Z' || car == 'R')
                    return 1;
                return 0;
            }
    return 0;
}
