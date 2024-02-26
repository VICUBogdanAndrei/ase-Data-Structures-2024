#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int zi, luna, an;
} dataTransmitere;

typedef struct
{
	dataTransmitere data;
	char* expeditor;
	float dimensiune;
} email;

typedef struct
{
	email inf;
	struct nodStiva* next;
} nodStiva;

typedef struct
{
	email inf;
	struct nodCoada* next;
} nodCoada;

nodStiva* push(nodStiva* varf, email e)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.data.zi = e.data.zi;
	nou->inf.data.luna = e.data.luna;
	nou->inf.data.an = e.data.an;
	nou->inf.dimensiune = e.dimensiune;
	nou->inf.expeditor = (char*)malloc((strlen(e.expeditor) + 1) 
		* sizeof(char));
	strcpy(nou->inf.expeditor, e.expeditor);
	nou->next = NULL;
	if (varf == NULL)
		varf = nou;
	else
	{
		nou->next = varf;
		varf = nou;
	}
	return varf;
}

int pop(nodStiva** varf, email* e)
{
	if (*varf == NULL)
		return -1;
	else
	{
		(*e).data.zi = (*varf)->inf.data.zi;
		(*e).data.luna = (*varf)->inf.data.luna;
		(*e).data.an = (*varf)->inf.data.an;
		(*e).dimensiune = (*varf)->inf.dimensiune;
		(*e).expeditor = (char*)malloc((strlen((*varf)->inf.expeditor) + 1) * sizeof(char));
		strcpy((*e).expeditor, (*varf)->inf.expeditor);
		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->inf.expeditor);
		free(temp);
		return 0;
	}
}

void put(nodCoada** prim, nodCoada** ultim, email e)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.data.zi = e.data.zi;
	nou->inf.data.luna = e.data.luna;
	nou->inf.data.an = e.data.an;
	nou->inf.dimensiune = e.dimensiune;
	nou->inf.expeditor = (char*)malloc((strlen(e.expeditor) + 1)
		* sizeof(char));
	strcpy(nou->inf.expeditor, e.expeditor);
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

int get(nodCoada** prim, nodCoada** ultim, email* e)
{
	if (*prim != NULL && *ultim != NULL)
	{
		(*e).data.zi = (*prim)->inf.data.zi;
		(*e).data.luna = (*prim)->inf.data.luna;
		(*e).data.an = (*prim)->inf.data.an;
		(*e).dimensiune = (*prim)->inf.dimensiune;
		(*e).expeditor = (char*)malloc((strlen((*prim)->inf.expeditor) + 1) * sizeof(char));
		strcpy((*e).expeditor, (*prim)->inf.expeditor);
		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.expeditor);
		free(temp);
		return 0;
	}
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void afisare(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("\nData: %d-%d-%d, Expeditor: %s, Dimensiune: %5.2f",
			temp->inf.data.zi, temp->inf.data.luna,
			temp->inf.data.an, temp->inf.expeditor,
			temp->inf.dimensiune);
		temp = temp->next;
	}
}

void afisareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nData: %d-%d-%d, Expeditor: %s, Dimensiune: %5.2f",
			temp->inf.data.zi, temp->inf.data.luna,
			temp->inf.data.an, temp->inf.expeditor,
			temp->inf.dimensiune);
		temp = temp->next;
	}
}

void conversieStivaVector(nodStiva* varf, email* vect, int* nr)
{
	email e;
	while (pop(&varf, &e) == 0)
	{
		vect[*nr] = e;
		(*nr)++;
	}
}

void conversieStivaCoada(nodStiva* varf, nodCoada** prim, nodCoada** ultim)
{
	email e;
	while (pop(&varf, &e) == 0)
		put(prim, ultim, e);
}

void main()
{
	int nr;
	nodStiva* varf = NULL;
	nodCoada* prim = NULL, * ultim = NULL;
	char buffer[20];
	email e;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++)
	{
		fscanf(f, "%d", &e.data.zi);
		fscanf(f, "%d", &e.data.luna);
		fscanf(f, "%d", &e.data.an);
		fscanf(f, "%s", buffer);
		e.expeditor = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(e.expeditor, buffer);
		fscanf(f, "%f", &e.dimensiune);
		varf = push(varf, e);
		//put(&prim, &ultim, e);
		free(e.expeditor);
	}
	afisare(varf);

	printf("\n-------------------\n");

	/*email* vect = (email*)malloc(nr * sizeof(email));
	int nrVect = 0;
	conversieStivaVector(varf, vect, &nrVect);
	for (int i = 0; i < nrVect; i++)
	{
		printf("\nData: %d-%d-%d, Expeditor: %s, Dimensiune: %5.2f",
			vect[i].data.zi, vect[i].data.luna,
			vect[i].data.an, vect[i].expeditor,
			vect[i].dimensiune);
	}
	for (int i = 0; i < nrVect; i++)
		free(vect[i].expeditor);
	free(vect);*/

	/*while (pop(&varf, &e) == 0)
		free(e.expeditor);*/

	printf("\n---------Coada----------\n");
	
	conversieStivaCoada(varf, &prim, &ultim);
	
	afisareCoada(prim);

	while (get(&prim, &ultim, &e) == 0)
		free(e.expeditor);
}

