#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Functie ce transforma un numar din baza 10 in baza 2
// Parametrii: vectorul ce contine numarul in baza 10, numarul de cifre ale numarului
int binary_to_decimal(int binary[5], int n)
{
    int i,decimal=0;
    for(i=n-1;i>=0;i--)
    {
        decimal += binary[i] * pow(2,n-1-i);
    }
    return decimal;
}

// Functie pentru adunarea a doua numere in baza 10 (a si b)
void adunare(int rez[5],  int a[5], int b[5])
{
    int i,rest=0;
    // Parcurgem vectorii de la dreapta la stanga si ne folosim de un rest pentru a calcula suma acestora
    for(i=3;i>=0;i--)
    {
        rez[i] = (a[i] + b[i] + rest)%2;
        rest =  (a[i] + b[i] + rest)/2;
    }
}

// Functie pentru interschimbare
void interschimbare(int rez[5], int a[5], int b[5])
{
    int pos1,pos2,p1[2],p2[2],i;

    // Calculam pozitiile pe care trebuie sa le interschimbam
    p1[0] = b[0];
    p1[1] = b[1];
    p2[0] = b[2];
    p2[1] = b[3];

    // Transformam pozitiile din baza 10 in baza 2
    pos1 = binary_to_decimal(p1,2);
    pos2 = binary_to_decimal(p2,2);

    // Interschimbam valorile
    int aux = a[pos1];
    a[pos1] = a[pos2];
    a[pos2] = aux;

    // Copiem rezultatul in vectorul rez
    for(i=0;i<4;i++)
        rez[i] = a[i];
}

// Functie pentru rotire
void rotire(int rez[5], int a[5], int b[5])
{
    int i;
    // Transformam numarul b din baza 10 in baza 2 pentru a rotii vectorul a de atatea ori
    for(i=0;i<binary_to_decimal(b,4);i++)
    {
        // Rotim vectorul a spre stanga
        int aux = a[0];
        a[0] = a[1];
        a[1] = a[2];
        a[2] = a[3];
        a[3] = aux;
    }

    // Copiem rezultatul in vectorul rez
    for(i=0;i<4;i++)
        rez[i] = a[i];
}

// Functie pentru xor
void xor(int rez[5], int a[5], int b[5])
{
    int i;
    // Parcurgem vectorii si facem operatia xor
    // Daca vectorii sunt diferiti, rezultatul va fi 1, altfel 0
    for(i=0;i<4;i++)
        rez[i] = a[i] != b[i] ? 1 : 0;
}

// Functie pentru transformarea unui numar din baza 2 in baza 10
void to_binary(int rez[33],unsigned int nr, int nr_operatii)
{
    int i=0,aux[33],j,k=0;

    // Parcurgem numarul si il transformam in baza 10, salvandu-l intr-un vector
    // Salvam doar primii nr_operatii*6+4 biti
    while(nr != 0 && i<(nr_operatii*6)+4)
    {
        aux[i] = nr % 2;
        nr /= 2;
        i++;
    }

    // Copiem vectorul aux in vectorul rez, dar invers, pentru a ajunge la transformarea corecta in baza 10
    for(j=i-1;j>=0;j--)
    {
        rez[k] = aux[j];
        k++;
    }
}

// Functie pentru descompunerea unui numar in operatii
void descompunere(unsigned int nr, int nr_operatii)
{
    int a[5], b[5],binary_nr[33], rez[5];
    int i,j,k=4,first=1;
    char op[3];

    void (*operatie[4])(int *,int *,int *) = {adunare,interschimbare,rotire,xor};

    // Transformam numarul in baza 10
    to_binary(binary_nr,nr, nr_operatii);

    // Daca numarul de operatii introdus este 0, afisam primii 4 biti ai numarului in baza 2
    if(nr_operatii == 0)
    {
        printf("%d",binary_to_decimal(binary_nr,4));
        return;
    }

    // Salvam primii 4 biti ai numarului in vectorul a
    for(j=0;j<4;j++)
        a[j] = binary_nr[j];
    
    // Pentru fiecare operatie, salvam urmatorii 2 biti in op si urmatorii 4 biti in vectorul b
    for(i=0;i<nr_operatii;i++)
    {
        // Daca nu este prima operatie, copiem rezultatul de la calculul precedent in vectorul a
        if(!first)
            for(j=0;j<4;j++)
            {
                a[j] = rez[j];
            }

        // Salvam urmatorii 2 biti in op pentru a ii folosii ca sir de caractere
        op[0] = binary_nr[k] + '0';
        op[1] = binary_nr[k+1] + '0';
        op[2] = '\0';

        // Salvam urmatorii 4 biti in vectorul b
        for(j=k+2;j<k+6;j++)
        {
            b[j-k-2] = binary_nr[j];
        }

        // Daca op este 00, apelam functia adunare
        if(strcmp(op,"00") == 0)
            (*operatie[0])(rez,a,b);
        // Daca op este 01, apelam functia interschimbare
        else if(strcmp(op,"01") == 0)
            (*operatie[1])(rez,a,b);
        // Daca op este 10, apelam functia rotire
        else if(strcmp(op,"10") == 0)
            (*operatie[2])(rez,a,b);
        // Daca op este 11, apelam functia xor
        else if(strcmp(op,"11") == 0)
            (*operatie[3])(rez,a,b);
        
        // Incrementam k cu 6 pentru a trece la urmatoarea operatie
        k=k+6;
        first = 0;
    }
    // Afisam rezultatul
    printf("%d",binary_to_decimal(rez,4));
}


int main()
{
    int nr_operatii;
    unsigned int nr;

    // Citim numarul de operatii si numarul
    scanf("%d", &nr_operatii);
    scanf("%u", &nr);

    // Descompunem numarul si facem calculele
    descompunere(nr, nr_operatii);

    return 0;
}