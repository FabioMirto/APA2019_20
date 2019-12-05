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
b **leggiFile2(FILE *fp, int nr, int nc, t *tiles);
void powerset(int pos, t **tiles, int nc, int len, int nr, int c_val, int *b_val, int *b_sol, b **board, b**bboard);
int check(t *tiles, int nc, int nr, b **board);

int main() {
    t *tiles;
    b **board, **bboard;
    int len, i, j, nr, nc, b_val, *bsol = 0;
    FILE *ft = fopen("tiles.txt", "r");
    FILE *fb = fopen("board.txt", "r");
    if(ft == NULL || fb == NULL)
            return 0;
    fscanf(ft, "%d%*c", &len);
    tiles = leggiFile1(ft, len);
    fscanf(fb, "%d %d", &nr, &nc);
    board = leggiFile2(fb, nr, nc, tiles);
    bboard = malloc(nr * sizeof(b*));
      for(i = 0; i < nr; i++){
           bboard[i] = malloc(nc * sizeof(b));
       }

      for(i = 0; i < len; i++) {
          printf("%c %d %c %d\n", tiles[i].C1, tiles[i].V1, tiles[i].C2, tiles[i].V2);
        }
        for(i = 0; i < nr; i++){
            for(j = 0; j < nc; j++){
                printf("%d/%d ", board[i][j].t, board[i][j].r);
            }
            printf("\n");
        }

    powerset(0, &tiles, nc, len, nr,0,&b_val, bsol ,board, bboard);


    for (i = 0; i < nr; i++) {
        for (j = 0; j < nc; j++) {
            printf("%d/%d ", bboard[i][j].t, bboard[i][j].r);
            }
        printf("\n");
        }
    printf("VALORE MATRICE %d", b_val);
        return 0;
    }


t *leggiFile1(FILE *fp, int len){
    int i;
    t *tiles = malloc(len * sizeof(t));
    for(i = 0; i < len; i++){
        fscanf(fp, "%*c%c%*c%d%*c%c%*c%d%*c", &tiles[i].C1, &tiles[i].V1, &tiles[i].C2, &tiles[i].V2);
    }
    fclose(fp);
    return tiles;
}

b **leggiFile2(FILE *fp, int nr, int nc, t *tiles){
    int i, j;
    b **board;
    board = malloc(nr * sizeof(b));
    for(i = 0; i < nr; i++){
        board[i] = malloc(nc * sizeof(b));
    }
    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            fscanf(fp, "%d/%d", &board[i][j].t, &board[i][j].r);
            if(board[i][j].t != -1){
                tiles[board[i][j].t].inUso = 1;
            }
        }
    }
    return board;
}

void powerset(int pos, t **tiles, int nc, int len, int nr, int c_val, int *b_val, int *b_sol, b **board, b **bboard) {
    int j, i, k;

    if (pos >= nr*nc) {
        c_val = check(*tiles, nc, nr, board);
        if (c_val > *b_val) {
            *b_val = c_val;
            for (i = 0; i < nr; i++) {
                for (j = 0; j < nc; j++) {
                        bboard[i][j] =  board[i][j];
                }
            }
         }
        return;
    }

    i = pos / nr;
    j = pos % nc;

    if (board[i][j].t >= 0) {
        return powerset(pos + 1, tiles, nc, len, nr, c_val, b_val, b_sol, board, bboard);
    }

    for(k = 0; k < len; k++) {
        if ((*tiles)[k].inUso == 0) {
            (*tiles)[k].inUso = 1;
            board[i][j].t = k;
            board[i][j].r = 0;
            powerset(pos + 1, tiles, nc, len, nr, c_val, b_val, b_sol, board, bboard);
            board[i][j].r = 1;
            powerset(pos + 1, tiles, nc, len, nr, c_val, b_val, b_sol, board, bboard);
            (*tiles)[k].inUso = 0;
            board[i][j].t = -1;
        }
    }
}

int check(t *tiles, int nc, int nr, b **board){
    int i, j, val_tmp1 = 0, val_tmp2 = 0, temp;
    t tmp[9];
    for(i = 0; i < 9; i++){
        tmp[i].inUso = tiles[i].inUso;
        tmp[i].C1 = tiles[i].C1;
        tmp[i].V1 = tiles[i].V1;
        tmp[i].V2 = tiles[i].V2;
        tmp[i].C2 = tiles[i].C2;
    }

    for(i = 0; i < nr; i++){
        for(j = 0; j < nc; j++){
            if(board[i][j].r == 1){
                tmp[board[i][j].t].C2 = tiles[board[i][j].t].C1;
                tmp[board[i][j].t].V2 = tiles[board[i][j].t].V1;
                tmp[board[i][j].t].C1 = tiles[board[i][j].t].C2;
                tmp[board[i][j].t].V1 = tiles[board[i][j].t].V2;
            }
        }
    }
        for (i = 0; i < nr; i++) {
            temp = 0;
            for (j = 0; j < nc; j++) {
                if (tmp[board[i][j].t].C1 == tmp[board[i][0].t].C1) {
                    temp++;
                }
                if (temp == nc) {
                    for (j = 0; j < nc; j++) {
                        val_tmp2 += tmp[board[i][j].t].V1;
                    }
                }
            }
        }
    for(j = 0; j < nc; j++) {
        temp = 0;
        for (i = 0; i < nr; i++) {
            if (tmp[board[i][j].t].C2 == tmp[board[0][j].t].C2) {
                temp++;
            }
            if (temp == nr) {
                for (i = 0; i < nr; i++) {
                    val_tmp1 += tmp[board[i][j].t].V2;
                }
            }
        }
    }

    return val_tmp1+val_tmp2;
}
