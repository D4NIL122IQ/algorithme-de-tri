#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    int i;
    for (i = 0; i < taille; i++)
    {
        tab2[i] = tab1[i];
    }
}

void identique2(int tab0[], int tab1[], int tab2[], int tab3[], int tab4[], int tab5[], int taille)
{
    int i;
    for (i = 0; i < taille; i++)
    {
        tab1[i] = tab0[i];
        tab2[i] = tab0[i];
        tab3[i] = tab0[i];
        tab4[i] = tab0[i];
        tab5[i] = tab0[i];
    }
}

void permutation(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void tri_bulles(int tab[], int taille) // boucle while
{
    int temp;
    int i = taille;
    bool trie = true;
    while (i >= 0)
    {
        for (int j = 1; j <= i; j++)
        {
            if (tab[j - 1] > tab[j])
            {
                temp = tab[j];
                tab[j] = tab[j - 1];
                tab[j - 1] = temp;
            }
        }
        i--;
    }
}

void tri_selction(int tab[], int taille)
{
    int i = taille - 1;
    int j, temp, position, tempo;
    while (i >= 0)
    {
        temp = tab[i];
        tempo = -1;
        for (j = 0; j < i - 1; j++)
        {

            if (tab[j] > temp)
            {
                temp = tab[j];
                position = j;
                tempo = 101;
            }
        }
        if (tempo == 101)
        {
            permutation(&tab[i], &tab[position]);
        }
        i--;
    }
}

void tri_insertion(int tab[], int taille)
{
    int x;
    int j;

    for (int i = 1; i < taille; i++)
    {
        x = tab[i];
        j = i - 1;
        while (j >= 0 && tab[j] > x)
        {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = x;
    }
}

void tri_rapide(int tab[], int debut, int fin)
{
    int i, j, pivot;

    if (debut < fin)
    {
        pivot = debut;
        i = debut;
        j = fin;
        while (i < j)
        {
            while (tab[i] <= tab[pivot] && i < fin)
                i++;
            while (tab[j] > tab[pivot])
                j--;
            if (i < j)
            {
                permutation(&tab[i], &tab[j]);
            }
        }
        permutation(&tab[pivot], &tab[j]);
        tri_rapide(tab, debut, j - 1);
        tri_rapide(tab, j + 1, fin);
    }
}

void tri_fusion(int i, int j, int tab[], int tmp[])
{

    if (j <= i)
    {
        return;
    }

    int m = (i + j) / 2;

    tri_fusion(i, m, tab, tmp);     // trier la moitié gauche récursivement
    tri_fusion(m + 1, j, tab, tmp); // trier la moitié droite récursivement
    int pg = i;                     // pg pointe au début du sous-tableau de gauche
    int pd = m + 1;                 // pd pointe au début du sous-tableau de droite
    int c;                          // compteur
    // on boucle de i à j pour remplir chaque élément du tableau final fusionné
    for (c = i; c <= j; c++)
    {
        if (pg == m + 1)
        { // le pointeur du sous-tableau de gauche a atteint la limite
            tmp[c] = tab[pd];
            pd++;
        }
        else if (pd == j + 1)
        { // le pointeur du sous-tableau de droite a atteint la limite
            tmp[c] = tab[pg];
            pg++;
        }
        else if (tab[pg] < tab[pd])
        { // le pointeur du sous-tableau de gauche pointe vers un élément plus petit
            tmp[c] = tab[pg];
            pg++;
        }
        else
        { // le pointeur du sous-tableau de droite pointe vers un élément plus petit
            tmp[c] = tab[pd];
            pd++;
        }
    }
    for (c = i; c <= j; c++)
    { // copier les éléments de tmp[] à tab[]
        tab[c] = tmp[c];
    }
}

// manU
int main()
{
    int taille = 1000;
    int tab_selec[taille];
    int tab_inser[taille];
    int tab_bulles[taille];
    int tab_fusion[taille];
    int vide[taille];
    int tab_rapide[taille];
    int temp[taille];
    int choix;
    FILE *fichDataTemps = NULL;
    FILE *gnuplotPipe = NULL;

    srand(time(NULL));
    setup_tab(vide, taille);
    do
    {
        do // le menu
        {
            printf("|====================Menu====================|");
            printf("\n|| Taper 1 pour le trie par Selection      ||");
            printf("\n|| Taper 2 pour le trie par insertion      ||");
            printf("\n|| Taper 3 pour le trie a bulles           ||");
            printf("\n|| Taper 4 pour le trie par fusion         ||");
            printf("\n|| Taper 5 pour le trie rapide             ||");
            printf("\n|| Taper 6 pour la creation du fichier csv ||");
            printf("\n|| Taper 7 pour ploter le resultat         ||");
            printf("\n|| Taper 0 pour quitter ||\n");
            printf("--------------------------------------------\n");
            printf("-Votre choix : ");
            scanf("%d", &choix);
        } while (choix < 0 && choix > 5);

        switch (choix)
        {
        case 1:
            printf("\n------------------------Trie par Selection-----------------------\n");
            identique(vide, tab_selec, taille);
            printf(" \n \n ");
            clock_t debut1 = clock(); // debut du compte
            tri_selction(tab_selec, taille);
            clock_t fin1 = clock(); // fin du compte
            affichage(tab_selec, taille);
            double sec1 = (double)(fin1 - debut1) / CLOCKS_PER_SEC; // calcule de difference
            printf("le temps d'execution est de %f secondes\n", sec1);
            printf("\n---------------------------FIN du trie---------------------------\n");
            break;
        case 2:
            printf("\n------------------------Trie par Insertion------------------------\n");
            identique(vide, tab_inser, taille);
            printf(" \n \n ");
            clock_t debut2 = clock(); // debut du compte
            tri_insertion(tab_inser, taille);
            clock_t fin2 = clock();                                 // fin du compte
            double sec2 = (double)(fin2 - debut2) / CLOCKS_PER_SEC; // calcule de difference
            affichage(tab_inser, taille);
            printf("le temps d'execution est de %f secondes\n", sec2);
            printf("\n---------------------------FIN du trie---------------------------\n");
            break;
        case 3:
            printf("\n------------------------Trie a Bulles------------------------\n");
            identique(vide, tab_bulles, taille);
            printf(" \n \n ");
            clock_t debut3 = clock(); // debut du compte
            tri_bulles(tab_bulles, taille);
            clock_t fin3 = clock();                                 // fin du compte
            double sec3 = (double)(fin3 - debut3) / CLOCKS_PER_SEC; // calcule de difference
            affichage(tab_bulles, taille);
            printf("le temps d'execution est de %f secondes\n", sec3);

            printf("\n---------------------------FIN du trie---------------------------\n");
            break;
        case 4:
            printf("\n------------------------Trie par Fusion------------------------\n");
            identique(vide, tab_fusion, taille);
            printf(" \n \n ");
            clock_t debut4 = clock(); // debut du compte
            tri_fusion(0, taille, tab_fusion, temp);
            clock_t fin4 = clock();
            double sec4 = (double)(fin4 - debut4) / CLOCKS_PER_SEC; // calcule de difference
            affichage(tab_fusion, taille);
            printf("le temps d'execution est de %f secondes\n", sec4);
            printf("\n---------------------------FIN du trie---------------------------\n");
            break;
        case 5:
            printf("\n----------------------------Trie Rapide---------------------------\n");
            identique(vide, tab_rapide, taille);
            printf(" \n \n \n \n");
            clock_t debut5 = clock(); // debut du compte
            tri_rapide(tab_rapide, 0, taille);
            clock_t fin5 = clock();                                 // fin du compte
            double sec5 = (double)(fin5 - debut5) / CLOCKS_PER_SEC; // calcule de difference
            affichage(tab_rapide, taille);
            printf("le temps d'execution est de %f secondes\n", sec5);
            printf("\n---------------------------FIN du trie---------------------------\n");
            break;
        case 6:
            fichDataTemps = fopen("donnees_triage.csv", "a"); // ouverture du fichier en mode ajout
            if (fichDataTemps == NULL)
            {
                printf("erreur au niveau du fichier csv");
                return 0;
            }
            else
            {
                fprintf(fichDataTemps, "tailleTab,triSelection,triInsertion,triBulles,triFusion,triRapide\n");
                int debutTaille = taille;
                int finTaille = taille * 10 * 3;
                int pas = 1000;
                int vide[finTaille];
                int tab_selec[finTaille];
                int tab_inser[finTaille];
                int tab_bulles[finTaille];
                int tab_fusion[finTaille];
                int tab_rapide[finTaille];
                int temp[finTaille];
                while (debutTaille <= finTaille) // bouvle pour augmenter la taille du tableau a trier progrisivement
                {

                    setup_tab(vide, debutTaille);
                    identique2(vide, tab_bulles, tab_fusion, tab_inser, tab_rapide, tab_selec, debutTaille);

                    clock_t debut1 = clock();
                    tri_selction(tab_selec, debutTaille);
                    clock_t fin1 = clock();
                    double tempsExeTabSelec = (double)(fin1 - debut1) / CLOCKS_PER_SEC;

                    clock_t debut2 = clock();
                    tri_insertion(tab_inser, debutTaille);
                    clock_t fin2 = clock();
                    double tempsExeTabInser = (double)(fin2 - debut2) / CLOCKS_PER_SEC;

                    clock_t debut3 = clock();
                    tri_bulles(tab_bulles, debutTaille);
                    clock_t fin3 = clock();
                    double tempsExeTabBulles = (double)(fin3 - debut3) / CLOCKS_PER_SEC;

                    clock_t debut4 = clock();
                    tri_fusion(0, taille, tab_fusion, temp);
                    clock_t fin4 = clock();
                    double tempsExeTabFusion = (double)(fin4 - debut4) / CLOCKS_PER_SEC;

                    clock_t debut5 = clock();
                    tri_rapide(tab_rapide, 0, debutTaille);
                    clock_t fin5 = clock();
                    double tempsExeTabRapide = (double)(fin5 - debut5) / CLOCKS_PER_SEC;

                    fprintf(fichDataTemps, "%d,%f,%f,%f,%f,%f\n", debutTaille, tempsExeTabSelec, tempsExeTabInser, tempsExeTabBulles, tempsExeTabFusion, tempsExeTabRapide);
                    debutTaille += pas;
                }
                printf("fichier des donnees en CSV cree.\n");
            }
            fclose(fichDataTemps);
            choix = 7;
            break;
        case 7:
            // cette partie concerne la tracage des graphes
            gnuplotPipe = popen("gnuplot -persistent", "w");

            if (gnuplotPipe != NULL)
            {
                // Charger le fichier CSV et tracer les données
                fprintf(gnuplotPipe, "set terminal png\n");
                fprintf(gnuplotPipe, "set output 'courbe.png'\n");
                fprintf(gnuplotPipe, "set datafile separator ','\n");
                fprintf(gnuplotPipe, "set title 'Temps exécution des algorithmes de tri'\n");
                fprintf(gnuplotPipe, "set xlabel 'Taille du tableau'\n");
                fprintf(gnuplotPipe, "set ylabel 'Temps exécution (s)'\n");
                fprintf(gnuplotPipe, "set key top left\n");
                fprintf(gnuplotPipe, "set grid\n"); // Définir le séparateur de colonnes
                fprintf(gnuplotPipe, "plot 'donnees_triage.csv' using 1:2 with linespoints title 'TriSelection', \
 'donnees_triage.csv' using 1:3 with linespoints title 'TriInsetion', \
 'donnees_triage.csv' using 1:4 with linespoints title 'TriBulles', \
 'donnees_triage.csv' using 1:5 with linespoints title 'TrieFusion',\
 'donnees_triage.csv' using 1:6 with linespoints title 'TrieRapide' \n");

                // Fermer le processus GNUplot
                pclose(gnuplotPipe);
            }
            else // en cas d'erreur du plot
            {
                perror("Erreur lors de l'ouverture de GNUplot");
            }

            return 0;
        case 0:
            printf("---------------------FIN---------------------");
            return 0;
            break;
        default:
            break;
        }
    } while (choix != 0);
}
