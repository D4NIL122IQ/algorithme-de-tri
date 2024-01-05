#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct noeud
{
    int val;
    struct noeud *fd;
    struct noeud *fg;
} noeud;

typedef noeud arbre;

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

void affichageArbre(arbre *racine, char caaa)
{
    if (racine != NULL)
    {
        printf("%c __%d__", caaa, racine->val);
        affichageArbre(racine->fg, 'g');
        affichageArbre(racine->fd, 'd');
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

arbre *CreationNoeud(int val)
{
    arbre *new = malloc(sizeof(arbre));
    new->val = val;
    new->fd = new->fg = NULL;
    return new;
}

arbre *CreationABR(arbre *ABR, int val)
{
    if (ABR == NULL)
    {
        ABR = CreationNoeud(val);
    }
    else
    {
        if (val < ABR->val)
        {
            if (ABR->fg == NULL)
            {
                ABR->fg = CreationNoeud(val);
            }
            else
            {
                CreationABR(ABR->fg, val);
            }
        }
        else
        {
            if (ABR->fd == NULL)
            {
                ABR->fd = CreationNoeud(val);
            }
            else
            {
                CreationABR(ABR->fd, val);
            }
        }
    }
    return ABR;
}

arbre *TransformationABR(arbre *ABR, int tab[], int i, int taille)
{
    if (i < taille)
    {
        ABR = CreationABR(ABR, tab[i]);
        TransformationABR(ABR, tab, i + 1, taille);
    }

    return ABR;
}

int indice = 0;

void infixeINtab(arbre *ABR, int tab[])
{
    if (ABR != NULL)
    {
        infixeINtab(ABR->fg, tab);
        tab[indice] = ABR->val;
        indice += 1;
        infixeINtab(ABR->fd, tab);
    }
}

void triArborescent(int tab[], int taille)
{
    arbre *racineABR = NULL;

    racineABR = TransformationABR(racineABR, tab, 0, taille);
    infixeINtab(racineABR, tab);
}

int main()
{
    int taille = 10;
    int rep = 2;
    int choix;
    int tabComptage[taille];
    int temp[taille];
    int tabPi[taille];
    int tabArbre[taille];

    srand(time(NULL));
    setup_tab(temp, taille);
    do
    {
        printf("1. pour le tri comptage\n");
        printf("2. pour le tri pair-impair\n");
        printf("3. pour le tri arborescent\n");
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

        case 3:
            identique(temp, tabArbre, taille);
            clock_t debut3 = clock();
            triArborescent(tabArbre, taille);
            clock_t fin3 = clock();
            double resultat3 = (double)(fin - debut) / CLOCKS_PER_SEC;
            affichage(tabArbre, taille);
            printf("temps d'execution du tri pair impair : %f s", resultat1);
            rep = 0;
            break;
        default:
            break;
        }
    } while (rep != 0);

    return 0;
}