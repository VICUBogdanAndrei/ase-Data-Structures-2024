#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int prioritate;
	char* denumire;
	int efortDepus;
} dorinta;

typedef struct
{
	dorinta* vect;
	int nrElem;
	int nrModif;
} heap;

void filtrare(heap h, int index)
{
	int indexRad = index;
	int indexSt = 2 * index + 1;
	int indexDr = 2 * index + 2;

	if (indexSt < h.nrModif && h.vect[indexSt].prioritate>
		h.vect[indexRad].prioritate)
		indexRad = indexSt;
	if (indexDr < h.nrModif && h.vect[indexDr].prioritate>
		h.vect[indexRad].prioritate)
		indexRad = indexDr;

	if (index != indexRad)
	{
		dorinta aux = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = aux;

		filtrare(h, indexRad);
	}
}

heap inserare(heap h, dorinta noua)
{
	dorinta* vectNou = (dorinta*)malloc((h.nrElem + 1) *
		sizeof(dorinta));
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	h.nrElem++;
	h.nrModif = h.nrElem;
	vectNou[h.nrElem - 1] = noua;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

heap extragere(heap h, dorinta* extrasa)
{
	dorinta* vectNou = (dorinta*)malloc((h.nrElem - 1) *
		sizeof(dorinta));

	dorinta aux = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = aux;

	*extrasa = h.vect[h.nrElem - 1];

	h.nrElem--;
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

void afisareHeap(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		printf("\nPrioritate: %d, Denumire: %s, Efort: %d",
			h.vect[i].prioritate,
			h.vect[i].denumire,
			h.vect[i].efortDepus);
}

void sortareHeap(heap* h)
{
	if (h->nrModif == 0)
		return;
	dorinta aux = h->vect[0];
	h->vect[0] = h->vect[h->nrModif - 1];
	h->vect[h->nrModif - 1] = aux;
	h->nrModif--;
	for (int i = (h->nrModif - 1) / 2; i >= 0; i--)
		filtrare(*h, i);
	sortareHeap(h);
}

void dezalocareHeap(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		free(h.vect[i].denumire);
	free(h.vect);
}

void main()
{
	heap h;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &h.nrElem);
	h.vect = (dorinta*)malloc(h.nrElem * sizeof(dorinta));
	for (int i = 0; i < h.nrElem; i++)
	{
		fscanf(f, "%d", &h.vect[i].prioritate);
		fscanf(f, "%s", buffer);
		h.vect[i].denumire = (char*)malloc((strlen(buffer) + 1) *
			sizeof(char));
		strcpy(h.vect[i].denumire, buffer);
		fscanf(f, "%d", &h.vect[i].efortDepus);
	}
	fclose(f);
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	afisareHeap(h);

	dorinta noua;
	printf("\nPrioritate: ");
	scanf("%d", &noua.prioritate);
	printf("\nDenumire: ");
	scanf("%s", buffer);
	noua.denumire = (char*)malloc((strlen(buffer) + 1) *
		sizeof(char));
	strcpy(noua.denumire, buffer);
	printf("\nEfort depus:");
	scanf("%d", &noua.efortDepus);

	h = inserare(h, noua);
	afisareHeap(h);

	printf("\n----------------\n");

	sortareHeap(&h);

	printf("\n----------------\n");

	afisareHeap(h);
	/*dorinta extrasa;
	h = extragere(h, &extrasa);
	printf("\nPrioritate: %d, Denumire: %s, Efort: %d",
		extrasa.prioritate, extrasa.denumire, extrasa.efortDepus);
	
	printf("\n----------------\n");

	afisareHeap(h);*/

	dezalocareHeap(h);
}