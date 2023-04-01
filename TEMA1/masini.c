#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structura masina
struct masina
{
    char *brand;
    char *numar;
    char *combustibil;
    double consum;
    int km;
};

// Functie pentru cerinta a
void cerinta_a(struct masina *masini, int n, int combustibil[])
{
    // Initializam toate elementele vectorului cu 0
    for (int i = 0; i < 4; i++)
        combustibil[i] = 0;
    // 0 - benzina
    // 1 - motorina
    // 2 - hibrid
    // 3 - electric

    // Parcurgem vectorul de masini si incrementam elementul corespunzator combustibilului
    for (int i = 0; i < n; i++)
    {
        if (strcmp(masini[i].combustibil, "benzina") == 0)
            combustibil[0]++;
        if (strcmp(masini[i].combustibil, "motorina") == 0)
            combustibil[1]++;
        if (strcmp(masini[i].combustibil, "hibrid") == 0)
            combustibil[2]++;
        if (strcmp(masini[i].combustibil, "electric") == 0)
            combustibil[3]++;
    }
}

// Structura pentru fiecare brand de masina
struct brands
{
    char brand[20];
    double total_litrii;
    double suma_lei;
};

// Functie proprie pentru rotujirea unui numar n de tip double
double myround(double n)
{
    double aux;

    // Daca a 2 a cifra dupa virgula este 0, returnam numarul
    if ((int)(n * 1000) % 10 == 0)
        return n;
    
    // Daca a 2 a cifra dupa virgula este mai mica decat 5, rotunjim numarul la 0
    if ((int)(n * 1000) % 10 < 5)
    {
        int x1 = (int)(n * 1000);
        int x2 = (int)(n * 1000) % 10;
        int x3 = x1 - x2;
        return (double)x3 / 1000;
    }

    // Daca a 2 a cifra dupa virgula este 5, returnam numarul
    if ((int)(n * 1000) % 10 == 5)
        return n;
    
    // Daca a 2 a cifra dupa virgula este 5 si a 3 a cifra dupa virgula este mai mare decat 0, rotunjim a 2 a cifra
    // dupa virgula la cifra cu 1 mai mare
    if ((int)(n * 1000) % 10 == 5 && (int)(n * 10000) % 10 > 0)
        return (double)((n * 1000) + 1) / 1000;

    // Orice alt caz rotunjim numarul precum functia ceil()
    aux = (int)((n * 100) + 0.5);
    n = (double)aux / 100;
    return n;
}

// Functie pentru cerinta b
void cerinta_b(struct masina *masini, int n, struct brands *brands, int *len)
{
    int i, j, k = 0;

    // Parcurgem vectorul de masini
    for (i = 0; i < n; i++)
    {
        int ok = 0;
        for (j = 0; j < n; j++)
            if (strcmp(masini[i].brand, brands[j].brand) == 0)
            {
                ok = 1;
                break;
            }
        // Daca brandul masinii curente nu a mai fost adaugat in vectorul de brands, il adaugam
        // Calculam totalul de litrii si suma totala in lei
        if (ok)
        {
            brands[j].total_litrii += (double)((masini[i].consum * masini[i].km) / 100);
            if (strcmp(masini[i].combustibil, "benzina") == 0)
            {
                double aux = (double)((masini[i].consum * masini[i].km) / 100);
                brands[j].suma_lei += (double)(aux * 8.02);
            }
            if (strcmp(masini[i].combustibil, "motorina") == 0)
            {
                double aux = (double)((masini[i].consum * masini[i].km) / 100);
                brands[j].suma_lei += (double)(aux * 9.29);
            }
            if (strcmp(masini[i].combustibil, "hibrid") == 0)
            {
                double aux = (double)((masini[i].consum * masini[i].km) / 100);
                brands[j].suma_lei += (double)(aux * 8.02);
            }
        }
        else
        {
            strcpy(brands[k].brand, masini[i].brand);
            brands[k].total_litrii += (double)((masini[i].consum * masini[i].km) / 100);
            if (strcmp(masini[i].combustibil, "benzina") == 0)
            {
                double aux = (double)((masini[i].consum * masini[i].km) / 100);
                brands[k].suma_lei += (double)(aux * 8.02);
            }
            if (strcmp(masini[i].combustibil, "motorina") == 0)
            {
                double aux = (double)((masini[i].consum * masini[i].km) / 100);
                brands[k].suma_lei += (double)(aux * 9.29);
            }
            if (strcmp(masini[i].combustibil, "hibrid") == 0)
            {
                double aux = (double)((masini[i].consum * masini[i].km) / 100);
                brands[k].suma_lei += (double)(aux * 8.02);
            }

            k++;
        }
    }
    *len = k;
}

// Structura auxiliara pentru memorarea brandului si numarului de inmatriculare
struct numere
{
    char numere[10];
    char brand[20];
};

// Functie pentru verificare corectitudine numar de inmatriculare
int verifica_numar(char *numar)
{
    int i = 0;
    char aux[10];

    // Stocam literele pana la prima cifra intr-un vector auxiliar
    aux[0] = '\0';
    while (isalpha(numar[i]))
    {
        aux[i] = numar[i];
        i++;
    }
    aux[i] = '\0';

    // Verificam daca numarul de litere este corect
    if (strlen(aux) > 2 || strlen(aux) < 1)
        return 0;

    // Stocam cifrele pana la prima litera intr-un vector auxiliar
    aux[0] = '\0';
    int k = 0;
    while (isdigit(numar[i]))
    {
        aux[k] = numar[i];
        k++;
        i++;
    }
    aux[k] = '\0';
    // Verificam daca numarul de cifre este corect
    if (strlen(aux) > 3 || strlen(aux) < 2)
        return 0;

    // Stocam literele pana la final de sir
    aux[0] = '\0';
    k = 0;
    while (isalpha(numar[i]))
    {
        aux[k] = numar[i];
        k++;
        i++;
    }
    aux[k] = '\0';

    // Verificam daca numarul de litere este corect
    if (strlen(aux) != 3)
        return 0;

    return 1;
}

//Functie pentru cerinta c
void cerinta_c(struct masina *masini, int n, struct numere *numere, int *len)
{
    int i, k = 0;
    // Parcurgem vectorul de masini
    for (i = 0; i < n; i++)
    {
        // Daca numarul de inmatriculare nu este corect, il adaugam in vectorul de numere
        if (!verifica_numar(masini[i].numar))
        {
            strcpy(numere[k].numere, masini[i].numar);
            strcpy(numere[k].brand, masini[i].brand);
            k++;
            *len = *len + 1;
        }
    }
}
int main()
{
    int N, i, rez[5];
    char aux_brand[21], aux_numar[21], aux_combustibil[21];
    char cerinta;

    // Citire numar de masini
    scanf("%d", &N);

    // Alocare vector de masini
    struct masina *masini = malloc(N * sizeof(struct masina));

    // Citire masini
    for (i = 0; i < N; i++)
    {
        scanf("%s %s %s %lf %d", aux_brand, aux_numar, aux_combustibil, &(masini[i].consum), &(masini[i].km));
        getchar();
        masini[i].brand = malloc((strlen(aux_brand) + 1) * sizeof(char));
        masini[i].numar = malloc((strlen(aux_numar) + 1) * sizeof(char));
        masini[i].combustibil = malloc((strlen(aux_combustibil) + 1) * sizeof(char));
        strcpy(masini[i].brand, aux_brand);
        strcpy(masini[i].numar, aux_numar);
        strcpy(masini[i].combustibil, aux_combustibil);
    }

    // Citire cerinta
    scanf("%c", &cerinta);
    getchar();

    // Apel functii si afisare rezultate
    if (cerinta == 'a')
    {
        cerinta_a(masini, N, rez);
        printf("benzina - %d\n", rez[0]);
        printf("motorina - %d\n", rez[1]);
        printf("hibrid - %d\n", rez[2]);
        printf("electric - %d\n", rez[3]);
    }
    if (cerinta == 'b')
    {
        struct brands *brands = calloc(N, sizeof(struct brands));
        int len = 0;
        cerinta_b(masini, N, brands, &len);
        for (i = 0; i < len; i++)
            printf("%s a consumat %.2lf - %.2lf lei\n", brands[i].brand, myround(brands[i].total_litrii), myround(brands[i].suma_lei));
    }
    if (cerinta == 'c')
    {
        struct numere *numere = calloc(N, sizeof(struct numere));
        int len = 0;
        cerinta_c(masini, N, numere, &len);
        if (len == 0)
            printf("Numere corecte!\n");
        for (i = 0; i < len; i++)
            printf("%s cu numarul %s: numar invalid\n", numere[i].brand, numere[i].numere);
    }
    return 0;
}