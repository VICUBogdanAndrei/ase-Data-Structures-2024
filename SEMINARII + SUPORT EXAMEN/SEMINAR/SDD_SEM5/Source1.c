#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
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
	struct nodlp* next;
}nodLP;

nodLS* creareLs(produs p)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc(strlen(p.denumire) + 1);
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->inf.cantitate = p.cantitate;
	nou->inf.categorie = (char*)malloc(strlen(p.categorie) + 1);
	strcpy(nou->inf.categorie, p.categorie);
	nou->next = NULL;
	return nou;
}

void inserareLs(nodLS** capLS, produs p)
{
	nodLS* nou = creareLs(p);
	if (*capLS == NULL)
		*capLS = nou;
	else
	{
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
	else
	{
		nodLP* temp = *capLP;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void traversareLs(nodLS* capLS)
{
	while (capLS)
	{
		printf("Cod=%d Denumire=%s pret=%f cantitate=%f categorie=%s", capLS->inf.cod,
			capLS->inf.denumire, capLS->inf.pret, capLS->inf.cantitate, capLS->inf.categorie);
		capLS = capLS->next;
	}
}

void traversareLP(nodLP* capLP)
{
	int i = 0;
	while (capLP)
	{
		printf("\nSublista: %d\n", ++i);
		traversareLs(capLP->inf);
		capLP = capLP->next;
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
	char buffer[20];
	nodLP* capLP = NULL;
	nodLS* capLSbio = NULL, * capLSbnonBIO = NULL;
	produs p;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrProd);
	for (int i = 0; i < nrProd; ++i)
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
			inserareLs(&capLSbio, p);
		else
			inserareLs(&capLSbnonBIO, p);
		free(p.denumire);
		free(p.categorie);
	}
	fclose(f);
	inserareLP(&capLP, capLSbio);
	inserareLP(&capLP, capLSbnonBIO);

	traversareLP(capLP);
	dezalocareLP(capLP);
}