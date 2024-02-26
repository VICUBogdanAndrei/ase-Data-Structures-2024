//LISTA SIMPLA INLANTUITA

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

// definirea structurii produs
typedef struct
{
	int* cod;
	char* denumire;
	float pret;
	float cantitate;
}produs;

//definirea strcuturii listei simple inlantuite
typedef struct {
	produs info;
	struct nodls* next;
}nodls;

nodls* inserareNod(nodls* cap, produs p)
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

	//pas 3 - inserare nod in lista (la inceput sau sfarsit)
	if (cap == NULL)
		cap = nou;
	else
	{
		//parcurgere pana la finalul listei pentru a gasi adresa ultimului nod
		//inseram la finalul listei noul nod
		nodls* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

// functia de traversare/afisare
void traversare(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		//afisare noduri
		printf("\nCod = %d \nDenumire = %s \nPret = %f \nCantitate = %f", (*temp->info.cod), temp->info.denumire, temp->info.pret, temp->info.cantitate);
		temp = temp->next;
	}
}

//dezalocare lista
void dezalocare(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		//declarare nod nou pentru nu a pierde adresa urmatorului nod din lista
		nodls* temp2 = temp->next;
		free(temp->info.cod);
		free(temp->info.denumire);
		free(temp);
		temp = temp2;
		
	}
}

void main()
{
	//citire elemente din fizier txt
	int n;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	nodls* cap = NULL;
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

		cap = inserareNod(cap, p);
		free(p.denumire);
		free(p.cod);
	}

	//inchidere fisier
	fclose(f);

	//apelare functii
	traversare(cap);
	dezalocare(cap);


}