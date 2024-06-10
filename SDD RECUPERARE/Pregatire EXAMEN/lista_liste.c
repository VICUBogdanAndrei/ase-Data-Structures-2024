#define _CRT_SECURE_NO_WARNINGS

#include<malloc.h>
#include<stdio.h>

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

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
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

nodLP* creareNodLP()
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->next = NULL;
	nou->info = NULL;

	return nou;
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

void sumaProgramri(nodLP* capLP, char* data, int* sumaTotala)
{
	
	nodLP* temp = capLP;
	while (temp != NULL)
	{
		if (strcmp(temp->info->info.dataProgramare, data) == 0)
		{
			nodLS* tempLS = temp->info;
			while (tempLS != NULL)
			{
				*sumaTotala += tempLS->info.cost;
				tempLS = tempLS->next;
			}
			return 0;
		}
		temp = temp->next;
	}
}

void modificareCost(nodLP** capLP, int costNou, char* numeNou)
{
	nodLP* temp = *capLP;
	while (temp != NULL)
	{
		nodLS* tempLS = temp->info;
		while (tempLS != NULL)
		{
			if (strcmp(tempLS->info.numeClient, numeNou) == 0)
				tempLS->info.cost = costNou;
			tempLS = tempLS->next;
		}
		temp = temp->next;
	}
}

void stergereNod(nodLP** capLP, nodLS** capLS, nodLP** pozitieLP, nodLS* nodSters) {
	if (*capLS == NULL || nodSters == NULL) {
		return 0;
	}

	if (*capLS == nodSters)
	{
		if (nodSters->next == NULL)
			*capLS = NULL;
		else
		{
			*capLS = nodSters->next;
		}

		*pozitieLP = (*capLS);
		free(nodSters->info.dataProgramare);
		free(nodSters->info.numeClient);
		free(nodSters->info.serviciiEfectuate);
		free(nodSters);
		return 0;
	}

	nodLS* temp1 = *capLS;
	nodLS* temp2 = (*capLS)->next;

	while (temp2->next != NULL)
	{
		if (temp2 == nodSters)
		{
			temp1->next = temp2->next;
			free(nodSters->info.dataProgramare);
			free(nodSters->info.numeClient);
			free(nodSters->info.serviciiEfectuate);
			free(nodSters);

			return 0;
		}
		else {
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}

	if (temp2 == nodSters)
	{
		temp1->next = NULL;
		free(nodSters->info.dataProgramare);
		free(nodSters->info.numeClient);
		free(nodSters->info.serviciiEfectuate);
		free(nodSters);

		return 0;
	}

	return 0;

}

void cautareNodSters(nodLP** capLP, float pragDurata)
{
	nodLP* tempLP = *capLP;
	while (tempLP != NULL)
	{
		nodLS* tempLS = (*capLP)->info;
		nodLS** capLS = &tempLP->info;
		while (tempLS != NULL)
		{
			if (tempLS->info.durata < pragDurata)
			{
				nodLS* nodSters = tempLS;
				tempLS = tempLS->next;
				stergereNod(capLP, capLS, &tempLP , nodSters);
			}
			else
			{
				tempLS = tempLS->next;
			}
		}
		tempLP = tempLP->next;
	}
}

void main()
{
	nodLP* capLP = NULL;
	nodLS* capLS = NULL;
	programare p;
	char buffer[20];
	int nrElem = 0;

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

		free(p.dataProgramare);
		free(p.numeClient);
		free(p.serviciiEfectuate);

		if (capLP == NULL)
		{
			nodLP* nouLP = creareNodLP();
			nouLP->info = programare;
			capLP = nouLP;
		}
		else {
			nodLP* gasit = cautarePozitieLP(capLP, programare->info.dataProgramare);

			if (gasit == NULL)
			{
				nodLP* tempLP = capLP;
				while (tempLP->next != NULL)
					tempLP = tempLP->next;
				nodLP* nouLP = creareNodLP();
				tempLP->next = nouLP;
				nouLP->info = programare;
			}
			else
			{
				nodLS* tempLS = gasit->info;
				while (tempLS->next != NULL)
					tempLS = tempLS->next;
				tempLS->next = programare;

				//dezalocare gasit
				//free(gasit);
			}
			

		}


	}

	printf("\n-->> PARCURGERE LISTA DE LISTE <<--");
	parcurgereLP(capLP);

	printf("\n\n-->> SUMA PROGRAMARI DATA CUNSCUTA <<--\n");
	char* data = (char*)malloc((strlen("12/02/2024") + 1) * sizeof(char));
	strcpy(data, "12/02/2024");
	int sumaTotala = 0;
	sumaProgramri(capLP, data, &sumaTotala);
	printf("Suma totala a programrilor din data de %s este de %d.\n", data, sumaTotala);

	printf("\n\n-->> MODIFICARE COST <<--\n");
	char* numeNou = (char*)malloc((strlen("Bogdan") + 1) * sizeof(char));
	strcpy(numeNou, "Bogdan");
	int sumaNoua = 1099;
	modificareCost(&capLP, sumaNoua, numeNou);
	parcurgereLP(capLP);

	printf("\n\n-->> CAUTARE SI STERGERE NOD DUPOA DURATA <<--\n");
	float durata = 3.5;
	cautareNodSters(&capLP, durata);
	parcurgereLP(capLP);


	printf("\n\n");
	dezalocareLP(capLP);

	fclose(f);

}
