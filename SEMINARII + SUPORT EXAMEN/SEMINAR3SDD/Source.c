//LISTA DUBLA INLANTUITA

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

typedef struct {
	int* cod;
	char* denumire;
	float pret;
	float cantitate;
}produs;

typedef struct {
	produs info;
	struct nodls* next, *prev;
}nodls;

nodls* inserareNod(nodls* cap, nodls** coada, produs p)
{
	//pas 1 - alocare spatiu nod nou
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	//pas 2 - initializare nod nou <=> informatia utila + adresa urmatorului nod
	nou->info.cod = (int*)malloc(1 * sizeof(int));
	*(nou->info.cod) = *(p.cod);
	nou->info.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, p.denumire);
	nou->info.pret = p.pret;
	nou->info.cantitate = p.cantitate;
	nou->next = NULL;
	nou->prev = NULL;
	//pas 3 - inserare nod nou in lista (la sfarsit sau la inceput)
	if (cap == NULL)
	{
		cap = nou;
		nou->next = cap;
		nou->prev = cap;
		*coada = nou;
	}
	else
	{
		nodls* temp = cap;
		while (temp->next != cap)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
		(*coada)->next = cap;   
		cap->prev = *coada;
	}
	return cap;

}

void traversare(nodls* cap)
{
	nodls* temp = cap;
	while (temp->next != cap)
	{
		//afisare noduri
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f",
			*(temp->info.cod), temp->info.denumire, temp->info.pret, temp->info.cantitate);
		temp = temp->next;
	}
	printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f",
		*(temp->info.cod), temp->info.denumire, temp->info.pret, temp->info.cantitate);
}


void traversareInvers(nodls* coada)
{
	nodls* temp = coada;
	while (temp->prev != coada)
	{
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f",
			*(temp->info.cod), temp->info.denumire, temp->info.pret, temp->info.cantitate);
		temp = temp->prev;
	}
	printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f",
		*(temp->info.cod), temp->info.denumire, temp->info.pret, temp->info.cantitate);
}

void salvareProdusePret(nodls* cap, produs* vect, int* nr)
{
	nodls* temp = cap;
	while (temp->next != cap)
	{
		if (temp->info.pret < 9)
		{
			//copiere in vector
			//*nr pentru ca are & la parametrii functiei
			vect[*nr].cod = (int*)malloc(sizeof(int));
			*(vect[*nr].cod) = *(temp->info.cod);
			vect[*nr].denumire = (char*)malloc((strlen(temp->info.denumire) + 1) * sizeof(char));
			strcpy(vect[*nr].denumire, temp->info.denumire);
			vect[*nr].pret = temp->info.pret;
			vect[*nr].cantitate = temp->info.cantitate;
			(*nr)++;
		}
		temp = temp->next;
	}
	if (temp->info.pret < 9)
	{
		vect[*nr].cod = (int*)malloc(sizeof(int));
		*(vect[*nr].cod) = *(temp->info.cod);
		vect[*nr].denumire = (char*)malloc((strlen(temp->info.denumire) + 1) * sizeof(char));
		strcpy(vect[*nr].denumire, temp->info.denumire);
		vect[*nr].pret = temp->info.pret;
		vect[*nr].cantitate = temp->info.cantitate;
		(*nr)++;
	}
}

void dezalocare(nodls* cap)
{
	nodls* temp = cap;
	while (temp->next != cap)
	{
		nodls* temp2 = temp->next;
		free(temp->info.denumire);
		free(temp->info.cod);
		free(temp);
		temp = temp2;
	}
	free(temp->info.denumire);
	free(temp->info.cod);
	free(temp);
}
void main()
{
	int n;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	nodls* cap = NULL, *coada = NULL;
	produs p;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		//cod
		p.cod = (int*)malloc(1 * sizeof(int));
		fscanf(f, "%d", p.cod);

		//denumire
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);

		//pret
		fscanf(f, "%f", &p.pret);

		//cantitate
		fscanf(f, "%f", &p.cantitate);

		cap = inserareNod(cap, &coada, p);
		free(p.denumire);
		free(p.cod);
	}

	//inchidere fisier
	fclose(f);

	traversare(cap);
	printf("\n");
	traversareInvers(coada);

	//salavre in vector
	printf("\n\n--------------------------------\n");
	produs* vect = (produs*)malloc(n * sizeof(produs));
	int nr = 0;
	salvareProdusePret(cap, vect, &nr);
	for (int i = 0; i < nr; i++)
	{
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f",
			*(vect[i].cod), vect[i].denumire, vect[i].pret, vect[i].cantitate);
	}
	for (int i = 0; i < nr; i++)
	{
		free(vect[i].denumire);
		free(vect[i].cod);
	}
	free(vect);

	dezalocare(cap);


}