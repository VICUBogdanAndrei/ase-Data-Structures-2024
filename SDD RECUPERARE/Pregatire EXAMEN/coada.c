#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct Coada nodCoada;
typedef struct Consultatie consultatie;

struct Consultatie {
	char* dataConsultatie;
	char* numeMedic;
	char* specialitate;
	char* diagnostic;
	int pret;
};

struct Coada {
	consultatie info;
	nodCoada* next;
};

void put(nodCoada** prim, nodCoada** ultim, consultatie c)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));

	nou->info.dataConsultatie = (char*)malloc((strlen(c.dataConsultatie) + 1) * sizeof(char));
	strcpy(nou->info.dataConsultatie, c.dataConsultatie);
	nou->info.numeMedic = (char*)malloc((strlen(c.numeMedic) + 1) * sizeof(char));
	strcpy(nou->info.numeMedic, c.numeMedic);
	nou->info.specialitate = (char*)malloc((strlen(c.specialitate) + 1) * sizeof(char));
	strcpy(nou->info.specialitate, c.specialitate);
	nou->info.diagnostic = (char*)malloc((strlen(c.diagnostic) + 1) * sizeof(char));
	strcpy(nou->info.diagnostic, c.diagnostic);
	nou->info.pret = c.pret;

	nou->next = NULL;

	if (*prim == NULL || *ultim == NULL)
	{
		(*prim) = nou;
		(*ultim) = nou;
	}
	else
	{
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

int get(nodCoada** prim, nodCoada** ultim, consultatie* c)
{
	if (*prim == NULL || *ultim == NULL)
	{
		return -1;
	}
	else
	{
		(*c).dataConsultatie = (char*)malloc((strlen((*prim)->info.dataConsultatie) + 1) * sizeof(char));
		strcpy((*c).dataConsultatie, (*prim)->info.dataConsultatie);
		(*c).numeMedic = (char*)malloc((strlen((*prim)->info.numeMedic) + 1) * sizeof(char));
		strcpy((*c).numeMedic, (*prim)->info.numeMedic);
		(*c).specialitate = (char*)malloc((strlen((*prim)->info.specialitate) + 1) * sizeof(char));
		strcpy((*c).specialitate, (*prim)->info.specialitate);
		(*c).diagnostic = (char*)malloc((strlen((*prim)->info.diagnostic) + 1) * sizeof(char));
		strcpy((*c).diagnostic, (*prim)->info.diagnostic);
		(*c).pret = (*prim)->info.pret;

		nodCoada* temp = (*prim)->next;
		free((*prim)->info.dataConsultatie);
		free((*prim)->info.numeMedic);
		free((*prim)->info.specialitate);
		free((*prim)->info.diagnostic);
		free((*prim));
		(*prim) = temp;

		return 0;
	}	
}
void traversareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nData consultatie = %s, Nume medic = %s, Specialitate = %s, Diagnostic = %s, Pret = %d",
			temp->info.dataConsultatie, temp->info.numeMedic, temp->info.specialitate, temp->info.diagnostic, temp->info.pret);
		temp = temp->next;
	}
}

void main()
{
	nodCoada* prim = NULL;
	nodCoada* ultim = NULL;

	consultatie c;
	char buffer[20];
	int nrElem = 0;

	FILE* f = fopen("coada.txt", "r");
	fscanf(f, "%d", &nrElem);
	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%s", buffer);
		c.dataConsultatie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.dataConsultatie, buffer);

		fscanf(f, "%s", buffer);
		c.numeMedic = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.numeMedic, buffer);

		fscanf(f, "%s", buffer);
		c.specialitate = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.specialitate, buffer);

		fscanf(f, "%s", buffer);
		c.diagnostic = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.diagnostic, buffer);

		fscanf(f, "%d", &c.pret);

		put(&prim, &ultim, c);

		free(c.dataConsultatie);
		free(c.numeMedic);
		free(c.specialitate);
		free(c.diagnostic);
	}

	printf("-->> TRAVERSARE COADA <<--\n");
	traversareCoada(prim);

	printf("\n-->> NUMARARE NODURI LA DEZALOCARE <<--\n");
	int nr = 0;
	while (get(&prim, &ultim, &c) == 0)
	{
		nr++;
	}
	printf("LA dezalocare, au fost stersi din memorie %d elemente din stiva!\n", nr);

}