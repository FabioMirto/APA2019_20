#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char C1, C2;
    int V1, V2;
    int inUso;
} t;

typedef struct{
    int t, r;
} b;

t *leggiFile1(FILE *fp, int len);
b **leggiFile2(FILE *fp, int nr, int nc);
void powerset(int pos, t **tiles, int nc, int k, int len, int nr, int c_val, int *b_val, int *b_sol, b **board, b**bboard);

        int main() {
    t *tiles;
    b **board, **bboard;
    int len, i, j, nr, nc;
    FILE *ft = fopen("tiles.txt", "r");
    FILE *fb = fopen("board.txt", "r");
    if(ft == NULL || fb == NULL)
        return 0;
    fscanf(ft, "%d", &len);
    tiles = leggiFile1(ft, len);
    fscanf(fb, "%d %d", &nr, &nc);
    board = leggiFile2(fb, nr, nc);
            bboard = malloc(nr * sizeof(b));
            for(i = 0; i < nr; i++){
                bboard[i] = malloc(nc * sizeof(b));
            }
    for(i = 0; i < len*2; i++)
        printf("%c %d %c %d\n", tiles[i].C1, tiles[i].V1, tiles[i].C2, tiles[i].V2);

    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            printf("%d/%d ", board[i][j].t, board[i][j].r);
        }
        printf("\n");
    }

    powerset(0, &tiles, nc, nr*nc, len, nr,0,0,0,board, bboard);
            for(i = 0; i < nr; i++){
                for(j = 0; j < nc; j++){
                    printf("%d/%d ", bboard[i][j].t, bboard[i][j].r);
                }
                printf("\n");
            }
    return 0;
}

t *leggiFile1(FILE *fp, int len){
    int i;
    t *tiles = malloc(len * sizeof(t));
    for(i = 0; i < len; i++){
        fscanf(fp, "%c %d %c %d", &tiles[i].C1, &tiles[i].V1, &tiles[i].C2, &tiles[i].V2);
        tiles[i].inUso = 0;
    }
    for(i = 0; i < len; i++)
        printf("%c %d %c %d\n", tiles[i].C1, tiles[i].V1, tiles[i].C2, tiles[i].V2);

    fclose(fp);
    return tiles;
}

b **leggiFile2(FILE *fp, int nr, int nc){
    int i, j;
    b **board;
    board = malloc(nr * sizeof(b));
    for(i = 0; i < nr; i++){
        board[i] = malloc(nc * sizeof(b));
    }
    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            fscanf(fp, "%d/%d", &board[i][j].t, &board[i][j].r);
        }
    }
    return board;
}

void powerset(int pos, t **tiles, int nc, int k, int len, int nr, int c_val, int *b_val, int *b_sol, b **board, b **bboard) {
    int j, i, m;
    j = pos%nc;
    i = pos/nr;
    if (pos >= k) {
        for(i = 0; i < nr; i++) {
            for (j = 0; j < nc; j++) {
                bboard[i][j] = board[i][j];
            }
        }
        return;
    }
            if (board[i][j].t >= 0) {
                return powerset(pos+1, tiles, nc, k, len, nr, c_val, b_val, b_sol, board,bboard);


    }
for(m = 0; m < len*2; m++) {
    if(tiles[k]->inUso == 0){
        board[i][j].t = k;
        tiles[k]->inUso = 1;
        board[i][j].r = 0;
        powerset(pos + 1, tiles, nc, k, len, nr, c_val, b_val, b_sol, board, bboard);
        board[i][j].r = 1;
        powerset(pos + 1, tiles, nc, k, len, nr, c_val, b_val, b_sol, board,bboard);
        board[i][j].t = -1;
        tiles[k]->inUso = 0;
        }
    }
}
