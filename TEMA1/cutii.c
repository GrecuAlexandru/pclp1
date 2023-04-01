#include <stdio.h>

// Verifica daca numarul i apartine unui ciclu
void check(int n, int i, int h[501], int box[501], int pr[501])
{
    int j = 1, first = i, k = i;
    while (j <= n)
    {
        h[j] = i; // In h[] stocam istoricul ciclului
        i = box[i];
        j++;
        // Iteram printre cutii pana ajungem la cutia initiala
        // Daca ciclul gasit are lungimea mai mica decat n/2 il consideram ciclu bun
        if (first == i)
        {
            h[j] = i;
            if (j <= (n / 2) + 1)
                pr[k] = 1;
            else
                pr[k] = 2;
            break;
        }
    }
    return;
}

int main()
{
    int n, box[501], ok = 1, i, j, k, history[501][501] = {{0}}, pr[501] = {0};

    // Citire nr prizonieri
    scanf("%d", &n);

    // Citire vector cutii
    for (i = 1; i <= n; i++)
        scanf("%d", &box[i]);

    // Pentru fiecare numar i, verificam daca exista in vreun ciclu precedent
    // Istoricul de cicluri este stocat in matricea history
    // Daca nu exista, verificam daca apartine unui ciclu prin functia check
    for (i = 1; i <= n; i++)
    {
        int ok = 1;
        for (j = 1; j < i; j++)
            for (k = 1; k <= n; k++)
                if (history[j][k] == i)
                    ok = 0;
        if (ok)
            check(n, i, history[i], box, pr);
    }

    // Daca nu exista niciun ciclu bun, jocul este pierdut
    for (i = 1; i <= n; i++)
        if (pr[i] == 2)
        {
            ok = 0;
            break;
        }

    // Afisare rezultat joc
    if (ok)
        printf("Da\n");
    else
        printf("Nu\n");

    // Afisare cicluri
    for (i = 1; i < n; i++)
    {
        // Daca cutia din cutia i incepe un ciclu, il afisam
        if (history[i][1] != 0)
        {
            if (history[i][2] == history[i][1])
                printf("%d", history[i][1]);
            else
                printf("%d ", history[i][1]);

            j = 2;
            while (history[i][j] != history[i][1])
            {
                if (history[i][j + 1] == history[i][1])
                    printf("%d", history[i][j]);
                else
                    printf("%d ", history[i][j]);
                j++;
            }

            printf("\n");
        }
    }
}