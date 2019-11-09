#include <stdio.h>
#define n 3

int majority( int *a, int N);
int maj (int *a, int l, int r);

int main() {
    int i;
    int vet[n];
    printf("Digita un vettore di %d cifre\n", n);
    for(i = 0;i < n; i++){
        scanf("%d", &vet[i]);
    }

    printf("%d\n", majority(vet, n));

    return 0;
}

int majority(int *a, int N){
   return maj(a, 0, N-1);
}


int maj (int *a, int l, int r) {
    int countsx = 0, countdx = 0, i;
    int dx, sx;
    int q = (l + r) / 2;
    if (l == r)
        return a[l];
    if (r - l == 1) {
        if (a[l] == a[r])
            return a[l];
        return -1;
    }
    sx = maj(a, l, q);
    dx = maj(a, q + 1, r);
    for (i = l; i <= r; i++) {
        if (a[i] == sx)
            countsx++;
        if (a[i] == dx)
            countdx++;
    }
         if (countsx > (r + l) / 2)
            return sx;
        if (countdx > (r + l) / 2)
             return dx;
    return -1;
}
