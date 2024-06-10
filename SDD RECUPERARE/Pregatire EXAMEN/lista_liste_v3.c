#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct ListaPrincipala nodLP;
typedef struct ListaSecundara nodLS;
typedef struct Student student;

typedef struct HashTable hashT;

struct Student {
	int nrMatricol;
	char* nume;
	float medie;
};

struct ListaSecundara {
	student info;
	nodLS* next;
};

struct ListaPrincipala {
	nodLS* info;
	nodLP* next;
};

struct HashTable {
	int nrElem;
	nodLS** vect;
};

nodLS* creareNodLS_Hash(nodLS** cap, student s)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.nrMatricol = s.nrMatricol;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;

	nou->next = NULL;

	if (*cap == NULL)
		*cap = nou;
	else {
		nodLS* temp = *cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}

	return *cap;
}

int functieHash(hashT tabela, char* cheie)
{
	return strlen(cheie) % tabela.nrElem;
}

hashT inserareHash(hashT tabela, student s)
{
	int poz = functieHash(tabela, s.nume);
	creareNodLS_Hash(&tabela.vect[poz], s);
}

nodLS* creareNodLS(student s)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.nrMatricol = s.nrMatricol;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;

	nou->next = NULL;

	return nou;
}

nodLP* creareNodLP()
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->info = NULL;
	nou->next = NULL;

	return nou;
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
	{
		printf("\nNr Matricol = %d, Nume = %s, Medie = %5.2f",
			temp->info.nrMatricol, temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}

void traversareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
		{
			printf("\nPozitie #%d: ", i);
			traversareLS(tabela.vect[i]);
		}
	}
}


void traversareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	int i = 1;
	while (temp != NULL)
	{
		printf("\Pozitie #%d: ", i);
		traversareLS(temp->info);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp);
		temp = aux;
	}
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

void dezalocareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp != NULL)
	{
		nodLP* aux = temp->next;
		dezalocareLS(temp->info);
		free(temp);
		temp = aux;
	}
}

nodLP* cautareNod(nodLP* capLP, int nrMatricol)
{
	nodLP* temp = capLP;
	while (temp != NULL)
	{
		if (temp->info->info.nrMatricol % 10 == nrMatricol % 10)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

void transformareHash(nodLP* capLP, hashT tabela)
{
	nodLP* temp = capLP;
	while (temp != NULL)
	{
		nodLS* tempLS = temp->info;
		while (tempLS != NULL)
		{
			inserareHash(tabela, tempLS->info);
			tempLS = tempLS->next;
		}
		temp = temp->next;
	}
}

void main()
{
	nodLP* capLP = NULL;
	nodLS* capLS = NULL;

	student s;
	char buffer[30];
	int nrElem = 0;

	FILE* f = fopen("lista_liste_v3.txt", "r");
	fscanf(f, "%d", &nrElem);

	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		nodLS* student = creareNodLS(s);
		free(s.nume);

		if (capLP == NULL)
		{
			nodLP* primLP = creareNodLP();
			primLP->info = student;
			capLP = primLP;
		}
		else
		{
			nodLP* gasit = cautareNod(capLP, s.nrMatricol);
			if (gasit == NULL)
			{
				nodLP* final = creareNodLP();
				nodLP* temp = capLP;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = final;
				final->info = student;
			}
			else
			{
				nodLS* temp = gasit->info;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = student;
			}
		}
	}

	printf("\n\n-->> AFISARE LISTA DE LISTE <<--\n");

	traversareLP(capLP);

	printf("\n\n-->> TRANSFORMARE IN HASH TABLE <<--\n");
	hashT tabela;
	tabela.nrElem = 4 * nrElem + 1;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;
	transformareHash(capLP, tabela);
	traversareHash(tabela);

	dezalocareHash(tabela);
	dezalocareLP(capLP);

	fclose(f);

}