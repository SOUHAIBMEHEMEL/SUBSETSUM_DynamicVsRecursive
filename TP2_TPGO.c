#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>


#define max 2000


int E[];        //L'ensemble
int pos = 0;    //var globale qui gère les positions dans la table de tous les ensembles
int Ebit[max];  //Table de bits

int subsetTab_TF[max][max] ; //tableau utilisé pour la programmation dynamique contenant Vrai ou faux (1 ou 0)
int cardmax[max][max] ;      //Tableau contenant la card maximale des sous ensemble qu'on peut constituer à partir de E ayant une somme égale a sum


int NbElmt[] = {10,50,100,500,1000} ; //Taille des ensembles générées à la partie 2
double Sol_Dyn[5], Sol_Rec[5];

struct Ens_Card {
int exist  ;
int card ;
};

/*********************************************************************************************************************/


int main()
{
    long cal = 6000000L;
    clock_t start, finish;
    double duration;
    start = clock();
    while( cal-- );


    int Tab[max];
    int n ,s ,num,nbr_ensembles ;

    printf("\n   /***************************  SubSetSum  ***************************/\n\n");
    printf("\n   /***************************  PARTIE 1  ***************************/\n\n");

    //Récupérer la taille de l'ensemble
    printf("Donner le nombre d'elements de votre ensemble: ") ;
    scanf("%d", &n) ;


    //Récupérer les éléments un par un et remplir la table des bits
    printf("\nIntroduisez les elements : \n") ;
    int i ;
    for (i = 0 ;i< n;i++)
    {   printf("Element[%d] = ",i+1);
        scanf("%d", &num) ;
        E[i] = num ;
        Ebit[i] = 0 ;
    }

    //Affichage de l'ensemble
    afficher_ensemle(E,"E",n) ;


    //Récuerer la somme s
    printf("\nIntroduisez la somme : ") ;
    scanf("%d", &s) ;


    //Trouver les sous ensembles

    // Question 1
    printf("\n        /**********************  Question 1 **********************/\n\n");
    nbr_ensembles=SubSetSum(Tab,n,s);
    if ( nbr_ensembles>= 1){ printf("\nTRUE , Il existe au moins un sous-ensemble de E tq la somme de ses elements est egale a %d",s) ;
        printf("\nNombre des ensembles possibles: %d",nbr_ensembles);
    }
    else
    {
        printf("\n FALSE  Il n'existe aucun sous-ensemble de E tq la somme de ses elements est egale a %d",s) ;

        finish = clock();
        duration = (double)(finish - start) ; // CLOCKS_PER_SEC;
        printf( "%2.4f ms\n", duration );
        goto etiq ;

    }

    //Question2

    printf("\n\n\n        /**********************  Question 2 **********************/\n\n");
    afficher_ensemle(Ebit,"Tab des bits",n) ;
    printf("\n\n  L'ensemle contenant tous les elements de tous les ensembles : \n\t {"  ) ;
    for (i = 0 ; i< n ; i++)
    {
        if (Ebit[i] == 1)
        {
            printf(" %d ",E[i]) ;
        }
    }
    printf("}");

    //Question3

    printf("\n\n\n        /**********************  Question 3 **********************/\n\n");
    printf("\n Les sous ensembles sont :\n") ;
    Afficher_tous_les_ensemble(Tab,pos,s) ;


  etiq :  printf("\n   /***************************  PARTIE 2  ***************************/\n\n");



    printf("\n cardinalite maximale avec programmation dynamique : %d elements" ,Constituer_tableau(n,s)) ;
    struct Ens_Card maximum ;
    SubSetSumMax(n,s,&maximum);
    if (maximum.exist == 1) printf("\n Subsetsum Existe : TRUE  \n cardinalite maximale avec recursivite : %d   elements" , maximum.card ) ;
    else printf("\n Subsetsum Existe : FALSE  \n cardinalite maximale avec recursivite : %d   elements" , maximum.card ) ;
    printf("\n\n TABLE DE SUBSET 1 = TRUE 0=FALSE\n") ;
    Afficher_tableau(subsetTab_TF,n,s+1) ;
    printf("\n TABLE DE CARDINALITE\n") ;
    Afficher_tableau(cardmax,n,s+1) ;

    printf("\n") ;

    contituer_Tableau_comaraison();
    printf("\n   /****************  PARTIE 3: Tableau comparatif  ******************/\n\n");
    printf("\n n ( Taille des Ensembles)    =      10           50           100           500             1000\n\n");
    printf("\n Temps avec Prog Dynamique    =      %2.4f      %2.4f      %2.4f      %2.4f      %2.4f\n\n",Sol_Dyn[0],Sol_Dyn[1],Sol_Dyn[2],Sol_Dyn[3],Sol_Dyn[4]);
    printf("\n Temps avec recursivite       =      %2.4f      %2.4f      %2.4f      %2.4f      %2.4f\n\n",Sol_Rec[0],Sol_Rec[1],Sol_Rec[2],Sol_Rec[3],Sol_Rec[4]);
    printf("\n\n   /******************************************************************/\n");

    finish = clock();
    duration = (double)(finish - start) ;// CLOCKS_PER_SEC;
    printf( "\n Temps d'execution du programme principal:  %2.4f ms\n", duration );
    printf("\n  /*******************************   FIN   *******************************/\n\n");

    return 0;
}
/*********************************************************************************************************************/


//Retourne Vrai si subsetsum(n,s) sinon faux
//Constitue la Table de bits et la table Tab contenant tous les ensembles
int SubSetSum(int Tab[],int n, int s)
{
    int resault,resault1,resault2 ;
    if (s == 0)
    {
        return 1 ; //True
    }
    if (s < 0) return 0 ; //False
    if ((n==0) && (s>0)) return 0 ; //False
    else
    {
        resault1 = SubSetSum(Tab,n-1,s-E[n-1]) ;
        if (resault1 == 1)
        {
            Ebit[n-1] = 1 ;
            Tab[pos] = E[n-1] ;
            pos++ ;
        }
        resault2 = SubSetSum(Tab,n-1,s) ;
        resault =  resault1 + resault2  ;
        if (resault >= 1) return 1 ;
        else return 0 ;
    }
}



/*********************************************************************************************************************/
//Affiche un tableau de lin lignes et col colonnes
void Afficher_tableau(int TABLE[max][max]  , int lin , int col)
{
    int i,j ;
    printf("\n") ;
    for (i=0;i<lin;i++)
    {
        for (j=0;j<col;j++)
        {
            printf("   %d",TABLE[i][j]) ;
        }
        printf("\n") ;
    }
}



/*********************************************************************************************************************/

//Affiche un ensemble nom
void afficher_ensemle(int Ens[],char *nom,int taille)
{
    int j ;
    printf(" %s = { " , nom ) ;
    for (j = 0; j<taille ;j++)
    {
        printf("%d",Ens[j]) ;
        if (j != taille-1) printf(" ,") ;
    }
    printf(" } \n") ;
}


/*********************************************************************************************************************/

//Vérifie si l'élément elmt appartient a l'ensemble Ens
int exist_element(int Ens[],int taille,int elmt)
{
    int i = 0;
    while (i<taille)
    {
        if (Ens[i] == elmt) return 1 ;
        i++ ;
    }
}


/*********************************************************************************************************************/
//Affiche tous les sous ensembles ainsi que l'ensemble optimal
void Afficher_tous_les_ensemble(int T[],int taille,int sum)
{
    int i, j=0 ,k, somme =0 ,nb = 1,cpt=taille;
    int sous_ens[max]  ;
    int Ens_opt[max];
    for (i=0 ; i<taille ; i++)
    {
        somme = somme + T[i] ;
        sous_ens[j] = T[i] ;
        j++ ;
        if (somme == sum)
        {
            printf(" Sous ensemle %d" , nb) ;
            nb++ ;
            afficher_ensemle(sous_ens,"",j) ;

            //Récuerer l'ensemble optimal
            //if(j<cpt)
            //{
            //   for(k=0;k<j;k++){Ens_opt[k]=sous_ens[k];}
            //    cpt=j;
            //}
            j = 0 ;
            somme = 0 ;
        }
    }
    //printf("\n\n\t/********************/\n\n Sous ensemle optimal : ") ;
    //afficher_ensemle(Ens_opt,"",cpt) ;
}

/*********************************************************************************************************************/



int max_elmt (int a, int b)
{
    if (a>b) return a ;
    else return b ;
}



/*********************************************************************************************************************/

/*int SubSetSum(int n, int s)
{
    int resault,resault1,resault2 ;
    if (s == 0)
    {
        return 1 ; //True
    }
    if (s < 0) return 0 ; //False
    if ((n==0) && (s>0)) return 0 ; //False
    else
    {
        resault1 = SubSetSum(n-1,s-E[n-1]) ;
        resault2 = SubSetSum(n-1,s) ;
        resault =  resault1 + resault2  ;
        if (resault >= 1) return 1 ;
        else return 0 ;
    }
} */

/*********************************************************************************************************************/
int Constituer_tableau(int n,int sum)
{
    int i , j ;

	for (i = 0; i < n; i++)
    {
			subsetTab_TF[i][0] = 1;
			cardmax[i][0] = 0;
    }

    for (i = 1; i <= sum; i++)
    {
        if (E[0] == i)
        {
            subsetTab_TF[0][i] = 1;
            cardmax[0][i] = 0;
        }
        else
        {
            subsetTab_TF[0][i] = 0;
            cardmax[0][i] = -1;
        }
    }
    for (i = 1; i < n; i++)
    {
        for (j = 1; j <= sum; j++)
        {
            subsetTab_TF[i][j] = subsetTab_TF[i-1][j];
            cardmax[i][j] = cardmax[i-1][j];
            if (j >= E[i])
            {
                subsetTab_TF[i][j] = max_elmt(subsetTab_TF[i-1][j], subsetTab_TF[i - 1][j - E[i]] );
                if (subsetTab_TF[i][j]==1) cardmax[i][j] = max_elmt(cardmax[i-1][j], cardmax[i - 1][j - E[i]] + 1);
            }
        }
    }

    //Afficher_tableau(subsetTab_TF,n,sum+1) ;
    //Afficher_tableau(cardmax,n,sum+1) ;

    return (cardmax[n-1][sum]+1);

}

/*********************************************************************************************************************/

int SubSetSumMax(int n, int s,struct Ens_Card *result)
{
    //nb est le nombre max d'element
    //retourne vrai ou faux
    struct Ens_Card a ;
    struct Ens_Card b;

    if (s == 0)
    {
        result->card = 0 ;
        result->exist = 1 ;
        return 1 ;
        //True
    }
    if (s < 0)
    {
        result->card= -1 ;
        result->exist = 0 ;
        return 0 ;
         //False
    }
    if ((n==0) && (s>0))
    {
        result->card = -1 ;
        result->exist = 0 ;
        return 0 ;
         //False
    }
    else
    {
         SubSetSumMax(n-1,s-E[n-1],&a) ;
        if (a.exist == 1 )
        {
            a.card++ ;
        }

        SubSetSumMax(n-1,s,&b) ;


        int maxab  = max_elmt( a.card , b.card ) ;

        if ( maxab == a.card)
        {
            result->card = a.card ;
            result->exist = a.exist ;
        }
        else
        {
            result->card = b.card ;
            result->exist = b.exist;
        }
        if(result->exist == 1) return 1 ;
        else return 0 ;

    }
}

/*********************************************************************************************************************/

double Temps_solution_dynamique_MaxEns(int n,int s)
{
    long cal = 6000000L;
    clock_t start, finish;
    start = clock();
    while( cal-- );
    Sleep(10);
    Constituer_tableau(n,s) ;

    finish = clock();
    return ((double)(finish - start)); // CLOCKS_PER_SEC);


}

/*********************************************************************************************************************/

double Temps_solution_recursive_MaxEns(int n,int s)
{
    long cal = 6000000L;
    clock_t start, finish;
    start = clock();
    while( cal-- );

    struct Ens_Card maximum ;
    SubSetSumMax(n,s,&maximum);

    finish = clock();
    return ((double)(finish - start)); // CLOCKS_PER_SEC);


}

/*********************************************************************************************************************/

void contituer_Tableau_comaraison ()
{
    int randomValue;
    int i = 0, j=0 ;
    int E1[10],E2[50],E3[100],E4[300],E5[1000];
    int s[5];
    int val;
    for (i=0;i<5;i++ )
    {
        val=NbElmt[i]*5;
        for(j=0;j<NbElmt[i];j++){
           randomValue = rand() % val;
           E[j]=randomValue;
        }
        s[i]=rand() % 20;
        Sol_Dyn[i]=Temps_solution_dynamique_MaxEns(NbElmt[i],s[i]);
        Sol_Rec[i]=Temps_solution_recursive_MaxEns(NbElmt[i],s[i]);
    }

}
