#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct {
	int cod;
	char* den;
	float pret;
	float cantitate;
}produs;

void citireVectorProduse(produs* vp, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("COD = ");
		scanf("%d", &vp[i].cod);

		printf("DENUMIRE = ");
		char buffer[20];
		scanf("%s", buffer);
		vp[i].den = (char*)malloc((strlen(buffer) + 1)*sizeof(char));
		strcpy(vp[i].den, buffer);

		printf("PRET = ");
		scanf("%f", &vp[i].pret);

		printf("CANTITATE = ");
		scanf("%f", &vp[i].cantitate);
	}
}

void afisareVectorProduse(produs* vp, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("COD = %d \n DENUMIRE = %s \n PRET = %5.2f \n Cantitate = %5.2f \n\n", vp[i].cod, vp[i].den, vp[i].pret, vp[i].cantitate);
	}
}

void dezalocareVectorProduse(produs* vp, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(vp[i].den);
	}
	free(vp);
}

void dezalocare4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati, int n)
{
	free(coduri);
	for (int i = 0; i < n; i++)
	{
		free(denumiri[i]);
	}
	free(denumiri);
	free(preturi);
	free(cantitati);
}

void citire4Vectori(int* coduri, char**denumiri, float* preturi, float* cantitati, int n)
{
	
	for (int i = 0; i < n; i++)
	{
		printf("COD = ");
		scanf("%d", &coduri[i]);

		printf("DENUMIRE = ");
		char buffer[20];
		scanf("%s", buffer);
		denumiri[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(denumiri[i], buffer);

		printf("PRET = ");
		scanf("%f", &preturi[i]);

		printf("CANTITATE = ");
		scanf("%f", &cantitati[i]);
	}
}
void afisare4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("COD = %d \n DENUMIRE = %s \n PRET = %5.2f \n Cantitate = %5.2f \n\n", coduri[i], denumiri[i], preturi[i], cantitati[i]);
	}
}

void citireMatrice(float** mat, char** denumiri, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("DENUMIRE = ");
		char buffer[20];
		scanf("%s", buffer);
		denumiri[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(denumiri[i], buffer);

		for (int j = 0; j < 3; j++)
		{
			printf("mat[%d][%d] = ", i, j);
			scanf("%f", &mat[i][j]);
		}
	}
}

void afisareMatrice(float** mat, char** denumiri, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("\nDENUMIRE = %s ", denumiri[i]);
		printf("\nCOD = %5.sf", mat[i][0]);
		printf("\nPRET = %5.2f", mat[i][1]);
		printf("\nCANTITATE = %d", mat[i][2]);
	}
}

void dezalocareMatrice(float** mat, char** denumiri, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(denumiri[i]);
		free(mat[i]);
	}
	free(denumiri);
	free(mat);
}

int main()
{
	int n;
	printf("NR. PRODUSE = ");
	scanf("%d", &n);

	/*produs* vp = (produs*)malloc(n * sizeof(produs));
	citireVectorProduse(vp, n);
	afisareVectorProduse(vp, n);*/

	int* coduri = (int*)malloc(n * sizeof(int));
	char** denumiri = (char**)malloc(n * sizeof(char*));
	float* preturi = (float*)malloc(n * sizeof(float));
	float* cantitati = (float*)malloc(n * sizeof(float));
	citire4Vectori(coduri, denumiri, preturi, cantitati, n);
	afisare4Vectori(coduri, denumiri, preturi, cantitati, n);
	dezalocare4Vectori(coduri, denumiri, preturi, cantitati, n);

	char** denumiri = (char**)malloc(n * sizeof(char*));
	float** mat = (float**)malloc(n * sizeof(float*));
	for (int i = 0; i < n; i++)
	{
		mat[i] = (float*)malloc(3 * sizeof(float));
	}

	citireMatrice(mat, denumiri, n);
	afisareMatrice(mat, denumiri, n);
	dezalocareMatrice(mat, denumiri, n);
	return 0;
}