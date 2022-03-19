/* Musuroi Daniel-Nicusor - 313CB */

#include "Tema1.h"

TH *IniTH(int M, TFHash fh){
    TH* h = (TH *)calloc(1, sizeof(TH));
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->v = (TLDG *)calloc(M, sizeof(TLDG));
    if(!h->v) {
        printf("eroare alocare vector de pointeri TLDG in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}

void DistrTH(TH** ah, TF fe)
{
    TLDG *p, el, aux;
    int i;

    //parcurgere cu pointeri
    for (i = 0; i < (*ah)->M; i++){
        p = (*ah)->v + i;
        //daca exista elemente corespunzatoare acestui hash
        //eliberam info din celula si apoi eliberam celula
        if (*p){
            for(aux = *p, el = (*p)->urm; el != *p; el = aux->urm) {
                fe(aux->info);
                free(aux);
                aux = el;
            }
            fe(aux->info);
            free(aux);
        }
    }
    free((*ah)->v);
    free(*ah);
    *ah = NULL;
}

int codHash(char *key, int M){
    char *x = key;

    int s = 0; //s reprezinta suma caracterelor
    for (; *x != '\0'; x++){
        s += *x;
    }

    return (s % M);
}

TLDG InitTLDG(void *el){
    TLDG celula = (TLDG)malloc(sizeof(TCelulaG));
    if (!celula){
        printf("ALocarea unei celule dintr-o lista nu a reusit\n");
        return NULL;
    }

    celula->info = el;
    if (!celula->info){
        printf("Alocarea unei informatii ditr-o celula nu a reusit\n");
        free(celula);
        return NULL;
    }

    return celula;
}

TElement *InitElement(char *key, char *value){
    TElement *el;
    el = (TElement *)malloc(sizeof(TElement));
    if (!el){
        printf("Eroare alocare element!\n");
        return NULL;
    }
    el->key = (char *)malloc((strlen(key) + 1) * sizeof(char));
    if (!el->key){
        printf("Eroare alocare element->key!\n");
        free(el);
        return NULL;
    }
    el->value = (char *)malloc((strlen(value) + 1) * sizeof(char));
    if (!el->value){
        printf("Eroare alocare element->value!\n");
        free(el->key);
        free(el);
        return NULL;
    }
    strcpy(el->key, key);
    strcpy(el->value, value);

    return el;
}

void DistrugeElement(void *el){
    free(((TElement *)el)->key);
    free(((TElement *)el)->value);
    free(((TElement *)el));
}

//inserare dupa celula cu adresa a -> 1/0
int InsDupa(TLDG a, void* x){
	TLDG aux = (TLDG)malloc(sizeof(TCelulaG));
	if(!aux) return 0;
	aux->info = x;
	aux->pre = a;
	aux->urm = a->urm;
	a->urm->pre = aux;
	a->urm = aux;
    return 1;
}

//Functia se aplica doar pentru L nevida:
//Parcurgand lista, se gaseste primul element
//din lista care respecta conditia
//strcmp(key(x), key(el)) >= 0
//In cazul in care nu se gaseste un astfel de element
//se va intoarce NULL, astel ca toate elementele din 
//lista respecta conditia strcmp(key(x), key(el)) < 0
TLDG GasesteKey_gt_Keyel(TLDG L, void *el){
    TLDG p;
    for (p = L; p->urm != L; p = p->urm){
        if (strcmp(KEY(p->info), KEY(el)) >= 0)
            return p;
    }

    //Testez si pentru ultimul element din lista:
    if (strcmp(KEY(p->info), KEY(el)) >= 0)
        return p;

    return NULL;
}

//Pentru o lista cu cel putin doua elemente:
void Elim(TLDG *L, TLDG p){
    //Daca p este prima celula din *L
    if (p == *L){
        *L = (*L)->urm;
    }
    p->pre->urm = p->urm;
    p->urm->pre = p->pre;
    DistrugeElement(p->info);
    free(p);
}

void put(TH *tabelaH, void *el){
    TLDG *L = &(tabelaH->v[tabelaH->fh(((TElement *)el)->key, tabelaH->M)]);
    TLDG p;

    //lista vida:
    if (*L == NULL){
        *L = InitTLDG(el);
        if(!(*L)){
            printf("Initializarea unei celule nu a fost facuta cu succes\n");
            return;
        }
        (*L)->urm = *L;
        (*L)->pre = *L;
        return;
    }

    p = GasesteKey_gt_Keyel(*L, el);
    //Daca elementul trebuie introdus la sfarsitul listei:
    if (p == NULL){
        InsDupa((*L)->pre, el);
        return;
    }

    //Daca KEY(p)=KEY(el), elementul a mai fost adaugat o data
    if (strcmp(KEY(p->info), KEY(el)) == 0){
        DistrugeElement(el);
        return;
    }

    //Daca elementul trebuie introdus la inceputul listei:
    if (p == *L){
        InsDupa((*L)->pre, el);
        tabelaH->v[tabelaH->fh(((TElement *)el)->key, tabelaH->M)] = p->pre;
        return;
    }

    //Daca elementul trebuie introdus undeva la mijlocul listei
    InsDupa(p->pre, el);
}

void print(FILE *out, TH *tabelaH){
    int i;
    TLDG p;
    for (i = 0; i < tabelaH->M; i++){
        if (tabelaH->v[i]){
            fprintf(out, "%d: ", i);
            for (p = tabelaH->v[i]; p->urm != tabelaH->v[i]; p = p->urm){
                fprintf(out, "%s ", VALUE(p->info));
            }
            fprintf(out, "%s \n", VALUE(p->info));
        }
    }
}

char *get_function(TH *tabelaH, char *key){
    TLDG L = tabelaH->v[tabelaH->fh(key, tabelaH->M)];

    TLDG p;
    if (!L)
        return "NULL";

    for (p = L; p->urm != L; p = p->urm){
        if (strcmp(KEY(p->info), key) == 0){
            return VALUE(p->info);
        }
    }

    if (strcmp(KEY(p->info), key) == 0){
        return VALUE(p->info);        
    }

    return "NULL";
}


void remove_function(TH *tabelaH, char *key){
    TLDG *L = &(tabelaH->v[tabelaH->fh(key, tabelaH->M)]);

    //Lista este vida:
    if (!(*L))
        return;

    //Lista contine un singur element
    if ((*L)->urm == *L && (*L)->pre == (*L)){
        if (strcmp(KEY((*L)->info), key) == 0){
            DistrugeElement((void *) (*L)->info);
            free(*L);
            *L = NULL;
        }
        return;
    }

    TLDG p;
    for (p = *L; p->urm != *L; p = p->urm){
        if (strcmp(KEY(p->info), key) == 0){
            Elim(L, p);
            return;
        }
    }

    if (strcmp(KEY(p->info), key) == 0){
        Elim(L, p);
    }

}

void print_bucket(FILE *out, TH* tabelaH, int index_bucket){
    if (index_bucket >= tabelaH->M || index_bucket < 0){
        return;
    }

    TLDG L = tabelaH->v[index_bucket];

    if (!L){
        fprintf(out, "VIDA\n");
        return;
    }

    TLDG p;
    for (p = L; p->urm != L; p = p->urm){
        fprintf(out, "%s ", VALUE(p->info));
    }

    fprintf(out, "%s \n", VALUE(p->info));
}

char *find(TH *tabelaH, char *key){
    TLDG L = tabelaH->v[tabelaH->fh(key, tabelaH->M)];

    if (!L){
        return "False";
    }

    TLDG p;
    for (p = L; p->urm != L; p = p->urm){
        if (strcmp(KEY(p->info), key) == 0){
            return "True";
        }
    }

    if (strcmp(KEY(p->info), key) == 0){
        return "True";
    }

    return "False";
}
