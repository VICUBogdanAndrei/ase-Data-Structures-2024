#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>


typedef struct {
	int nrMatricol;
	char* nume;
	float medie;
}student;

typedef struct
{
	student info;
	struct nodArb* stanga, *dreapta;
}nodArb;

typedef struct {
	student info;
	struct nodLS* next;
}nodLS;

//arbore binar de cautare

nodArb* creareNod(student s, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->info.nrMatricol = s.nrMatricol;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;

	nou->stanga = st;
	nou->dreapta = dr;

	return nou;
}

nodArb* inserareNod(nodArb* rad, student s)
{
	if (rad != NULL)
	{
		if (s.nrMatricol < rad->info.nrMatricol)
		{
			rad->stanga = inserareNod(rad->stanga,s);
			return rad;
		}
		else
			if (s.nrMatricol > rad->info.nrMatricol)
			{
				rad->dreapta = inserareNod(rad->dreapta,s);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(s, NULL, NULL);
}

nodLS* inserarreNodLista(nodLS* cap, student s)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.nrMatricol = s.nrMatricol;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;
	nou->next = NULL;

	if (cap == NULL)
		cap = nou;
	else
	{
		nodLS* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

void traversareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp!=NULL)
	{
		printf("\nNr Matricol = %d, Nume = %s, Medie = %5.2f", temp->info.nrMatricol, temp->info.nume, temp->info.medie);
		temp = temp->next;
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

void salvareStudentiInitiala(nodArb* rad, nodLS** cap, char litera)
{
	if (rad != NULL)
	{
		if (rad->info.nume[0]==litera)
			*cap = inserarreNodLista(*cap, rad->info);
		salvareStudentiInitiala(rad->stanga, cap, litera);
		salvareStudentiInitiala(rad->dreapta, cap, litera);
		
	}
}

void preordine(nodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nNr Matricol = %d, Nume = %s, Medie = %5.2f", rad->info.nrMatricol, rad->info.nume, rad->info.medie);
		preordine(rad->stanga);
		preordine(rad->dreapta);
	}
}


//inordine 


void dezalocare(nodArb* rad)
{
	if (rad != NULL)
	{

		//preordine RSD
		/*nodArb* st = rad->stanga;
		nodArb* dr = rad->dreapta;

		free(rad->info.nume);
		free(rad);
		dezalocare(st);
		dezalocare(dr);*/

		//inordinea SRD 
		
		//dezalocare postordine SDR
		dezalocare(rad->stanga);
		dezalocare(rad->dreapta);
		free(rad->info.nume);
		free(rad);
	}
}

void salvareVectorFrunze(nodArb* rad, student* vect, int* nr)
{
	if (rad != NULL)
	{
		if (rad->stanga == NULL && rad->dreapta == NULL)
		{
			vect[*nr] = rad->info;
			(*nr)++;
		}
		salvareVectorFrunze(rad->stanga, vect, nr);
		salvareVectorFrunze(rad->dreapta, vect, nr);
	}
}

//media peste 9 

void nrStudetMediePrag(nodArb* rad, int* nr, float prag)
{
	if (rad != NULL)
	{
		if (rad->info.medie >= prag)
			(*nr)++;
		nrStudetMediePrag(rad->stanga, nr, prag);
		nrStudetMediePrag(rad->dreapta, nr, prag);
	}
}
//salvare lista simpla studentii care incep cu G

void main()
{
	student s;
	nodArb* rad = NULL;
	char buffer[30];
	
	FILE* f = fopen("fisier.txt", "r");
	int nr = 0;

	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);

		rad = inserareNod(rad, s);
		free(s.nume);
	}

	preordine(rad);


	printf("\n\n---SALVARE VECTOR NODURI FRUNZA---\n");
	int nrElem = 0;
	student* vect = (student*)malloc(nr * sizeof(student));
	salvareVectorFrunze(rad, vect, &nrElem);

	for (int i = 0; i < nrElem; i++)
	{
		printf("\nNr Matricol = %d, Nume = %s, Medie = %5.2f", vect[i].nrMatricol, vect[i].nume, vect[i].medie);
	}

	free(vect);
	

	printf("\n\n-----------Lista Simpla------------\n");
	nodLS* cap = NULL;
	salvareStudentiInitiala(rad, &cap, 'G');
	traversareLista(cap);
	dezalocareLista(cap);


	printf("\n\n-----\n");
	
	int prag = 9;
	int nrStudentiPrag = 0;
	nrStudetMediePrag(rad, &nrStudentiPrag, prag);
	printf("\nNr Student cu media mai mare decat %d este %d.\n\n", prag, nrStudentiPrag);

	dezalocare(rad);

	fclose(f);
}