///////////////////////////////////////////////////////
Projet de l’UE programmation parallèle et distribuée
CALCUL DES EL´ EMENTS PROPRES D’UNE MATRICE
SYMETRIQUE AVEC OPENMP
IATIC4 (ISTY) - 2022/2023
Professeurs : N. Emad, France Boillod-Cerneux
Réalisé par : AGHLAL NIZAR & ELFRANI KHADIJA
//////////////////////////////////////////////////////

## Introduction 

Ce projet traite l'implémentation d’un programme pour calculer un petit nombre de valeurs propres et leur vecteur 
propres correspondants d'une matrice symétrique A de grande taille n en utilisant la méthode Padé-Rayleigh-Ritz (PRR). 
Cette méthode de calcul parallèle et distribuée est un sujet important dans notre formation car elle permet de 
résoudre des problèmes de grande taille de manière efficace. En utilisant des fonctions de librairies existantes,
nous allons projeter le problème de taille n dans un sous-espace de taille m beaucoup plus petite que n et résoudre 
ce sous-problème en utilisant des techniques d'inversion de matrices, de produits matriciels et de calcul des éléments propres.
Les résultats obtenus à la fin de ce processus nous permettront de calculer une approximation des éléments propres de la matrice A. 

## Contraintes 

Ce projet est conçu pour résoudre ce problème pour une matrice de taille grande, cependant, vous allez trouver que le test (main.c) 
est effectué sur une matrice de taille 200 , cette matrice est alors projetée dans un sous espace beaucoup plus petit (m = 3) , vous pouvez à tout moment :
	- Génerer une nouvelle matrice de taille différente pour tester ( décommenter la fonction génerer matrice dans main_functions.c ).
	- Changer la taille de m dans le main.c ( #define SIZE_M 3 ) .
	 
## Prérequis

- Compilateur C installé
- Librarie GSL installée
- OpenMP installé

## Installation

- Liens utiles :
	-> https://solarianprogrammer.com/2020/01/26/getting-started-gsl-gnu-scientific-library-windows-macos-linux/
	-> https://curc.readthedocs.io/en/latest/programming/OpenMP-C.html

## Utilisation

- Ce fichier contient les fichier sources suivants :
	- main.c : contient la fonction main .
	- main_functions.c : contient les fonction de manipulation de matrice ( affichage , inverse,..)
	- projection_functions.c : contient les fonctions de qui ont permis la phase de projection d'avoir lieu.
	- calculate_eigenvalues.c : contient les fonction de calcul des vecteurs propres et valeurs propres.

- Après avoir installé les prérequis ,  vous pouvez exécuter le Makefile.
	Windows cmd : $make (build)
		      $make run (run)

## Licence

Ce code est open source, vous pouvez alors le recopier, modifier ou l'ajuster à vos besoins.
