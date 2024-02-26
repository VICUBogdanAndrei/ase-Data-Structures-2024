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
	produs** vect;
	int nrElem;
} hashT;

int functieDispersie(hashT tabela, int cheie)
{
	return cheie % tabela.nrElem;
}

void inserareTabela(hashT tabela, produs* p)
{
	if (tabela.vect != NULL)
	{
		int pozitie = functieDispersie(tabela, (*p).cod);
		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = p;
		else
		{
			int index = 1;
			while (pozitie + index < tabela.nrElem)
			{
				if (tabela.vect[pozitie + index] == NULL)
				{
					pozitie += index;
					tabela.vect[pozitie] = p;
					break;
				}
				else
					index++;
			}
		}
	}
}

void traversareTabela(hashT tabela)
{
	if(tabela.vect!=NULL)
		for (int i = 0; i < tabela.nrElem; i++)
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie: %d", i);
				printf("\nCod=%d, Denumire=%s, Pret=%5.2f, Cantitate=%5.2f, Categorie=%s",
					tabela.vect[i]->cod, tabela.vect[i]->denumire,
					tabela.vect[i]->pret, tabela.vect[i]->cantitate,
					tabela.vect[i]->categorie);
			}
}

void dezalocareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
			if (tabela.vect[i] != NULL)
			{
				free(tabela.vect[i]->denumire);
				free(tabela.vect[i]->categorie);
				free(tabela.vect[i]);
			}
		free(tabela.vect);
	}
}

void main()
{
	int nrProd;
	char buffer[20];

	hashT tabela;
	tabela.nrElem = 31;
	tabela.vect = (produs**)malloc(tabela.nrElem * sizeof(produs*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	produs *p;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrProd);
	for (int i = 0; i < nrProd; i++)
	{
		p = (produs*)malloc(sizeof(produs));
		fscanf(f, "%d", &p->cod);
		fscanf(f, "%s", buffer);
		p->denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p->denumire, buffer);
		fscanf(f, "%f", &p->pret);
		fscanf(f, "%f", &p->cantitate);
		fscanf(f, "%s", buffer);
		p->categorie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p->categorie, buffer);
		inserareTabela(tabela, p);
	}
	fclose(f);
	traversareTabela(tabela);
	dezalocareTabela(tabela);
}