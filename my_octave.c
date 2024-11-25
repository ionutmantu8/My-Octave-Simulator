#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./My_octave_functii.h"
//Copyright Ionut Mantu 313 CAb 2023-2024
int main(void)
{
int ***v = NULL, x = 1, nrmatrici = 0, *linii = NULL, *coloane = NULL;
int m, n, index, index_1, putere;
v = (int ***)malloc(x * sizeof(int **));
if (!v)
	exit(-1);
linii = (int *)malloc(x * sizeof(int));
if (!linii)
	exit(-1);
coloane = (int *)malloc(x * sizeof(int));
if (!coloane)
	exit(-1);
while (1) {
	char caracter;
	scanf(" %c", &caracter);
	if (nrmatrici + 1 > x)
		realocare(&v, &x, &linii, &coloane);
	switch (caracter) {
	case 'L':
	scanf("%d%d", &m, &n);
	linii[nrmatrici] = m;
	coloane[nrmatrici] = n;
	alocare(v, m, n, nrmatrici);
	citire(v, m, n, nrmatrici);
	nrmatrici++;
	break;
	case 'D':
	scanf("%d", &index);
	if (index >= 0 && index < nrmatrici)
		printf("%d %d\n", linii[index], coloane[index]);
	else
		printf("No matrix with the given index\n");
	break;
	case 'P':
	scanf("%d", &index);
	afisare(v, linii, coloane, nrmatrici, index);
	break;
	case 'T':
	scanf("%d", &index);
	transpusa(v, linii, coloane, index, nrmatrici);
	break;
	case 'M':
	scanf("%d", &index);
	scanf("%d", &index_1);
	inmultire(v, linii, coloane, index, index_1, &nrmatrici);
	break;
	case 'O':
	sortare(v, nrmatrici, linii, coloane);
	break;
	case 'Q':
	eliberare_totala(v, nrmatrici, linii, coloane);
	exit(0);
	break;
	case 'F':
	scanf("%d", &index);
	stergere_si_mutare(v, index, &nrmatrici, linii, coloane);
	break;
	case 'C':
	scanf("%d", &index);
	redimensionare(v, index, nrmatrici, linii, coloane);
	break;
	case 'R':
	scanf("%d", &index);
	scanf("%d", &putere);
	putere_matr(v, index, putere, nrmatrici, linii, coloane);
	break;
	case 'S':
	scanf("%d", &index);
	scanf("%d", &index_1);
	strassen(v, index, index_1, linii, coloane, &nrmatrici);
	break;
	default:
	if (caracter >= 'A' && caracter <= 'Z')
		printf("Unrecognized command\n");
	}
}

return 0;
}
