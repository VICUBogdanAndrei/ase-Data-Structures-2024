#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int nrMatricol;
	char* nume;
	float medie;
}student;

//lista simpla inlantuita

typedef struct
{
	student info; // informatie utila
	struct nodLS* next; // pointer de legatura
}nodLS;

nodLS* inserareNod(nodLS* cap, student s)
{
	//pas 1 - alocare spatiu memorie pentru noul nod inserat
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	//pas 2 - initializare nod --- informatie utila + pointer de legatura
	//nou->info = s;

	nou->info.nrMatricol = s.nrMatricol;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;

	nou->next = NULL;

	//pas 3 - inserare nod nou in lista ---- la inceput sau la final
	if (cap == NULL)
		cap = nou; // verifica daca lista este vida
	else
	{
		//parcurgem lista pana la final si atasam noul nou la ultimul nod din lista
		nodLS* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}

	return cap;


}

void traversare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("\nNr. Matricol = %d, Nume = %s, Media = %5.2f", 
			temp->info.nrMatricol, temp->info.nume, temp->info.medie);

		temp = temp->next; // deplasare pe urmatorul nod
	}
}

void dezalocare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		//stergere
		nodLS* aux = temp->next;
		free(temp->info.nume); //pointer de legatura pentru urmatorul nod
		free(temp);
		temp = aux;
	}
}

void salvareVector(nodLS* cap, student* vect, int* nrElem, float prag)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		if (temp->info.medie >= prag)
		{
			//deep copy
			vect[*nrElem].nrMatricol = temp->info.nrMatricol;
			vect[*nrElem].nume = (char*)malloc((strlen(temp->info.nume) + 1) * sizeof(char));
			strcpy(vect[*nrElem].nume, temp->info.nume);
			vect[*nrElem].medie = temp->info.medie;
			(*nrElem)++;
		}

		temp = temp->next;
	}
}

void main()
{
	int nrStudent;
	nodLS* cap = NULL;
	student s;
	char buffer[20];
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStudent);
	for (int i = 0; i < nrStudent; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);
		cap = inserareNod(cap, s);
		free(s.nume);
	}

	fclose(f);
	traversare(cap);
	printf("\n--------------------------------------\n");

	int nrElem = 0;
	student* vect = (student*)malloc(nrStudent * sizeof(student));
	salvareVector(cap, vect, &nrElem, 9.0f);
	for (int i = 0; i < nrElem; i++)
	{
		printf("\nNr. Matricol = %d, Nume = %s, Media = %5.2f",
			vect[i].nrMatricol, vect[i].nume, vect[i].medie);
	}

	for (int i = 0; i < nrElem; i++)
		free(vect[i].nume);
	free(vect);

	dezalocare(cap);
}