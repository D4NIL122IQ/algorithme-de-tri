#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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

void permutation(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
void triComptage(int tab[], int tai)
{
    int tem[tai];
    int tabPosition[tai];
    int i, j, c;

    affichage(tab, tai);
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
    affichage(tabPosition, tai);

    for (i = 0; i < tai; i++)
    {
        c = 0;
        while (tabPosition[c] != i)
        {
            c++;
        }
        tem[i] = tab[c];
    }
    identique(tem, tab, tai);
}

void triPairImpair(int tab[], int taille)
{
    bool tri = false;
    int i;
    int temp;
    while (tri == false)
    {
        tri = true;
        i = 0;
        while (i < taille - 1)
        {
            if (tab[i] > tab[i + 1])
            {
                temp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = temp;
                tri = false;
            }
            i += 2;
        }
        i = 1;
        while (i < taille - 1)
        {
            if (tab[i] > tab[i + 1])
            {
                temp = tab[i];
                tab[i] = tab[i + 1];
                tab[i + 1] = temp;
                tri = false;
            }
            i += 2;
        }
    }
}
int main()
{
    int taille = 10;
    int rep = 2;
    int choix;
    int tabComptage[taille];
    int temp[taille];
    int tabPi[taille];

    srand(time(NULL));
    setup_tab(temp, taille);
    do
    {
        printf("1. pour le tri comptage\n");
        printf("2. pour le tri pair-impair\n");
        printf("votre choix : ");
        scanf("%d", &choix);
        switch (choix)
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

        case 2:
            identique(temp, tabPi, taille);
            clock_t debut2 = clock();
            triPairImpair(tabPi, taille);
            clock_t fin2 = clock();
            double resultat2 = (double)(fin - debut) / CLOCKS_PER_SEC;
            affichage(tabPi, taille);
            printf("temps d'execution du tri pair impair : %f s", resultat1);
            rep = 0;
            break;

        default:
            break;
        }
    } while (rep != 0);

    return 0;
}