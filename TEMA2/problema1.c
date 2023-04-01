#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Functie pentru verificarea unui singur cuvant
int single_word_check(char *text, char *word, int *is_first_word, int word_positions[], int word_count, int start_end_positions[101], int *SEP_count_1)
{
    int SEP_count = *SEP_count_1;
    int MATCH = 0, i,j;
    char keywords[20][20] = {"for",
                             "from",
                             "in",
                             "is",
                             "unit",
                             "or",
                             "while",
                             "int",
                             "float",
                             "double",
                             "string"};
    // Itereaza prin toate cuvintele din keywords
    for (i = 0; i < 11; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
        {
            // Cuvantul se potriveste cu un keyword
            MATCH = 1;
            char *word_aux, search_word[100];

            // Creez un search_word care contine keyword-ul si un spatiu inainte si dupa acesta (pentru a nu se confunda cu cuvintele care contin keyword-ul)
            strcpy(search_word, keywords[i]);
            if (*is_first_word)
                strcat(search_word, " "); // Daca este primul cuvant din text, adaug un spatiu la sfarsit, altfel, adaug si in fata
            else
            {
                strcat(search_word, "  ");
                for (j = strlen(search_word) - 1; j > 0; j--)
                    search_word[j] = search_word[j - 1];
                search_word[0] = ' ';
            }

            // Caut pozitia cuvantului in text si o salvez
            if (word_count == 0)
                word_aux = strstr(text, search_word);
            else
                word_aux = strstr(text + word_positions[word_count - 2], search_word);
            if (word_aux == NULL)
            {
                search_word[strlen(search_word) - 1] = '\0';
                word_aux = strstr(text + word_positions[word_count - 2], search_word);
            }

            if (*is_first_word)
            {
                // Salvez pozitia la care incepe cuvantul (pentru subliniere)
                start_end_positions[SEP_count] = word_aux - text;
                SEP_count += 1;
                // Salvez pozitia la care se termina cuvantul (pentru subliniere)
                start_end_positions[SEP_count] = word_aux - text + (int)strlen(word) - 1;
                SEP_count += 1;
            }
            else
            {
                // Salvez pozitia la care incepe cuvantul (pentru subliniere)
                start_end_positions[SEP_count] = word_aux + 1 - text;
                SEP_count += 1;
                // Salvez pozitia la care se termina cuvantul (pentru subliniere)
                start_end_positions[SEP_count] = word_aux + 1 - text + (int)strlen(word) - 1;
                SEP_count += 1;
            }
        }
    }
    *SEP_count_1 = SEP_count;
    *is_first_word = 0;
    return MATCH;
}

int check(char *text, int start_end_positions[101], int *SEP_count_1)
{
    int MATCH = 0, i,j, is_first_word = 1, SEP_count = 0, word_positions[101] = {0}, word_count = 0, word_last_letter_pos;
    char *aux_text, save_first_word[100];

    // Copiez textul intr-un auxiliar pentru a putea folosi functia strstr
    aux_text = malloc(strlen(text) + 1);
    strcpy(aux_text, text);

    // Trec prin fiecare cuvant din text
    char *p = strtok(text, " ");
    while (p)
    {
        char *word_pos_aux;

        // Caut pozitie cuvantului in text
        if (word_count == 0)
            word_pos_aux = strstr(aux_text, p);
        else
            word_pos_aux = strstr(aux_text + word_positions[word_count - 1] + 1, p);

        word_last_letter_pos = word_pos_aux - aux_text + strlen(p) - 1;

        // Salvez pozitia ultimei litere din cuvant
        word_positions[word_count] = word_last_letter_pos;
        word_count++;

    gohere: ;

        char keywords[20][20] = {"first",
                                 "of", 
                                 "for", 
                                 "each", 
                                 "list", 
                                 "of", 
                                 "is", 
                                 "a",
                                 "for",
                                 "from",
                                 "in",
                                 "is",
                                 "unit",
                                 "or",
                                 "while",
                                 "int",
                                 "float",
                                 "double",
                                 "string"};

        // Verific daca cuvantul curent se gaseste in keywords
        for (i = 0; i < 19; i++)
        {

            if (i==0 || i==2 || i== 4 || i==6)
            {
                // Keyword contine spatiu
                char *k = malloc(strlen(keywords[i]) + 1);
                strcpy(k, keywords[i]);
                // Verific daca primul cuvant din keyword este egal cu cuvantul curent
                if (strcmp(k, p) == 0)
                {
                    // Primul cuvant din keyword este egal cu cuvantul curent
                    char *first_word;

                    // Caut pozitia si lungimea primului cuvant din keyword in text si le salvez
                    if (is_first_word)
                        first_word = strstr(aux_text, p);
                    else
                        first_word = strstr(aux_text + word_positions[word_count - 2], p);
                    int first_word_pos = first_word - aux_text;
                    strcpy(save_first_word, p);

                    // Trec la al doilea cuvant din keyword
                    i++;
                    k = realloc(k, strlen(keywords[i]) + 1);
                    strcpy(k, keywords[i]);
                    p = strtok(NULL, " ");

                    // Daca cuvantul curent este ultimul din text, verific daca acesta se potriveste cu vreun cuvant din keywords
                    if (p == NULL)
                    {
                        MATCH += single_word_check(aux_text, save_first_word, &is_first_word, word_positions, word_count, start_end_positions, &SEP_count);
                        break;
                    }

                    // Verific daca al doilea cuvant din keyword este egal cu cuvantul curent
                    if (strcmp(k, p) == 0)
                    {
                        // Al doilea cuvant din keyword este egal cu cuvantul curent => S-a gasit o secventa de 2 cuvinte consecutive

                        // Caut pozitia si lungimea celui de-al doilea cuvant din keyword in text si le salvez
                        char *second_word = strstr(aux_text + word_positions[word_count - 1], p);
                        int second_word_pos = second_word - aux_text;
                        int second_word_len = strlen(p);

                        // Salvez pozitila la care incepe primul cuvant (pentru subliniere)
                        start_end_positions[SEP_count] = first_word_pos;
                        SEP_count += 1;

                        // Salvez pozitia la care se termina al doilea cuvant (pentru subliniere)
                        start_end_positions[SEP_count] = second_word_pos + second_word_len - 1;
                        SEP_count += 1;

                        MATCH += 1;

                        // Salvez pozitia ultimei litere din cuvant pentru a nu mai cauta inainte acesteia cu strstr
                        word_positions[word_count] = second_word_pos + second_word_len - 1;
                        word_count++;
                    }
                    else
                    {
                        // Primul cuvant din secventa se potriveste, dar al doilea nu se potriveste

                        // Verific primul cuvant separat folosind variabila auxiliara save_first_word
                        MATCH += single_word_check(aux_text, save_first_word, &is_first_word, word_positions, word_count, start_end_positions, &SEP_count);

                        // Salvez pozitia ultimei litere din cuvant
                        char *word_pos_aux;
                        word_pos_aux = strstr(aux_text + word_positions[word_count - 2], save_first_word);
                        word_last_letter_pos = word_pos_aux - aux_text + strlen(p) - 1;
                        word_positions[word_count] = word_last_letter_pos;
                        word_count++;

                        // In p am salvat al doilea cuvant din keyword, deci trebuie sa il verific de la inceput
                        goto gohere;
                    }
                }
            }
            else if(i!=1 && i!=3 && i!=5 && i!=7)
            {
                // Keyword nu contine spatiu
                if (strcmp(p, keywords[i]) == 0)
                {
                    // Cuvantul se potriveste cu un keyword
                    MATCH += 1;

                    // Creez un search_word care contine keyword-ul si un spatiu inainte si dupa acesta (pentru a nu se confunda cu cuvintele care contin keyword-ul)
                    char *word_aux, search_word[100];
                    strcpy(search_word, keywords[i]);
                    if (is_first_word)
                        strcat(search_word, " "); // Daca este primul cuvant din text, adaug un spatiu la sfarsit, altfel, adaug si in fata
                    else
                    {
                        strcat(search_word, "  ");
                        for (j = strlen(search_word) - 1; j > 0; j--)
                            search_word[j] = search_word[j - 1];
                        search_word[0] = ' ';
                    }

                    // Caut pozitia cuvantului in text si o salvez
                    if (word_count == 0)
                        word_aux = strstr(aux_text, search_word);
                    else
                        word_aux = strstr(aux_text + word_positions[word_count - 2], search_word);
                    if (word_aux == NULL)
                    {
                        search_word[strlen(search_word) - 1] = '\0';
                        word_aux = strstr(aux_text + word_positions[word_count - 2], search_word);
                    }

                    if (is_first_word)
                    {
                        // Salvez pozitia la care incepe cuvantul (pentru subliniere)
                        start_end_positions[SEP_count] = word_aux - aux_text;
                        SEP_count += 1;
                        // Salvez pozitia la care se termina cuvantul (pentru subliniere)
                        start_end_positions[SEP_count] = word_aux - aux_text + (int)strlen(p) - 1;
                        SEP_count += 1;
                    }
                    else
                    {
                        // Salvez pozitia la care incepe cuvantul (pentru subliniere)
                        start_end_positions[SEP_count] = word_aux + 1 - aux_text;
                        SEP_count += 1;
                        // Salvez pozitia la care se termina cuvantul (pentru subliniere)
                        start_end_positions[SEP_count] = word_aux + 1 - aux_text + (int)strlen(p) - 1;
                        SEP_count += 1;
                    }
                }
            }
        }
        // Trec la urmatorul cuvant din text
        p = strtok(NULL, " ");

        is_first_word = 0;
    }
    *SEP_count_1 = SEP_count;
    return MATCH;
}

// Functie pentru sublinierea cuvintelor
void make_underline_line(char *text, int start_end_positions[101], int SEP_count)
{
    int i, j;
    // Aloca memorie pentru linia de subliniere
    char *highlight_line = malloc((strlen(text) + 1));
    // Afisez textul introdus
    printf("%s\n", text);
    // Umplu linia de subliniere cu spatii
    for (i = 0; i < strlen(text); i++)
    {
        highlight_line[i] = ' ';
    }
    // Inlocuiesc spatiile cu _ in functie de start_end_positions[] pentru a sublinia cuvintele
    for (i = 0; i < SEP_count - 1; i += 2)
    {
        for (j = start_end_positions[i]; j <= start_end_positions[i + 1]; j++)
        {
            highlight_line[j] = '_';
        }
    }
    // Afisez linia de subliniere
    printf("%s\n", highlight_line);
}

int main()
{
    int i, n, SEP_count = 0;
    char aux[501];

    // Cititre numar linii
    scanf("%d", &n);
    getchar();

    // Alocare memorie pentru text
    char **text = (char **)malloc(n * sizeof(char *));

    // Citeste fiecare rand, il salveaza in text[i] si aloca memorie pentru el
    for (i = 0; i < n; i++)
    {

        scanf("%[^\n]", aux);
        getchar();
        aux[strlen(aux)] = '\0';
        text[i] = malloc((strlen(aux) + 1));
        strcpy(text[i], aux);
    }

    // Verifica fiecare linie
    for (i = 0; i < n; i++)
    {
        // Vector cu pozitiile de start si end ale cuvintelor ce trebuie subliniate
        int start_end_positions[101] = {0};

        // Contor pentru cate inceputuri si sfarsituri de cuvinte am gasit (2 * numar cuvinte ce trebuie subliniate)
        SEP_count = 0;

        char *aux_text = malloc(strlen(text[i]) + 1);
        strcpy(aux_text, text[i]);

        // Verifica daca linia contine cuvinte cheie. Daca contine, le subliniaza, altfel, afiseaza linia goala
        if (check(text[i], start_end_positions, &SEP_count) != 0)
        {
            make_underline_line(aux_text, start_end_positions, SEP_count);
        }
        else
        {
            printf("%s\n", aux_text);
            int i;
            char *highlight_line = malloc((strlen(aux_text) + 1));
            for (i = 0; i < strlen(aux_text); i++)
            {
                highlight_line[i] = ' ';
            }
            printf("%s\n", highlight_line);
        }
    }
    return 0;
}