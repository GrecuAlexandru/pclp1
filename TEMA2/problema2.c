#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


// Structura pentru un cuvant din dictionar
struct dictionary_entry
{
    char *word;
    int priority;
};


// Functie care verifica daca un cuvant din dictionar este cel mai bun match
char *check_best(char *entry_text, char *dict_word, int best_match_int, int *best_priority, struct dictionary_entry **dictionary, int n_dictionary)
{
    char best_match[21];
    int i;

    // Asumam ca primul cuvant care se potriveste este cel mai bun match
    strcpy(best_match, dict_word);

    // Parcurgem dictionarul si verificam daca exista un cuvant care se potriveste mai bine
    for (i = 0; i < n_dictionary; i++)
    {

        // Verificam daca cuvantul din dictionar incepe cu textul introdus de user
        char *s = strstr((*dictionary)[i].word, entry_text);
        if (s != NULL)
        {
            int s_pos = s - (*dictionary)[i].word;
            if (s_pos == 0)
            {
                // Verificam daca cuvantul din dictionar are prioritate mai mare decat cel mai bun match
                if((*dictionary)[i].priority > *best_priority)
                {
                    // Daca prioritatea este mai mare, actualizam cuvantul, prioritatea si pozitia
                    *best_priority = (*dictionary)[i].priority;
                    best_match_int = i;
                    strcpy(best_match, (*dictionary)[i].word);
                }
                else if((*dictionary)[i].priority == *best_priority)
                {
                    // Daca prioritatea este egala, verificam daca cuvantul din dictionar este mai mic lexicografic
                    if(strcmp((*dictionary)[i].word, best_match) < 0)
                    {
                        // Daca cuvantul din dictionar este mai mic, actualizam cuvantul, prioritatea si pozitia
                        *best_priority = (*dictionary)[i].priority;
                        best_match_int = i;
                        strcpy(best_match, (*dictionary)[i].word);
                    }
                }
            }
        }
    }
    // Incrementam prioritatea cuvantului cel mai bun match
    (*dictionary)[best_match_int].priority++;

    // Returnam cel mai bun match
    char *best_match_final = (char *)malloc((strlen(best_match) + 1) * sizeof(char));
    strcpy(best_match_final, best_match);
    return best_match_final;
}

// Functie care adauga un cuvant in dictionar
void adaugare(char *word, struct dictionary_entry **dictionary, int *n_dictionary)
{
    // Realocam inca un spatiu de memorie pentru noul cuvant
    *dictionary = realloc(*dictionary, (*n_dictionary + 1) * sizeof(struct dictionary_entry));

    // Alocam memorie pentru cuvantul nou
    (*dictionary)[*n_dictionary].word = (char *)malloc((strlen(word) + 1) * sizeof(char));

    // Copiem cuvantul in dictionar
    strcpy((*dictionary)[*n_dictionary].word, word);

    // Setam prioritatea cuvantului la 1
    (*dictionary)[*n_dictionary].priority = 1;

    // Incrementam numarul de cuvinte din dictionar
    (*n_dictionary)++;
}

// Functie care cauta un cuvant in dictionar
char *cautare(char *entry_text, struct dictionary_entry **dictionary, int *n_dictionary)
{
    int i;

    // Daca cuvantul se termina cu *, stergem steluta si adaugam cuvantul in dictionar daca nu este deja
    if (entry_text[strlen(entry_text) - 1] == '*')
    {
        // Stergem steluta
        entry_text[strlen(entry_text) - 1] = '\0';

        // Verificam daca cuvantul este deja in dictionar
        for(i=0;i<*n_dictionary;i++)
        {
            if(strcmp((*dictionary)[i].word, entry_text) == 0)
            {
                // Daca este, ii incrementam prioritatea
                (*dictionary)[i].priority++;
                return entry_text;
            }
        }
        // Daca nu este, il adaugam in dictionar
        adaugare(entry_text, &(*dictionary), &(*n_dictionary));
        return entry_text;
    }


    int best_priority = 0;

    // Parcurgem dictionarul si cautam cuvintele care incep cu textul introdus de user
    for (i = 0; i < *n_dictionary; i++)
    {
        char *s = strstr((*dictionary)[i].word, entry_text);
        if (s != NULL)
        {
            int s_pos = s - (*dictionary)[i].word;
            if (s_pos == 0)
            {
                // Daca gasim un cuvant care incepe cu textul introdus de user, verificam daca este cel mai bun match si returnam rezutatul
                char *dict_word = (*dictionary)[i].word;
                best_priority = (*dictionary)[i].priority;
                char *best_match = check_best(entry_text, dict_word,i, &best_priority, &(*dictionary), *n_dictionary);
                return best_match;
            }
        }
    }
    // Daca cuvantul nu exista in dictionar, il adaugam
    adaugare(entry_text, &(*dictionary), &(*n_dictionary));
    return entry_text;
}

int main()
{
    int n_dictionary, n_entry, i;
    char aux[21], entry_text[21];

    // Citire nr de cuvinte din dictionar
    scanf("%d", &n_dictionary);

    // Alocare memorie pentru dictionar
    struct dictionary_entry *dictionary = (struct dictionary_entry *)malloc(n_dictionary * sizeof(struct dictionary_entry));
    
    // Citire cuvinte din dictionar si alocare memorie pentru fiecare cuvant
    for (i = 0; i < n_dictionary; i++)
    {
        scanf("%s", aux);
        dictionary[i].word = (char *)malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(dictionary[i].word, aux);
        dictionary[i].priority = 0;
    }

    // Citire nr de cuvinte introdus de user
    scanf("%d", &n_entry);

    // Citeste fiecare cuvant si apeleaza functia cautare pentru autocomplete
    for (i = 0; i < n_entry; i++)
    {
        scanf("%s", entry_text);
        printf("%s ", cautare(entry_text, &dictionary, &n_dictionary));
    }
    return 0;
}