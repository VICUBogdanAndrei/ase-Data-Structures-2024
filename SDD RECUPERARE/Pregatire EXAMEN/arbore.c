#define _CRT_SECURE_NO_WARNINGS

#include<malloc.h>
#include<stdio.h>


typedef struct Arbore nodArb;
typedef struct Proiect proiect;

struct Proiect {
	unsigned char id;
	char* titlu;
	char* contractant;
	unsigned char durata;
	float buget;
	float procentExecutie;
};

struct Arbore {
	proiect info;
	nodArb* st, * dr;
};

nodArb* creareNodArb(proiect p, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.id = p.id;
	nou->info.titlu = (char*)malloc((strlen(p.titlu) + 1) * sizeof(char));
	strcpy(nou->info.titlu, p.titlu);

	nou->info.contractant = (char*)malloc((strlen(p.contractant) + 1) * sizeof(char));
	strcpy(nou->info.contractant, p.contractant);

	nou->info.durata = p.durata;
	nou->info.buget = p.buget;
	nou->info.procentExecutie = p.procentExecutie;

	nou->st = st;
	nou->dr = dr;

	return nou;
}

nodArb* inserareNodArb(nodArb* rad, proiect p)
{
	if (rad != NULL)
	{
		if (p.id < rad->info.id)
		{
			rad->st = inserareNodArb(rad->st, p);
			return rad;
		}
		else
		{
			if (p.id > rad->info.id)
			{
				rad->dr = inserareNodArb(rad->dr, p);
				return rad;
			}
			else return rad;
		}

	}
	else
		creareNodArb(p, NULL, NULL);

}

//preordine
void parcurgereArbPreordine(nodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nID = %u, Titlu = %s, Contractant = %s, Durata = %u, Buget = %5.2f, Stadiu = %5.2f",
			rad->info.id, rad->info.titlu, rad->info.contractant, rad->info.durata, rad->info.buget, rad->info.procentExecutie);
		parcurgereArbPreordine(rad->st);
		parcurgereArbPreordine(rad->dr);
	}
}

void dezalocareArbPreordine(nodArb* rad)
{
	if (rad != NULL) {
		dezalocareArbPreordine(rad->st);
		dezalocareArbPreordine(rad->dr);

		free(rad->info.titlu);
		free(rad->info.contractant);
		free(rad);
	}
}

void numarareProiect(nodArb* rad, char* denumire, int* nr)
{
	if (rad != NULL)
	{
		if (strcmp(rad->info.titlu, denumire) == 0)
			(*nr)++;
		numarareProiect(rad->st, denumire, nr);
		numarareProiect(rad->dr, denumire, nr);
	}
}

void modificareStatiu(nodArb* rad, float procent, unsigned char idProiect)
{
	if (rad != NULL)
	{
		if (rad->info.id == idProiect)
			rad->info.procentExecutie = procent;
		modificareStatiu(rad->st, procent, idProiect);
		modificareStatiu(rad->dr, procent, idProiect);
	}
}

void main()
{
	nodArb* rad = NULL;
	int nrElem = 0;

	FILE* f = fopen("arbore.txt", "r");
	fscanf(f, "%d", &nrElem);

	proiect p;

	char buffer[30];
	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%u", &p.id);
		fscanf(f, "%s", buffer);

		p.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.titlu, buffer);

		fscanf(f, "%s", buffer);
		p.contractant = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.contractant, buffer);
		fscanf(f, "%u", &p.durata);
		fscanf(f, "%f", &p.buget);
		fscanf(f, "%f", &p.procentExecutie);

		rad = inserareNodArb(rad, p);

		free(p.titlu);
		free(p.contractant);

	}

	printf("\n\n-->> AFISARE PREORDINE ARBORE <<--\n");
	parcurgereArbPreordine(rad);

	printf("\n\n-->> NUMAR NODURI <<--\n");
	int numar = 0;
	numarareProiect(rad, "Sanatate", &numar);
	printf("\nNumarul nodurilor este %d.", numar);

	printf("\n\n-->> MODIFICARE PROCENT <<--\n");
	float procentNou = 45.5;
	unsigned char idProiect = 2;
	modificareStatiu(rad, procentNou, idProiect);
	parcurgereArbPreordine(rad);

	dezalocareArbPreordine(rad);


	fclose(f);
}