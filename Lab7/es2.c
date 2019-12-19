#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
      char gemma;
      int quantita;
      int valore;
      int n;
} g;

typedef struct {
      char *val;
      int quantita;
      int valore;
} s;

s disp_rip(int pos, g gem[], char *sol, s tmp, int n, int k, int count, int max_rip);
int pruning(char *sol, int i, char value, int max_rip);

int main() {
    clock_t start, end;
    double tempo;
    start=clock();
    int i, max_rip = 3;
    s b, tmp, bsol;
    char *sol;
    g gem[4] = {'Z', 8, 6, 0,
                'S', 5, 8, 0,
                'R', 1,  6, 0,
                'T', 10, 20, 0};
    int TOT = gem[0].quantita +  gem[1].quantita
              + gem[2].quantita + gem[3].quantita;
       b.quantita = 0;
       bsol.valore = 0;
       b.val = malloc(TOT * sizeof(char));
       bsol.val = malloc(TOT * sizeof(char));
       sol = malloc(TOT * sizeof(char));


       for (i = 1; i < TOT; i++) {
           tmp = disp_rip(0, gem, sol, b, 4, i, 0, max_rip);
            if (tmp.valore > bsol.valore) {
                bsol.valore = tmp.valore;
                bsol.quantita = tmp.quantita;
                strcpy(bsol.val, tmp.val);
              }
          }
       printf("\nVALORE COLLANA %d GEMME %d\n"
              "COLLANA: %s\n", bsol.valore, bsol.quantita, bsol.val);
       free(b.val);
       free(bsol.val);
       free(sol);
       end=clock();
       tempo=((double)(end-start))/CLOCKS_PER_SEC;
       printf("TEMPO DI ESECUZIONE IN SECONDI %.2f", tempo);
       return 0;
}


s disp_rip(int pos, g gem[], char *sol, s tmp, int n, int k, int count, int max_rip) {
    int i, c_val = 0;
    gem[0].n = 0;
    gem[1].n = 0;
    gem[2].n = 0;
    gem[3].n = 0;
      if (pos >= k) {
          for (i = 0; i < pos; i++) {
              if (sol[i] == 'Z') {
                  gem[0].n++;
              } else if (sol[i] == 'S') {
                  gem[1].n++;
              } else if (sol[i] == 'R') {
                  gem[2].n++;
              } else if (sol[i] == 'T') {
                  gem[3].n++;
              }
          }
          if (gem[0].n <= gem[1].n) {
              for (i = 0; i < k; i++)
                  c_val = gem[0].valore * gem[0].n + gem[1].valore * gem[1].n +
                          gem[2].valore *  gem[2].n + gem[3].valore *  gem[3].n;
              if (tmp.valore < c_val) {
                  tmp.valore = c_val;
                  tmp.quantita = gem[0].n + gem[1].n + gem[2].n + gem[3].n;
                  for (i = 0; i < k; i++)
                      tmp.val[i] = sol[i];
              }
          }
          return tmp;
      }
      for (i = 0; i < n; i++) {
          if (gem[i].quantita > 0 && pruning(sol, pos - 1, gem[i].gemma, max_rip) == 0) {
              sol[pos] = gem[i].gemma;
              gem[i].quantita--;
              tmp = disp_rip(pos + 1, gem, sol, tmp, n, k, count, max_rip);
              gem[i].quantita++;
          }
      }
      return tmp;
  }

int pruning(char *sol, int i, char value, int max_rip) {
      int j, count = 0;
      if (i + 1 >= max_rip) {
          for (j = 0; j <= max_rip; j++) {
              if (sol[i - j] == sol[i])
                  count++;
              else
                  break;
          }
          if (count >= max_rip && sol[i] == value)
              return 1;
      }
      if(sol[i] == 'Z' || sol[i] == 'T'){
          if(value != 'Z' && value != 'R')
              return 1;
          return 0;
      } else if(sol[i] == 'S' || sol[i] == 'R'){
          if(value !=  'S' && value != 'T')
              return 1;
          return 0;
      }
      return 0;
}
