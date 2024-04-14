#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>

typedef struct {
	int zi, luna, an;
}dataPrimire;

typedef struct {
	dataPrimire data;
	int prioritate;
	char* aplicatie;
	float durata;
}notificare;

typedef struct {
	notificare info;
	struct nodStiva* next;
}nodStiva;


void push(nodStiva** varf, notificare val)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->info.data.zi = val.data.zi;
	nou->info.data.luna = val.data.luna;
	nou->info.data.an = val.data.an;

	nou->info.prioritate = val.prioritate;
	nou->info.aplicatie = (char*)malloc((strlen(val.aplicatie) + 1) * sizeof(char));
	strcpy(nou->info.aplicatie, val.aplicatie);

	nou->info.durata = val.durata;
	nou->next = NULL;

	if (*varf == NULL)
		*varf = nou;
	else {
		nou->next = *varf;
		*varf = nou;
	}
	
}

int pop(nodStiva** varf, notificare* val)
{
	if (*varf == NULL)
		return -1;
	else
	{
		(*val).data.zi = (*varf)->info.data.zi;
		(*val).data.luna = (*varf)->info.data.luna;
		(*val).data.an = (*varf)->info.data.an;

		(*val).prioritate = (*varf)->info.prioritate;
		(*val).aplicatie = (char*)malloc((strlen((*varf)->info.aplicatie) + 1) * sizeof(char));
		strcpy((*val).aplicatie, (*varf)->info.aplicatie);

		(*val).durata = (*varf)->info.durata;

		nodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp->info.aplicatie);
		free(temp);

		return 0;
	}
}

void traversare(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("\nData = %d/%d/%d, Prioritate = %d, Aplicatie = %s, Durata = %5.2f",
			temp->info.data.zi, temp->info.data.luna, temp->info.data.an, temp->info.prioritate, temp->info.aplicatie, temp->info.durata);
		temp = temp->next;
	}
}

void salvareVector(nodStiva* varf, notificare* vect, int* nrNotif)
{
	notificare notif;
	while (pop(&varf, &notif) == 0)
	{
		vect[*nrNotif] = notif;
		(*nrNotif)++;
	}
}

typedef struct {
	notificare info;
	struct nodLS* next;
}nodLS;

nodLS* inserareNod(nodLS** cap, nodStiva* copie)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.data.zi = copie->info.data.zi;
	nou->info.data.luna = copie->info.data.luna;
	nou->info.data.an = copie->info.data.an;

	nou->info.prioritate = copie->info.prioritate;
	nou->info.aplicatie = (char*)malloc((strlen(copie->info.aplicatie) + 1) * sizeof(char));
	strcpy(nou->info.aplicatie, copie->info.aplicatie);

	nou->info.durata = copie->info.durata;
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
nodLS* inserareInFata(nodLS** cap, nodStiva* copie)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info.data.zi = copie->info.data.zi;
	nou->info.data.luna = copie->info.data.luna;
	nou->info.data.an = copie->info.data.an;

	nou->info.prioritate = copie->info.prioritate;
	nou->info.aplicatie = (char*)malloc((strlen(copie->info.aplicatie) + 1) * sizeof(char));
	strcpy(nou->info.aplicatie, copie->info.aplicatie);

	nou->info.durata = copie->info.durata;
	nou->next = NULL;

	if (*cap == NULL)
	{
		*cap = nou;
	}
	else
	{
		nou->next = *cap;
		*cap = nou;
	}

	return *cap;
}

void conversieStiva_LS(nodStiva* varf, nodLS** cap1, nodLS** cap2)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		inserareNod(cap1, temp);
		inserareInFata(cap2, temp);
		temp = temp->next;
	}
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != NULL)
	{
		printf("\nData = %d/%d/%d, Prioritate = %d, Aplicatie = %s, Durata = %5.2f",
			temp->info.data.zi, temp->info.data.luna, temp->info.data.an, temp->info.prioritate, temp->info.aplicatie, temp->info.durata);
		temp = temp->next;
	}
}

void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp->next != NULL)
	{
		nodLS* aux = temp->next;
		free(temp->info.aplicatie);
		free(temp);
		temp = aux;
	}
	free(temp->info.aplicatie);
	free(temp);
}

void main()
{
	int nrElem = 0;
	nodStiva* varf = NULL;
	char buffer[20];
	notificare notif;
	FILE* f = fopen("notificare.txt", "r");
	fscanf(f, "%d", &nrElem);
	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%d", &notif.data.zi);
		fscanf(f, "%d", &notif.data.luna);
		fscanf(f, "%d", &notif.data.an);

		fscanf(f, "%d", &notif.prioritate);
		fscanf(f, "%s", buffer);
		notif.aplicatie = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(notif.aplicatie, buffer);
		fscanf(f, "%f", &notif.durata);

		push(&varf, notif);
		free(notif.aplicatie);
	}

	printf("\n\n----AFISARE STIVA----\n\n");

	traversare(varf);

	printf("\n\n----TRANSFORMARE IN LISTA----\n\n");
	nodLS* cap1 = NULL, *cap2=NULL;
	conversieStiva_LS(varf, &cap1, &cap2);
	traversareLS(cap1);
	printf("\n\n--------\n\n");
	traversareLS(cap2);

	printf("\n\n----AFISARE STIVA----\n\n");

	traversare(varf);

	printf("\n\n----SALVARE VECTOR----\n\n");
	notificare* vect = (notificare*)malloc(nrElem * sizeof(notificare));
	int nrNotifVect = 0;
	salvareVector(varf, vect, &nrNotifVect);

	for (int i = 0; i < nrNotifVect; i++)
	{
		printf("\nData = %d/%d/%d, Prioritate = %d, Aplicatie = %s, Durata = %5.2f",
			vect[i].data.zi, vect[i].data.luna, vect[i].data.an, vect[i].prioritate, vect[i].aplicatie, vect[i].durata);
	}

	for (int i = 0; i < nrNotifVect; i++)
	{
		free(vect[i].aplicatie);
	}

	free(vect);

	//dezalocare stiva
	/*while (pop(&varf, &notif) == 0)
	{
		free(notif.aplicatie);
	}*/


	fclose(f);
	dezalocareLS(cap1);
	dezalocareLS(cap2);
}