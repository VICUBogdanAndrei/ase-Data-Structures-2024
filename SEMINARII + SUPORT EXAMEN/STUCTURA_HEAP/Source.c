#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct
{
	int prioritate;
	char* denumire;
	float cost;
} cheltuiala;


typedef struct {
	cheltuiala* vect;
	int nrElem;
}heap;

void filtrare(heap h, int index)
{
	int indexRad = index;
	int indexStanga = index * 2 + 1;
	int indexDreapta = index * 2 + 2;

	if (indexStanga < h.nrElem && h.vect[indexStanga].prioritate > h.vect[indexRad].prioritate)
		indexRad = indexStanga;

	if (indexDreapta < h.nrElem && h.vect[indexDreapta].prioritate > h.vect[indexRad].prioritate)
		indexRad = indexDreapta;

	if (index != indexRad)
	{
		cheltuiala temp = h.vect[index];
		h.vect[index] = h.vect[indexRad];
		h.vect[indexRad] = temp;

		filtrare(h,indexRad);
	}
}

heap inserare(heap h, cheltuiala noua)
{
	cheltuiala* vectNou = (cheltuiala*)malloc(sizeof(cheltuiala) * (h.nrElem + 1));
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	h.nrElem++;
	vectNou[h.nrElem - 1] = noua;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

heap extragere(heap h, cheltuiala* extrasa)
{
	cheltuiala* vectNou = (cheltuiala*)malloc((h.nrElem - 1) * sizeof(cheltuiala));

	cheltuiala temp = h.vect[0];
	h.vect[0] = h.vect[h.nrElem - 1];
	h.vect[h.nrElem - 1] = temp;

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

void afisare(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
		printf("\nPrioritate: %d, Denumire: %s, Cost: %5.2f", 
			h.vect[i].prioritate, h.vect[i].denumire, h.vect[i].cost);
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
	h.vect = (cheltuiala*)malloc(h.nrElem * sizeof(cheltuiala));
	for (int i = 0; i < h.nrElem; i++)
	{
		fscanf(f, "%d", &h.vect[i].prioritate);
		fscanf(f, "%s", buffer);
		h.vect[i].denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(h.vect[i].denumire, buffer);
		fscanf(f, "%f", &h.vect[i].cost);
	}
	fclose(f);
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	afisare(h);

	cheltuiala extras;
	h = extragere(h, &extras);
	printf("\n\n---------------------------\n");
	printf("Elementul extras este #%s, cu prioritatea %d\n\n", extras.denumire, extras.prioritate);

	afisare(h);
}
