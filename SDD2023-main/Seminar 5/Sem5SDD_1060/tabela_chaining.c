#include <stdio.h>
#include <malloc.h>

typedef struct
{
	char* nume;
	int nrGrupa;
	float medie;
} student;

typedef struct
{
	student inf;
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

int functieDispersieNume(hashT tabela, char nume[20])
{
	return nume[0] % tabela.nrElem;
}

int functieDispersieChar(hashT tabela, char initiala)
{
	return initiala % tabela.nrElem;
}

void inserareHashTable(hashT tabela, student s)
{
	if (tabela.vect != NULL)
	{
		//int pozitie = functieDispersie(tabela, s.nrGrupa);
		//int pozitie = functieDispersieNume(tabela, s.nume);
		int pozitie = functieDispersieChar(tabela, s.nume[0]);
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
		strcpy(nou->inf.nume, s.nume);
		nou->inf.nrGrupa = s.nrGrupa;
		nou->inf.medie = s.medie;
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
		printf("\nNume=%s, Grupa=%d, Medie=%5.2f",
			temp->inf.nume, temp->inf.nrGrupa,
			temp->inf.medie);
		temp = temp->next;
	}
}

void traversareHashTable(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie=%d", i);
				traversareLS(tabela.vect[i]);
			}
		}
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = temp2;
	}
}

void dezalocareHashTable(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
			if (tabela.vect[i] != NULL)
				dezalocareLS(tabela.vect[i]);
	}
	free(tabela.vect);
}

void main()
{
	int nrStud;
	hashT tabela;
	tabela.nrElem = 31;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	char buffer[20];
	student s;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%d", &s.nrGrupa);
		fscanf(f, "%f", &s.medie);
		inserareHashTable(tabela, s);
		free(s.nume);
	}
	fclose(f);
	traversareHashTable(tabela);
	dezalocareHashTable(tabela);
}