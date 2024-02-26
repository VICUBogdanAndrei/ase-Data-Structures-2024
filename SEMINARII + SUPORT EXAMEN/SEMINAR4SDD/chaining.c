#define _CRT_SECURE_NO_WARNINGS

//tabela de dispersie Chaining

#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* nume;
	float medie;
}student;

typedef struct
{
	student info;
	struct nodLS* next;
}nodLS;

typedef struct
{
	struct nodLS** vect;
	int size;
}hashT;

int functieHash(int cheie, hashT tabela)
{
	return cheie % tabela.size;
}

void inserare(hashT tabela, student s)
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash(s.cod, tabela);
		nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
		nou->info.cod = s.cod;
		nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
		strcpy(nou->info.nume, s.nume);
		nou->info.medie = s.medie;
		nou->next = NULL;
		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = nou;
		else {
			nodLS* temp = tabela.vect[pozitie];
			while (temp->next)
				temp = temp->next;
			temp->next = nou;
		}
	}
	//return pozitie;
}

void traversareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		printf("\nCod: %d, Nume: %s, Medie: %5.2f", temp->info.cod, temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitia #%d :", i);
				traversareLista(tabela.vect[i]);
			}
		}
	}
}

void dezalocareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp->info.nume);
		free(temp);
		temp = temp2;
	}
}

void dezalocareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for(int i=0;i<tabela.size;i++)
			if (tabela.vect[i] != NULL)
			{
				dezalocareLista(tabela.vect[i]);
			}
		free(tabela.vect);
	}
}

void stergereNod(nodLS* nod)
{
	free(nod->info.nume);
	free(nod);
}

//stergerea unui nod dupa un cod cunoscut
int stergere(hashT tabela, int cod)
{
	int pozitie = 0;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash(cod, tabela);
		nodLS* temp = tabela.vect[pozitie];
		if (temp == NULL)
			return -1;
		else
		{
			if (temp->info.cod == cod)
			{
				if (temp->next == NULL)
				{
					stergereNod(temp);
					tabela.vect[pozitie] = NULL;
				}
				else
				{
					nodLS* temp2 = temp;
					tabela.vect[pozitie] = temp->next;
					stergereNod(temp2);
				}
			}
			else
			{
				while (temp->next != NULL)
				{
					nodLS* temp2 = temp->next;
					if (temp2->info.cod != cod)
						temp = temp->next;
					else
						break;
				}
				nodLS* p = temp->next;
				if (p != NULL)
				{
					if (p->next != NULL)
					{
						temp->next = p->next;
						stergereNod(p);
					}
					else
					{
						temp->next = NULL;
						stergereNod(p);
					}
				}
				else
					return -1;
			}
		}
	}
	return pozitie;
}


void main()
{
	hashT tabela;
	tabela.size = 101;
	tabela.vect = (nodLS**)malloc(tabela.size * sizeof(nodLS*));
	for (int i = 0; i < tabela.size; i++)
		tabela.vect[i] = NULL;
	int n;

	FILE* f = fopen("fisier.txt", "r");
	student s;
	char buffer[20];
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);
		inserare(tabela, s);
		free(s.nume);
	}
	fclose(f);
	traversareTabela(tabela);
	stergere(tabela, 5);

	printf("\n--------dupa stergere--------\n");
	traversareTabela(tabela);
	dezalocareTabela(tabela);
}