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
	student** vect;
	int nrElem;
} hashT;

int functieDispersie(hashT tabela, int cheie)
{
	return cheie % tabela.nrElem;
}

void inserareTabela(hashT tabela, student* s)
{
	if (tabela.vect != NULL)
	{
		int pozitie = functieDispersie(tabela, (*s).nrGrupa);
		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = s;
		else
		{
			int index = 1;
			int c = 2;
			while (pozitie + c*index*index < tabela.nrElem)
			{
				if (tabela.vect[pozitie + c*index*index] == NULL)
				{
					pozitie += c*index*index;
					tabela.vect[pozitie] = s;
					break;
				}
				else
					index++;
			}

			if (pozitie + c*index*index >= tabela.nrElem) {
				index = 1;
				while (pozitie - c*index*index >= 0)
				{
					if (tabela.vect[pozitie - c*index*index] == NULL)
					{
						pozitie -= c*index*index;
						tabela.vect[pozitie] = s;
						break;
					}
					else
						index++;
				}
			}
		}
	}
}

void traversareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie: %d", i);
				printf("\nNume=%s, Grupa=%d, Medie=%5.2f",
					tabela.vect[i]->nume, tabela.vect[i]->nrGrupa,
					tabela.vect[i]->medie);
			}
	}
}

void dezalocareTabela(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
			if (tabela.vect[i] != NULL)
			{
				free(tabela.vect[i]->nume);
				free(tabela.vect[i]);
			}
		free(tabela.vect);
	}
}

void main()
{
	int nrStud;
	hashT tabela;
	tabela.nrElem = 31;
	tabela.vect = (student**)malloc(tabela.nrElem * sizeof(student*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	char buffer[20];
	student* s;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		s = (student*)malloc(sizeof(student));
		fscanf(f, "%s", buffer);
		s->nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s->nume, buffer);
		fscanf(f, "%d", &s->nrGrupa);
		fscanf(f, "%f", &s->medie);
		inserareTabela(tabela, s);
	}
	fclose(f);
	traversareTabela(tabela);
	dezalocareTabela(tabela);
}