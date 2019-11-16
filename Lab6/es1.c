#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int u;
    int v;
} ve;


void powerset_disp_rip(int pos, ve *vertex, int *sol, int n);
void let(int *sol, int len, ve *vertex, int N);


int main(void) {
    int i, n, cnt = 0, *val, *sol;
    int N, E;
    ve *vertex;
    int *vertici;
    FILE *fp = fopen("vertex_cover.txt", "r");

    fscanf(fp, "%d %d", &N, &E);

    vertex = calloc(E, sizeof(ve));
    vertici = calloc(N, sizeof(ve));


    for (i = 0; i < N; i++) {
        fscanf(fp, "%d %d", &vertex[i].u, &vertex[i].v);
    }

    for(i = 0; i < N; i++){
        vertici[i] = i;
    }

    printf("The powerset of set {");
    for(i =0; i < N; i++)
        printf(" %d %d ", vertex[i].u, vertex[i].v);
    printf("} is \n");



    powerset_disp_rip(0, vertex, sol, N);

    free(vertex);

    return 0;
}
void powerset_disp_rip(int pos, ve *vertex, int *sol, int n) {
    int i, flag = 1, cnt = 0;

    if (pos >= n) {
        let(sol, n, vertex, n);
        return;

    }
    sol[pos] = 0;
    powerset_disp_rip(pos+1, vertex, sol, n);
    sol[pos] = 1;
    powerset_disp_rip(pos+1, vertex, sol, n);

}

void let(int *sol, int len, ve *vertex, int N) {
    int i, flag = 0;

    for (i = 0; i < N; i++) {
        if (sol[vertex[i].u] != 0 && sol[vertex[i].v] != 0)
            flag = 1;
    }
    if (flag) {
        for (int j = 0; j < len; ++j) {
            if (sol[j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}
