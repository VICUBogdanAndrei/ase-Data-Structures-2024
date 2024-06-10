#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct ListaPrincipala nodLP;
typedef struct ListaSecundara nodLS;
typedef struct Programare programare;

struct Programare {
	char* dataProgramare;
	char* numeClient;
	float durata;
	char* serviciiEfectuate;
	int cost;
};

struct ListaSecundara {
	programare info;
	nodLS* next;
};

struct ListaPrincipala {
	nodLP* next;
	nodLS* info;
};

nodLS* creareNodLS(programare p)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.dataProgramare = (char*)malloc((strlen(p.dataProgramare) + 1) * sizeof(char));
	strcpy(nou->info.dataProgramare, p.dataProgramare);

	nou->info.numeClient = (char*)malloc((strlen(p.numeClient) + 1) * sizeof(char));
	strcpy(nou->info.numeClient, p.numeClient);

	nou->info.durata = p.durata;

	nou->info.serviciiEfectuate = (char*)malloc((strlen(p.serviciiEfectuate) + 1) * sizeof(char));
	strcpy(nou->info.serviciiEfectuate, p.serviciiEfectuate);

	nou->info.cost = p.cost;

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

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp!=NULL)
	{
		nodLS* aux = temp->next;
		free(temp->info.dataProgramare);
		free(temp->info.numeClient);
		free(temp->info.serviciiEfectuate);
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

nodLP* cautarePozitieLP(nodLP* capLP, char* dataProgramare)
{
	nodLP* temp = capLP;
	while (temp != NULL)
	{
		if (strcmp(temp->info->info.dataProgramare, dataProgramare) == 0)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

void parcurgereLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
	{
		printf("\nData Programare = %s, Numele Clientului = %s, Durata = %5.2f, Servicii = %s, Cost = %d",
			temp->info.dataProgramare, temp->info.numeClient, temp->info.durata, temp->info.serviciiEfectuate, temp->info.cost);
		temp = temp->next;
	}
}

void parcurgereLP(nodLP* capLP)
{
	nodLP* temp = capLP;
	int i = 1;
	while (temp != NULL)
	{
		printf("\n\nPozitia #%d: %s", i, temp->info->info.dataProgramare);
		parcurgereLS(temp->info);
		temp = temp->next;

		i++;
	}
}

void main()
{
	nodLP* capLP = NULL;
	nodLS* capLS = NULL;

	char buffer[20];
	int nrElem = 0;
	programare p;

	FILE* f = fopen("lista_liste.txt", "r");
	fscanf(f, "%d", &nrElem);

	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%s", buffer);
		p.dataProgramare = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.dataProgramare, buffer);

		fscanf(f, "%s", buffer);
		p.numeClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.numeClient, buffer);

		fscanf(f, "%f", &p.durata);

		fscanf(f, "%s", buffer);
		p.serviciiEfectuate = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.serviciiEfectuate, buffer);

		fscanf(f, "%d", &p.cost);

		nodLS* programare = creareNodLS(p);
		free(p.numeClient);
		free(p.dataProgramare);
		free(p.serviciiEfectuate);

		if (capLP == NULL)
		{
			nodLP* nouLP = creareNodLP();
			nouLP->info = programare;
			capLP = nouLP;
		}
		else
		{
			nodLP* gasit = cautarePozitieLP(capLP, programare->info.dataProgramare);

			if (gasit == NULL)
			{
				nodLP* finalLP = creareNodLP();
				nodLP* temp = capLP;
				while (temp->next != NULL)
					temp = temp->next;
				temp->next = finalLP;
				finalLP->info = programare;
			}
			else
			{
				nodLS* tempLS = gasit->info;
				while (tempLS->next != NULL)
					tempLS = tempLS->next;
				tempLS->next = programare;
			}
		}

	}

	printf("\n\n-->> TRAVERSARE LISTA DE LISTE <<--\n\n");
	parcurgereLP(capLP);

	dezalocareLP(capLP);

	fclose(f);
}