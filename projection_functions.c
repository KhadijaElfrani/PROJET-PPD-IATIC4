#include "header.h"


// fonctions de projection

int rec_taille_de_la_matrice(){

    // lire le fichier

    int taille = 0;
    FILE* fich;
    char getcar;


    fich = fopen("matrice_200.txt", "r");
    getcar = fgetc(fich);


    //
    // lire la premiere ligne et extraire la premiere valeur entiere pour l'affecter à la taille de lamat
    while(getcar != ' '){
        taille *= 10;
        taille += getcar - '0';
        getcar = fgetc(fich);
    }
    fclose(fich);
    return taille;
}

void lire_matrice(int taille, double *matrice){


    char getcar;
    FILE* fich;
    int i = -1;
    int j = -1;
    int  tmp = 0;
    int signe = 1;
    fich = fopen("matrice_200.txt", "r");


    // lire les valeurs de la matrice puis les stocker dans une matrice

    while(getcar != '\n')
        getcar = fgetc(fich);
        getcar = fgetc(fich);
    while(getcar != EOF){
        if(getcar == '-')
        {
            signe = -1;
            getcar = fgetc(fich);
        }
        tmp *= 10;
        tmp += getcar - '0';
        getcar = fgetc(fich);
        if(  getcar == '\n'||getcar == EOF ||getcar == ' '){
            if(i == -1)
                i = tmp;
            else if(j == -1)
                j = tmp;
            else{
                *(matrice +taille*(i) + j) = tmp*signe;

                i = -1;
                j = -1;
                signe = 1;
            }
            tmp = 0;
            getcar = fgetc(fich);
        }
    }
    fclose(fich);
}



double multiplication_matrice_vecteur(double *Matrice1, double *Matrice2, int *X, int n){


    // multiplication d'un vecteur X par une matrice M1 et le stockers dans M2
    double tmp1[n];
    double tmp2[n];
    double tmp=0;

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        tmp1[i] = 0;
        for (int j = 0; j < n; j++) {

                // remplir la matrice à travers un tableau unidimensionnel
            tmp1[i] +=  * (Matrice1+i*n+j) * (*(X+j));
        }
    }


    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        tmp2[i] = 0;
        for (int j = 0; j < n; j++) {
            tmp2[i] += *(Matrice2+i*n+j) * (*(X+j));
        }
    }


    #pragma omp parallel for reduction(+:tmp)

    // La directive reduction(+:tmp) indique que la variable tmp est utilisée dans la boucle pour effectuer une opération d'addition, et que le résultat final de ces additions doit être combiné de manière à donner le résultat final correct.
    for (int i = 0; i < n; i++)
        tmp += tmp1[i]*tmp2[i];
    return tmp;
}



// calcul du produit scalaire des matrices Ai et Aj avec le vecteur X
double produit_scalaire(int i, int j, double *A, int n, int *X){



    double tmp[n][n]; // matrice temporaire
    double Ai[n][n];
    double Aj[n][n];



    //Parallélisation de la boucle "for" pour initialiser tmp
    #pragma omp parallel for

    for (int x = 0; x < n; x++){
        for (int y = 0; y < n; y++)
        {
            if(y == x)
                tmp[x][x] = 1;
            else
                tmp[x][y] = 0;
        }
    }

    // calcul du  produit scalaire pour Ai

    #pragma omp parallel for
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
            Ai[x][y] = *(A+n*x+y);
    }

    #pragma omp parallel for
    for (int k = 0; k < i; k++)
    {
        multiplication_matrice(&Ai[0][0], A, &tmp[0][0], n);
        for (int x = 0; x < n; x++)
        {
            for (int y = 0; y < n; y++)
                Ai[x][y] = tmp[x][y];
        }
    }
    if(i == 0){
        for (int x = 0; x < n; x++)
        {
            for (int y = 0; y < n; y++)
                Ai[x][y] = tmp[x][y];
        }
    }
    // calcul du produit scalaire pour Aj


    #pragma omp parallel for
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            Aj[x][y] = *(A+n*x+y);
            if(x==y)
                tmp[x][y] = 1;
            else
                tmp[x][y] = 0;
        }
    }
    #pragma omp parallel for
    for (int k = 0; k < j; k++)
    {
        multiplication_matrice(&Aj[0][0], A, &tmp[0][0], n);
        for (int x = 0; x < n; x++)
        {
            for (int y = 0; y < n; y++)
                Aj[x][y] = tmp[x][y];
        }
    }
    if(j == 0){
        for (int x = 0; x < n; x++)
        {
            for (int y = 0; y < n; y++)
                Aj[x][y] = tmp[x][y];
        }
    }

    return multiplication_matrice_vecteur(&Ai[0][0], &Aj[0][0], X, n);
}



double* projection_matrice(double *matriceA, int *X, int n, int m, int i, int j){

    double *B= malloc(sizeof(double)*m*m);
    for (int x = 0; x < m; x++)
    {
        for (int y = 0; y < m; y++)
        {
            *(B+x*m + y) = produit_scalaire(i, y+x, matriceA, n, X);
        }
    }
    return B;
}
void multiplication_matrice(double *A, double *B, double *C, int n){

    //#pragma omp parallel for private(i,j,k)
    // la matrice   C est la résultante de la multip de la matrice A et B , on stocke le resultat dans C
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(C+n*i+j) = 0;
            for (int k = 0; k < n; k++) {
                *(C+n*i+j) += *(A+n*i+k) * (*(B+n*k+j));
            }
        }
    }
}
