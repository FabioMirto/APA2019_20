#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define S 30
#define CHAR 200

#define NOME_FILE1 "sorgente.txt"
#define NOME_FILE2 "dizionario.txt"
#define NOME_FILE3 "riordinato.txt"

typedef struct {
    char originale[20]; //caratteri massimi per le parole nel dizionario 19+1
    char ricodifica[20]; //dato a piacere
}  dizionario;


int main() {
    FILE *fp1, *fp2, *fp3;
    dizionario diz[S];
    int num, i, k, flag, j, lun;
    char riga[CHAR+1];

     fp1 = fopen(NOME_FILE1, "r");
     fp2 = fopen(NOME_FILE2, "r");
     fp3 = fopen(NOME_FILE3, "w");

     if (fp1 == NULL || fp2 == NULL || fp3 == NULL)
         exit(-1);

     fscanf(fp2, "%d", &num);
     for(i = 0; i < num; i++){
         fscanf(fp2, "%s %s", diz[i].ricodifica, diz[i].originale);
     }
      i = 0;
     lun = 0;
     while(fgets(riga, CHAR + 1, fp1) != NULL){
             for(i = 0; i < strlen(riga); i++){
                 flag = 0;
                 for(j = 0; j < num; j++) {
                         lun = strlen(diz[j].originale);
                         if (strncmp(&riga[i], diz[j].originale, lun) == 0) {
                             flag = 1;
                             break;
                         }

                 }
                 if(flag==1){
                     fprintf(fp3, "%s", diz[j].ricodifica);
                     i += ( lun - 1);
                 } else{
                     fprintf(fp3, "%c", riga[i]);
                 }
             }
     }
     fclose(fp1);
     fclose(fp2);
     fclose(fp3);
     return 0;
}
