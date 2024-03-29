#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

typedef struct {
	int cod;
	char* denumire;
	float pret;
	float cantitate;
} produs;

typedef struct {
	produs inf;
	struct nodls* next;
}nodls;

//functie cu void

//void inserareNod(nodls** cap, produs p)
//{
//	//pas 1 - alocare spatiu de memorie pentru un nod nou
//	nodls* nou = (nodls*)malloc(sizeof(nodls));
//	//pas 2 - initializare nod nou (informatie utila + poiter legatura)
//	nou->inf = p;
//	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
//	strcpy(nou->inf.denumire, p.denumire);
//	nou->inf.pret = p.pret;
//	nou->inf.cantitate = p.cantitate;
//	nou->next = NULL;
//	//pas 3 - inserare nod nou in lista (la sfarsit sau la inceput)
//	if (*cap == NULL)
//		*cap = nou;
//	else
//	{
//		nodls* temp = *cap;
//		while (temp->next != NULL)
//			temp = temp->next;
//		temp->next = nou;
//	}
//}


nodls* inserareNod(nodls* cap, produs p)
{
	//pas 1 - alocare spatiu de memorie pentru un nod nou
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	//pas 2 - initializare nod nou (informatie utila + poiter legatura)
	nou->inf = p;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;
	nou->next = NULL;
	//pas 3 - inserare nod nou in lista (la sfarsit sau la inceput)
	if (cap == NULL)
		cap = nou;
	else
	{
		nodls* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

void traversare(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		printf("\nCod = %d, Denumire = %s, Pret = %5.2f, Cantitate = %5.2f", temp->inf.cod, temp->inf.denumire, temp->inf.pret, temp->inf.cantitate);
		temp = temp->next;
	}
}

void dezalocare(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		nodls* temp2 = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = temp2;
	}
}


void main()
{
	//citire de la tastatura
	//citire din fisier

	int n;
	//printf("Nr produse = ");
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f,"%d", &n);
	nodls* cap = NULL;
	produs p;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		//printf("Cod = ");
		fscanf(f,"%d", &p.cod);
		//printf("Denumire = ");
		fscanf(f,"%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		//printf("Pret = ");
		fscanf(f,"%f", &p.pret);
		//printf("Cantitate = ");
		fscanf(f,"%f", &p.cantitate);
		cap = inserareNod(cap, p);
		free(p.denumire);
	}
	fclose(f);
	traversare(cap);
	dezalocare(cap);
}
