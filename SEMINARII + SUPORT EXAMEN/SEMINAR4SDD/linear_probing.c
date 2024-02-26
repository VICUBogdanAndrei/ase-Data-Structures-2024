#define _CRT_SECURE_NO_WARNINGS

//tabela de dispersie Linear Probing

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
	student** vect;
	int size;
}hashT;


int functieHash(int cheie, hashT tabela)
{
	return cheie % tabela.size;
}

int inserare(hashT tabela, student* s)
{
	int pozitie;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash((*s).cod, tabela);
		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = s;
		else
		{
			int index = 1;
			while (pozitie + index < tabela.size)
			{
				if (tabela.vect[pozitie + index] == NULL)
				{
					tabela.vect[pozitie + index] = s;
					pozitie = pozitie + s;
					break;
				}
				index++;
			}
		}
	}
	return pozitie;
}

int stergere(hashT tabela, int cod)
{
	int pozitie;
	if (tabela.vect != NULL)
	{
		pozitie = functieHash(cod, tabela);
		if (tabela.vect[pozitie] == NULL)
			return -1;
		else
		{
			if (tabela.vect[pozitie]->cod == cod)
			{
				free(tabela.vect[pozitie]->nume);
				free(tabela.vect[pozitie]);
				tabela.vect[pozitie] = NULL;
			}
			else
			{
				int index = 1;
				while (pozitie + index < tabela.size)
				{
					if (tabela.vect[pozitie + index]->cod == cod)
					{
						pozitie = pozitie + index;
						free(tabela.vect[pozitie]->nume);
						free(tabela.vect[pozitie]);
						tabela.vect[pozitie] = NULL;
						break;
					}
					index++;
				}
			}
				
		}
	}
	return pozitie;
}

void traversare(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for(int i=0;i<tabela.size;i++)
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie #%d :", i);
				printf("\nCod = %d, Nume = %s, Medie = 5.2f", 
					tabela.vect[i]->cod, tabela.vect[i]->nume, tabela.vect[i]->medie);

		}
	}
}

void dezalocare(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				free(tabela.vect[i]->nume);
				free(tabela.vect[i]);
			}
		}
		free(tabela.vect);
	}
}

void main()
{
	hashT tabela;
	tabela.size = 101;
	tabela.vect = (student**)malloc(tabela.size * sizeof(student*));
	for (int i = 0; i < tabela.size; i++)
		tabela.vect[i] = NULL;
	int n;

	FILE* f = fopen("fisier.txt", "r");
	student* s;
	char buffer[20];
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		s = (student*)malloc(sizeof(student));
		fscanf(f, "%d", &s->cod);
		fscanf(f, "%s", buffer);
		s->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s->nume, buffer);
		fscanf(f, "%f", &s->medie);
		inserare(tabela, s);
		//free(s->nume);
	}
	fclose(f);
	traversare(tabela);
	stergere(tabela, 405);

	printf("\n------dupa stergere-------\n");

	traversare(tabela);

	dezalocare(tabela);
}