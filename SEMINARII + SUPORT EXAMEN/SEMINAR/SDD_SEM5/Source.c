#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct
{
	int cod;
	char* denumire;
	float pret;
	float cantitate;
	char* categorie;
}produs;

typedef struct
{
	produs inf;
	struct nodLS* next;
}nodLS;

typedef struct
{
	struct nodLS* inf;
	struct nodLP* next;
}nodLP;

void inserareLS(nodLS** capLS, produs p)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc(strlen(p.denumire)+1);
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;
	nou->inf.categorie = (char*)malloc(strlen(p.categorie) + 1);
	strcpy(nou->inf.categorie, p.categorie);
	nou->next = NULL;
	if (*capLS == NULL)
		*capLS = nou;
	else{
		nodLS* temp = *capLS;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}


void inserareLP(nodLP** capLP, nodLS* capLS)
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->inf = capLS;
	nou->next = NULL;

	if (*capLP == NULL)
		*capLP = nou;
	else {
		nodLS* temp = *capLP;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		printf("\n Cod = %d, Denumire = &s, Pret = %5.2f, Cantitate = %5.2f, Categorie = %s", temp->inf.cod, temp->inf.denumire, temp->inf.pret, temp->inf.cantitate, temp->inf.categorie);
		temp = temp->next;
		
	}
}
void traversareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	int i = 1;
	while (temp)
	{
		printf("Sublista: %d", i++);
		traversare(temp->inf);
		temp = temp->next;

	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp->inf.denumire);
		free(temp->inf.categorie);
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp)
	{
		nodLP* temp2 = temp->next;
		dezalocareLS(temp->inf);
		free(temp);
		temp = temp2;

	}
}

void main()
{
	int nrProd;
	char  buffer[20];
	nodLP* capLP = NULL;
	nodLS* capLSbio = NULL, *capLSnonbio = NULL;
	produs p;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrProd);
	for (int i = 0; i < nrProd; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);

		p.denumire = (char*)malloc(strlen(buffer) + 1);
		strcpy(p.denumire, buffer);
		fscanf(f, "%f", &p.pret);
		fscanf(f, "%f", &p.cantitate);
		fscanf(f, "%s", buffer);
		p.categorie = (char*)malloc(strlen(buffer) + 1);
		strcpy(p.categorie, buffer);
		if (strcmp(p.categorie, "BIO") == 0)
			inserareLS(&capLSbio, p);
		else
			inserareLS(&capLSnonbio, p);
		free(p.denumire);
		free(p.categorie);

	}
	fclose(f);
	inserareLP(&capLP, capLSbio);
	inserareLP(&capLP, capLSnonbio);

	traversareLP(capLP);
	dezalocareLP(capLP);
}