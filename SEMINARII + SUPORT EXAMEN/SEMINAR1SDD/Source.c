#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int* cod;
	char* denumire;
	float pret;
	float cantitate;
}produs;

void citireVectoriProduse(produs* vp, int n)
{
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		printf("Cod = ");
		vp[i].cod = (int*)malloc(1 * sizeof(int));
		scanf("%d", vp[i].cod);
		printf("Denumire = ");
		scanf("%s", buffer);
		vp[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(vp[i].denumire, buffer);
		printf("Pret = ");
		scanf("%f", &vp[i].pret);
		printf("Cantitate = ");
		scanf("%f", &vp[i].cantitate);
	}
}

void afisareVecotriProdise(produs* vp, int n)
{
	for (int i = 0; i < n; i++)
		printf("\nCod = %d \nDenumire = %s \nPret = %5.2f \nCantitate = %5.2f\n",*(vp[i].cod), vp[i].denumire, vp[i].pret, vp[i].cantitate);
}


void dezalocareVectorProduse(produs* vp, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(vp[i].cod);
		free(vp[i].denumire);
	}
	free(vp);
}

void citire4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati, int n)
{
	char buffer[100];
	for (int i = 0; i < n; i++)
	{
		printf("Cod = ");
		scanf("%d", &coduri[i]);
		printf("Denumire = ");
		scanf("%s", buffer);
		denumiri[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(denumiri[i], buffer);
		printf("Pret = ");
		scanf("%f", &preturi[i]);
		printf("Cantitate = ");
		scanf("%f", &cantitati[i]);
	}
}

void afisare4Vectori(int* coduri, char** denumiri, float* preturi, float* cantitati, int n)
{
	for (int i = 0; i < n; i++)
		printf("\nCod = %d \nDenumire = %s \nPret = %5.2f \nCantitate = %5.2f\n", coduri[i], denumiri[i], preturi[i], cantitati[i]);
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

void citireMatrice(float** mat, char** denumire, int n)
{
	char buffer[100];
	for (int i = 0; i < n; i++)
	{
		printf("Denumire = ");
		scanf("%s", buffer);
		denumire[i] = (char**)malloc((strlen(buffer) + 1) * sizeof(char*));
		strcpy(denumire[i], buffer);
		//for (int j = 0; j < 3; j++)
		//{
			printf("Cod: mat[%d][0] = ", i);
			scanf("%f", &mat[i][0]);
			printf("Pret: mat[%d][1] = ", i);
			scanf("%f", &mat[i][1]);
			printf("Cantitate: mat[%d][2] = ", i);
			scanf("%f", &mat[i][2]);
		//}
	}
}

void afisareMatrice(float** mat, char** denumire, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("\nCod = %5.2f \nDenumire = %s \nPret = %5.2f \nCantitate = %5.2f", mat[i][0], denumire[i], mat[i][1], mat[i][2]);
	}
}

void dezalocareMatrice(float** mat, char** denumire, int n)
{
	for (int i = 0; i < n; i++)
	{
		free(denumire[i]);
		free(mat[i]);
	}
	free(denumire);
	free(mat);
}


void main()
{
	//vector de produse

	/*int n = 1;
	produs* vp = (produs*)malloc(n * sizeof(produs));
	citireVectoriProduse(vp, n);
	afisareVecotriProdise(vp, n);
	dezalocareVectorProduse(vp, n);*/

	//4Vectori

	/*int n;
	printf("n = ");
	scanf("%d", &n);
	int* coduri = (int*)malloc(n * sizeof(int));
	char** denumiri = (char**)malloc(n * sizeof(char*));
	float* preturi = (float*)malloc(n * sizeof(float));
	float* cantitati = (float*)malloc(n * sizeof(float));
	
	citire4Vectori(coduri, denumiri, preturi, cantitati, n);
	afisare4Vectori(coduri, denumiri, preturi, cantitati, n);
	dezalocare4Vectori(coduri, denumiri, preturi, cantitati, n);*/

	//matrice + denumiriVector
	int n;
	printf("n = ");
	scanf("%d", &n);
	char** denumire = (char**)malloc(n * sizeof(char*));
	float** mat = (float**)malloc(n * sizeof(float*));
	for (int i = 0; i < n; i++)
		mat[i] = (float*)malloc(3 * sizeof(float));
	citireMatrice(mat, denumire, n);
	afisareMatrice(mat, denumire, n);
	dezalocareMatrice(mat, denumire, n);


}