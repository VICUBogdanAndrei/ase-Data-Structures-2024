#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

typedef struct {
	int nrInventar;
	char* numeProdus;
	float cantitate;
	float pret;
	char* producator;
}produs;

typedef struct {
	produs info;
	struct nodLD* prev, * next;
}nodLD;

typedef struct {
	produs info;
	struct nodLS * next;
}nodLS;

nodLD* inserareNod(nodLD* cap, nodLD** coada, produs p)
{
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));

	nou->info.nrInventar = p.nrInventar;
	nou->info.numeProdus = (char*)malloc((strlen(p.numeProdus) + 1) * sizeof(char));
	strcpy(nou->info.numeProdus, p.numeProdus);

	nou->info.cantitate = p.cantitate;
	nou->info.pret = p.pret;

	nou->info.producator = (char*)malloc((strlen(p.producator) + 1) * sizeof(char));
	strcpy(nou->info.producator, p.producator);

	nou->prev = NULL;
	nou->next = NULL;
	if (cap == NULL)
	{
		nou->next = nou;
		nou->prev = nou;
		cap = nou;
		*coada = nou;
	}
	else
	{
		nodLD* temp = cap;
		while (temp->next != cap)
		{
			temp = temp->next;
		}
		temp->next = nou;
		nou->prev = temp;
		(*coada) = nou;
		nou->next = cap;
		cap->prev = nou;
		(*coada) = nou;
		//(*coada)->next = cap;
		//cap->prev = *coada;
	}

	return cap;
}

nodLS* inserareLS(nodLS** cap, nodLD* copie)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));

	nou->info.nrInventar = copie->info.nrInventar;
	nou->info.numeProdus = (char*)malloc((strlen(copie->info.numeProdus) + 1) * sizeof(char));
	strcpy(nou->info.numeProdus, copie->info.numeProdus);

	nou->info.cantitate = copie->info.cantitate;
	nou->info.pret = copie->info.pret;

	nou->info.producator = (char*)malloc((strlen(copie->info.producator) + 1) * sizeof(char));
	strcpy(nou->info.producator, copie->info.producator);

	nou->next = NULL;

	if (*cap == NULL)
	{
		*cap = nou;
	}
	else {
		nodLS* temp = *cap;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = nou;
	}
	return *cap;
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp!=NULL)
	{
		printf("\nNr Inventar = %d, Nume Produs = %s, Cantitate = %5.2f, Pret = %5.2f, Producator = %s",
			temp->info.nrInventar, temp->info.numeProdus, temp->info.cantitate, temp->info.pret, temp->info.producator);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->info.numeProdus);
		free(temp->info.producator);
		free(temp);
		temp = aux;
	}
	free(temp);
}

void copiereLD_LS(nodLD* capLD, nodLS** capLS)
{
	nodLD* tempLD = capLD;

	inserareLS(capLS, tempLD);
	tempLD = tempLD->next;

	// lista dubla este circulara
	while (tempLD != capLD)
	{
		inserareLS(capLS, tempLD);
		tempLD = tempLD->next;
	}

}

void traversare(nodLD* cap)
{
	nodLD* temp = cap;
	while (temp->next != cap)
	{
		printf("\nNr Inventar = %d, Nume Produs = %s, Cantitate = %5.2f, Pret = %5.2f, Producator = %s",
			temp->info.nrInventar, temp->info.numeProdus, temp->info.cantitate, temp->info.pret, temp->info.producator);
		temp = temp->next;
	}
	printf("\nNr Inventar = %d, Nume Produs = %s, Cantitate = %5.2f, Pret = %5.2f, Producator = %s",
		temp->info.nrInventar, temp->info.numeProdus, temp->info.cantitate, temp->info.pret, temp->info.producator);
}

void traversareInversa(nodLD* coada)
{
	nodLD* temp = coada;
	while (temp->next != coada)
	{
		printf("\nNr Inventar = %d, Nume Produs = %s, Cantitate = %5.2f, Pret = %5.2f, Producator = %s",
			temp->info.nrInventar, temp->info.numeProdus, temp->info.cantitate, temp->info.pret, temp->info.producator);
		temp = temp->next;
	}
	printf("\nNr Inventar = %d, Nume Produs = %s, Cantitate = %5.2f, Pret = %5.2f, Producator = %s",
		temp->info.nrInventar, temp->info.numeProdus, temp->info.cantitate, temp->info.pret, temp->info.producator);

}

void stergereNod(nodLD** cap, nodLD** coada, nodLD* nodSters)
{
	if (cap == NULL || coada == NULL || nodSters == NULL)
	{
		return 0;
	}

	if (*cap == nodSters)
	{
		nodLD* aux = (*cap)->next;
		aux->prev = *coada;
		(*coada)->next = aux;
		*cap = aux;
		free(nodSters->info.numeProdus);
		free(nodSters->info.producator);
		free(nodSters);

		return 0;
	}

	if (*coada == nodSters)
	{
		nodLD* aux = (*coada)->prev;
		aux->next = *cap;
		(*cap)->prev = aux;
		*coada = aux;

		free(nodSters->info.numeProdus);
		free(nodSters->info.producator);
		free(nodSters);

		return 0;
	}

	nodLD* anterior = nodSters->prev;
	nodLD* urmator = nodSters->next;

	anterior->next = urmator;
	urmator->prev = anterior;

	free(nodSters->info.numeProdus);
	free(nodSters->info.producator);
	free(nodSters);

	return 0;
	

}

void stergereIndice(nodLD** cap, nodLD** coada, char c)
{
	nodLD* temp = *cap;
	while(temp->next != *cap)
	{
		if (temp->info.producator[0] == c)
		{
			nodLD* nodSters = temp;
			temp = temp->next;
			stergereNod(cap, coada, nodSters);
			
		}
		else {
			temp = temp->next;
		}
	}
	if (temp->info.producator[0] == c)
	{
		nodLD* nodSters = temp;
		stergereNod(cap, coada, nodSters);
		temp = temp->next;
	}
}

void dezalocare(nodLD* cap)
{
	nodLD* temp= cap;
	while (temp->next != cap)
	{
		nodLD* aux = temp->next;
		free(temp->info.numeProdus);
		free(temp->info.producator);
		free(temp);
		temp = aux;
	}
	free(temp->info.numeProdus);
	free(temp->info.producator);
	free(temp);
}


void main()
{
	produs p;
	nodLD* cap = NULL, * coada = NULL;
	nodLS* capLS = NULL;
	int nrElem = 0;
	char buffer[30];
	FILE* f = fopen("produse.txt", "r");
	fscanf(f, "%d", &nrElem);
	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%d", &p.nrInventar);

		fscanf(f, "%s", buffer);
		p.numeProdus = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.numeProdus, buffer);

		fscanf(f, "%f", &p.cantitate);
		fscanf(f, "%f", &p.pret)
			;
		fscanf(f, "%s", buffer);
		p.producator = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.producator, buffer);

		cap = inserareNod(cap, &coada, p);
		free(p.numeProdus);
		free(p.producator);
	}
	fclose(f);

	printf("\n-----AFISARE LISTA DUBLA ST-DR-----\n");

	traversare(cap);

	printf("\n-----AFISARE LISTA DUBLA DR-ST-----\n");

	traversareInversa(coada);

	printf("\n\n\n-----TRANSFORMARE IN LISTA SIMPLA-----");

	printf("\n-----COPIERE LISTA DUBLA CIRCULARA IN LISTA SIMPLA LINIARA-----\n");

	copiereLD_LS(cap, &capLS);
	traversareLS(capLS);


	printf("\n\n-----STERGERE PRODUSE, UNDE PRODUCATORUL INCEPE CU LITERA 'N'-----\n");

	stergereIndice(&cap, &coada, 'N');
	traversare(cap);

	printf("\n----------\n");

	//dezalocare lista simpla dubla
	dezalocare(cap);
	//dezalocare lista simpla
	dezalocareLS(capLS);
}