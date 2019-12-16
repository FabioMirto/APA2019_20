#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int s;
    int f;
    int d;
} att;

void Soluzione(att *v, int len);
int check(int len, att *v, int i);
void DisplaySol(att *sol, int len, int d, int i);

int main() {
    att *v, tmp;
    int i, j, len;
    FILE *fp = fopen("att.txt", "r");
    fscanf(fp, "%d", &len);
    v = malloc(len*sizeof(att));
    for (i = 0; i < len; i++) {
        fscanf(fp, "%d %d", &v[i].s, &v[i].f);
        v[i].d = v[i].f - v[i].s;
    }
    for(i = 0; i < len; i++) {
        for (j = i; j < len; j++) {
            if (v[i].s > v[j].s) {
                tmp = v[i];
                v[i] = v[j];
                v[j] = tmp;
            } else if (v[i].s == v[j].s) {
                if (v[i].f > v[j].f) {
                    tmp = v[i];
                    v[i] = v[j];
                    v[j] = tmp;
                }
            }
        }
    }

    for (i = 0; i < len; i++) {
        printf("%d %d INTERVALLO: %d\n", v[i].s, v[i].f, v[i].d);
    }

    Soluzione(v, len);

    return 0;
}

void Soluzione(att *v, int len){
    int i, d = 0, k[len];
    att *sol = calloc(len, sizeof(att));
    sol[0] = v[0];
    d = sol[0].d;
    for(i = 0; i < len-1; i++){
        if(!((sol[0].s < v[i].f) && (v[i].s < sol[0].f))) {
            k[i] = check(len, v, i);
            if(k[i] != k[i-1])
                sol[i] = v[k[i]];
        }
    }
    for(i = 1; i < len; i++){
        d += sol[i].d;
    }
    printf("SOLUZIONE:\n");
    DisplaySol(sol, len, d, 0);
    printf("CON DURATA %d", d);
}

int check(int len, att *v, int i){
    int j;
    for(j = 0; j < len; j++){
        if(v[i].s == v[j].s && v[i].f == v[j].f) {
            i++;
            j++;
        }
        if((v[i].s == v[j].s) || (v[i].f == v[j].f)){
            if(v[i].d > v[j].d)
                return i;
            else
                return j;
        }
    }
    return 0;
}
void DisplaySol(att *sol, int len, int d, int i) {
        if (sol[i].s != 0 && i < len) {
            printf("(%d, %d)\n", sol[i].s, sol[i].f);
        }
        if(i < len)
            DisplaySol(sol, len, d, i+1);
}
