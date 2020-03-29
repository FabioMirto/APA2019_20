#include <stdio.h>
#include "Graph.h"
#define N_SCELTE 3

void stampaMenu(char *scelte[], int *selezione){
    int i=0;
    printf("\nMENU'\n");
    for(i = 0; i < N_SCELTE; i++)
        printf("%2d -> %s\n",i,scelte[i]);
    scanf(" %d",selezione);
}

int main() {
    char *scelte[] = {
            "Leggi grafo",
            "Individuazione di tutti gli insiemi di archi di cardinalità minima la cui rimozione renda il grafo\n"
            "originale un DAG",
            "Calcolo delle distanze massime da ogni nodo sorgente verso ogni nodo del DAG",
            "Uscita"
    };

    int fine = 0, selezione, N, card;
    FILE *fp;
    char string[11];
    Graph G = NULL, DAG = NULL;
    Edge **EdgetoDAG, *edge = NULL;

    while(!fine) {
        stampaMenu(scelte, &selezione);
        switch (selezione){
            case 0:
                printf("Inserire il nome del file\n");
                scanf("%s",string);
                fp=fopen(string,"r");
                G=GRAPHload(fp);
                break;
            case 1:
                GRAPHtoDAG(G, &card, &N, &edge);
                printf("%d insiemi di archi a cardinalità minima %d che rendono il grafo DAG\n", N, card);
                free(edge);
                break;
            case 2:
                EdgetoDAG = GRAPHtoDAG(G, &card, &N, &edge);
                DAG = GRAPHcreateDAG(G, EdgetoDAG, N, card, edge);
                free(edge);
                break;
            case 3:
                fine=1;
                break;
            default :
                printf("Comando inserito non valido\n");
        }
    }
    GRAPHfree(G);
    GRAPHfree(DAG);
    return 0;
}
