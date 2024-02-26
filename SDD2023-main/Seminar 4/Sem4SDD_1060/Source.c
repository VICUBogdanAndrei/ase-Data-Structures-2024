#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int zi, luna, an;
} dataReceptionare;

typedef struct
{
	dataReceptionare data;
	char* mesaj;
	int durata;
} notificare;

typedef struct
{
	notificare inf;
	struct nodStiva* next;
} nodStiva;

typedef struct
{
	notificare inf;
	struct nodCoada* next;
} nodCoada;

void push(nodStiva** varf, notificare n)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf.data.zi = n.data.zi;
	nou->inf.data.luna = n.data.luna;
	nou->inf.data.an = n.data.an;
	nou->inf.mesaj = (char*)malloc((strlen(n.mesaj) + 1) * sizeof(char));
	strcpy(nou->inf.mesaj, n.mesaj);
	nou->inf.durata = n.durata;
	nou->next = NULL;
	if (*varf == NULL)
		*varf = nou;
	else
	{
		nou->next = *varf;
		*varf = nou;
	}
}

int pop(nodStiva** varf, notificare* n)
{
	if (*varf == NULL)
		return -1;
	else
	{
		(*n).data.zi = (*varf)->inf.data.zi;
		(*n).data.luna = (*varf)->inf.data.luna;
		(*n).data.an = (*varf)->inf.data.an;
		(*n).mesaj = (char*)malloc((strlen((*varf)->inf.mesaj) + 1) * sizeof(char));
		strcpy((*n).mesaj, (*varf)->inf.mesaj);
		(*n).durata = (*varf)->inf.durata;

		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->inf.mesaj);
		free(temp);
		return 0;
	}
}

void put(nodCoada** prim, nodCoada** ultim, notificare n)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->inf.data.zi = n.data.zi;
	nou->inf.data.luna = n.data.luna;
	nou->inf.data.an = n.data.an;
	nou->inf.mesaj = (char*)malloc((strlen(n.mesaj) + 1) * sizeof(char));
	strcpy(nou->inf.mesaj, n.mesaj);
	nou->inf.durata = n.durata;
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

int get(nodCoada** prim, nodCoada** ultim, notificare* n)
{
	if (*prim != NULL && *ultim != NULL)
	{
		(*n).data.zi = (*prim)->inf.data.zi;
		(*n).data.luna = (*prim)->inf.data.luna;
		(*n).data.an = (*prim)->inf.data.an;
		(*n).mesaj = (char*)malloc((strlen((*prim)->inf.mesaj) + 1) * sizeof(char));
		strcpy((*n).mesaj, (*prim)->inf.mesaj);
		(*n).durata = (*prim)->inf.durata;

		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp->inf.mesaj);
		free(temp);
		return 0;
	}
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void afisareStiva(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("\nData: %d-%d-%d, Mesaj: %s, Durata: %d",
			temp->inf.data.zi, temp->inf.data.luna,
			temp->inf.data.an, temp->inf.mesaj,
			temp->inf.durata);
		temp = temp->next;
	}
}

void afisareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nData: %d-%d-%d, Mesaj: %s, Durata: %d",
			temp->inf.data.zi, temp->inf.data.luna,
			temp->inf.data.an, temp->inf.mesaj,
			temp->inf.durata);
		temp = temp->next;
	}
}

void conversieStivaVector(nodStiva* varf, notificare* vect, int* nr)
{
	notificare n;
	while (pop(&varf, &n) == 0)
	{
		vect[*nr] = n;
		(*nr)++;
	}
}

void conversieStivaCoada(nodStiva* varf, nodCoada** prim, nodCoada** ultim)
{
	notificare n;
	while (pop(&varf, &n) == 0)
		put(prim, ultim, n);
}

void main()
{
	int nr;
	nodStiva* varf = NULL;
	char buffer[30];
	notificare n;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++)
	{
		fscanf(f, "%d", &n.data.zi);
		fscanf(f, "%d", &n.data.luna);
		fscanf(f, "%d", &n.data.an);
		fscanf(f, "%s", buffer);
		n.mesaj = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(n.mesaj, buffer);
		fscanf(f, "%d", &n.durata);
		push(&varf, n);
		free(n.mesaj);
	}
	afisareStiva(varf);

	printf("\n------------------\n");
	/*notificare* vect = (notificare*)malloc(nr * sizeof(notificare));
	int nrElem = 0;
	conversieStivaVector(varf, vect, &nrElem);
	for(int i=0;i<nrElem;i++)
		printf("\nData: %d-%d-%d, Mesaj: %s, Durata: %d",
			vect[i].data.zi, vect[i].data.luna,
			vect[i].data.an, vect[i].mesaj,
			vect[i].durata);

	for (int i = 0; i < nrElem; i++)
		free(vect[i].mesaj);
	free(vect);*/

	/*while (pop(&varf, &n) == 0)
		free(n.mesaj);*/

	nodCoada* prim = NULL, * ultim = NULL;
	conversieStivaCoada(varf, &prim, &ultim);
	afisareCoada(prim);

	while (get(&prim, &ultim, &n) == 0)
		free(n.mesaj);
}