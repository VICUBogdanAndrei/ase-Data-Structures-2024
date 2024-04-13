#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct {
	int nrMatricol;
	char* nume;
	float medie;
}student;

typedef struct {
	student info;
	struct nodLS* next;
}nodLS;


nodLS* inserareNod(nodLS* cap, student s)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->info.nrMatricol = s.nrMatricol;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;

	nou->next = NULL;

	if (cap == NULL)
	{
		cap = nou;
	}
	else
	{
		nodLS* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}

	return cap;

}

void traversareLista(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("\nID = %d, Nume = %s, Medie = %5.2f", temp->info.nrMatricol, temp->info.nume, temp->info.medie);
		temp = temp->next;
	}
}

void dezalocare(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp);
		temp = aux;
	}
	free(temp);
}

void stergereElem(nodLS** cap, nodLS* nodSters)
{
	
	//primul nod
	if (*cap==nodSters)
	{
		(*cap)->next = *cap;

		free(nodSters->info.nume);
		free(nodSters);
		return 0;
	}

	//interior
	nodLS* temp1 = *cap;
	nodLS* temp2 = (*cap)->next;
	while (temp2->next != NULL)
	{
		if (temp2 == nodSters)
		{
			temp1->next = temp2->next;
			free(nodSters->info.nume);
			free(nodSters);
			temp2 = temp1->next;
		}
		else {
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}

	//la final
	if (temp2 == nodSters)
	{
		temp1->next = NULL;
		free(nodSters->info.nume);
		free(nodSters);
	}

	return 0;

}

void stergere(nodLS** cap)
{
	nodLS* temp = *cap;
	while (temp != NULL)
	{
		if (temp->info.medie < 5)
		{
			nodLS* nodSters = temp;
			temp = temp->next;
			stergereElem(cap, nodSters);
		}
		else {
			temp = temp->next;
		}
	}
}



void main()
{
	nodLS* cap=NULL;
	student s;
	char buffer[20];
	int nr;
	FILE* f = fopen("student.txt", "r");
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);
		cap = inserareNod(cap, s);
		free(s.nume);
	}

	printf("\n----AFISARE LISTA----\n");

	traversareLista(cap);

	stergere(&cap);

	printf("\n----AFISARE LISTA MODIFICATA----\n");

	traversareLista(cap);

	dezalocare(cap);


	fclose(f);
}