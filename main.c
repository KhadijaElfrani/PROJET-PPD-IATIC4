/***********************************************************\
    PROJET PROGRAMMATION PARALLÈLE DISTRIBUÉE
    CALCUL DES ELEEMENTS PROPRES D’UNE MATRICE ´
    SYMETRIQUE AVEC OPENMP
    RÉALISÉ PAR : ELFRANI KHADIJA & AGHLAL NIZAR
    IATIC4 2022-2023
************************************************************/
#include "header.h"
#define SIZE_M 3
int main() {

    printf("\n--- PHASE DE PROJECTION ---- \n");
    printf("\n\n");

    int n = rec_taille_de_la_matrice();
    double matriceA[n][n];
    int X[n];
    for (int i = 0; i < n; i++)
    {
        srand(time(NULL));
        X[i] = rand() % (2) + 1;
        X[i] = 3;
        for (int j = 0; j < n; j++)
            matriceA[i][j] = 0;
    }

    lire_matrice(n, &matriceA[0][0]);

    // on a pris la taille m= 3 comme étant une taille plus petite que n pour aboutir à un problème de taille toujours plus petite que n

    double* Bm_1;
    double* Bm;


    printf(" la matrice b(m-1) : ");
    printf("\n\n");
    Bm_1 = projection_matrice(&matriceA[0][0], &X[0], n, SIZE_M, 0, SIZE_M-1);
    for (int i = 0; i < SIZE_M; i++)
    {
        for (int j = 0; j < SIZE_M; j++)
        {
            printf("%f \t", *(Bm_1+i*SIZE_M+j));
        }
        printf("\n");
    }
    printf("\n");


    printf(" la matrice bm : ");
    printf("\n\n");


    Bm = projection_matrice(&matriceA[0][0], &X[0], n , SIZE_M , 1, SIZE_M-1);

    for (int i = 0; i < SIZE_M; i++)
    {
        for (int j = 0; j < SIZE_M; j++)
        {
            printf("%f \t", *(Bm+i*SIZE_M+j));
        }
        printf("\n");
    }
    printf("\n");

    /*
    *   casting of matrixs Bm and Bm-1
    */
    gsl_matrix* Bm_gsl = convert_double_to_gsl(Bm , 3,3);
    gsl_matrix* Bm_1_gsl = convert_double_to_gsl(Bm_1 , 3,3);

    /*
    * Calcul de la matrice Em =(l’inverse de Bm−1).
    */
    gsl_matrix* Em = inverse_matrix(Bm_1_gsl);

    printf("\n--- INVERSION DE LA MATRICE Bm-1 ---\n\n");

    print_matrix(Em);

    /*
    * : Calcul du produit matriciel :Fm = Em × Bm.
    */

    printf("\n--- CALCUL DU PRODUIT Fm ---\n\n");
    gsl_matrix* Fm = matrix_multiply(Em , Bm_gsl);
    print_matrix(Fm);

    printf("\n--- CALCULE DES VALEURS PROPRES ET VECTEURS PROPRES DE LA MATRICE Fm ---\n\n");

    // Allocate memory for the output eigenvalue vector and eigenvector matrix
    gsl_vector *eigenvalues;
    gsl_matrix *eigenvectors;

    // Call the function to calculate eigenvalues and eigenvectors

    char mode;
    printf("Choisissez le mode de calcul ;  S: sequentielle , P: Parallele\n (S/P) ? : ");
    scanf("%c", &mode);

    clock_t start, end;

    if (mode == 'S' || mode == 's'){
        start = clock();
        calculate_eigen_seq(Fm, &eigenvalues, &eigenvectors);
        end = clock();
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Le temps d'execution en sequentiel est : %f secondes\n", elapsed);
  }
    else if (mode == 'p' || mode == 'p'){
        start = clock();
        calculate_eigen_seq(Fm, &eigenvalues, &eigenvectors);
        end = clock();
        double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Le temps d'exécution en parallèle est : %f secondes\n", elapsed);
   }
    // Print the results
    printf("\nEigenvalues:\n");
    for (int i = 0; i < SIZE_M; i++) {
            printf("%.8f\n", gsl_vector_get(eigenvalues, i));
  }

    printf("\nEigenvectors:\n");
    for (int i = 0; i < SIZE_M; i++) {
        for (int j = 0; j < SIZE_M; j++) {
            printf("%.8f ", gsl_matrix_get(eigenvectors, i, j));
        }
    printf("\n");
  }

    // Freeing memory
    gsl_matrix_free(Fm);
    gsl_vector_free(eigenvalues);
    gsl_matrix_free(eigenvectors);
    gsl_matrix_free(Bm_gsl);
    gsl_matrix_free(Bm_1_gsl);
    gsl_matrix_free(Em);

    return 0;
}
