#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct {
	int nrVagon;
	int nrLocuri;
	int nrPasageri;
	char* companieTransport;
	char* tipTren;
}vagon;

typedef struct {
	vagon info;
	struct nodLD* next, * prev;
}nodLD;

nodLD* inserareNod(nodLD* cap, nodLD** coada, vagon v)
{
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));

	nou->info.nrVagon = v.nrVagon;
	nou->info.nrLocuri = v.nrLocuri;
	nou->info.nrPasageri = v.nrPasageri;

	nou->info.companieTransport = (char*)malloc((strlen(v.companieTransport) + 1) * sizeof(char));
	strcpy(nou->info.companieTransport, v.companieTransport);

	nou->info.tipTren = (char*)malloc((strlen(v.tipTren) + 1) * sizeof(char));
	strcpy(nou->info.tipTren, v.tipTren);

	nou->next = NULL;
	nou->prev = NULL;

	if (cap == NULL)
	{
		cap = nou;
		coada = nou;
	}
	else {
		nodLD* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
	}

	return cap;
}

void traversare(nodLD* cap)
{
	nodLD* temp = cap;
	while (temp->next != NULL)
	{
		printf("\nNr Vagon = %d, Nr locuri = %d, Nr pasageri = %d, Comapanie = %s, Tip Tren = %s",
			temp->info.nrVagon, temp->info.nrLocuri, temp->info.nrPasageri, temp->info.companieTransport, temp->info.tipTren);
		temp = temp->next;
	}
	printf("\nNr Vagon = %d, Nr locuri = %d, Nr pasageri = %d, Comapanie = %s, Tip Tren = %s",
		temp->info.nrVagon, temp->info.nrLocuri, temp->info.nrPasageri, temp->info.companieTransport, temp->info.tipTren);

}

void traversareInversa(nodLD* coada)
{
	nodLD* temp = coada;
	while (temp->prev != NULL)
	{
		printf("\nNr Vagon = %d, Nr locuri = %d, Nr pasageri = %d, Comapanie = %s, Tip Tren = %s",
			temp->info.nrVagon, temp->info.nrLocuri, temp->info.nrPasageri, temp->info.companieTransport, temp->info.tipTren);
		temp = temp->prev;
	}
	printf("\nNr Vagon = %d, Nr locuri = %d, Nr pasageri = %d, Comapanie = %s, Tip Tren = %s",
		temp->info.nrVagon, temp->info.nrLocuri, temp->info.nrPasageri, temp->info.companieTransport, temp->info.tipTren);
}

void dezalocare(nodLD* cap)
{
	nodLD* temp = cap;
	while (temp->next != NULL)
	{
		nodLD* aux = temp->next;
		free(temp->info.companieTransport);
		free(temp->info.tipTren);
		free(temp);
		temp = aux;
	}
	free(temp->info.companieTransport);
	free(temp->info.tipTren);
	free(temp);
}

void interschimbareValori(nodLD** cap, int nrElem)
{
	nodLD* temp1 = *cap;
	nodLD* temp2 = (*cap)->next;

	for (int i = 1; i < nrElem; i++)
	{
		int aux = temp1->info.nrPasageri;
		temp1->info.nrPasageri = temp2->info.nrPasageri;
		temp2->info.nrPasageri = aux;
		
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
}

void simetrie(nodLD* cap, nodLD* coada, int nrElem)
{
	nodLD* temp1 = cap;
	nodLD* temp2 = coada;
	int ok = 1;

	for (int i = 1; i <= (int)nrElem / 2 && ok==1; i++)
	{
		if (temp1->info.nrPasageri != temp2->info.nrPasageri)
			ok = 0;
		temp1 = temp1->next;
		temp2 = temp2->prev;
	}

	if (ok == 0) printf("\tLista NU este simetrica!");
	else printf("\tLista este simetrica!");
}


void var1_salvareVector(nodLD* coada, vagon* vect, int* nrElem)
{
	nodLD* temp = coada;
	while (temp->prev != NULL)
	{
		vect[*nrElem].nrVagon = temp->info.nrVagon;
		vect[*nrElem].nrLocuri = temp->info.nrLocuri;
		vect[*nrElem].nrPasageri = temp->info.nrPasageri;

		vect[*nrElem].companieTransport = (char*)malloc((strlen(temp->info.companieTransport) + 1) * sizeof(char));
		strcpy(vect[*nrElem].companieTransport, temp->info.companieTransport);

		vect[*nrElem].tipTren = (char*)malloc((strlen(temp->info.tipTren) + 1) * sizeof(char));
		strcpy(vect[*nrElem].tipTren, temp->info.tipTren);
		(*nrElem)++;
		temp = temp->prev;
	}
	vect[*nrElem].nrVagon = temp->info.nrVagon;
	vect[*nrElem].nrLocuri = temp->info.nrLocuri;
	vect[*nrElem].nrPasageri = temp->info.nrPasageri;

	vect[*nrElem].companieTransport = (char*)malloc((strlen(temp->info.companieTransport) + 1) * sizeof(char));
	strcpy(vect[*nrElem].companieTransport, temp->info.companieTransport);

	vect[*nrElem].tipTren = (char*)malloc((strlen(temp->info.tipTren) + 1) * sizeof(char));
	strcpy(vect[*nrElem].tipTren, temp->info.tipTren);
}

void var2_salvareVector(nodLD* coada, vagon* vect, int nrElem)
{
	nodLD* temp = coada;
	for (int i = 0; i < nrElem; i++)
	{
		vect[i].nrVagon = temp->info.nrVagon;
		vect[i].nrLocuri = temp->info.nrLocuri;
		vect[i].nrPasageri = temp->info.nrPasageri;

		vect[i].companieTransport = (char*)malloc((strlen(temp->info.companieTransport) + 1) * sizeof(char));
		strcpy(vect[i].companieTransport, temp->info.companieTransport);

		vect[i].tipTren = (char*)malloc((strlen(temp->info.tipTren) + 1) * sizeof(char));
		strcpy(vect[i].tipTren, temp->info.tipTren);

		temp = temp->prev;
	}
}

void afisareFisier(FILE* g, nodLD* cap, vagon* vect2, int nrElem)
{
	fprintf(g, "\n\n---- LISTA DUBLA ----\n\n");
	nodLD* temp = cap;
	while (temp->next != NULL)
	{
		fprintf(g, "\nNr Vagon = %d, Nr locuri = %d, Nr pasageri = %d, Comapanie = %s, Tip Tren = %s",
			temp->info.nrVagon, temp->info.nrLocuri, temp->info.nrPasageri, temp->info.companieTransport, temp->info.tipTren);
		temp = temp->next;
	}
	fprintf(g, "\nNr Vagon = %d, Nr locuri = %d, Nr pasageri = %d, Comapanie = %s, Tip Tren = %s",
		temp->info.nrVagon, temp->info.nrLocuri, temp->info.nrPasageri, temp->info.companieTransport, temp->info.tipTren);

	fprintf(g, "\n\n---- VECTOR ----\n\n");
	for (int i = 0; i < nrElem; i++)
	{
		fprintf(g, "\nNr Vagon = %d, Nr locuri = %d, Nr pasageri = %d, Comapanie = %s, Tip Tren = %s",
			vect2[i].nrVagon, vect2[i].nrLocuri, vect2[i].nrPasageri, vect2[i].companieTransport, vect2[i].tipTren);
	}
}

void main()
{
	vagon v;
	nodLD* cap = NULL, * coada = NULL;
	int nrElem = 0;
	char buffer[30];

	FILE* f = fopen("vagon.txt", "r");
	fscanf(f, "%d", &nrElem);
	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%d", &v.nrVagon);
		fscanf(f, "%d", &v.nrLocuri);
		fscanf(f, "%d", &v.nrPasageri);

		fscanf(f, "%s", buffer);
		v.companieTransport = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(v.companieTransport, buffer);

		fscanf(f, "%s", buffer);
		v.tipTren = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(v.tipTren, buffer);

		cap = inserareNod(cap, &coada, v);
		free(v.tipTren);
		free(v.companieTransport);
	}
	printf("\n\n-----TRAVERSARE LISTA DUBLA-----\n\n");

	traversare(cap);
	printf("\n\n");
	traversareInversa(coada);

	printf("\n\n----- INTERSCHIMBARE VALORI k-1 si k -----\n\n");
	interschimbareValori(&cap, nrElem); //pentru rulare simetrie mai usor comentati linia aceasta
	traversare(cap);

	//mare atentie pentru ca se apeleaza interschimbarea
	printf("\n\n----- LISTA SIMETRICA -----\n\n");
	simetrie(cap, coada, nrElem);

	printf("\n----SALAVRE VECTOR  VARIANTA 1----");
	vagon* vect1 = (vagon*)malloc(nrElem * sizeof(vagon));
	int nrElemVect = 0;
	var1_salvareVector(coada, vect1, &nrElemVect);
	for (int i = 0; i < nrElemVect; i++)
	{
		printf("\nNr Vagon = %d, Nr locuri = %d, Nr pasageri = %d, Comapanie = %s, Tip Tren = %s",
			vect1[i].nrVagon, vect1[i].nrLocuri, vect1[i].nrPasageri, vect1[i].companieTransport, vect1[i].tipTren);

	}

	
	printf("\n----SALAVRE VECTOR  VARIANTA 2----");
	//folosim nrElem citit din fisier
	vagon* vect2 = (vagon*)malloc(nrElem * sizeof(vagon));
	var2_salvareVector(coada, vect2, nrElem);
	for (int i = 0; i < nrElem; i++)
	{
		printf("\nNr Vagon = %d, Nr locuri = %d, Nr pasageri = %d, Comapanie = %s, Tip Tren = %s",
			vect2[i].nrVagon, vect2[i].nrLocuri, vect2[i].nrPasageri, vect2[i].companieTransport, vect2[i].tipTren);
	}

	//afisare finala in fisier
	FILE* g = fopen("output.txt", "w");

	afisareFisier(g, cap, vect2, nrElem);


	printf("\n\n");





	//dezalocare vector1
	for (int i = 0; i < nrElemVect; i++)
	{
		free(vect1[i].companieTransport);
		free(vect1[i].tipTren);
	}
	free(vect1);

	//dezalocare vector1
	for (int i = 0; i < nrElem; i++)
	{
		free(vect2[i].companieTransport);
		free(vect2[i].tipTren);
	}
	free(vect2);

	//dezalocare lista dubla
	dezalocare(cap);
	fclose(f);
	fclose(g);
}