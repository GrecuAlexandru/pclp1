#include <stdio.h>
#include <string.h>
#include <math.h>

// Initializare functii pentru adunare si scadere
void add(int rez[], int a[], int b[], int *rez_sign, int a_sign, int b_sign, int n);
void subtract(int rez[], int a[], int b[], int *rez_sign, int a_sign, int b_sign, int n);

// Functie pentru transformarea unui sir de caractere intr-un vector de intregi
void char_to_array(char ch[], int array[])
{
    int n = strlen(ch);
    for (int i = 0; i < n; i++)
        array[i] = (int)(ch[i] - '0');
}

// Functie pentru obtinerea semnului partii reale din numar
void get_sign_real(int x_array[], int *x_sign)
{
    *x_sign = x_array[0];
}

// Functie pentru obtinerea semnului partii imaginare din numar
void get_sign_img(int x_array[], int *x_sign, int n)
{
    *x_sign = x_array[(n - 1) / 2];
}

// Functie pentru obtinerea partii reale din numar
// Partea reala se obtine din vectorul x_array, de la pozitia 1 pana la pozitia (n-1)/2-1 inclusiv
void get_real(int x_array[], int a_real[], int n)
{
    int i;
    for (i = 1; i <= ((n - 1) / 2) - 1; i++)
        a_real[i - 1] = x_array[i];
}
// Functie pentru obtinerea partii imaginare din numar
// Partea imaginara se obtine din vectorul x_array, de la pozitia (n-1)/2+1 pana la pozitia n-1 inclusiv
void get_img(int x_array[], int a_real[], int n)
{
    int i, k = 0;
    for (i = ((n - 1) / 2) + 1; i <= n - 1; i++)
    {
        a_real[k] = x_array[i];
        k++;
    }
}

// Functie pentru adunare
void add(int rez[], int a[], int b[], int *rez_sign, int a_sign, int b_sign, int n)
{
    // Initializam vectorul rez cu 0
    for (int i = 0; i < n - 1; i++)
        rez[i] = 0;

    // In functie de semnele vectorilor a si b, se urmeaza 4 cazuri
    // Cazul 1: a negativ si b pozitiv -> -a + b = b - a (apelam scaderea lui b din a)
    if (a_sign == 1 && b_sign == 0)
    {
        subtract(rez, b, a, rez_sign, 0, 0, n);
    }
    // Cazul 2: a negativ si b negativ -> -a + (-b) = -(a + b) (apelam adunarea lui a si b si semnul rezultatului este negativ)
    else if (a_sign == 1 && b_sign == 1)
    {
        // De la pozitia (n-3)/2-1 pana la pozitia 0, adunam element cu element vectorii a si b
        // Daca suma este mai mare decat 9, atunci rezultatul va fi suma%10 si vom aduna 1 la elementul de pe pozitia i-1
        for (int i = ((n - 3) / 2) - 1; i >= 0; i--)
        {
            rez[i] += a[i] + b[i];
            if (rez[i] > 9)
            {
                rez[i] = rez[i] % 10;
                rez[i - 1]++;
            }
        }
        // Setam semnul rezultatului ca fiind negativ
        *rez_sign = 1;
    }
    // Cazul 3: a pozitiv si b pozitiv -> a + b = a + b (apelam adunarea lui a si b)
    else if (a_sign == 0 && b_sign == 0) //+ cu +
    {
        for (int i = ((n - 3) / 2) - 1; i >= 0; i--)
        {
            rez[i] += a[i] + b[i];
            if (rez[i] > 9)
            {
                rez[i] = rez[i] % 10;
                rez[i - 1]++;
            }
        }
    }
    // Cazul 4: a pozitiv si b negativ -> a + (-b) = a - b (apelam scaderea lui b din a)
    else
        subtract(rez, a, b, rez_sign, 0, 0, n);
}
// Functie pentru scadere
void subtract(int rez[], int a[], int b[], int *rez_sign, int a_sign, int b_sign, int n)
{
    int ok = 0, k = 0;

    // Initializam vectorul rez cu 0
    for (int i = 0; i < n - 1; i++)
        rez[i] = 0;

    // In functie de semnele vectorilor a si b, se urmeaza 4 cazuri
    // Cazul 1: a pozitiv si b pozitiv -> a - b = a - b (apelam scaderea lui b din a)
    if (a_sign == 0 && b_sign == 0)
    {
        // Daca a este mai mic decat b, atunci vom interschimba valorile lui a si b
        while (!ok && k < n - 1)
        {
            if (a[k] > b[k])
                break;
            if (a[k] < b[k])
            {
                for (int i = 0; i < n - 1; i++)
                {
                    int aux = a[i];
                    a[i] = b[i];
                    b[i] = aux;
                }
                ok = 1;
                *rez_sign = 1;
            }
            k++;
        }
        // De la pozitia (n-3)/2-1 pana la pozitia 0, scadem element cu element vectorii a si b
        // Daca rezultatul este mai mic decat 0, atunci rezultatul va fi 10 + rezultatul si vom scadea 1 de la elementul de pe pozitia i-1
        for (int i = ((n - 3) / 2) - 1; i >= 0; i--)
        {
            rez[i] += a[i] - b[i];
            if (rez[i] < 0)
            {
                rez[i] = 10 + rez[i];
                rez[i - 1]--;
            }
        }
    }
    // Cazul 2: a negativ si b negativ -> -a - (-b) = b - a (apelam scaderea lui b din a)
    else if (a_sign == 1 && b_sign == 1)
    {
        subtract(rez, b, a, rez_sign, 0, 0, n);
    }
    // Cazul 3: a pozitiv si b negativ ->  a - (-b) = a + b (apelam adunarea lui a si b)
    else if (a_sign == 0 && b_sign == 1)
    {
        *rez_sign = 0;
        add(rez, a, b, rez_sign, 0, 0, n);
    }
    // Cazul 4: a negativ si b pozitiv -> -a - b = -(a + b) (apelam adunarea lui a si b si semnul rezultatului este negativ)
    else if (a_sign == 1 && b_sign == 0)
    {
        *rez_sign = 1;
        add(rez, a, b, rez_sign, 0, 0, n);
    }
}
// Functie pentru concatenarea partii reale, imaginare si a semnelor
void make_out_array(int out[], int real[], int img[], int sign_real, int sign_img, int n)
{
    int i, k = 0;
    out[0] = sign_real;
    for (i = 1; i <= ((n - 1) / 2) - 1; i++)
        out[i] = real[i - 1];
    out[(n - 1) / 2] = sign_img;
    for (i = ((n - 1) / 2) + 1; i <= n - 1; i++)
    {
        out[i] = img[k];
        k++;
    }
}

int main()
{
    char a[1001], b[1001];
    int a_array[1001], b_array[1001], out_array[1001], a_sign_real, b_sign_real,
        a_sign_img, b_sign_img, a_real[1001], b_real[1001], a_img[1001], b_img[1001],
        out_real[1001], out_img[1001], out_sign_real, out_sign_img;
    char operatie;
    int N;

    // Citire numar de cifre
    scanf("%d", &N);

    // Citire numar a
    scanf("%s", a);
    getchar();

    // Transformare char a in vector de int
    char_to_array(a, a_array);

    // Ruleaza cat timp nu se introduce 0
    while (1)
    {
        // Citire operatie
        scanf("%c", &operatie);
        getchar();

        // Daca operatia este 0, atunci se iese din program
        if (operatie == '0')
            break;

        // Citire numar b
        scanf("%s", b);
        getchar();

        // Transformare char b in vector de int
        char_to_array(b, b_array);
        // Obtinere semn parte reala si imaginara pentru a si b
        get_sign_real(a_array, &a_sign_real);
        get_sign_real(b_array, &b_sign_real);
        get_sign_img(a_array, &a_sign_img, N);
        get_sign_img(b_array, &b_sign_img, N);

        // Obtinere partea reala si imaginara pentru a si b
        get_real(a_array, a_real, N);
        get_real(b_array, b_real, N);
        get_img(a_array, a_img, N);
        get_img(b_array, b_img, N);

        // Initializare semne rezultat
        out_sign_real = 0;
        out_sign_img = 0;

        // Daca operatia este +, atunci se apeleaza functia de adunare
        if (operatie == '+')
        {
            add(out_real, a_real, b_real, &out_sign_real, a_sign_real, b_sign_real, N);
            add(out_img, a_img, b_img, &out_sign_img, a_sign_img, b_sign_img, N);
        }
        // Daca operatia este -, atunci se apeleaza functia de scadere
        else
        {
            subtract(out_real, a_real, b_real, &out_sign_real, a_sign_real, b_sign_real, N);
            subtract(out_img, a_img, b_img, &out_sign_img, a_sign_img, b_sign_img, N);
        }

        // Concatenare partea reala, imaginara si semne
        make_out_array(out_array, out_real, out_img, out_sign_real, out_sign_img, N);

        // Afisare rezultat
        for (int i = 0; i < N - 1; i++)
            printf("%d", out_array[i]);
        for (int i = 0; i < N - 1; i++)
        {
            a_array[i] = out_array[i];
            out_array[i] = 0;
        }
        printf("\n");
    }
    return 0;
}