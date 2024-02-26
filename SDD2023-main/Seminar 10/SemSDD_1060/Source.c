#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int id;
	char* denumire;
	int nrLocuitori;
} oras;

typedef struct
{
	int inf;
	struct nodStiva* next;
} nodStiva;

typedef struct
{
	int inf;
	struct nodCoada* next;
} nodCoada;

typedef struct
{
	int idNodStart, idNodFinal, greutateArc;
	struct nodLista* next;
} nodLista;

void push(nodStiva** varf, int val)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf = val;
	nou->next = NULL;
	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodStiva** varf, int* val)
{
	if (*varf == NULL)
		return -1;
	else
	{
		*val = (*varf)->inf;
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp);
		return 0;
	}
}

void put(nodCoada** prim, nodCoada** ultim, int val)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf = val;
	nou->next = NULL;
	if (*prim == NULL || *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

int get(nodCoada** prim, nodCoada** ultim, int* val)
{
	if (*prim != NULL && *ultim != NULL)
	{
		*val = (*prim)->inf;
		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp);
		return 0;
	}
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void parcurgereAdancime(int** mat, int nrNoduri, oras* vect,
	int* vizitat, int idNodStart)
{
	for (int i = 0; i < nrNoduri; i++)
		vizitat[i] = 0;

	nodStiva* varf = NULL;

	push(&varf, idNodStart);
	vizitat[idNodStart] = 1;
	while (varf != NULL)
	{
		pop(&varf, &idNodStart);
		printf("\n%d %s %d", idNodStart + 1,
			vect[idNodStart].denumire, vect[idNodStart].nrLocuitori);
		for(int k=0;k<nrNoduri;k++)
			if (mat[idNodStart][k] != 0 && vizitat[k] == 0)
			{
				push(&varf, k);
				vizitat[k] = 1;
			}
	}
}

void parcurgereLatime(int** mat, int nrNoduri, oras* vect,
	int* vizitat, int idNodStart)
{
	for (int i = 0; i < nrNoduri; i++)
		vizitat[i] = 0;

	nodCoada* prim = NULL, * ultim = NULL;

	put(&prim, &ultim, idNodStart);
	vizitat[idNodStart] = 1;
	while (prim != NULL)
	{
		get(&prim, &ultim, &idNodStart);
		printf("\n%d %s %d", idNodStart + 1,
			vect[idNodStart].denumire, vect[idNodStart].nrLocuitori);
		for (int k = 0; k < nrNoduri; k++)
			if (mat[idNodStart][k] != 0 && vizitat[k] == 0)
			{
				put(&prim, &ultim, k);
				vizitat[k] = 1;
			}
	}
}

nodLista* inserareLista(nodLista* cap, int idNodS, int idNodF, int gr)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->idNodStart = idNodS;
	nou->idNodFinal = idNodF;
	nou->greutateArc = gr;
	nou->next = NULL;
	if (cap == NULL)
		cap = nou;
	else
	{
		nodLista* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

void afisareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		printf("(%d, %d, %d) -> ", temp->idNodStart,
			temp->idNodFinal, temp->greutateArc);
		temp = temp->next;
	}
}

void transformListaArce(nodLista** cap, int** mat, int nrNoduri)
{
	for (int i = 0; i < nrNoduri; i++)
		for (int j = 0; j < nrNoduri; j++)
			if (mat[i][j] != 0)
				*cap = inserareLista(*cap, i + 1, j + 1, mat[i][j]);
}

nodLista* arcGreutateMinima(nodLista* cap)
{
	nodLista* temp = cap;
	nodLista* min = cap;
	while (temp)
	{
		if (min->greutateArc > temp->greutateArc)
			min = temp;
		temp = temp->next;
	}
	return min;
}

void main()
{
	FILE* f = fopen("fisier.txt", "r");
	int nrNoduri, nrArce;
	fscanf(f, "%d", &nrNoduri);
	int** mat = (int**)malloc(nrNoduri * sizeof(int*));
	for (int i = 0; i < nrNoduri; i++)
		mat[i] = (int*)malloc(nrNoduri * sizeof(int));
	for (int i = 0; i < nrNoduri; i++)
		for (int j = 0; j < nrNoduri; j++)
			mat[i][j] = 0;

	oras* vect = (oras*)malloc(nrNoduri * sizeof(oras));
	char buffer[20];
	for (int i = 0; i < nrNoduri; i++)
	{
		fscanf(f, "%d", &vect[i].id);
		fscanf(f, "%s", buffer);
		vect[i].denumire = (char*)malloc((strlen(buffer) + 1) *
			sizeof(char));
		strcpy(vect[i].denumire, buffer);
		fscanf(f, "%d", &vect[i].nrLocuitori);
	}
	fscanf(f, "%d", &nrArce);
	int ii, jj, greutate;
	for (int i = 0; i < nrArce; i++)
	{
		fscanf(f, "%d", &ii);
		fscanf(f, "%d", &jj);
		fscanf(f, "%d", &greutate);
		mat[ii - 1][jj - 1] = greutate;
		mat[jj - 1][ii - 1] = greutate;
	}
	fclose(f);

	int* vizitat = (int*)malloc(nrNoduri * sizeof(int));
	int idNodStart;
	printf("\nNod start parcurgere adancime: ");
	scanf("%d", &idNodStart);
	parcurgereAdancime(mat, nrNoduri, vect, vizitat, idNodStart);
	printf("\nNod start parcurgere latime: ");
	scanf("%d", &idNodStart);
	parcurgereLatime(mat, nrNoduri, vect, vizitat, idNodStart);

	nodLista* cap = NULL;
	transformListaArce(&cap, mat, nrNoduri);
	afisareLista(cap);

	nodLista* min = arcGreutateMinima(cap);
	printf("\nArc greutate minima: (%d, %d, %d)",
		min->idNodStart, min->idNodFinal, min->greutateArc);
}