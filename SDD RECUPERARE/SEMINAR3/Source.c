#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct
{
	int nrMatricol;
	char* nume;
	float medie;
} student;

//parametru care se returneaza modificat si de asta ii dau 2 stelute lu coada

typedef struct
{
	student inf; //informatie utila
	struct nodLS* next, * prev; //pointeri de legatura
} nodLS;

nodLS* inserareNod(nodLS* cap, nodLS** coada, student s)
{
	//creare nod
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	//initializare nod
	//nou->inf = s;
	nou->inf.nrMatricol = s.nrMatricol;
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) *
		sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.medie = s.medie;
	nou->next = NULL;
	nou->prev = NULL;
	//adaugare nod in lista
	if (cap == NULL)
	{
		nou->next = nou;
		nou->prev = nou;
		cap = nou;
		*coada = nou; //noutate

	}
	else
	{
		nodLS* temp = cap;
		while (temp->next != cap)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp; //nouatte
		*coada = nou;
		(*coada)->next = cap;
		cap->prev = (*coada);
	}
	return cap;
}

void traversare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp->next !=  cap)
	{
		//prelucrare a inf. utile
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
			temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
		temp = temp->next; //deplasare pe nod urmator
	}
	printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
		temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
}

void traversareInvers(nodLS* coada)
{
	nodLS* temp = coada;
	while (temp->prev != coada)
	{
		//prelucrare a inf. utile
		printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
			temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
		temp = temp->prev; //deplasare pe nod anterior
	}
	printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
		temp->inf.nrMatricol, temp->inf.nume, temp->inf.medie);
}

void dezalocare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		//stergere
		nodLS* aux = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = aux;
	}
	free(temp->inf.nume);
	free(temp);
}

void stergereNod(nodLS** cap, nodLS** coada, nodLS* NodSters)
{
	if (*cap == NULL || NodSters == NULL || *coada == NULL)
	{
		return 0;
	}

	if (*cap == NodSters)
	{
		*cap = (*cap)->next;
		if (*cap != NULL)
			(*cap)->prev = NULL;

		free(NodSters->inf.nume);
		free(NodSters);

		return 0;
	}

	if (*coada == NodSters)
	{
		*coada = (*coada)->prev;
		(*coada)->next = NULL;

		free(NodSters->inf.nume);
		free(NodSters);

		return 0;
	}

	nodLS* urmator = NodSters->next;
	nodLS* anterior = NodSters->prev;

	anterior->next = urmator;
	urmator->prev = anterior;

	free(NodSters->inf.nume);
	free(NodSters);

	return 0;
}



void stergereNume(nodLS** cap, nodLS** coada, char* denumire)
{
	nodLS* temp = *cap;
	while (temp->next != *cap)
	{
		if (strcmp(denumire, temp->inf.nume) == 0)
		{
			nodLS* NodSters = temp;
			temp = temp->next;
			stergereNod(cap, coada, NodSters);
		}
		else {
			temp = temp->next;
		}
	}
	if (strcmp(denumire, temp->inf.nume) == 0)
	{
		nodLS* NodSters = temp;
		temp = temp->next;
		stergereNod(cap, coada, NodSters);
	}
}

void salvareVector(nodLS* cap, student* vect, int* nrElem, float prag)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		if (temp->inf.medie >= prag)
		{
			//deep copy
			vect[*nrElem].nrMatricol = temp->inf.nrMatricol;
			vect[*nrElem].nume = (char*)malloc((strlen(temp->inf.nume) + 1) * sizeof(char));
			strcpy(vect[*nrElem].nume, temp->inf.nume);
			vect[*nrElem].medie = temp->inf.medie;
			(*nrElem)++;
		}

		temp = temp->next;
	}
	if (temp->inf.medie >= prag)
	{
		//deep copy
		vect[*nrElem].nrMatricol = temp->inf.nrMatricol;
		vect[*nrElem].nume = (char*)malloc((strlen(temp->inf.nume) + 1) * sizeof(char));
		strcpy(vect[*nrElem].nume, temp->inf.nume);
		vect[*nrElem].medie = temp->inf.medie;
		(*nrElem)++;
	}
}

void main()
{
	int nrStud;
	nodLS* cap = NULL, * coada = NULL;
	student s;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);
		cap = inserareNod(cap, &coada, s);
		free(s.nume);
	}
	fclose(f);

	traversare(cap);
	printf("\n---------------------\n");
	traversareInvers(coada);


	printf("\n---------------------\n");


	printf("\nNoua Lista dupa Stergere: \n");

	stergereNume(&cap, &coada, "Dorel");


	traversare(cap);
	printf("\n---------------------\n");
	traversareInvers(coada);

	printf("\n---------------------\n");
	printf("\n---------------------\n");
	int nrElem = 0;
	student* vect = (student*)malloc(nrStud * sizeof(student));
	salvareVector(cap, vect, &nrElem, 6.5f);
	//for (int i = 0; i < nrElem; i++)
	//	printf("\nNr. matricol = %d, Nume = %s, Medie = %5.2f",
	//		vect[i].nrMatricol, vect[i].nume, vect[i].medie);
	for (int i = 0; i < nrElem; i++)
		free(vect[i].nume);
	free(vect);

	dezalocare(cap);
}


//TEMA: Sa se stearga nodul de pe poztia x din lista simpla/dubla
	//  Sa se stearga nodurile de pe pozitiile pare / impare
	//  Sa se interschimbe nodurile de pe pozitiile i si i+1
	//  Sa se determine studentul cu media minima/maxima din lista
	// SEMINARUL URMATOR ->> STIVA si COADA