#include <stdio.h>
#include <malloc.h>

typedef struct
{
	char* nume;
	int nrGrupa;
	float medie;
} student;

typedef struct
{
	student inf;
	struct nodLS* next;
} nodLS;

typedef struct
{
	struct nodLS* inf;
	struct nodLP* next;
} nodLP;

void inserareLS(nodLS** capLS, student s)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->inf.nume, s.nume);
	nou->inf.nrGrupa = s.nrGrupa;
	nou->inf.medie = s.medie;
	nou->next = NULL;
	if (*capLS == NULL)
		*capLS = nou;
	else
	{
		nodLS* temp = *capLS;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

nodLP* inserareLP(nodLP* capLP, nodLS* capLS)
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->inf = capLS;
	nou->next = NULL;
	if (capLP == NULL)
		capLP = nou;
	else
	{
		nodLP* temp = capLP;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
	return capLP;
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		printf("\nNume=%s, Grupa=%d, Medie=%5.2f",
			temp->inf.nume, temp->inf.nrGrupa,
			temp->inf.medie);
		temp = temp->next;
	}
}

void traversareLP(nodLS* capLP)
{
	nodLP* temp = capLP;
	int i = 1;
	while (temp)
	{
		printf("\nSublista: %d", i);
		traversareLS(temp->inf);
		temp = temp->next;
		i++;
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		free(temp->inf.nume);
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	while (temp)
	{
		nodLP* temp2 = temp->next;
		dezalocareLS(temp->inf);
		free(temp);
		temp = temp2;
	}
}

void main()
{
	int nrStud;
	nodLP* capLP = NULL;
	nodLS* capLSpromovat = NULL, *capLSnepromovat = NULL;
	char buffer[20];
	student s;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrStud);
	for (int i = 0; i < nrStud; i++)
	{
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%d", &s.nrGrupa);
		fscanf(f, "%f", &s.medie);
		if (s.medie >= 5)
			inserareLS(&capLSpromovat, s);
		else
			inserareLS(&capLSnepromovat, s);
		free(s.nume);
	}
	fclose(f);
	capLP = inserareLP(capLP, capLSpromovat);
	capLP = inserareLP(capLP, capLSnepromovat);

	traversareLP(capLP);
	dezalocareLP(capLP);
}


