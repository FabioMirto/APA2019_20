#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *nome;
    int tipo;
    int ing;
    int usc;
    int pre;
    int fin;
    float val;
    int dif;
} elementi;

int disp_ripet(int pos, elementi *val, elementi *sol, int len, int k, int count, float DSOL);
int pruning(int pos, elementi *val, elementi *sol, int len, int i);

int main() {
    FILE *fp;
    elementi *e, *sol;
    int len, i, count;
    char nome[100+1];
    fp = fopen("elementi.txt", "r");
    fscanf(fp, "%d", &len);
    e = malloc(len * sizeof(elementi));
    sol = malloc(len * sizeof(elementi));
    for(i = 0; i < len; i++){
        fscanf(fp, "%s %d %d %d %d %d %f %d", nome,  &e[i].tipo, &e[i].ing, &e[i].usc,
               &e[i].pre, &e[i].fin, &e[i].val, &e[i].dif);
        e[i].nome = strdup(nome);
    }
    count = disp_ripet(0, e, sol, len, 5, 0, 0);
    return 0;
}

int disp_ripet(int pos, elementi *val, elementi *sol, int len, int k, int count, float DSOL){
    int i;
    float DD = 10;
    if (pos >= k) {
        for(int j = 0; j < len; j++){
            printf("%s ", sol[j].nome);
        }
        printf("%f", DSOL);
        printf("\n");
       return count+1;
    }
    if(pos == 0){
        for(int l = 0; l < len; l++){
            if(val[l].ing == 0 || val[l].pre == 1){
                l++;
            } else {
                sol[pos] = val[l];
                count = disp_ripet(pos + 1, val, sol, len, k, count, DSOL);
            }
        }
        DSOL += sol[pos].val;
        pos++;

    }
    for (i = 0; i < len; i++) {
        if (pruning(pos, val, sol, len, i) == 1 && DSOL+val[i].val < DD) {
            sol[pos] = val[i];
            DSOL += sol[pos].val;
            count = disp_ripet(pos + 1, val, sol, len, k, count, DSOL);
        }
    }
    return count;
}

int pruning(int pos, elementi *val, elementi *sol, int len, int i){
    int flag = 0;
    if(pos > 0) {
        if ((sol[pos - 1].usc == 1 && val[i].ing == 1) || (sol[pos - 1].usc == 0 && val[i].ing == 0)) {
            flag = 1;
        }
        if (val[i].tipo == 0) {
            flag = 0;
        }
        if(val[i].pre == 0)
            flag = 0;
        if(val[i].fin == 0)
            flag = 1;
    }
    if(flag)
        return flag;
    else
        return 0;
}
