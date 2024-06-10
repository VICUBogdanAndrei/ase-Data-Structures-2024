#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<malloc.h>

typedef struct Stiva nodStiva;
typedef struct Student student;

struct Student {
	int nrMatricol;
	char* nume;
	char* prenume;
	char* facultate;
	float medie;
};

struct Stiva {
	student info;
	nodStiva* next;
};

void push(nodStiva** varf, student s)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));

	nou->info.nrMatricol = s.nrMatricol;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.prenume = (char*)malloc((strlen(s.prenume) + 1) * sizeof(char));
	strcpy(nou->info.prenume, s.prenume);
	nou->info.facultate = (char*)malloc((strlen(s.facultate) + 1) * sizeof(char));
	strcpy(nou->info.facultate, s.facultate);
	nou->info.medie = s.medie;

	nou->next = NULL;

	if (*varf == NULL)
	{
		(*varf) = nou;
	}
	else
	{
		nou->next = (*varf);
		(*varf) = nou;
	}

}

int pop(nodStiva** varf, student* s)
{
	if (*varf == NULL)
		return -1;
	else
	{
		(*s).nrMatricol = (*varf)->info.nrMatricol;
		(*s).nume = (char*)malloc((strlen((*varf)->info.nume) + 1) * sizeof(char));
		strcpy((*s).nume, (*varf)->info.nume);
		(*s).prenume = (char*)malloc((strlen((*varf)->info.prenume) + 1) * sizeof(char));
		strcpy((*s).prenume, (*varf)->info.prenume);
		(*s).facultate = (char*)malloc((strlen((*varf)->info.facultate) + 1) * sizeof(char));
		strcpy((*s).facultate, (*varf)->info.facultate);
		(*s).medie = (*varf)->info.medie;

		nodStiva* temp = (*varf);
		(*varf) = (*varf)->next;
		free(temp->info.nume);
		free(temp->info.prenume);
		free(temp->info.facultate);
		free(temp);

		return 0;
	}
}

void traversareStiva(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("Nr Matricol = %d, Nume = %s, Prenume = %s, Facultate = %s, Medie = %5.2f\n",
			temp->info.nrMatricol, temp->info.nume, temp->info.prenume, temp->info.facultate, temp->info.medie);
		temp = temp->next;
	}
}

void main()
{
	nodStiva* varf = NULL;
	student s;
	char buffer[20];
	int nrElem = 0;
	FILE* f = fopen("stiva.txt", "r");
	fscanf(f, "%d", &nrElem);
	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%s", buffer);
		s.prenume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.prenume, buffer);
		fscanf(f, "%s", buffer);
		s.facultate = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.facultate, buffer);
		fscanf(f, "%f", &s.medie);

		push(&varf, s);

		free(s.nume);
		free(s.prenume);
		free(s.facultate);
	}

	printf("-->> TRAVERSARE STIVA <<--\n");
	traversareStiva(varf);

	printf("\n-->> EXTRAGERE DIN STIVA + DEZALOCARE <<--\n");

	int nr = 0;
	while (pop(&varf, &s)==0)
	{
		nr++;
	}
	printf("LA dezalocare, au fost stersi din memorie %d elemente din stiva!\n", nr);
	

}