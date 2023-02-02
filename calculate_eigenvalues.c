/*
Copyright (c) 2023 Elfrani Khadija and Aghlal Nizar.

Ce code est en cadre de notre projet en Module de Programmation parall�le et distribu�e � l'ISTY.
Ce code est open source, vous pouvez alors le recopier, modifier ou l'ajuster � vos besoins.
Ce code source est con�u pour �tre utilis� avec la biblioth�que GSL (GNU Scientific Library).
Cette partie de code n�cessite aussi la librarie openMP pour effectuer le parall�lisme.
Elle inclut des fonctions pour calculer les valeurs propres et les vecteurs propres d'une matrice
en deux modes : S�quentiel et Parall�le.
*/

#include "header.h"

/*
 Fonction pour calculer les valeurs propres et vecteurs propres de la matrice Fm de mani�re s�quentielle.
*/

void calculate_eigen_seq(gsl_matrix *Fm, gsl_vector **eigenvalues, gsl_matrix **eigenvectors) {
    int n = Fm->size1;

    // Allouer de la m�moire pour le vecteur de valeurs propres
    *eigenvalues = gsl_vector_alloc(n);

    // Allouer de la m�moire pour la matrice de vecteurs propres
    *eigenvectors = gsl_matrix_alloc(n, n);

    // Allouer de la m�moire pour l'espace de travail des valeurs propres
    gsl_eigen_symmv_workspace *workspace = gsl_eigen_symmv_alloc(n);

    // Calculer les valeurs propres et les vecteurs propres
    gsl_eigen_symmv(Fm, *eigenvalues, *eigenvectors, workspace);

    // Trier les valeurs propres et les vecteurs propres dans l'ordre d�croissant
    gsl_eigen_symmv_sort(*eigenvalues, *eigenvectors, GSL_EIGEN_SORT_VAL_DESC);

    // Lib�rer la m�moire
    gsl_eigen_symmv_free(workspace);
}

/*
 Fonction pour calculer les valeurs propres et vecteurs propres de la matrice Fm de mani�re parall�le.
*/

void calculate_eigen_parallel(gsl_matrix *Fm, gsl_vector **eigenvalues, gsl_matrix **eigenvectors) {
    int n = Fm->size1;

    // Allouer de la m�moire pour le vecteur de valeurs propres
    *eigenvalues = gsl_vector_alloc(n);

    // Allouer de la m�moire pour la matrice de vecteurs propres
    *eigenvectors = gsl_matrix_alloc(n, n);

    // Allouer de la m�moire pour l'espace de travail des valeurs propres
    gsl_eigen_symmv_workspace *workspace = gsl_eigen_symmv_alloc(n);

    // Calculer les valeurs propres et les vecteurs propres de mani�re parall�le
    #pragma omp parallel num_threads(6)
    {
        #pragma omp single
        {
            gsl_eigen_symmv(Fm, *eigenvalues, *eigenvectors, workspace);
        }
    }

    // Trier les valeurs propres et les vecteurs propres dans l'ordre d�croissant
    gsl_eigen_symmv_sort(*eigenvalues, *eigenvectors, GSL_EIGEN_SORT_VAL_DESC);

    // Lib�rer la m�moire
  gsl_eigen_symmv_free(workspace);
}
