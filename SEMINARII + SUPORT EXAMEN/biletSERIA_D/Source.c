#define _CRT_SECURE_NO_WARNINGS

#include<malloc.h>
#include<stdio.h>
#include <string.h>

typedef struct
{
	unsigned int codProiect;
	char* titluProiect;
	char* beneficiar;
	unsigned int numarExecutanti;
	float buget;
}proiect;

typedef struct
{
	proiect info;
	struct nodld* prev, * next;
}nodld;

typedef struct
{
	proiect* vect;
	int nrElem;
}heap;


nodld* inserareNod(nodld* cap, nodld** coada, proiect p)
{
	nodld* nou = (nodld*)malloc(sizeof(nodld));
	nou->info.codProiect = p.codProiect;
	nou->info.titluProiect = (char*)malloc((strlen(p.titluProiect) + 1) * sizeof(char));
	strcpy(nou->info.titluProiect, p.titluProiect);
	nou->info.beneficiar = (char*)malloc((strlen(p.beneficiar) + 1) * sizeof(char));
	strcpy(nou->info.beneficiar, p.beneficiar);
	nou->info.numarExecutanti = p.numarExecutanti;
	nou->info.buget = p.buget;
	nou->next = NULL;
	nou->prev = NULL;

	if (cap == NULL)
	{
		cap = nou;
		nou->next = cap;
		nou->prev = cap; 
		*coada = nou;
	}
	else
	{
		nodld* temp = cap;
		while (temp->next != cap)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		(*coada) = nou;
		(*coada)->next = cap;
		cap->prev = *coada;
	}
	return cap;
}

void traversare(nodld* cap)
{
	nodld* temp = cap;
	while (temp->next != cap)
	{
		printf("\nCod Proiect = %d, Titlu Proiect = %s, Beneficiar = %s, Numar Executanti = %d, Buget = %5.2f",
			temp->info.codProiect, temp->info.titluProiect, temp->info.beneficiar, temp->info.numarExecutanti, temp->info.buget);
		temp = temp->next;
	}
	printf("\nCod Proiect = %d, Titlu Proiect = %s, Beneficiar = %s, Numar Executanti = %d, Buget = %5.2f",
		temp->info.codProiect, temp->info.titluProiect, temp->info.beneficiar, temp->info.numarExecutanti, temp->info.buget);
}

void traversareInversa(nodld* coada)
{
	nodld* temp = coada;
	while (temp->prev != coada)
	{
		printf("\nCod Proiect = %d, Titlu Proiect = %s, Beneficiar = %s, Numar Executanti = %d, Buget = %5.2f",
			temp->info.codProiect, temp->info.titluProiect, temp->info.beneficiar, temp->info.numarExecutanti, temp->info.buget);
		temp = temp->prev;
	}
	printf("\nCod Proiect = %d, Titlu Proiect = %s, Beneficiar = %s, Numar Executanti = %d, Buget = %5.2f",
		temp->info.codProiect, temp->info.titluProiect, temp->info.beneficiar, temp->info.numarExecutanti, temp->info.buget);
}

int numarExecutanti(nodld* cap, unsigned char prag)
{
	int nr = 0;
	nodld* temp = cap;
	while (temp->next != cap)
	{
		if (temp->info.numarExecutanti > prag)nr++;
		temp = temp->next;
	}
	if (temp->info.numarExecutanti > prag) nr++;

	return nr;
}

void actualizareBuget(nodld* cap, char* beneficiar, int procent)
{

	nodld* temp = cap;
	while (temp->next != cap)
	{
		if (strcmp(temp->info.beneficiar, beneficiar) == 0)
		{
			temp->info.buget = temp->info.buget+(temp->info.buget * procent) / 100;
		}
		temp = temp->next;
	}
	if (strcmp(temp->info.beneficiar, beneficiar) == 0)
	{
		temp->info.buget = temp->info.buget + (temp->info.buget * procent) / 100;
	}

}

void ordoanreListaDubla(nodld* cap)
{
	/*if (*cap == NULL || (*cap)->next == NULL)
		return;
	int schimbat = 1;
	//nodld* prim = *cap;
	/*while (schimbat)
	{
		schimbat = 0;
		nodld* temp = prim;
		while(temp->next!=(*cap) && temp->next!=prim)
		{ 
			nodld* temp2 = temp->next;
			if (temp->info.buget > temp2->info.buget)
			{
				proiect aux = temp->info;
				temp->info = temp2->info;
				temp2->info = aux;
				schimbat = 1;
			}
			temp = temp->next;
		}
		prim = prim->next;
	}
	nodld* temp = cap;
	int nr = 0;
	while (temp->next != cap) 
	{
		nr++;
		temp = temp->next;
	}
	for (int i = 0; i < nr-1; i++)
	{
		temp = *cap;
		for (int j = i + 1; j < nr; i++)
		{
			nodld* temp2 = temp->next;
			if (temp->info.buget > temp2->info.buget)
			{
				proiect aux = temp->info;
				temp->info = temp2->info;
				temp2->info = aux;
				schimbat = 1;

			}
			temp = temp->next;
		}
	}*/
	/*int swapped, i;
	nodld* ptr1;
	nodld* lptr = NULL;*/

	/* Checking for empty list */
	/*if (cap == NULL)
		return;

	do
	{
		swapped = 0;
		ptr1 = cap;

		while (ptr1->next != lptr)
		{
			nodld* temp2 = ptr1->next;
			if (ptr1->info.buget > temp2->info.buget)
			{
				swap(ptr1->info.buget, temp2->info.buget);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	} while (swapped);*/

}

void filtrare(heap h, int index)
{
	int indexRad = index;
	int indexStanga = (index * 2) + 1;
	int indexDreapta = (index) * 2 + 2;
	if (indexStanga<indexRad && h.vect[indexStanga].codProiect>h.vect[indexRad].codProiect)
		indexRad = indexStanga;
	if (indexDreapta<indexRad && h.vect[indexDreapta].codProiect>h.vect[indexRad].codProiect)
		indexRad = indexDreapta;

	if (indexRad != index)
	{
		proiect temp = h.vect[indexRad];
		h.vect[indexRad] = h.vect[index];
		h.vect[index] = h.vect[indexRad];

		filtrare(h, indexRad);
	}
}

heap inserare(heap h, proiect nou)
{
	proiect* vectNou = (proiect*)malloc((h.nrElem + 1) * sizeof(proiect));
	for (int i = 0; i < h.nrElem; i++)
		vectNou[i] = h.vect[i];
	h.nrElem++;
	vectNou[h.nrElem - 1] = nou;
	free(h.vect);
	h.vect = vectNou;
	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	return h;
}

void afisare(heap h)
{
	for (int i = 0; i < h.nrElem; i++)
	{
		printf("\nCod Proiect = %d, Titlu Proiect = %s, Beneficiar = %s, Numar Executanti = %d, Buget = %5.2f",
			h.vect[i].codProiect, h.vect[i].titluProiect, h.vect[i].beneficiar, h.vect[i].numarExecutanti, h.vect[i].buget);
	}
}


void main()
{
	FILE* f = fopen("fisier.txt", "r");
	int n;
	fscanf(f, "%d", &n);
	char buffer[30];
	proiect p;
	nodld* cap = NULL, *coada = NULL;
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &p.codProiect);
		fscanf(f, "%s", buffer);
		p.titluProiect = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.titluProiect, buffer);
		fscanf(f, "%s", buffer);
		p.beneficiar = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.beneficiar, buffer);
		fscanf(f, "%d", &p.numarExecutanti);
		fscanf(f, "%f", &p.buget);

		cap = inserareNod(cap, &coada, p);
	}
	fclose(f);

	traversare(cap);

	printf("\n\n---------------------\n");

	traversareInversa(coada);

	printf("\n\n---------------------\n\n");

	printf("Numar executanti cu prag 200: %d", numarExecutanti(cap, 200));

	printf("\n\n---------------------\n\n");

	char* beneficiar = (char*)malloc((strlen("Bogdan") + 1) * sizeof(char));
	strcpy(beneficiar, "Bogdan");
	actualizareBuget(cap, beneficiar, 10);
	traversare(cap);

	printf("\n\n---------------------\n\n");
	//ordoanreListaDubla(&cap);
	//traversare(cap);

	heap h;
	h.nrElem = 0;
	nodld* temp = cap;
	while (temp->next != cap)
	{
		if (strcmp(temp->info.beneficiar, beneficiar) == 0)
			h.nrElem++;
		temp = temp->next;
	}
	if (strcmp(temp->info.beneficiar, beneficiar) == 0)
		h.nrElem;

	h.vect = (proiect*)malloc(h.nrElem * sizeof(proiect));

	while (temp->next != cap)
	{
		if (strcmp(temp->info.beneficiar, beneficiar) == 0)
			inserare(h, temp->info);
		temp = temp->next;
	}
	if (strcmp(temp->info.beneficiar, beneficiar) == 0)
		inserare(h, temp->info);
	afisare(h);
}