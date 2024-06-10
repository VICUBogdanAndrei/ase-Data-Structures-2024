#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct ListaDubla nodLD;
typedef struct ListaSimpla nodLS;
typedef struct HashTable hashT;
typedef struct Reteta reteta;

struct Reteta {
	unsigned int numar;
	char* numePacient;
	char* numeMedic;
	char* statut;
	unsigned char numarMedicamente;
	float procentCompensare;
};

struct ListaDubla {
	nodLD* next, *prev;
	reteta info;
};

struct ListaSimpla {
	nodLS* next;
	reteta info;
};

struct HashTable {
	int nrElem;
	nodLS** vect;
};

nodLD* inserareLD(nodLD* capLD, nodLD** coada, reteta r)
{
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));
	nou->info.numar = r.numar;
	nou->info.numePacient = (char*)malloc((strlen(r.numePacient) + 1) * sizeof(char));
	strcpy(nou->info.numePacient, r.numePacient);
	nou->info.numeMedic = (char*)malloc((strlen(r.numeMedic) + 1) * sizeof(char));
	strcpy(nou->info.numeMedic, r.numeMedic);
	nou->info.statut = (char*)malloc((strlen(r.statut) + 1) * sizeof(char));
	strcpy(nou->info.statut, r.statut);
	nou->info.numarMedicamente = r.numarMedicamente;
	nou->info.procentCompensare = r.procentCompensare;

	nou->next = NULL;
	nou->prev = NULL;

	if (capLD == NULL || *coada==NULL)
	{
		capLD = nou;
		*coada = nou;
	}
	else {
		nodLS* temp = capLD;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		*coada = nou;
		(*coada)->prev = temp;
	}

	return capLD;
}

void traversareLD(nodLD* capLD)
{
	nodLD* temp = capLD;
	while (temp!=NULL)
	{
		printf("\nNumar = %d, Nume Pacient = %s, Nume Medic = %s, Statut Special = %s, Numar Medicamente = %u, Procent compensare = %5.2f",
			temp->info.numar, temp->info.numePacient, temp->info.numeMedic, temp->info.statut, temp->info.numarMedicamente, temp->info.procentCompensare);
		temp = temp->next;
	}
}

void traversareInversaLD(nodLD* coadaLD)
{
	nodLD* temp = coadaLD;
	while (temp!=NULL)
	{
		printf("\nNumar = %d, Nume Pacient = %s, Nume Medic = %s, Statut Special = %s, Numar Medicamente = %u, Procent compensare = %5.2f",
			temp->info.numar, temp->info.numePacient, temp->info.numeMedic, temp->info.statut, temp->info.numarMedicamente, temp->info.procentCompensare);
		temp = temp->prev;
	}
}

void dezalocareLD(nodLD* capLD)
{
	nodLD* temp = capLD;
	while (temp!=NULL)
	{
		nodLD* aux = temp->next;
		free(temp->info.numeMedic);
		free(temp->info.numePacient);
		free(temp->info.statut);
		free(temp);
		temp = aux;
	}

}

void determinareNumarRetete(nodLD* capLD, int* nrRetete, unsigned char pragMedicamente)
{
	nodLD* temp = capLD;
	while (temp != NULL)
	{
		if (temp->info.numarMedicamente > pragMedicamente)
			(*nrRetete)++;
		temp = temp->next;
	}
}

void modificareProcent(nodLD* capLD, char* nume)
{
	nodLD* temp = capLD;
	while (temp != NULL)
	{
		if (strcmp(temp->info.numePacient, nume) == 0)
		{
			temp->info.procentCompensare = temp->info.procentCompensare - (0.1 * temp->info.procentCompensare);
		}

		temp = temp->next;
	}
}

void stergereNod(nodLD** capLD, nodLD** coadaLD, nodLD* nodSters)
{
	if (*capLD == NULL || *coadaLD == NULL || nodSters == NULL)
		return 0;

	if (*capLD == nodSters)
	{
		(*capLD) = nodSters->next;
		(*capLD)->prev = NULL;
		free(nodSters->info.numeMedic);
		free(nodSters->info.numePacient);
		free(nodSters->info.statut);
		free(nodSters);

		return 0;
	}

	if (*coadaLD == nodSters)
	{
		(*coadaLD) = nodSters->prev;
		(*coadaLD)->next = NULL;
		free(nodSters->info.numeMedic);
		free(nodSters->info.numePacient);
		free(nodSters->info.statut);
		free(nodSters);

		return 0;
	}

	nodLD* anterior = nodSters->prev;
	nodLD* urmator = nodSters->next;

	anterior->next = urmator;
	urmator->prev = anterior;

	free(nodSters->info.numeMedic);
	free(nodSters->info.numePacient);
	free(nodSters->info.statut);
	free(nodSters);

	return 0;
}

void cautareNod(nodLD** capLD, nodLD** coadaLD, unsigned char prag)
{
	nodLD* temp = *capLD;
	while (temp != NULL)
	{
		if (temp->info.numarMedicamente < prag)
		{
			nodLD* nodSters = temp;
			temp = temp->next;
			stergereNod(capLD, coadaLD, nodSters);
		}
		else
			temp = temp->next;
	}
}


nodLS* inserarenodLS(nodLS** cap, reteta r)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.numar = r.numar;
	nou->info.numePacient = (char*)malloc((strlen(r.numePacient) + 1) * sizeof(char));
	strcpy(nou->info.numePacient, r.numePacient);
	nou->info.numeMedic = (char*)malloc((strlen(r.numeMedic) + 1) * sizeof(char));
	strcpy(nou->info.numeMedic, r.numeMedic);
	nou->info.statut = (char*)malloc((strlen(r.statut) + 1) * sizeof(char));
	strcpy(nou->info.statut, r.statut);
	nou->info.numarMedicamente = r.numarMedicamente;
	nou->info.procentCompensare = r.procentCompensare;

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
		printf("\nNumar = %d, Nume Pacient = %s, Nume Medic = %s, Statut Special = %s, Numar Medicamente = %u, Procent compensare = %5.2f",
			temp->info.numar, temp->info.numePacient, temp->info.numeMedic, temp->info.statut, temp->info.numarMedicamente, temp->info.procentCompensare);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		nodLD* aux = temp->next;
		free(temp->info.numeMedic);
		free(temp->info.numePacient);
		free(temp->info.statut);
		free(temp);
		temp = aux;
	}
}

int functieHash(hashT tabela, int cheie)
{
	return (cheie % 10) %tabela.nrElem;
}

hashT inserareHash(hashT tabela, reteta r)
{
	int poz = functieHash(tabela, r.numar);
	inserarenodLS(&tabela.vect[poz], r);
}

void traversareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
		{
			printf("\n\nPozitia: #%d", i);
			traversareLS(tabela.vect[i]);
		}
	}
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

void inserare_ListDubla_Hash(nodLD* capLD, hashT tabela, char* medic)
{
	nodLD* temp = capLD;
	while (temp != NULL)
	{
		if (strcmp(temp->info.numeMedic, medic) == 0)
		{
			inserareHash(tabela, temp->info);
		}
		temp = temp->next;
	}
}

void main()
{
	FILE* f = fopen("bilet2.txt", "r");

	int nrElem = 0;
	fscanf(f, "%d", &nrElem);

	hashT tabela;
	tabela.nrElem = 4 * nrElem + 1;
	tabela.vect = (nodLS**)malloc(tabela.nrElem * sizeof(nodLS*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	reteta r;
	char buffer[30];
	nodLD* capLD = NULL;
	nodLD* coadaLD = NULL;

	nodLS* capLS = NULL;

	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%d", &r.numar);
		fscanf(f, "%s", buffer);
		r.numePacient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(r.numePacient, buffer);

		fscanf(f, "%s", buffer);
		r.numeMedic = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(r.numeMedic, buffer);

		fscanf(f, "%s", buffer);
		r.statut = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(r.statut, buffer);

		fscanf(f, "%u", &r.numarMedicamente);
		fscanf(f, "%f", &r.procentCompensare);

		capLD = inserareLD(capLD, &coadaLD, r);

		free(r.numePacient);
		free(r.numeMedic);
		free(r.statut);
	}

	printf("\n-->> AFISARE LISTA DUBLA <<--\n");
	traversareLD(capLD);

	printf("\n\n-->> TRAVERSARE INVERSA <<--\n");
	traversareInversaLD(coadaLD);

	printf("\n\n-->> NUMAR RETETE DUPA PRAG NUMAR MEDICAMENTE <<--\n");
	unsigned char prag = 4;
	int nrRetete = 0;
	determinareNumarRetete(capLD, &nrRetete, prag);
	printf("Numarul retelor care au minim %u de medicamente sunt %d.", prag, nrRetete);

	printf("\n\n-->> MODIFICARE PROCENT <<--\n");
	char* nume = (char*)malloc((strlen("Victor") + 1) * sizeof(char));
	strcpy(nume, "Victor");
	modificareProcent(capLD, nume);
	traversareLD(capLD);

	printf("\n\n-->> STERGERE <<--\n");
	cautareNod(&capLD, &coadaLD, prag);
	traversareLD(capLD);


	printf("\n\n-->> HASH TABLE <<--\n\n");



	char* medic = (char*)malloc((strlen("Pop") + 1) * sizeof(char));
	strcpy(medic, "Pop");
	inserare_ListDubla_Hash(capLD, tabela, medic);

	traversareHash(tabela);

	printf("\n\n\n");

	dezalocareLD(capLD);
	dezalocareHash(tabela);

	fclose(f);
}

