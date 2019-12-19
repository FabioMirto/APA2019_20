#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char car;
    int value;
} g;

int check(char car, int i, char *sol);
int solution(int pos, g gem[], char *sol, int k, int count, char *val, int TOT);

int main() {
    clock_t start, end;
    double tempo;
    start=clock();
    int i;
    char *sol, val[4];
    int z = 12;
    int s = 20;
    int r = 17;
    int t = 20;
    int TOT = s+z+r+t;

    g gem[4] = {'Z', z, 'S', s, 'R', r, 'T', t};

    sol = calloc(TOT, sizeof(char));

    for (i = 1; i <= TOT; i++) {
        if(solution(0, gem, sol, i, 0, val, 4))
            printf("%s", sol);
        printf("\n");
    }
    printf("\nTOTALE %lu\n", strlen(sol));
    end=clock();
    tempo=((double)(end-start))/CLOCKS_PER_SEC;
    printf("TEMPO DI ESECUZIONE IN SECONDI %.2f", tempo);
    return 0;
}

int solution(int pos, g gem[], char *sol, int k, int count, char *val, int TOT) {
    int i, flag = 0;
    if (pos >= k) {
        return 1;
    }
    for (i = 0; i < TOT; i++) {
        if(pos == 0){
            gem[i].value--;
            sol[pos] = gem[i].car;
            count = solution(pos + 1, gem, sol, k, count, val, TOT);
            gem[i].value++;
        }
        if(gem[i].value > 0 && check(gem[i].car, pos - 1, sol)){
            gem[i].value--;
            sol[pos] = gem[i].car;
            if(solution(pos + 1, gem, sol, k, count, val, TOT))
                flag = 1;
            gem[i].value++;
            if(flag)
                return 1;
        }
    }
    return 1;
}

int check(char car, int i, char *sol){
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
