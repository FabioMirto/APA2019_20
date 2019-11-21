#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

typedef enum {
    r_stampa, r_ins, r_ins_file, r_delete, r_delete_date, r_ricerca, r_fine, r_err
} comando_e;

typedef struct Person *link;

struct Person {
    char codice[6+1];
    char nome[MAX + 1];
    char cognome[MAX + 1];
    int gg;
    int mm;
    int aaaa;
    int dataInt;
    char via[MAX + 1];
    char citta[MAX + 1];
    int cap;
    link next;
};


comando_e leggiComando(void);
link SortListIns(link h, struct Person val);
link newNode(struct Person person, link next);
void ListIns(link registry, int file);
struct Person *ListSearch(link h, char *code);
struct Person ListExtrKeyP(link *hp, char *code);
struct Person ListExtrKeyPDate(link *hp, int data1, int data2);

int main() {
    struct Person *registry;
    registry = malloc(sizeof(struct Person));
    int continua = 1;
    char code[6];
    struct Person *match, deleted;
    int dataInt1, dataInt2, g1, g2, m1, m2, a1, a2, datatmp;
    FILE *fp;
    comando_e codiceComando;
    while (continua) {
        codiceComando = leggiComando();
        switch (codiceComando) {
            case r_stampa:
                fp = fopen("list.txt", "w");
                while (registry != NULL) {
                    fprintf(fp, "%s %s %s %d/%d/%d %s %s %d\n", registry->codice, registry->nome, registry->cognome,
                            registry->gg, registry->mm, registry->aaaa, registry->via,
                            registry->citta, registry->cap);
                    registry = registry->next;
                }
                fclose(fp);
                printf("Lista stampata su 'list.txt'\n");
                break;
            case r_ins:
                ListIns(registry, 0);
                while (registry != NULL) {
                    printf("%s %s %s %d/%d/%d %s %s %d\n", registry->codice, registry->nome, registry->cognome,
                           registry->gg, registry->mm, registry->aaaa, registry->via,
                           registry->citta, registry->cap);
                    registry = registry->next;
                }
                break;
            case r_ins_file:
                ListIns(registry, 1);
                while (registry != NULL) {
                    printf("%s %s %s %d/%d/%d %s %s %d\n", registry->codice, registry->nome, registry->cognome,
                           registry->gg, registry->mm, registry->aaaa, registry->via,
                           registry->citta, registry->cap);
                    registry = registry->next;
                }
                break;
            case r_delete:
                printf("Inserire codice:");
                scanf("%s", code);
                deleted = ListExtrKeyP(&registry, code);
                deleted.codice[0] != '0' ? printf("\nEliminato correttamente: %s\n", deleted.codice) : printf(
                        "Non trovato.\n");
                while (registry != NULL) {
                    printf("%s %s %s %d/%d/%d %s %s %d\n", registry->codice, registry->nome, registry->cognome,
                           registry->gg, registry->mm, registry->aaaa, registry->via,
                           registry->citta, registry->cap);
                    registry = registry->next;
                }

                break;
            case r_delete_date:
                printf("\nInserire date nel formato <gg/mm/aaaa> <gg/mm/aaaa>:");
                scanf("%d/%d/%d %d/%d/%d", &g1, &m1, &a1, &g2, &m2, &a2);
                dataInt1 = a1*10000 + m1 *100 + g1;
                dataInt2 = a2*10000 + m2 *100 + g2;
                if(dataInt1 > dataInt2){
                    datatmp = dataInt1;
                    dataInt1 = dataInt2;
                    dataInt2 = datatmp;
                }
                    deleted = ListExtrKeyPDate(&registry, dataInt1, dataInt2);
                deleted.codice[0] != '0' ? printf("\nEliminato correttamente: %s\n", deleted.codice) : printf(
                        "Non trovato.\n");
                while (registry != NULL) {
                    printf("%s %s %s %d/%d/%d %s %s %d\n", registry->codice, registry->nome, registry->cognome,
                           registry->gg, registry->mm, registry->aaaa, registry->via,
                           registry->citta, registry->cap);
                    registry = registry->next;
                }
                break;
            case r_ricerca:
                printf("Inserire codice:");
                scanf("%s", code);
                match = ListSearch(registry, code);
                match != NULL ? printf("%s\n", match->cognome) : printf("Non trovato.\n");
                while (registry != NULL) {
                    printf("%s %s %s %d/%d/%d %s %s %d\n", registry->codice, registry->nome, registry->cognome,
                           registry->gg, registry->mm, registry->aaaa, registry->via,
                           registry->citta, registry->cap);
                    registry = registry->next;
                }
                break;
            case r_fine:
                continua = 0;
                break;
            case r_err:
            default:
                printf("comando errato\n");
                break;
        }
    }
}

comando_e leggiComando(void) {
    comando_e c;
    char cmd[21];
    char *tabella[r_err] = {"stampa", "ins", "ins_file", "cancella", "cancella_date", "ricerca", "fine"};
    int i;
    printf("Inserire comando (stampa/ins/ins_file/cancella/cancella_date/ricerca/fine): ");
    scanf("%s", cmd);
    for (i = 0; cmd[i] != '\0'; i++)
        cmd[i] = tolower(cmd[i]);
    c = r_stampa;
    while (c < r_err && strcmp(cmd, tabella[c]) != 0)
        c++;
    return (c);
}

void ListIns(struct Person *registry, int file) {
    struct Person tmp;
    char file_name[50];
    FILE *fp;
    if (file) {
        printf("Inserire nome file:");
        scanf("%s", file_name);
        fp = fopen(file_name, "r");
        if (fp != NULL) {
                while (fscanf(fp, "%s %s %s %d/%d/%d %s %s %d\n", tmp.codice, tmp.nome, tmp.cognome,
                                &tmp.gg, &tmp.mm, &tmp.aaaa, tmp.via,
                                tmp.citta, &tmp.cap) != EOF) {
                    tmp.dataInt = tmp.aaaa * 10000 + tmp.mm * 100 + tmp.gg;
                    registry = SortListIns(registry, tmp);
                }
        }

    } else {
        scanf("%s %s %s %d/%d/%d %s %s %d", tmp.codice, tmp.nome, tmp.cognome, &tmp.gg, &tmp.mm, &tmp.aaaa, tmp.via, tmp.citta, &tmp.cap);
        tmp.dataInt = tmp.aaaa * 10000 + tmp.mm * 100 + tmp.gg;
        if (ListSearch(registry, tmp.codice) == NULL) {
            registry = SortListIns(registry, tmp);
        }
    }
}

struct Person *ListSearch(link h, char *code) {
    link x;
    for (x = h; x != NULL; x = x->next) {
        if (strcmp(code, x->codice) == 0)
            return x;
    }
    return NULL;
}

struct Person ListExtrKeyP(link *hp, char *code) {
    link *xp, t;
    struct Person i={'0'};
    for (xp = hp; (*xp) != NULL; xp = &((*xp)->next)) {
        if (strcmp((*xp)->codice, code) == 0) {
            t = *xp;
            *xp = (*xp)->next;
            i = *t;
            free(t);
            break;
        }
    }
    return i;
}
struct Person ListExtrKeyPDate(link *hp, int data1, int data2) {
    link *xp, t;
    struct Person i = {'0'};
    for (xp = hp; (*xp) != NULL; xp = &((*xp)->next)) {
        if ( (data1 <= (*xp)->dataInt) && ( (*xp)->dataInt <= data2)) {
            t = *xp;
            *xp = (*xp)->next;
            i = *t;
            free(t);
            break;
        }
    }
    return i;
}

link SortListIns(link h, struct Person val) {
    link x, p;
    int k = val.dataInt;
    if (h == NULL || h->dataInt > k)
        return newNode(val, h);
    for (x = h->next, p = h;
         x != NULL && k > x->dataInt;
         p = x, x = x->next);
    p->next = newNode(val, x);
    return h;
}

link newNode(struct Person person, link next) {
    link x = malloc(sizeof *x);
    if (x == NULL)
        return NULL;
    strcpy(x->codice, person.codice);
    strcpy(x->nome, person.nome);
    strcpy(x->cognome, person.cognome);
    x->dataInt = person.dataInt;
    x->gg = person.gg;
    x->mm = person.mm;
    x->aaaa = person.aaaa;
    strcpy(x->via, person.via);
    strcpy(x->citta, person.citta);
    x->cap = person.cap;
    x->next = next;
    return x;
}
