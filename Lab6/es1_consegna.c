#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int u;
    int v;
} ve;

int powerset_r(int pos, int *val, int *sol, int k, int start, int count, int E, ve *vertex);

int main(void) {
    int i, *sol, *vertici;
    int N, E; //E numero di archi, N numero di vertici
    ve *vertex;
    FILE *fp = fopen("grafo.txt", "r");

    fscanf(fp, "%d %d", &N, &E);

    vertex = calloc(E, sizeof(ve));
    vertici = calloc(N, sizeof(ve));
    sol = malloc(N* sizeof(int));

    for (i = 0; i < N; i++) {
        fscanf(fp, "%d %d", &vertex[i].u, &vertex[i].v);
    }

    for(i = 0; i < N; i++){
        vertici[i] = i;
    }
    
    printf("Il vertex cover per un grafo di %d archi e %d vertici e'\n", E, N);
    powerset_r(0, vertici, sol, N, 0, 0, E, vertex);
    
    free(vertex);
    free(vertici);
    free(sol);

    return 0;
}

int powerset_r(int pos, int *val, int *sol, int k, int start, int count, int E, ve *vertex) {
    int i, j, flag1, flag2;//flag2 controlla se la soluzione, alla fine del ciclo è vera
    if (start >= k) { //flag1 controlla il valore di sol i-esimo può essere soluzione
        flag2 = 1;
        for (j = 0; j < E && flag2 == 1; j++) {
                flag1 = 0;
            for (i = 0; i < pos && flag1 == 0; i++) {
                if (sol[i] == vertex[j].u || sol[i] == vertex[j].v)
                    flag1 = 1;
            }
            if (flag1 == 0)
                flag2 = 0;
        }
        if (flag2) {
            for (i = 0; i < pos; i++)
                printf("%d ", sol[i]);
            printf("\n");
        }
        return count + 1;
    }
    for (i = start; i < k; i++) { 
        sol[pos] = val[i];
        count = powerset_r(pos + 1, val, sol, k, i + 1, count, E, vertex);
    }
    count = powerset_r(pos, val, sol, k, k, count, E, vertex);
    return count;
}
