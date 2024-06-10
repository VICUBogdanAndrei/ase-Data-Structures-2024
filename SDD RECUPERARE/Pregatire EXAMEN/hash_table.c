#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct HashTable hashT;
typedef struct ListaSimpla nodLS;
typedef struct Student student;

struct Student {
	int nrMatricol;
	char* nume;
	float medie;
};

struct ListaSimpla {
	student info;
	nodLS* next;
};

struct HashTable {
	int nrElem;
	nodLS** vect;
};

nodLS* inserareLS(nodLS** cap, student s)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.nrMatricol = s.nrMatricol;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;

	nou->next = NULL;

	if (*cap == NULL)
	{
		*cap = nou;
	}
	else
	{
		nodLS* temp = *cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}

	return *cap;
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
	{
		printf("\nNr matricol = %d, Nume = %s, Medie = %5.2f",
			temp->info.nrMatricol, temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while(temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp);

		temp = aux;
	}
}

int functiaHash(hashT tabela, char* cheie)
{
	return strlen(cheie) % tabela.nrElem;
}

hashT inserareHash(hashT tabela, student s)
{
	int poz = functiaHash(tabela, s.nume);
	inserareLS(&tabela.vect[poz], s);
}

void dezalocareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
			dezalocareLS(tabela.vect[i]);
	}
	free(tabela.vect);
}

void traversareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL) {
			printf("\nPozitia #%d: \n", i);
			traversareLS(tabela.vect[i]);
		}
	}
}

void main()
{
	hashT tabela;
	student s;
	char buffer[30];
	int nrElem;



	FILE* f = fopen("hash_table.txt", "r");
	fscanf(f, "%d", &nrElem);

	tabela.nrElem = 4 * nrElem + 1;

	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		inserareHash(tabela, s);

		free(s.nume);
	}

	printf("<<-- TRAVERSARE HASH -->>\n");
	traversareTabela(tabela);



	dezalocareHash(tabela);


	fclose(f);
}

