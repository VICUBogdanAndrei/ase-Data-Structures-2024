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
	struct nodLS** vect;
	int nrElem
}hashT;

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
		int pozitie = functieDispersie(tabela, p.cod);
			nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
			nou->inf.cod = p.cod;
			nou->inf.denumire = (char*)malloc(strlen(p.denumire) + 1);
			strcpy(nou->inf.denumire, p.denumire);
			nou->inf.pret = p.pret;
			nou->inf.cantitate = p.cantitate;
			nou->inf.categorie = (char*)malloc(strlen(p.categorie) + 1);
			strcpy(nou->inf.categorie, p.categorie);
			nou->next = NULL;
			if (tabela.vect[pozitie] == NULL)
				tabela.vect[pozitie] = nou;
			else 
			{
				nodLS* temp = *capLS;
				while (temp->next)
					temp = temp->next;
				temp->next = nou;
			}

	}
}

