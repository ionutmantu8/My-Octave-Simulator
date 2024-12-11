#include <stdio.h>
#include <stdlib.h>
//Copyright Ionut Mantu 313 CAb 2023-2024
void eliberare_v_matr(int ***v, int *l, int *c, int index);


void alocare(int ***v, int m, int n, int index);


void eliberare(int ***v, int index, int m);


void citire(int ***v, int m, int n, int index);


void afisare(int ***v, int *l, int *c, int x, int index);

void realocare(int ****v, int *x, int **l, int **c);


void transpusa(int ***v, int *l, int *c, int index, int nrmatrici);

void inmultire(int ***v, int *l, int *c, int index, int index_1, int *nrmat);

void sortare(int ***v, int nrmatrici, int *l, int *c);

void eliberare_totala(int ***v, int nrmatrici, int *l, int *c);

void stergere_si_mutare(int ***v, int index, int *nrmat, int *l, int *c);

void redimensionare(int ***v, int index, int nrmatrici, int *l, int *c);


void inmultire_simpla(int ***v, int *l, int *c, int index);


void putere_matr(int ***v, int index, int putere, int nrmatrici, int *l, int *c);

void adunare_matr_patr(int **A, int **B, int **rezultat, int index);

void scadere_matr_patr(int **A, int **B, int **rezultat, int index);

void inmultire_ptr_str(int **A, int **B, int **rezultat, int index);

void eliberare_matr_ptr_str(int **v, int marime);

void aloc_blocuriA_str(int ***A1, int ***A2, int ***A3, int ***A4, int marime);

void aloc_blocuriB_str(int ***B1, int ***B2, int ***B3, int ***B4, int marime);

void aloc_blocuriC_str(int ***C1, int ***C2, int ***C3, int ***C4, int marime);

void al_bl_M_1_4(int ***M1, int ***M2, int ***M3, int ***M4, int marime);

void al_bl_M_5_7(int ***M5, int ***M6, int ***M7, int marime);

void dealoc_blocA(int **A1, int **A2, int **A3, int **A4, int marime);

void dealoc_blocB(int **B1, int **B2, int **B3, int **B4, int marime);

void dealoc_blocC(int **C1, int **C2, int **C3, int **C4, int marime);

void dealoc_M14(int **M1, int **M2, int **M3, int **M4, int marime);

void dealoc_M57(int **M5, int **M6, int **M7, int marime);

void initializare_C(int **C1, int **C2, int **C3, int **C4, int index);

void valori_A(int ***v, int marime, int **A1, int **A2, int **A3, int **A4);

void valori_B(int ***v, int marime, int **B1, int **B2, int **B3, int **B4);

void operatii_str(int **v1, int **v2, int **rez, int marime);

void strassen(int ***v, int index, int index_1, int *l, int *c, int *nrmat);
