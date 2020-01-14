#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int aaaa;
    int mm;
    int gg;
} data;

typedef struct{
    int h;
    int m;
} ora;

typedef struct titolo_s *titolo_t;
typedef struct titoli_s *titoli_t;

titoli_t newNode(titolo_t val, titoli_t next);
titoli_t SortListIns(titoli_t h, titolo_t val);
titoli_t Listin(FILE *fp, titoli_t col);
