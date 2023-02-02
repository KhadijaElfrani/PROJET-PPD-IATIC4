#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix_double.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <math.h>
#include <omp.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>

/*
* PROTOTYPES :
*/

// MAIN FUNCTIONS : FUNCTIONS DE MANIPULATION DE MATRICES : AFFICHAGE, INVERSE, PRODUIT ,...

gsl_matrix* generate_random_matrix(int n);
double** random_matrix(int size);
void print_2D_matrix(double** mat, int size);
void print_matrix(gsl_matrix* matrix);
gsl_matrix* inverse_matrix(gsl_matrix* matrix);
gsl_matrix* matrix_multiply(gsl_matrix* A, gsl_matrix* B);
gsl_matrix* convert_double_to_gsl(double *matrix, size_t rows, size_t cols);

// PROJECTION FUNCTIONS : FUNCTIONS DE LA PHASE DE PROJECTION

int rec_taille_de_la_matrice();
void lire_matrice(int, double*);
void multiplication_matrice(double*, double*, double*, int);
double multiplication_matrice_vecteur(double*, double*, int*, int);
double produit_scalaire(int i, int j, double *A, int n, int *X);

// MAIN FUNCTIONS : FUNCTIONS DE CALCULE DE VALEURS PROPRES
void calculate_eigen_seq(gsl_matrix *Fm, gsl_vector **eigenvalues, gsl_matrix **eigenvectors);
void calculate_eigen_parallel(gsl_matrix *Fm, gsl_vector **eigenvalues, gsl_matrix **eigenvectors);


