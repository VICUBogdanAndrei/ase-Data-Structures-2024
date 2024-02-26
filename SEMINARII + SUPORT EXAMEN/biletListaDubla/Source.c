#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>


typedef struct
{
	int numarVagon;
	char* firmaTransport;
	int numarBileteVandute;
	int capacitateVagon;
}vagon;

typedef struct {
	struct nodls* prev, * next;
	vagon info;
}nodls;


nodls* inserareNod(nodls* cap, nodls** coada, vagon s)
{
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->info.numarVagon = s.numarVagon;
	nou->info.firmaTransport = (char*)malloc((strlen(s.firmaTransport) + 1) * sizeof(char));
	strcpy(nou->info.firmaTransport, s.firmaTransport);
	nou->info.numarBileteVandute = s.numarBileteVandute;
	nou->info.capacitateVagon = s.capacitateVagon;
	nou->next = NULL;
	nou->prev = NULL;
	if (cap == NULL)
	{
		cap = nou;
		nou->next = cap;
		nou->prev = cap;
		(*coada) = nou;
	}
	else {
		nodls* temp = cap;
		while (temp->next != cap)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		(*coada) = nou;
		(*coada)->next = cap;
		cap->prev = (*coada);
	}
	return cap;
}

void traversare(nodls* cap)
{
	nodls* temp = cap;
	while (temp->next != cap)
	{
		printf("\nNumar Vagon = %d, Firma Transport = %s, Numar Bilete Vandute = %d, CapacitateVagon = %d",
			temp->info.numarVagon, temp->info.firmaTransport, temp->info.numarBileteVandute, temp->info.capacitateVagon);
		temp = temp->next;
	}
	printf("\nNumar Vagon = %d, Firma Transport = %s, Numar Bilete Vandute = %d, CapacitateVagon = %d",
		temp->info.numarVagon, temp->info.firmaTransport, temp->info.numarBileteVandute, temp->info.capacitateVagon);
}

void traversareInversa(nodls* coada)
{
	nodls* temp = coada;
	while (temp->prev != coada)
	{
		printf("\nNumar Vagon = %d, Firma Transport = %s, Numar Bilete Vandute = %d, CapacitateVagon = %d",
			temp->info.numarVagon, temp->info.firmaTransport, temp->info.numarBileteVandute, temp->info.capacitateVagon);
		temp = temp->prev;
	}
	printf("\nNumar Vagon = %d, Firma Transport = %s, Numar Bilete Vandute = %d, CapacitateVagon = %d",
		temp->info.numarVagon, temp->info.firmaTransport, temp->info.numarBileteVandute, temp->info.capacitateVagon);
}

int numarMinimBilete(nodls* cap)
{
	int min = 100000;
	nodls* temp = cap;
	while (temp->next != cap)
	{
		if (temp->info.numarBileteVandute < min) min = temp->info.numarBileteVandute;
		temp = temp->next;
	}
	if (temp->info.numarBileteVandute < min) min = temp->info.numarBileteVandute;

	return min;
}

void stergere(nodls* cap)
{
	nodls* temp = cap;
	int min = numarMinimBilete(cap);
	while (temp->next != cap)
	{
		if (temp->info.numarBileteVandute == min)
		{
			nodls* tempnext = temp->next;
			nodls* tempprev = temp->prev;
			tempprev->next = tempnext;
			tempnext->prev = tempprev;
			free(temp->info.firmaTransport);
			free(temp);
			temp = tempnext;
		}
		else
			temp = temp->next;
	}
	if (temp->info.numarBileteVandute == min)
	{
		nodls* temp2 = temp->prev;
		temp2->next = cap;
		cap->prev = temp2;
		free(temp->info.firmaTransport);
		free(temp);
	}
	
}
	
void stergereInvers(nodls* coada)
{
	nodls* temp = coada;
	int min = numarMinimBilete(coada);
	while (temp->prev != coada)
	{
		if (temp->info.numarBileteVandute == min)
		{
			nodls* tempnext = temp->next;
			nodls* tempprev = temp->prev;
			tempprev->next = tempnext;
			tempnext->prev = tempprev;
			free(temp->info.firmaTransport);
			free(temp);
			temp = tempnext;
		}
		else
			temp = temp->prev;
	}
	if (temp->info.numarBileteVandute == min)
	{
		nodls* temp2 = temp->next;
		temp2->prev = coada;
		coada->next = temp2;
		free(temp->info.firmaTransport);
		free(temp);
	}

}


void dezalocare(nodls* cap)
{
	nodls* temp=cap;
	while (temp->next != cap)
	{
		nodls* temp2 = temp->next;
		free(temp->info.firmaTransport);
		free(temp);
		temp = temp2;
	}
	free(temp->info.firmaTransport);
	free(temp);
}

void main()
{
	int n;
	vagon v;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	nodls* cap =NULL, * coada=NULL;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &v.numarVagon);
		fscanf(f, "%s", buffer);
		v.firmaTransport = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(v.firmaTransport, buffer);
		fscanf(f, "%d", &v.numarBileteVandute);
		fscanf(f, "%d", &v.capacitateVagon);

		cap = inserareNod(cap, &coada, v);
		free(v.firmaTransport);
	}
	fclose(f);
	traversare(cap);
	printf("\n\n--------------------------------\n");
	traversareInversa(coada);
	printf("\n\n--------------------------------\n");
	
	
	//printf("%d",numarMinimBilete(cap));
	
	
	//stergere(cap);
	//traversare(cap);

	//printf("\n\n--------------------------------\n");

	stergereInvers(coada);
	traversareInversa(coada);


	dezalocare(cap);


}