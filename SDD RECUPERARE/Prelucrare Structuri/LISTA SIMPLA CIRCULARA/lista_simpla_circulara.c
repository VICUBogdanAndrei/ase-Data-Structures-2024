#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct {
	int nrMatricol;
	char* nume;
	char* initialaTata;
	float medie;
	char* scoala;
}elev;

typedef struct {
	elev info;
	struct nodLS* next;
}nodLS;


nodLS* inserare(nodLS* cap, elev e)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	
	nou->info.nrMatricol = e.nrMatricol;
	nou->info.nume = (char*)malloc((strlen(e.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, e.nume);
	nou->info.initialaTata = (char*)malloc((strlen(e.initialaTata) + 1) * sizeof(char));
	strcpy(nou->info.initialaTata, e.initialaTata);
	nou->info.medie = e.medie;
	nou->info.scoala = (char*)malloc((strlen(e.scoala) + 1) * sizeof(char));
	strcpy(nou->info.scoala, e.scoala);

	nou->next = NULL;

	if (cap == NULL)
	{
		cap = nou;
		cap->next = cap;
	}
	else
	{
		nodLS* temp = cap;
		while (temp->next != cap)
		{
			temp = temp->next;
		}
		temp->next = nou;
		nou->next = cap;
	}

	return cap;
}

void traversare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		printf("\nNr Matricol = %d, Nume = %s, Initiala Tata = %s, Medie = %5.2f, Scoala = %s",
			temp->info.nrMatricol, temp->info.nume, temp->info.initialaTata, temp->info.medie, temp->info.scoala);
		temp = temp->next;
	}
	printf("\nNr Matricol = %d, Nume = %s, Initiala Tata = %u, Medie = %5.2f, Scoala = %s",
		temp->info.nrMatricol, temp->info.nume, temp->info.initialaTata, temp->info.medie, temp->info.scoala);
}

void dezalocare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp->next != cap)
	{
		nodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp->info.initialaTata);
		free(temp->info.scoala);
		free(temp);
		temp = aux;
	}
	free(temp->info.nume);
	free(temp->info.initialaTata);
	free(temp->info.scoala);
	free(temp);
}

void main()
{
	elev e;
	nodLS* cap=NULL;
	char buffer[30];
	char buffer1[10];
	int nrELevi = 0;
	FILE* f = fopen("lista_circulara.txt", "r");
	fscanf(f, "%d", &nrELevi);
	for (int i = 0; i < nrELevi; i++)
	{
		fscanf(f, "%d", &e.nrMatricol);
		fscanf(f, "%s", buffer);
		e.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(e.nume, buffer);
		
		fscanf(f, "%s", buffer1);
		e.initialaTata = (char*)malloc((strlen(buffer1) + 1) * sizeof(char));
		strcpy(e.initialaTata, buffer1);
		
		fscanf(f, "%f", &e.medie);
		fscanf(f, "%s", buffer);
		e.scoala = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(e.scoala, buffer);
		

		cap = inserare(cap, e);

		free(e.nume);
		free(e.initialaTata);
		free(e.scoala);
	}

	printf("\n---------------------\n");

	traversare(cap);

	dezalocare(cap);


	fclose(f);
}