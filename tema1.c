/* Musuroi Daniel-Nicusor - 313CB */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Tema1.h"


void tema1(FILE *in, FILE *out, TH *tabelaH){
    char *key = (char *)malloc(MAX_LEN_STR * sizeof(char));
    if (!key){
        printf("Alocarea key nu a reusit!\n");
        return;
    }
    char *value = (char *)malloc(MAX_LEN_STR * sizeof(char));
    if (!value){
        printf("Alocarea value nu a reusit!\n");
        free(key);
        return;
    }
    char *operation = (char *)malloc(MAX_LEN_STR * sizeof(char));
    if (!operation){
        printf("Alocarea operation nu a reusit!\n");
        free(value);
        free(key);
        return;
    }

    //citesc fiecare operatia din fisierul de intrare
    //pana la intalnirea sfarsitului de fisier:
    while (fscanf(in, "%s", operation) != EOF){

        if (strcmp(operation, "put") == 0){
            fscanf(in, "%s %s", key, value);
            TElement *el = InitElement(key, value);
            if (!el){
                printf("Alocare unui element a esuat\n");
                return;
            }
            put(tabelaH, el);
        }

        if (strcmp(operation, "get") == 0){
            fscanf(in, "%s", key);
            fprintf(out, "%s\n", get_function(tabelaH, key));
        }

        if (strcmp(operation, "remove") == 0){
            fscanf(in, "%s", key);
            remove_function(tabelaH, key);
        }

        if (strcmp(operation, "find") == 0){
            fscanf(in, "%s", key);
            fprintf(out, "%s\n", find(tabelaH, key));
        }

        if (strcmp(operation, "print") == 0){
            print(out, tabelaH);
        }

        if (strcmp(operation, "print_bucket") == 0){
            int index_bucket;
            fscanf(in, "%d", &index_bucket);
            print_bucket(out, tabelaH, index_bucket);
        }

    }

    free(operation);
    free(key);
    free(value);
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Mod de rulare al temei incorect!\n");
        return 1;
    }

    int M = atoi(argv[1]);

    FILE *in = fopen(argv[2], "rt");
    if (in == NULL)
    {
        return 2;
    }
    FILE *out = fopen(argv[3], "wt");
    if (out == NULL)
    {
        return 2;
    }

    TH *tabelaH;
    //initializare tabela Hash
    tabelaH = IniTH(M, codHash);
    if (!tabelaH){
        return 3;
    }

    //functia care rezolva tema:
    tema1(in, out, tabelaH);

    fclose(in);
    fclose(out);

    DistrTH(&tabelaH, DistrugeElement);

    return 0;
}
