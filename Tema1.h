/* Musuroi Daniel-Nicusor - 313CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#ifndef _Functii_
#define _Functii_

#define MAX_LEN_STR 100


typedef int (*TFHash)(char *, int); //functie hash

typedef void (*TF)(void *); //functie de eliberare informatie
//EX: DistrugeElement

#define KEY(a) ((TElement *)(a))->key
#define VALUE(a) ((TElement *)(a))->value

typedef struct celulag
{
  void *info;           /* adresa informatie */
  struct celulag *urm, *pre;   /* adresa celulei urmatoare si
  a celulei precedente */
} TCelulaG, *TLDG; /* tipurile Celula, Lista  */

typedef struct
{
    size_t M;
    TFHash fh;
    TLDG *v;
} TH;

typedef struct element
{
    char *key, *value;
} TElement; // un element din lista

TH *IniTH(int M, TFHash fh); // initializeaza o tabela Hash

void DistrTH(TH** ah, TF fe); //distruge tabela hash, fe este functia 
// de eliberare a unui element dintr-o lista

int codHash(char *key, int M); //calculeaza codul Hash

TLDG InitTLDG(void *el); //initializeaza o celula cu elementul el

TElement *InitElement(char *key, char *value); //initializeaza un element
//dintr-o lista dublu inlantuita, un element TElement ce are in campul 
//key stringul key si in campul value strigul value

void DistrugeElement(void *el); //Distruge un element dintr-o lista 
//dublu inlantuita

int InsDupa(TLDG a, void* x);  /* inserare dupa celula cu adresa a -> 1/0 */

TLDG GasesteKey_gt_Keyel(TLDG L, void *el); //Gaseste elementul inaintea 
//caruia trebuie sa introduc un element nou (el) in lista. Se aplica doar
//listelor nevide

void Elim(TLDG *L, TLDG p);//elimina o celula din lista, se aplica doar pe
//listele cu cel putin doua elemente(celule)

void put(TH *tabelaH, void *el);

char *get_function(TH *tabelaH, char *key);

void remove_function(TH *tabelaH, char *key);

char *find(TH *tabelaH, char *key);

void print(FILE *out, TH *tabelaH);

void print_bucket(FILE *out, TH* tabelaH, int index_bucket);


#endif