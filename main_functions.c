/*
Copyright (c) 2023 Elfrani Khadija and Aghlal Nizar.

Ce code est en cadre de notre projet en Module de Programmation parallèle et distribuée à l'ISTY.
Ce code est open source, vous pouvez alors le recopier, modifier ou l'ajuster à vos besoins.
Ce code source est conçu pour être utilisé avec la bibliothèque GSL (GNU Scientific Library).
Il inclut des fonctions pour imprimer une matrice, trouver son inverse,
multiplier deux matrices et convertir une matrice double* en une matrice de type gsl_matrix.
*/
#include "header.h"

/*

// Fonction pour genrer une matrice aléatoire en fichier .txt
// Décommenter cette fonction si vous voulez generer une autre matrice de taille différente pour tester
// N'oublie pas alors de changer le nom de fichier dans les functions taille_de_la_matrice() et read_matrix().

void generer_matrice_alea(int n) {
    srand(time(0));

    char filename[256];
    //creation de fichier :
    sprintf(filename, "matrice_%d.txt", n);

    FILE *fp = fopen(filename, "w");
    // premiere ligne de fichier c la taille de la matrice :

    fprintf(fp, "%d %d\n", n, n);

    // a partir de la deuxième ligne on écrit les valeurs de la matrices de cette forme: ligne colonne valeur
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // les valeurs sont aléatoires entre -3 et 3
            double value = (rand() % 7 - 3); //+ (rand() % 10) / 10.0;
            fprintf(fp, "%d %d %.3f\n", i, j, value);
        }
    }
    fclose(fp);
}
*/

/*
Fonction pour imprimer une matrice de type gsl_matrix*.
*/
void print_matrix(gsl_matrix* matrix) {
    int n = matrix->size1;

    // Trouver le nombre maximum de chiffres dans chaque colonne.
    int max_digits[n];
    for (int j = 0; j < n; j++) {
    int max_digits_in_col = 0;
    for (int i = 0; i < n; i++) {
    double value = gsl_matrix_get(matrix, i, j);
    int digits_in_value = snprintf(NULL, 0, "%.9f", value);
    max_digits_in_col = (digits_in_value > max_digits_in_col) ? digits_in_value : max_digits_in_col;
    }
    max_digits[j] = max_digits_in_col;
    }

    // Imprimer les lignes de la matrice.
    for (int i = 0; i < n; i++) {
    printf("|");
    // Imprimer les colonnes de la matrice.
    for (int j = 0; j < n; j++) {
      double value = gsl_matrix_get(matrix, i, j);
      printf("%*.*f ", max_digits[j], max_digits[j]-4, value);
  }
    printf("|\n");
}
}

gsl_matrix* inverse_matrix(gsl_matrix* matrix) {
    int n = matrix->size1;

    // Allocate memory for the inverse matrix
    gsl_matrix* inverse = gsl_matrix_alloc(n, n);

    // Allocate memory for the LU decomposition
    gsl_permutation* permutation = gsl_permutation_alloc(n);

    int sign;

    // Compute the LU decomposition
    gsl_linalg_LU_decomp(matrix, permutation, &sign);

    // Compute the inverse matrix
    gsl_linalg_LU_invert (matrix, permutation, inverse);

    // Free the memory
    gsl_permutation_free(permutation);

    return inverse;
}

/*
Fonction pour multiplier deux matrices de type gsl_matrix*

A : première matrice à multiplier

B : deuxième matrice à multiplier

Renvoie la matrice produit de A et B
*/
gsl_matrix* matrix_multiply(gsl_matrix* A, gsl_matrix* B) {
    // Récupère la taille de la première matrice
    int n = A->size1;
    // Récupère la taille de la deuxième matrice
    int m = B->size2;
    // Alloue de la mémoire pour la matrice résultat
    gsl_matrix* C = gsl_matrix_alloc(n, m);
    // Calcule le produit de matrice de A et B
    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, A, B, 0.0, C);

    return C;
}
/*
    Fontion pour convertir le type d'une matrice de double * à gsl_matrix*
*/

gsl_matrix* convert_double_to_gsl(double *matrix, size_t rows, size_t cols) {
  gsl_matrix *gsl_mat = gsl_matrix_alloc(rows, cols);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      gsl_matrix_set(gsl_mat, i, j, matrix[i * cols + j]);
    }
  }

  return gsl_mat;
}
