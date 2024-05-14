#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int inf; //id nod;
	struct nodStiva* next;
}nodStiva;

// DF - stiva
// BF - coada


typedef struct {
	int inf; //id nod
	struct nodCoada* next;
}nodCoada;

void push(nodStiva** varf, int  idNod)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf = idNod;
	nou->next = NULL;
	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}


int pop(nodStiva** varf, int* idNod)
{
	if (*varf == NULL)
		return -1;
	else {
		*idNod = (*varf)->inf;
		nodStiva* aux = *varf;
		*varf = (*varf)->next;
		free(aux);
		return 0;
	}
}

void put(nodCoada** prim, nodCoada** ultim, int idNod)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf = idNod;
	nou->next = NULL;

	if (*prim == NULL || *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else {
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

int get(nodCoada** prim, nodCoada** ultim, int* idNod)
{
	if (*prim != NULL && *ultim != NULL)
	{
		*idNod = (*prim)->inf;
		nodCoada* aux = *prim;
		*prim = (*prim)->next;
		free(aux);
		return 0;
	}

	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

//folosim stiva
void parcurgereAdancime(int** mat, int* vizitate, int nrNoduri, int idNodStart)
{
	for (int i = 0; i < nrNoduri; i++)
		vizitate[i] = 0;
	nodStiva* varf = NULL;
	push(&varf, idNodStart);
	vizitate[idNodStart] = 1;

	while (varf != NULL)
	{
		pop(&varf, &idNodStart);
		printf("%d-", idNodStart + 1);
		for(int k=0; k<nrNoduri; k++)
			if (mat[idNodStart][k] != 0 && vizitate[k] == 0)
			{
				push(&varf, k);
				vizitate[k] = 1;
			}
	}

}

// se utilizeaza coada
void parcurgereLatime(int** mat, int* vizitate, int nrNoduri, int idNodStart)
{
	for (int i = 0; i < nrNoduri; i++)
		vizitate[i] = 0;
	nodCoada* prim = NULL, *ultim=NULL;
	put(&prim, &ultim, idNodStart);
	vizitate[idNodStart] = 1;

	while (prim != NULL)
	{
		get(&prim, &ultim, &idNodStart);
		printf("%d-", idNodStart + 1);
		for (int k = 0; k < nrNoduri; k++)
			if (mat[idNodStart][k] !=0 && vizitate[k] == 0)
			{
				put(&prim, &ultim, k);
				vizitate[k] = 1;
			}
	}

}



void main()
{
	FILE* f = fopen("fisier.txt", "r");
	
	int nrNoduri;
	fscanf(f, "%d", &nrNoduri);
	int** mat = (int**)malloc(nrNoduri * sizeof(int*));
	for (int i = 0; i < nrNoduri; i++)
		mat[i] = (int*)malloc(nrNoduri * sizeof(int));

	for (int i = 0; i < nrNoduri; i++)
		for (int j = 0; j < nrNoduri; j++)
			mat[i][j] = 0;

	int nrArce, idNodStart, idNodStop;
	int greutate, sum=0;

	fscanf(f, "%d", &nrArce);

	for (int i = 0; i < nrArce; i++)
	{
		fscanf(f, "%d", &idNodStart);
		fscanf(f, "%d", &idNodStop);
		fscanf(f, "%d", &greutate);

		if (idNodStart <= nrNoduri && idNodStop <= nrNoduri)
		{
			mat[idNodStart-1][idNodStop-1] = greutate;
			mat[idNodStop-1][idNodStart-1] = greutate;
			sum += greutate;
		}

		
	}

	fclose(f);

	int* vizitate = (int*)malloc(nrNoduri * sizeof(int));

	printf("Nodul Start = ");

	scanf("%d", &idNodStart);

	printf("\nParcurgere in adancime de la nodul %d: ", idNodStart);

	parcurgereAdancime(mat, vizitate, nrNoduri, idNodStart);


	printf("\nParcurgere in latime de la nodul %d: ", idNodStart);

	parcurgereLatime(mat, vizitate, nrNoduri, idNodStart);

	printf("\nSuma greutatilor = %d", sum);


	int minim = 10000;
	int linie = 0;
	int coloana = 0;
	for (int i = 0; i < nrNoduri; i++)
		for (int j = 0; j < nrNoduri; j++)
			if (mat[i][j] < minim && mat[i][j] != 0)
			{
				minim = mat[i][j];
				linie = i;
				coloana = j;
			}

	printf("\nArcul cu greutatea minima: %d-%d -- Greutatea: %d", linie+1, coloana+1, minim);
}

//[arcurgere in latime si adancime seminarul urmator