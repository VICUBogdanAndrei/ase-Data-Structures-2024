#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct TabelaHash hashT;
typedef struct ListaSimpla nodLS;
typedef struct Candidat candidat;

struct Candidat {
	int cod;
	char* nume;
	char* facultate;
	float medie;
	int salariu;
};

struct ListaSimpla {
	nodLS* next;
	candidat info;
};

struct TabelaHash {
	int nrElem;
	nodLS** vect;
};


nodLS* inserareNodLS(nodLS** cap, candidat c)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.cod = c.cod;
	nou->info.nume = (char*)malloc((strlen(c.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, c.nume);
	nou->info.facultate = (char*)malloc((strlen(c.facultate) + 1) * sizeof(char));
	strcpy(nou->info.facultate, c.facultate);
	nou->info.medie = c.medie;
	nou->info.salariu = c.salariu;

	nou->next = NULL;

	if (*cap == NULL)
	{
		*cap = nou;
	}
	else
	{
		nodLS* temp = *cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
	}
	return *cap;

}

void traversareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
	{
		printf("\nCod = %d, Nume = %s, Facultate = %s, Medie = %5.2f, Salariu = %d",
			temp->info.cod, temp->info.nume, temp->info.facultate, temp->info.medie, temp->info.salariu);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* capLS)
{
	nodLS* temp = capLS;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->info.nume);
		free(temp->info.facultate);
		free(temp);
		temp = aux;
	}
}

int funtieHash(hashT tabela, char* cheie)
{
	int sumaCaractere = 0;
	for (int i = 0; i < strlen(cheie); i++)
		sumaCaractere += cheie[i];
	return sumaCaractere % tabela.nrElem;
}

hashT inserareHash(hashT tabela, candidat c)
{
	int poz = funtieHash(tabela, c.facultate);
	inserareNodLS(&tabela.vect[poz], c);
}

void dezalocareHash(hashT tabela)
{

	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
		{
			dezalocareLS(tabela.vect[i]);
		}
	}

	free(tabela.vect);

}

void traversareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
		{
			printf("\nPozitie #%d: ", i);
			traversareLS(tabela.vect[i]);
		}
	}
}

void determinareMedie(hashT tabela, float* medieMaxima, char* facultate)
{
	int poz = funtieHash(tabela, facultate);
	nodLS* capLS = tabela.vect[poz];
	while (capLS != NULL)
	{
		if (*medieMaxima < capLS->info.medie)
			*medieMaxima = capLS->info.medie;
		capLS = capLS->next;
	}

}

void modificareSalariu(hashT tabela, int salariuNou, int codCandidat)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
		{
			nodLS* temp = tabela.vect[i];
			while (temp != NULL)
			{
				if (temp->info.cod == codCandidat)
				{
					temp->info.salariu = salariuNou;
					return 0;
				}
				temp = temp->next;
			}
		}
	}
}

void stergereNod(hashT tabela, int pozitie, nodLS* nodSters)
{
	nodLS* capLS = tabela.vect[pozitie];

	if (capLS == NULL || nodSters == NULL)
		return 0;

	if (capLS == nodSters)
	{
		if (capLS->next == NULL)
		{
			free(nodSters->info.facultate);
			free(nodSters->info.nume);
			free(nodSters);
		}
		else
		{
			capLS = capLS->next;
			free(nodSters->info.facultate);
			free(nodSters->info.nume);
			free(nodSters);
			
		}
		return 0;
	}
	else {
		nodLS* temp1 = capLS;
		nodLS* temp2 = capLS->next;

		while (temp2->next != NULL)
		{
			if (temp2 == nodSters)
			{
				temp1->next = temp2->next;
				free(nodSters->info.facultate);
				free(nodSters->info.nume);
				free(nodSters);
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
			else {
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}

		if (temp2 == nodSters)
		{
			temp1->next = NULL;
			free(nodSters->info.facultate);
			free(nodSters->info.nume);
			free(nodSters);
			
		}

		return 0;
	}
}


void cautareNod(hashT tabela, char* nume)
{
	int pozitieHash = -1;
	nodLS* nodSters = NULL;

	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
		{
			nodLS* temp = tabela.vect[i];
			while (temp != NULL)
			{
				if (strcmp(temp->info.nume, nume) == 0)
				{
					nodSters = temp;
					pozitieHash = i;
				}
				temp = temp->next;
			}

		}
	}
	stergereNod(tabela, pozitieHash, nodSters);

}

void main()
{
	hashT tabela;
	int nrElem = 0;
	char buffer[30];
	candidat c;
	FILE* f = fopen("hash_bilet4.txt", "r");
	fscanf(f, "%d", &nrElem);

	tabela.nrElem = 4 * nrElem + 1;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%d", &c.cod);
		fscanf(f, "%s", buffer);
		c.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.nume, buffer);
		fscanf(f, "%s", buffer);
		c.facultate = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.facultate, buffer);
		fscanf(f, "%f", &c.medie);
		fscanf(f, "%d", &c.salariu);

		inserareHash(tabela, c);

		free(c.nume);
		free(c.facultate);

	}

	printf("\n-->> TRVAERSARE HASH <<--\n");
	traversareHash(tabela);

	printf("\n-->> MEDIE MAXIMA <<--\n");
	float medieMaxima = 0;
	char* facultate = (char*)malloc((strlen("CSIE") + 1) * sizeof(char));
	strcpy(facultate, "CSIE");
	determinareMedie(tabela, &medieMaxima, facultate);
	printf("\nMedia maxima identificata pentru facultatea %s este %5.2f.\n", facultate, medieMaxima);

	printf("\n-->> MODIFICARE SALARIU <<--\n");
	int codCandidat = 78;
	int salariuNou = 7900;
	modificareSalariu(tabela, salariuNou, codCandidat);
	traversareHash(tabela);

	printf("\n-->> STERGERE NOD CAUTAT DUPA NUME <<--\n");
	char* nume= (char*)malloc((strlen("Mihnea") + 1) * sizeof(char));
	strcpy(nume, "Mihnea");
	cautareNod(tabela, nume);
	traversareHash(tabela);

	dezalocareHash(tabela);

	fclose(f);
}
