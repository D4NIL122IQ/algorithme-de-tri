#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void setup_tab(int tab[], int tai)
{
    int i;
    for (i = 0; i < tai; i++)
    {
        tab[i] = rand() % 100;
    }
}

void affichage(int tab[], int taille)
{
    for (int i = 0; i < taille; i++)
    {
        if ((i) % 10 == 0)
        {
            printf("|\n");
        }
        printf("| %d | ", tab[i]);
        if (tab[i] / 10 == 0)
            printf(" ");
    }
    printf("|\n");
}

void identique(int tab1[], int tab2[], int taille)
{
    for (int i = 0; i < taille; i++)
    {
        tab2[i] = tab1[i];
    }
}

void triComptage(int tab[], int tai)
{
    int tem[tai];
    int tabPosition[tai];
    int i, j, c;

    for (i = 0; i < tai; i++)
    {
        c = 0;
        for (j = 0; j < tai; j++)
        {
            if (tab[i] > tab[j])
            {
                c++;
            }
        }
        tabPosition[i] = c;
    }

    for (i = 0; i < tai; i++)
    {
        j = tabPosition[i];
        tem[j] = tab[i];
    }
    identique(tem, tab, tai);
}

int main()
{
    int taille = 10;
    int rep = 1;
    int tabComptage[taille];
    int temp[taille];

    srand(time(NULL));
    setup_tab(temp, taille);
    do
    {
        switch (rep)
        {
        case 1:
            identique(temp, tabComptage, taille);
            clock_t debut = clock();
            triComptage(tabComptage, taille);
            clock_t fin = clock();
            double resultat1 = (double)(fin - debut) / CLOCKS_PER_SEC;
            affichage(tabComptage, taille);
            printf("temps d'execution du tri comptageb : %f s", resultat1);
            rep = 0;
            break;

        default:
            break;
        }
    } while (rep != 0);

    return 0;
}