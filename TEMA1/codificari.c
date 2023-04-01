#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Functie pentru cresterea codului ASCII al unui caracter cu n pozitii
// Daca caracterul este 'z' se va trece la 'A'
// Daca caracterul este 'Z' se va trece la 'a'
char add(char letter, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (letter == 'z')
        {
            letter = 'A';
        }
        else if (letter == 'Z')
        {
            letter = 'a';
        }
        else
            letter++;
    }

    return letter;
}

// Functie pentru scaderea codului ASCII al unui caracter cu n pozitii
// Daca caracterul este 'A' se va trece la 'z'
// Daca caracterul este 'a' se va trece la 'Z'
char subtract(char letter, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (letter == 'A')
        {
            letter = 'z';
        }
        else if (letter == 'a')
        {
            letter = 'Z';
        }
        else
            letter--;
    }
    return letter;
}

// Functie pentru codificarea
void codificare_A(char text[], char input[])
{
    char cheie[51], matrice[500][500];
    int i, j, n, text_length, f[51] = {-1}, k = 0, matrice_col_length;

    // Extragere cheie din input
    strcpy(cheie, input + 12);

    // Lungimea cheii
    n = strlen(cheie);

    // Initializare vector auxiliar echivalent cu pozitiile initiale ale cheii
    for (i = 0; i < n; i++)
    {
        f[i] = i;
    }

    // Lungimea textului
    text_length = strlen(text);

    // Asezarea textului in matrice
    i = 0;
    j = 0;
    while (1)
    {
        matrice[i][j] = text[k];
        k++;
        j++;
        // Daca s-a ajuns la finalul cheii (ca lungime) se trece la urmatoarea linie
        if (j == n)
        {
            i++;
            j = 0;
        }
        // Completeaza restul de valori din vector cu spatii
        if (k == text_length)
        {
            while (j != n)
            {
                matrice[i][j] = ' ';
                j++;
            }
            break;
        }
    }

    matrice_col_length = i;

    // Sterge liniile care contin doar spatii
    for (i = matrice_col_length; i >= 0; i--)
    {
        int ok = 0;
        for (j = 0; j < n; j++)
        {
            if (matrice[i][j] != ' ')
                ok = 1;
            if (isalpha(matrice[i][j]))
            {
                ok = 2;
                break;
            }
        }
        if (ok == 2)
            break;
        if (!ok)
        {
            matrice_col_length--;
            for (j = 0; j < n; j++)
                matrice[i][j] = '\0';
        }
    }

    // Sortare cheie in ordine lexicografica si a vectorului auxiliar
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (cheie[i] > cheie[j])
            {
                char aux = cheie[i];
                cheie[i] = cheie[j];
                cheie[j] = aux;

                int auxx = f[i];
                f[i] = f[j];
                f[j] = auxx;
            }

    // Inlocuirea caracterelor din text cu spatii
    k = 0;
    for (i = 0; i < text_length; i++)
        text[i] = ' ';

    // Afisarea textului codificat
    for (i = 0; i < n; i++)
        for (j = 0; j <= matrice_col_length; j++)
        {
            printf("%c", matrice[j][f[i]]);
            text[k] = matrice[j][f[i]];
            k++;
        }

    text[k] = '\0';
    printf("\n");
}
void decodificare_A(char text[], char input[])
{
    char cheie[51], matrice[500][500] = {{' '}};
    int i, j, n, text_length, f[51] = {-1}, k = 0, matrice_col_length;

    // Extragere cheie din input
    strcpy(cheie, input + 14);

    // Lungimea cheii
    n = strlen(cheie);

    // Lungime text
    text_length = strlen(text);

    // Initializare vector auxiliar echivalent cu pozitiile initiale ale cheii
    for (i = 0; i < n; i++)
    {
        f[i] = i;
    }

    // Calculare lungime coloane matrice
    matrice_col_length = text_length / n;
    if (text_length % n != 0)
        matrice_col_length++;

    // Asezarea textului in matrice
    i = 0;
    j = 0;
    while (1)
    {
        matrice[i][j] = text[k];
        k++;
        i++;
        // Daca s-a ajuns la ultima linie se trece la urmatoarea coloana
        if (i == matrice_col_length)
        {
            j++;
            i = 0;
        }
        // Completeaza restul de valori din vector cu spatii
        if (k == text_length)
        {
            while (i != n)
            {
                matrice[i][j] = ' ';
                i++;
            }
            break;
        }
    }

    // Sortare cheie in ordine lexicografica si a vectorului auxiliar
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (cheie[i] > cheie[j])
            {
                char aux = cheie[i];
                cheie[i] = cheie[j];
                cheie[j] = aux;

                int auxx = f[i];
                f[i] = f[j];
                f[j] = auxx;
            }

    int p = 0;
    // Inlocuirea caracterelor din text cu spatii
    text[0] = '\0';
    for (i = 0; i < text_length; i++)
        text[i] = ' ';

    // Afisarea textului decodificat
    for (i = 0; i < matrice_col_length; i++)
        for (j = 0; j < n; j++)
            for (k = 0; k < n; k++)
                if (f[k] == j)
                {
                    if (matrice[i][k] != '\0')
                    {
                        text[p] = matrice[i][k];
                    }
                    p++;
                }
    text[p] = 0;
    // printf("\n");
    printf("%s", text);
    printf("\n");
}

// Functie codificare B
void codificare_B(char text[], char input[])
{
    char cheie[51];
    int i, j, text_length, cheie_nr;

    // Extragere cheie din input
    strcpy(cheie, input + 12);

    // Lungimea cheii
    text_length = strlen(text);

    // Transformare cheie in numar
    cheie_nr = atoi(cheie);

    // Rotirea textului cu cheie_nr pozitii spre dreapta si adaugarea a cheie_nr caractere la codul ASCII
    for (i = 0; i < cheie_nr; i++)
    {
        char aux = text[text_length - 1];
        for (j = text_length - 1; j >= 1; j--)
            text[j] = text[j - 1];
        if (aux != ' ')
            text[0] = add(aux, cheie_nr);
        else
            text[0] = aux;
    }
    printf("%s\n", text);
}

// Functie decodificare B
void decodificare_B(char text[], char input[])
{
    char cheie[51];
    int i, j, text_length, cheie_nr;

    // Extragere cheie din input
    strcpy(cheie, input + 14);

    // Transformare cheie in numar
    cheie_nr = atoi(cheie);

    // Lungimea cheii
    text_length = strlen(text);

    // Rotirea textului cu cheie_nr pozitii spre stanga si scaderea a cheie_nr caractere la codul ASCII
    for (i = 0; i < cheie_nr; i++)
    {
        char aux = text[0];
        for (j = 1; j <= text_length; j++)
            text[j - 1] = text[j];
        if (aux != ' ')
            text[text_length - 1] = subtract(aux, cheie_nr);
        else
            text[text_length - 1] = aux;
    }
    printf("%s\n", text);
}

int main()
{
    char text[501], input[100];

    // Citire text
    scanf("%501[^\n]", text);
    getchar();

    // Citire comenzi pana cand se citeste STOP
    while (1)
    {
        // Citire tip codificare
        scanf("%51[^\n]", input);
        getchar();

        // Daca se citeste STOP se opreste programul
        if (!strcmp(input, "STOP"))
            break;

        if (strstr(input, "CodificareA") != NULL)
            codificare_A(text, input);
        if (strstr(input, "CodificareB") != NULL)
            codificare_B(text, input);
        if (strstr(input, "DecodificareA") != NULL)
            decodificare_A(text, input);
        if (strstr(input, "DecodificareB") != NULL)
            decodificare_B(text, input);
    }
    return 0;
}