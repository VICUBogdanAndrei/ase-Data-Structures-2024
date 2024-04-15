#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

typedef struct ListaSimpla nodLS;
typedef struct ListaPrincipala nodLP;
typedef struct Student student;

struct Student {
	int nrMatricol;
	char* nume;
	char* facultate;
};

struct ListaSimpla {
	student s;
	nodLS* next;
};

struct ListaPrincipala {
	nodLS* info;
	nodLP* next;
};

nodLS* creareNodLS(student s)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	
	
	nou->s.nrMatricol = s.nrMatricol;
	nou->s.facultate = (char*)malloc((strlen(s.facultate) + 1) * sizeof(char));
	strcpy(nou->s.facultate, s.facultate);

	nou->s.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->s.nume, s.nume);

	nou->next = NULL;

	return nou;

}

nodLP* creareNodLP()
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->next = NULL;
	nou->info = NULL;

	return nou;
}

nodLP* cautaPozitieLP(nodLP* capLP, char* facultate)
{
	nodLP* temp = capLP;
	while (temp != NULL)
	{
		if (strcmp(temp->info->s.facultate, facultate) == 0)
			return temp;
		temp = temp->next;
	}

	return NULL;
}

void citireFisier(FILE* f, nodLP** capLP)
{
	f = fopen("student_ll.txt", "r");
	int nrelem = 0;
	student s;
	char buffer[30];
	fscanf(f, "%d", &nrelem);
	for (int i = 0; i < nrelem; i++)
	{
		fscanf(f, "%d", &s.nrMatricol);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%s", buffer);
		s.facultate = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.facultate, buffer);

		nodLS* student = creareNodLS(s);

		free(s.nume);
		free(s.facultate);

		if (*capLP == NULL)
		{
			nodLP* nouLP = creareNodLP();
			nouLP->info = student;
			*capLP = nouLP;
		}
		else
		{
			nodLP* gasit = cautaPozitieLP(*capLP,student->s.facultate);
			if (gasit == NULL)
			{
				nodLP* finalLP = creareNodLP();
				nodLP* temp = *capLP;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = finalLP;
				finalLP->info = student;
			}
			else
			{
				nodLS* temp = gasit->info;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = student;
			}
		}

	}

	fclose(f);
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
	{
		printf("\nNr Matricol = %d, Nume = %s, Facultate = %s",
			temp->s.nrMatricol, temp->s.nume, temp->s.facultate);
		temp = temp->next;
	}
}

void traversareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	int i = 1;
	while (temp != NULL)
	{
		printf("\nPozitia: #%d", i);
		i++;
		traversareLS(temp->info);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->s.nume);
		free(temp->s.facultate);
		free(temp);
		temp = aux;
	}
}

void dezalocareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp != NULL)
	{
		nodLP* aux = temp->next;
		dezalocareLS(temp->info);
		free(temp);
		temp = aux;
	}
}

void main()
{
	nodLP* capLP = NULL;
	FILE* f = NULL;
	citireFisier(f, &capLP);

	traversareLP(capLP);

	dezalocareLP(capLP);

}
