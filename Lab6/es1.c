
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int u;
    int v;
} ve;

int powerset_disp_rip(ve *vertex, int pos, int *val, int *sol, int n, int count);
void generateDeT(int pos, int *val, int len, int start, int *sol, ve *edges, int edgesLen);
void validateDeT(int *sol, int len, ve *edges, int edgesLen);

int main(void) {
    int i, n, cnt = 0, *sol;
    int N, E, *val;
    ve *vertex;
    int *vertici;
    FILE *fp = fopen("vertex_cover.txt", "r");

    fscanf(fp, "%d %d", &N, &E);

    vertex = calloc(E, sizeof(ve));
    vertici = calloc(N, sizeof(ve));
    sol = malloc(N* sizeof(int));
    val = malloc(N*sizeof(int));

    for (i = 0; i < N; i++) {
        fscanf(fp, "%d %d", &vertex[i].u, &vertex[i].v);
    }

    for(i = 0; i < N; i++){
        vertici[i] = i;
    }

    generateDeT(0, vertici, N, 0, sol, vertex, N);


    free(vertex);
    free(vertici);

    return 0;
}

void generateDeT(int pos, int *val, int len, int start, int *sol, ve *edges, int edgesLen){
    int i;
    if(start >= len){
        if(pos > 0) validateDeT(sol, pos, edges, edgesLen);
        return;
    }
    for(i = start; i < len; i++){
        sol[pos] = val[i];
        generateDeT(pos+1, val, len, i+1, sol, edges, edgesLen);
    }
    generateDeT(pos, val, len, len, sol, edges, edgesLen);
}


void validateDeT(int *sol, int len, ve *edges, int edgesLen){
    int i, j;
    int mark[edgesLen];
    int flag = 1;
    for(i = 0; i < edgesLen; i++){
        mark[i] = 0;
    }
    for(i = 0; i < len; i++){
        for(j = 0; j < edgesLen; j++){
            if(sol[i] == edges[j].u || sol[i] == edges[j].v) mark[j] = 1;
        }
    }
    for(i = 0; i < edgesLen; i++) if(mark[i] == 0) flag = 0;

    if(flag) {
        printf("(");
        for (i = 0; i < len; i++) {
            printf("%d", sol[i]);
            if (i < len - 1) printf(", ");
        }
        printf(")\n");
    }
}
