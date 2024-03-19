#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

// informatia utila
typedef struct
{
	int cod;
	char* denumire;
	float pret;
}produs;

// lista secundara
typedef struct
{
	produs inf;
	struct nodLS* next;
}nodLS;

// lista principala
typedef struct
{
	struct nodLS* inf;
	struct nodLP* next;
}nodLP;

//inserare lista secundara
void inserareLS(nodLS** capLS, produs p)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
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

void inserareLP(nodLP** capLP, nodLS* capLS)
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->inf = capLS;
	nou->next = NULL;
	if (*capLP == NULL)
		*capLP = nou;
	else
	{
		nodLP* temp = *capLP;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp)
	{
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f", temp->inf.cod, temp->inf.denumire, temp->inf.pret);
		temp = temp->next;
	}
}

void traversareLP(nodLP* capLP)
{
	int i = 1;
	nodLP* temp = capLP;
	while (temp)
	{
		printf("\nSublista #%d:", i);
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
		free(temp->inf.denumire);
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
	int nrProd;
	char buffer[20];
	nodLP* capLP = NULL;
	nodLS* capLS1 = NULL, *capLS2 = NULL;
	produs p;

	FILE* f = fopen("fisier.txt", "r");

	fscanf(f, "%d", &nrProd);
	for (int i = 0; i < nrProd; i++)
	{
		fcsnf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		fscanf(f, "%f", &p.pret);
		if (p.cod % 2 == 0)
			inserareLS(&capLS1, p);
		else
			inserareLS(&capLS2, p);

		free(p.denumire);
	}



	fclose(f);

	inserareLP(&capLP, capLS1);
	inserareLP(&capLS2, capLS2);

	traversareLP(capLP);
	dezalocare(capLP);
}
