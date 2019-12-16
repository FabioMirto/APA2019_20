#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int s;
    int f;
    int d;
} att;

void Soluzione(att *v, int n);
void DisplaySol(att *v, int *P, int len);
void ordinamento(att *v, int len);

int main() {
    att *v;
    int i, j, len;
    FILE *fp = fopen("att.txt", "r");
    fscanf(fp, "%d", &len);
    v = malloc(len*sizeof(att));
    for (i = 0; i < len; i++) {
        fscanf(fp, "%d %d", &v[i].s, &v[i].f);
        v[i].d = v[i].f - v[i].s;
    }
    ordinamento(v, len);
    for (i = 0; i < len; i++) {
        printf("%d %d INTERVALLO: %d\n", v[i].s, v[i].f, v[i].d);
    }
    Soluzione(v, len);
    return 0;
}

void DisplaySol(att *v, int *P, int i) {
    if (P[i] == -1) {
        printf("(%d, %d)\n", v[i].s, v[i].f);
        return;
    }
    DisplaySol(v, P, P[i]);
    printf("(%d, %d)\n", v[i].s, v[i].f);
}

void Soluzione(att *v, int len) {
    int i, j, ris = 1, last = 1, L[len], P[len];

    for (i = 0; i < len; i++) {
        L[i] = 0;
        P[i] = -1;
        for (j = 0; j < i; j++) {
            if ((v[i].s >= v[j].f || v[j].s >= v[i].f) && L[i] < L[j] + v[j].d) {
                L[i] += v[j].d;
                P[i] = j;
            }
        }
        if (ris <= L[i]) {
            ris = L[i];
            last = i;
        }
    }
    printf("SOLUZIONE:\n");
        DisplaySol(v, P, last);
    printf("CON DURATA: %d", ris);
}

void ordinamento(att *v, int len){
    int i, j;
    att tmp;
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
}
