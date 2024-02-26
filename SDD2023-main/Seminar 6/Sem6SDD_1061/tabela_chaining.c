#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int cod;
	char* denumire;
	float pret;
	float cantitate;
	char* categorie;
} produs;

typedef struct
{
	produs inf;
	struct nodLS* next;
} nodLS;

typedef struct
{
	struct nodLS** vect;
	int nrElem;
} hashT;

int functieDispersie(hashT tabela, int cheie)
{
	return cheie % tabela.nrElem;
}

int functieDispersie2(hashT tabela, char den[20])
{
	return den[0] % tabela.nrElem;
}

void inserareTabela(hashT tabela, produs p)
{
	if (tabela.vect != NULL)
	{
		int pozitie = functieDispersie2(tabela, p.categorie);
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->inf.cod = p.cod;
		nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
		strcpy(nou->inf.denumire, p.denumire);
		nou->inf.pret = p.pret;
		nou->inf.cantitate = p.cantitate;
		nou->inf.categorie = (char*)malloc((strlen(p.categorie) + 1) * sizeof(char));
		strcpy(nou->inf.categorie, p.categorie);
		nou->next = NULL;
		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = nou;
		else
		{
			nodLS* temp = tabela.vect[pozitie];
			while (temp->next)
				temp = temp->next;
			temp->next = nou;
		}
	}
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f, Categorie=%s",
			temp->inf.cod, temp->inf.denumire,
			temp->inf.pret, temp->inf.cantitate,
			temp->inf.categorie);
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for(int i=0;i<tabela.nrElem;i++)
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie: %d", i);
				traversareLS(tabela.vect[i]);
			}
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

void dezalocareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
			if (tabela.vect[i] != NULL)
				dezalocareLS(tabela.vect[i]);
		free(tabela.vect);
	}
}

void main()
{
	int nrProd;
	char buffer[20];

	hashT tabela;
	tabela.nrElem = 31;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	produs p;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrProd);
	for (int i = 0; i < nrProd; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		fscanf(f, "%f", &p.pret);
		fscanf(f, "%f", &p.cantitate);
		fscanf(f, "%s", buffer);
		p.categorie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.categorie, buffer);
		inserareTabela(tabela, p);
		free(p.denumire);
		free(p.categorie);
	}
	fclose(f);
	traversareTabela(tabela);
	dezalocareTabela(tabela);
}