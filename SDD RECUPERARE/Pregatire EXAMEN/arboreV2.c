#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct Arbore nodArb;
typedef struct Student student;

struct Student {
	int nrMatricol;
	char* nume;
	float medie;
};

struct Arbore {
	student info;
	nodArb* st, * dr;
};

nodArb* creareaNodArb(nodArb* stanga, nodArb* dreapta, student s)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.nrMatricol = s.nrMatricol;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;

	nou->st = stanga;
	nou->dr = dreapta;

	return nou;
}

nodArb* inserareNodArb(nodArb* rad, student s)
{
	if (rad != NULL)
	{
		if (strlen(rad->info.nume) < strlen(s.nume))
		{
			rad->st = inserareNodArb(rad->st, s);
			return rad;
		}
		else
		{
			if (strlen(rad->info.nume) >= strlen(s.nume))
			{
				rad->dr = inserareNodArb(rad->dr, s);
				return rad;
			}
			else return rad;
		}
	}
	else
		 creareaNodArb(NULL, NULL, s);
}

void dezalocareArb(nodArb* rad)
{
	if (rad != NULL)
	{
		dezalocareArb(rad->st);
		dezalocareArb(rad->dr);

		free(rad->info.nume);
		free(rad);
	}
}

void parcurgereRSD(nodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nNr Matricol = %d, Nume = %s, Medie = %5.2f",
			rad->info.nrMatricol, rad->info.nume, rad->info.medie);
		parcurgereRSD(rad->st);
		parcurgereRSD(rad->dr);
	}
}

void main()
{
	nodArb* rad = NULL;
	char buffer[30];
	int nrelem = 0;
	student s;

	FILE* f = fopen("arbore_v2.txt", "r");
	fscanf(f, "%d", &nrelem);

	for (int i = 0; i < nrelem; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		rad = inserareNodArb(rad, s);
		free(s.nume);
	}

	printf("\n\n-->> PARCURGERE ARBORE RSD <<--\n");
	parcurgereRSD(rad);


	dezalocareArb(rad);


	fclose(f);
}