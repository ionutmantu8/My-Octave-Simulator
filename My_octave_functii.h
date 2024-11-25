#include <stdio.h>
#include <stdlib.h>
//Copyright Ionut Mantu 313 CAb 2023-2024
void eliberare_v_matr(int ***v, int *l, int *c, int index)
{
	for (int i = 0; i < l[index]; i++) {
		for (int j = 0; j < c[index]; j++)
			free(v[i][j]);
		free(v[i]);
			}
			free(v);  //funct pt eliberarea unui vector de matrici
}

void alocare(int ***v, int m, int n, int index)
{
	v[index] = (int **)malloc(m * sizeof(int *));
	if (!v[index])
		exit(-1);
	for (int i = 0; i < m; i++) {
		v[index][i] = (int *)malloc(n * sizeof(int));
		if (!v[index][i])
			exit(-1);//funct pt alocarea memoriei pt o matrice
	}
}

void eliberare(int ***v, int index, int m)
{
	for (int i = 0; i < m; i++)
		free(v[index][i]);
	free(v[index]);//functie pentru eliberarea din memoriei a unei matrice
}

void citire(int ***v, int m, int n, int index)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf("%d", &v[index][i][j]);//funct pt citirea val unei matrice
}

void afisare(int ***v, int *l, int *c, int x, int index)
{
	if (index >= 0 && index < x) {
		for (int i = 0; i < l[index]; i++) {
			for (int j = 0; j < c[index]; j++) {
				printf("%d", v[index][i][j]);
				printf(" ");
			}
			printf("\n");
		}
	} else {
		printf("No matrix with the given index\n");
	}
} //functie pt afisarea valorilor unei matrice

void realocare(int ****v, int *x, int **l, int **c)
{
	*x *= 2;

	*v = (int ***)realloc(*v, (*x) * sizeof(int *));
	*l = (int *)realloc(*l, (*x) * sizeof(int));
	*c = (int *)realloc(*c, (*x) * sizeof(int));
} //functia de realocarea a vect de matrici cand trebuie sa mai adaug o matrice

void transpusa(int ***v, int *l, int *c, int index, int nrmatrici)
{
	if (index < 0 || index >= nrmatrici) {
		printf("No matrix with the given index\n");
		return;
	}
	int **transp;
	transp = (int **)malloc(c[index] * sizeof(int *));
	if (!transp)
		exit(-1);

	for (int i = 0; i < c[index]; i++)
		transp[i] = (int *)malloc(l[index] * sizeof(int));

	for (int i = 0; i < c[index]; i++)
		for (int j = 0; j < l[index]; j++)
			transp[i][j] = v[index][j][i];//interschimbarea liniilor si coloane
	eliberare(v, index, l[index]);
	v[index] = transp;
	int aux = 0;
	aux = l[index];
	l[index] = c[index];//interschimbarea pt vectorul de linii si coloane
	c[index] = aux;
}

void inmultire(int ***v, int *l, int *c, int index, int index_1, int *nrmat)
{
	if (index < 0 || index >= *nrmat) {
		printf("No matrix with the given index\n");
		return;
	}
	if (index_1 < 0 || index_1 >= *nrmat) {
		printf("No matrix with the given index\n");
		return;
	}
	if (c[index] != l[index_1]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	int **matr_inm;
	matr_inm = (int **)malloc(l[index] * sizeof(int *));
	for (int i = 0; i < l[index]; i++)
		matr_inm[i] = (int *)malloc(c[index_1] * sizeof(int));
	if (!matr_inm)
		exit(-1);

	for (int i = 0; i < l[index]; i++) {
		for (int j = 0; j < c[index_1]; j++) {
			matr_inm[i][j] = 0;
			for (int k = 0; k < c[index]; k++) {
				matr_inm[i][j] += v[index][i][k] * v[index_1][k][j];
				//aplicarea algoritmului de inmultire a doua matr
				matr_inm[i][j] = matr_inm[i][j] % 10007;
				while (matr_inm[i][j] < 0)
					matr_inm[i][j] += 10007;//rezultatul trecut modulo 10^4+7
			}
		}
	}

	(*nrmat) += 1;

	v[*nrmat - 1] = matr_inm;//matricea inmultire pusa la finalul vect de matr
	l[*nrmat - 1] = l[index];//liniile pt matricea inmultire
	c[*nrmat - 1] = c[index_1];//coloanele pt matricea inmultire
}

void sortare(int ***v, int nrmatrici, int *l, int *c)
{
	int *sumele;
	sumele = (int *)malloc(nrmatrici * sizeof(int));//vect in care retin sumele
	if (!sumele)
		exit(-1);
	for (int i = 0; i < nrmatrici; i++) {
		sumele[i] = 0;
		for (int j = 0; j < l[i]; j++) {
			for (int k = 0; k < c[i]; k++) {
				sumele[i] += v[i][j][k];
				sumele[i] = sumele[i] % 10007;
				while (sumele[i] < 0)
					sumele[i] += 10007;
			}
		}
	}

	// Sortăm matricile și sumele în ordine crescătoare
	for (int i = 0; i < nrmatrici - 1; i++) {
		for (int j = 0; j < nrmatrici - i - 1; j++) {
			if (sumele[j] > sumele[j + 1]) {
				// InterSchimb matricea
				int **tempmatr = v[j];
				v[j] = v[j + 1];
				v[j + 1] = tempmatr;

				// InterSchimb sumele
				int temps = sumele[j];
				sumele[j] = sumele[j + 1];
				sumele[j + 1] = temps;

				// InterSchimb si liniile si corespunzatoare matricilor
				int templ = l[j];
				l[j] = l[j + 1];
				l[j + 1] = templ;

				int tempc = c[j];
				c[j] = c[j + 1];
				c[j + 1] = tempc;
			}
		}
	}
	free(sumele);
}

void eliberare_totala(int ***v, int nrmatrici, int *l, int *c)
{
	for (int k = 0; k < nrmatrici; k++) {
		for (int i = 0; i < l[k]; i++)
			free(v[k][i]);
		free(v[k]);
		}
	free(v);
	v = NULL;
	free(l);
	l = NULL;
	free(c);
	c = NULL;
} //functia pt case Q ca sa eliberez absolut tot ce e in memorie

void stergere_si_mutare(int ***v, int index, int *nrmat, int *l, int *c)
{
	if (index < 0 || index >= *nrmat) {
		printf("No matrix with the given index\n");
		return;
	}
	if (*nrmat == 1) {
		//Daca numarul de matrici =1 sterg matricea din memorie
		eliberare(v, index, l[index]);
		*nrmat -= 1;
	} else {
		*nrmat -= 1;
		eliberare(v, index, l[index]);
		for (int k = index; k < *nrmat; k++) {
			v[k] = v[k + 1];
			l[k] = l[k + 1];
			c[k] = c[k + 1];
		}  //dupa eliberarea din memorie mut toate matricile la stanga
	}
} //functia pt case F

void redimensionare(int ***v, int index, int nrmatrici, int *l, int *c)
{
	if (index >= 0 && index < nrmatrici) {
		int redimensionare_lin, redimensionare_col, *red_val_l, *red_val_c;
		scanf("%d", &redimensionare_lin);
		//un vector in care retin liniile dupa care redimensionez
		red_val_l = (int *)malloc(redimensionare_lin * sizeof(int));
		for (int i = 0; i < redimensionare_lin; i++)
			scanf("%d", &red_val_l[i]);
		scanf("%d", &redimensionare_col);
		//un vector in care retin coloanele dupa care redimensionez
		red_val_c = (int *)malloc(redimensionare_col * sizeof(int));
		for (int i = 0; i < redimensionare_col; i++)
			scanf("%d", &red_val_c[i]);
		int **matr_aux;
		matr_aux = (int **)malloc(redimensionare_lin * sizeof(int *));
		for (int i = 0; i < redimensionare_lin; i++)
			matr_aux[i] = (int *)malloc(redimensionare_col * sizeof(int));
		for (int i = 0; i < redimensionare_lin; i++)
			for (int j = 0; j < redimensionare_col; j++)
				matr_aux[i][j] = v[index][red_val_l[i]][red_val_c[j]];
				//in aceasta matrice auxiliara pun matricea redimensionata
		eliberare(v, index, l[index]);
		v[index] = matr_aux; //adaug matricea auxiliara in vect de matr
		l[index] = redimensionare_lin;
		c[index] = redimensionare_col;
		//mai sus am updatat liniile si coloanele matricei redimensionate
		free(red_val_c);
		free(red_val_l);
	} else {
		printf("No matrix with the given index\n");
		return;
	}
}

void inmultire_simpla(int ***v, int *l, int *c, int index)
{
	for (int i = 0; i < l[index]; i++) {
		for (int j = 0; j < c[index]; j++) {
			for (int k = 0; k < c[index]; k++) {
				v[index][i][j] += v[index][i][k] * v[index][k][j];
				v[index][i][j] = v[index][i][j] % 10007;
				while (v[index][i][j] < 0)
					v[index][i][j] += 10007;
			} //functie care doar imi inmulteste 2 matrici
		}
	}
}

void putere_matr(int ***v, int index, int putere, int nrmatrici, int *l, int *c)
{
	if (index < 0 || index >= nrmatrici) {
		printf("No matrix with the given index\n");
		return;
	}
	if (putere < 0) {
		printf("Power should be positive\n");
		return;
	}
	if (l[index] != c[index]) {
		printf("Cannot perform matrix multiplication\n");
		return;
	}
	//Initializez matricea rezultat cu identitatea
	int ***rezultat;
	rezultat = (int ***)malloc(l[index] * sizeof(int **));
	for (int i = 0; i < l[index]; i++) {
		rezultat[i] = (int **)malloc(c[index] * sizeof(int *));
		for (int j = 0; j < c[index]; j++) {
			rezultat[i][j] = (int *)malloc(sizeof(int));
			if (i == j)
				rezultat[i][j][0] = 1;
			else
				rezultat[i][j][0] = 0;
		}
	}
	//Incep algoritmul pt ridicarea la putere in timp logaritmic
	while (putere > 0) {
		if (putere % 2 == 1) {
			int ***temp = (int ***)malloc(l[index] * sizeof(int **));
		for (int i = 0; i < l[index]; i++) {
			temp[i] = (int **)malloc(c[index] * sizeof(int *));
		for (int j = 0; j < c[index]; j++) {
			temp[i][j] = (int *)malloc(sizeof(int));
			temp[i][j][0] = 0;
		for (int k = 0; k < c[index]; k++) {
			temp[i][j][0] += rezultat[i][k][0] * v[index][k][j];
			temp[i][j][0] = temp[i][j][0] % 10007;
			while (temp[i][j][0] < 0)
				temp[i][j][0] += 10007;
					}
				}
		}

			for (int i = 0; i < l[index]; i++)
				for (int j = 0; j < c[index]; j++)
					rezultat[i][j][0] = temp[i][j][0];

			// Eliberăm memoria pentru matricea temporară
			eliberare_v_matr(temp, l, c, index);
		}
		int ***temp = (int ***)malloc(l[index] * sizeof(int **));
		for (int i = 0; i < l[index]; i++) {
			temp[i] = (int **)malloc(c[index] * sizeof(int *));
			for (int j = 0; j < c[index]; j++) {
				temp[i][j] = (int *)malloc(sizeof(int));
				temp[i][j][0] = 0;
				for (int k = 0; k < c[index]; k++) {
					temp[i][j][0] += v[index][i][k] * v[index][k][j];
					temp[i][j][0] = temp[i][j][0] % 10007;
					while (temp[i][j][0] < 0)
						temp[i][j][0] += 10007;
				}
			}
		}
		for (int i = 0; i < l[index]; i++)
			for (int j = 0; j < c[index]; j++)
				v[index][i][j] = temp[i][j][0];

		// Eliberez memoria pentru matricea temporara
		eliberare_v_matr(temp, l, c, index);

		putere /= 2;
	}
	// Copiez rezultatul în vect de matr
	for (int i = 0; i < l[index]; i++)
		for (int j = 0; j < c[index]; j++)
			v[index][i][j] = rezultat[i][j][0];
	// Eliberez memoria pentru matricea rezultat
	eliberare_v_matr(rezultat, l, c, index);
}

void adunare_matr_patr(int **A, int **B, int **rezultat, int index)
{
	for (int i = 0; i < index; i++) {
		for (int j = 0; j < index; j++) {
			rezultat[i][j] = A[i][j] + B[i][j];
			rezultat[i][j] = rezultat[i][j] % 10007;
			while (rezultat[i][j] < 0)
				rezultat[i][j] += 10007;
		} //functie pentru adunarea a 2 matrici
	}
}

void scadere_matr_patr(int **A, int **B, int **rezultat, int index)
{
	for (int i = 0; i < index; i++) {
		for (int j = 0; j < index; j++) {
			rezultat[i][j] = A[i][j] - B[i][j];
			rezultat[i][j] = rezultat[i][j] % 10007;
			while (rezultat[i][j] < 0)
				rezultat[i][j] += 10007;
		} //functie pentru scadrea a 2 matrici
	}
}

void inmultire_ptr_str(int **A, int **B, int **rezultat, int index)
{
	for (int i = 0; i < index; i++) {
		for (int j = 0; j < index; j++) {
			for (int k = 0; k < index; k++) {
				rezultat[i][j] += A[i][k] * B[k][j];
				rezultat[i][j] = rezultat[i][j] % 10007;
				while (rezultat[i][j] < 0)
					rezultat[i][j] += 10007;
			} //functie pentru inmultirea a 2 matr si pusa pe o matr rezultat
		}
	}
}

//de aici toate fct care contin str in nume sunt pt algoritmul lui Strassen

void eliberare_matr_ptr_str(int **v, int marime)
{
	for (int i = 0; i < marime; i++)
		free(v[i]);
	free(v);
} //elibearea unei simple matrici

void aloc_blocuriA_str(int ***A1, int ***A2, int ***A3, int ***A4, int marime)
{
	*A1 = (int **)malloc(marime * sizeof(int *));
	*A2 = (int **)malloc(marime * sizeof(int *));
	*A3 = (int **)malloc(marime * sizeof(int *));
	*A4 = (int **)malloc(marime * sizeof(int *));
	for (int i = 0; i < marime; i++) {
		(*A1)[i] = (int *)malloc(marime * sizeof(int));
		(*A2)[i] = (int *)malloc(marime * sizeof(int));
		(*A3)[i] = (int *)malloc(marime * sizeof(int));
		(*A4)[i] = (int *)malloc(marime * sizeof(int));
	}
} //functie pentru alocarea blocurilor A

void aloc_blocuriB_str(int ***B1, int ***B2, int ***B3, int ***B4, int marime)
{
	*B1 = (int **)malloc(marime * sizeof(int *));
	*B2 = (int **)malloc(marime * sizeof(int *));
	*B3 = (int **)malloc(marime * sizeof(int *));
	*B4 = (int **)malloc(marime * sizeof(int *));
	for (int i = 0; i < marime; i++) {
		(*B1)[i] = (int *)malloc(marime * sizeof(int));
		(*B2)[i] = (int *)malloc(marime * sizeof(int));
		(*B3)[i] = (int *)malloc(marime * sizeof(int));
		(*B4)[i] = (int *)malloc(marime * sizeof(int));
	}
} //functie pentru alocarea blocurilor B

void aloc_blocuriC_str(int ***C1, int ***C2, int ***C3, int ***C4, int marime)
{
	*C1 = (int **)malloc(marime * sizeof(int *));
	*C2 = (int **)malloc(marime * sizeof(int *));
	*C3 = (int **)malloc(marime * sizeof(int *));
	*C4 = (int **)malloc(marime * sizeof(int *));
	for (int i = 0; i < marime; i++) {
		(*C1)[i] = (int *)malloc(marime * sizeof(int));
		(*C2)[i] = (int *)malloc(marime * sizeof(int));
		(*C3)[i] = (int *)malloc(marime * sizeof(int));
		(*C4)[i] = (int *)malloc(marime * sizeof(int));
	} //functie pentru alocarea blocurilor C
}

void al_bl_M_1_4(int ***M1, int ***M2, int ***M3, int ***M4, int marime)
{
	*M1 = (int **)malloc(marime * sizeof(int *));
	*M2 = (int **)malloc(marime * sizeof(int *));
	*M3 = (int **)malloc(marime * sizeof(int *));
	*M4 = (int **)malloc(marime * sizeof(int *));
	for (int i = 0; i < marime; i++) {
		(*M1)[i] = (int *)malloc(marime * sizeof(int));
		(*M2)[i] = (int *)malloc(marime * sizeof(int));
		(*M3)[i] = (int *)malloc(marime * sizeof(int));
		(*M4)[i] = (int *)malloc(marime * sizeof(int));
	}
} //functie pentru alocarea blocurilor M1-M4

void al_bl_M_5_7(int ***M5, int ***M6, int ***M7, int marime)
{
	*M5 = (int **)malloc(marime * sizeof(int *));
	*M6 = (int **)malloc(marime * sizeof(int *));
	*M7 = (int **)malloc(marime * sizeof(int *));
	for (int i = 0; i < marime; i++) {
		(*M5)[i] = (int *)malloc(marime * sizeof(int));
		(*M6)[i] = (int *)malloc(marime * sizeof(int));
		(*M7)[i] = (int *)malloc(marime * sizeof(int));
	}
} //functie pentru alocarea blocurilor M5-M7

void dealoc_blocA(int **A1, int **A2, int **A3, int **A4, int marime)
{
	for (int i = 0; i < marime; i++) {
		free(A1[i]);
		free(A2[i]);
		free(A3[i]);
		free(A4[i]);
	}
	free(A1);
	free(A2);
	free(A3);
	free(A4);
} //functie pentru eliberarea blocurilor A

void dealoc_blocB(int **B1, int **B2, int **B3, int **B4, int marime)
{
	for (int i = 0; i < marime; i++) {
		free(B1[i]);
		free(B2[i]);
		free(B3[i]);
		free(B4[i]);
	}
	free(B1);
	free(B2);
	free(B3);
	free(B4);
} //functie pentru eliberarea blocurilor B

void dealoc_blocC(int **C1, int **C2, int **C3, int **C4, int marime)
{
	for (int i = 0; i < marime; i++) {
		free(C1[i]);
		free(C2[i]);
		free(C3[i]);
		free(C4[i]);
	}
	free(C1);
	free(C2);
	free(C3);
	free(C4);
} //functie pentru eliberarea blocurilor C

void dealoc_M14(int **M1, int **M2, int **M3, int **M4, int marime)
{
	for (int i = 0; i < marime; i++) {
		free(M1[i]);
		free(M2[i]);
		free(M3[i]);
		free(M4[i]);
	}
	free(M1);
	free(M2);
	free(M3);
	free(M4);
} //functie pentru eliberarea blocurilor M1-M4

void dealoc_M57(int **M5, int **M6, int **M7, int marime)
{
	for (int i = 0; i < marime; i++) {
		free(M5[i]);
		free(M6[i]);
		free(M7[i]);
	}
	free(M5);
	free(M6);
	free(M7);
} //functie pentru eliberarea blocurilor M5-M7

void initializare_C(int **C1, int **C2, int **C3, int **C4, int index)
{
	for (int i = 0; i < index; i++) {
		for (int j = 0; j < index; j++) {
			C1[i][j] = 0;
			C2[i][j] = 0;
			C3[i][j] = 0;
			C4[i][j] = 0;
		}
	}
} //functie pentru initializarea valorilor matr C cu 0

void valori_A(int ***v, int marime, int **A1, int **A2, int **A3, int **A4)
{
	for (int i = 0; i < marime; i++) {
		for (int j = 0; j < marime; j++) {
			A1[i][j] = *v[i][j];
			A2[i][j] = *v[i][j + marime];
			A3[i][j] = *v[i + marime][j];
			A4[i][j] = *v[i + marime][j + marime];
		}
	}
} //functie pentru valorile blocului A

void valori_B(int ***v, int marime, int **B1, int **B2, int **B3, int **B4)
{
	for (int i = 0; i < marime; i++) {
		for (int j = 0; j < marime; j++) {
			B1[i][j] = *v[i][j];
			B2[i][j] = *v[i][j + marime];
			B3[i][j] = *v[i + marime][j];
			B4[i][j] = *v[i + marime][j + marime];
		}
	}
} //functie pentru valorile blocurilor B
void operatii_str(int **v1, int **v2, int **rez, int marime)
{
	int **A1, **A2, **A3, **A4;
	int **B1, **B2, **B3, **B4;
	int **M1, **M2, **M3, **M4, **M5, **M6, **M7;
	int **C1, **C2, **C3, **C4;
	if (marime == 2) {
		inmultire_ptr_str(v1, v2, rez, marime);
		return;
	}
	marime /= 2;
	aloc_blocuriA_str(&A1, &A2, &A3, &A4, marime);
	aloc_blocuriB_str(&B1, &B2, &B3, &B4, marime);
	aloc_blocuriC_str(&C1, &C2, &C3, &C4, marime);
	al_bl_M_1_4(&M1, &M2, &M3, &M4, marime);
	al_bl_M_5_7(&M5, &M6, &M7, marime);
	valori_A(&v1, marime, A1, A2, A3, A4);
	valori_B(&v2, marime, B1, B2, B3, B4);
	initializare_C(C1, C2, C3, C4, marime);
	int **temp1, **temp2;
	temp1 = (int **)malloc(marime * sizeof(int *));
	temp2 = (int **)malloc(marime * sizeof(int *));
	for (int i = 0; i < marime; i++) {
		temp1[i] = (int *)malloc(marime * sizeof(int));
		temp2[i] = (int *)malloc(marime * sizeof(int));
	} //initializarea unor matrici temporare pentru a face operatiile
	adunare_matr_patr(A1, A4, temp1, marime);
	adunare_matr_patr(B1, B4, temp2, marime);
	operatii_str(temp1, temp2, M1, marime); //M1
	eliberare_matr_ptr_str(temp1, marime);
	eliberare_matr_ptr_str(temp2, marime);
	adunare_matr_patr(A3, A4, temp1, marime);
	operatii_str(temp1, B1, M2, marime); //M2
	eliberare_matr_ptr_str(temp1, marime);
	scadere_matr_patr(B2, B4, temp1, marime);
	operatii_str(A1, temp1, M3, marime); //M3
	eliberare_matr_ptr_str(temp1, marime);
	scadere_matr_patr(B3, B1, temp1, marime);
	operatii_str(A4, temp1, M4, marime); //M4
	eliberare_matr_ptr_str(temp1, marime);
	adunare_matr_patr(A1, A2, temp1, marime);
	operatii_str(temp1, B4, M5, marime); //M5
	eliberare_matr_ptr_str(temp1, marime);
	scadere_matr_patr(A3, A1, temp1, marime);
	adunare_matr_patr(B1, B2, temp2, marime);
	operatii_str(temp1, temp2, M6, marime); //M6
	eliberare_matr_ptr_str(temp1, marime);
	eliberare_matr_ptr_str(temp2, marime);
	scadere_matr_patr(A2, A4, temp1, marime);
	adunare_matr_patr(B3, B4, temp2, marime);
	operatii_str(temp1, temp2, M7, marime); //M7
	eliberare_matr_ptr_str(temp1, marime);
	eliberare_matr_ptr_str(temp2, marime);
	//incep algoritmul prin calcularea M1-M7
	adunare_matr_patr(C1, M1, C1, marime);
	adunare_matr_patr(C1, M4, C1, marime);
	scadere_matr_patr(C1, M5, C1, marime);
	adunare_matr_patr(C1, M7, C1, marime);
	//pun in fiecare bloc C operatiile dintre matricile M
	adunare_matr_patr(C2, M3, C2, marime);
	adunare_matr_patr(C2, M5, C2, marime);
	adunare_matr_patr(C3, M2, C3, marime);
	adunare_matr_patr(C3, M4, C3, marime);
	adunare_matr_patr(C4, M1, C4, marime);
	scadere_matr_patr(C4, M2, C4, marime);
	adunare_matr_patr(C4, M3, C4, marime);
	adunare_matr_patr(C4, M6, C4, marime);
	for (int i = 0; i < marime; i++) {
		for (int j = 0; j < marime; j++) {
			rez[i][j] = C1[i][j];
			rez[i][j + marime] = C2[i][j];
			rez[i + marime][j] = C3[i][j];
			rez[i + marime][j + marime] = C4[i][j];
	}
}

	dealoc_blocA(A1, A2, A3, A4, marime);
	dealoc_blocB(B1, B2, B3, B4, marime);
	dealoc_blocC(C1, C2, C3, C4, marime);
	dealoc_M14(M1, M2, M3, M4, marime);
	dealoc_M57(M5, M6, M7, marime);
}

void strassen(int ***v, int index, int index_1, int *l, int *c, int *nrmat)
{
	if (index < 0 && index > *nrmat && index_1 < 0 && index_1 > *nrmat) {
		printf("No matrix with the given index\n");
		return;
	}
	if (l[index] != c[index] || l[index_1] != c[index_1])
		printf("Cannot perform matrix multiplication");
	if (l[index < 4]) {
		inmultire(v, l, c, index, index_1, nrmat);
		return;
	}
	int **aux;
	aux = (int **)malloc(l[index] * sizeof(int *));
	for (int i = 0; i < l[index]; i++)
		aux[i] = (int *)malloc(l[index] * sizeof(int));
	operatii_str(v[index], v[index_1], aux, l[index]);
	*nrmat += 1;
	v[*nrmat - 1] = aux;
	l[*nrmat - 1] = index; //updatez liniile pentru matricea de inmultire
	c[*nrmat - 1] = index; //updatez coloanele pentru matricea de inmultire
}
