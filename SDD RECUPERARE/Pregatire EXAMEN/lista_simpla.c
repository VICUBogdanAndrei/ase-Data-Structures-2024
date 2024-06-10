#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>

typedef struct ListaSimpla nodLS;
typedef struct Student student;

struct Student {
	int nrMatricol;
	char* nume;
	char* facultate;
	float medie;
};

struct ListaSimpla {
	student info;
	nodLS* next;
};

nodLS* inserareNod(nodLS* cap, student s)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->info.nrMatricol = s.nrMatricol;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.facultate = (char*)malloc((strlen(s.facultate) + 1) * sizeof(char));
	strcpy(nou->info.facultate, s.facultate);
	nou->info.medie = s.medie;

	nou->next = NULL;

	if (cap == NULL)
	{
		cap = nou;
	}
	else {
		nodLS* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("Nr Matricol = %d, Nume = %s, Facultate = %s, Medie = %5.2f\n", 
			temp->info.nrMatricol, temp->info.nume, temp->info.facultate, temp->info.medie);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp!= NULL)
	{
		nodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp->info.facultate);
		free(temp);
		temp = aux;
	}
	free(temp);
}

void stergereNod(nodLS** cap, nodLS* nodSters)
{
	//null
	if (*cap == NULL || nodSters == NULL)
	{
		return 0;
	}

	//primul
	if (*cap == nodSters)
	{
		*cap = (*cap)->next;

		free(nodSters->info.nume);
		free(nodSters->info.facultate);
		free(nodSters);

		return 0;
	}

	//mijloc
	nodLS* temp1 = *cap;
	nodLS* temp2 = temp1->next;

	while (temp2->next != NULL)
	{
		if (temp2 == nodSters)
		{
			temp1->next = temp2->next;
			free(nodSters->info.nume);
			free(nodSters->info.facultate);
			free(nodSters);
			temp2 = temp1->next;
		}
		else
		{
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}



	//ullimul
	if(temp2->next==nodSters)
	{
		temp1->next = NULL;
		free(nodSters->info.nume);
		free(nodSters->info.facultate);
		free(nodSters);
		return 0;
	}

	

	return 0;

}

//medie intre (8,9)
void cautareNodSters(nodLS** cap)
{
	nodLS* temp = *cap;
	while (temp != NULL)
	{
		if (temp->info.medie > 8 && temp->info.medie < 9)
		{
			nodLS* nodSters = temp;
			temp = temp->next;
			stergereNod(cap, nodSters);

		}
		else {
			temp = temp->next;
		}
	}
}

void main()
{
	nodLS* cap = NULL;
	char buffer[20];
	FILE* f = fopen("lista_simpla.txt", "r");
	int nrNoduri;
	student s;
	fscanf(f, "%d", &nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);

		fscanf(f, "%s", buffer);
		s.facultate = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.facultate, buffer);
		
		fscanf(f, "%f", &s.medie);
		cap = inserareNod(cap, s);
		free(s.nume);
		free(s.facultate);
	}

	printf("-->> Traversare Lista Simpla <<--\n");
	traversareLS(cap);

	printf("-->> Stergere noduri <<--\n");
	cautareNodSters(&cap);
	traversareLS(cap);

	dezalocareLS(cap);

	fclose(f);
}