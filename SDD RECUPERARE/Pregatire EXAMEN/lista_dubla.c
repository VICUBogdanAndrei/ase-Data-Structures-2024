#define _CRT_SECURE_NO_WARNINGS

#include<malloc.h>
#include<stdio.h>

typedef struct ListaDubla nodLD;
typedef struct Factura factura;
typedef struct Stiva nodStiva;

struct Factura {
	int idFactura;
	char* dataEmitere;
	char* beneficiar;
	float sumaPlata;
	unsigned int nrZileScadenta;
};

struct ListaDubla {
	factura info;
	nodLD* next;
	nodLD* prev;
};

struct Stiva {
	factura info;
	nodStiva* next;
};

void push(nodStiva** varf, nodLD* nodInserare)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));

	nou->info.idFactura = nodInserare->info.idFactura;
	nou->info.dataEmitere = (char*)malloc((strlen(nodInserare->info.dataEmitere) + 1) * sizeof(char));
	strcpy(nou->info.dataEmitere, nodInserare->info.dataEmitere);
	nou->info.beneficiar = (char*)malloc((strlen(nodInserare->info.beneficiar) + 1) * sizeof(char));
	strcpy(nou->info.beneficiar, nodInserare->info.beneficiar);
	nou->info.sumaPlata = nodInserare->info.sumaPlata;
	nou->info.nrZileScadenta = nodInserare->info.nrZileScadenta;

	nou->next = NULL;

	if (*varf == NULL)
	{
		(*varf) = nou;
	}
	else {
		nou->next = (*varf);
		(*varf) = nou;
	}
}

int pop(nodStiva** varf, factura* fac)
{
	if (*varf == NULL)
		return -1;
	else
	{
		(*fac).idFactura = (*varf)->info.idFactura;
		(*fac).dataEmitere = (char*)malloc((strlen((*varf)->info.dataEmitere) + 1) * sizeof(char));
		strcpy((*fac).dataEmitere, (*varf)->info.dataEmitere);
		(*fac).beneficiar = (char*)malloc((strlen((*varf)->info.beneficiar) + 1) * sizeof(char));
		strcpy((*fac).beneficiar, (*varf)->info.beneficiar);
		(*fac).sumaPlata = (*varf)->info.sumaPlata;
		(*fac).nrZileScadenta = (*varf)->info.nrZileScadenta;

		nodStiva* temp = (*varf);
		(*varf) = (*varf)->next;
		free(temp->info.dataEmitere);
		free(temp->info.beneficiar);
		free(temp);

		return 0;
		
	}
}

void traversareStiva(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("Id Factura = %d, Data Emiterii = %s, Beneficiar = %s, Suma de Plata = %5.2f , Nr zile scadenta = %d\n",
			temp->info.idFactura, temp->info.dataEmitere, temp->info.beneficiar, temp->info.sumaPlata, temp->info.nrZileScadenta);
		temp = temp->next;
	}
}

//LISTA DUBLA CIRCULARA

nodLD* inserareLD(nodLD* cap, nodLD** coada, factura f)
{
	nodLD* nou = (nodLD*)malloc(sizeof(nodLD));

	nou->info.idFactura = f.idFactura;
	nou->info.dataEmitere = (char*)malloc((strlen(f.dataEmitere) + 1) * sizeof(char));
	strcpy(nou->info.dataEmitere,f.dataEmitere);
	nou->info.beneficiar = (char*)malloc((strlen(f.beneficiar) + 1) * sizeof(char));
	strcpy(nou->info.beneficiar, f.beneficiar);
	nou->info.sumaPlata = f.sumaPlata;
	nou->info.nrZileScadenta = f.nrZileScadenta;

	nou -> next = NULL;
	nou->prev = NULL;

	if (cap == NULL)
	{
		cap = nou;
		(*coada) = nou;
		cap->next = cap;
		cap->prev = cap;
	}
	else {
		nodLD* temp = cap;
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

void traversareLD(nodLD* cap)
{
	nodLD* temp = cap;
	while (temp->next != cap)
	{
		printf("Id Factura = %d, Data Emiterii = %s, Beneficiar = %s, Suma de Plata = %5.2f , Nr zile scadenta = %d\n",
			temp->info.idFactura, temp->info.dataEmitere, temp->info.beneficiar, temp->info.sumaPlata, temp->info.nrZileScadenta);
		temp = temp->next;
	}
	printf("Id Factura = %d, Data Emiterii = %s, Beneficiar = %s, Suma de Plata = %5.2f , Nr zile scadenta = %d\n",
		temp->info.idFactura, temp->info.dataEmitere, temp->info.beneficiar, temp->info.sumaPlata, temp->info.nrZileScadenta);

}

void traversareInversa(nodLD* coada)
{
	nodLD* temp = coada;
	while (temp->prev != coada)
	{
		printf("Id Factura = %d, Data Emiterii = %s, Beneficiar = %s, Suma de Plata = %5.2f , Nr zile scadenta = %d\n",
			temp->info.idFactura, temp->info.dataEmitere, temp->info.beneficiar, temp->info.sumaPlata, temp->info.nrZileScadenta);
		temp = temp->prev;
	}
	printf("Id Factura = %d, Data Emiterii = %s, Beneficiar = %s, Suma de Plata = %5.2f , Nr zile scadenta = %d\n",
		temp->info.idFactura, temp->info.dataEmitere, temp->info.beneficiar, temp->info.sumaPlata, temp->info.nrZileScadenta);
}

void dezalocareLD(nodLD* cap)
{
	nodLD* temp = cap;
	while (temp->next != cap)
	{
		nodLD* aux = temp->next;
		free(temp->info.beneficiar);
		free(temp->info.dataEmitere);
		free(temp);
		temp = aux;
	}
	free(temp->info.beneficiar);
	free(temp->info.dataEmitere);
	free(temp);
}

void sumaZileScadente(nodLD* cap, char* beneficiar, int* suma)
{
	nodLD* temp = cap;
	while (temp->next != cap)
	{
		if (strcmp(temp->info.beneficiar, beneficiar) == 0)
			(*suma) += temp->info.nrZileScadenta;
		temp = temp->next;
	}
	if (strcmp(temp->info.beneficiar, beneficiar) == 0)
		(*suma) += temp->info.nrZileScadenta;
}

void modifcicareSumaPlata(nodLD* cap, float sumaNoua, int idFac)
{
	nodLD* temp = cap;
	while (temp->next != cap)
	{
		if (temp->info.idFactura == idFac)
			temp->info.sumaPlata = sumaNoua;
		temp = temp->next;
	}
	if (temp->info.idFactura == idFac)
		temp->info.sumaPlata = sumaNoua;
}

void stergereNod(nodLD** cap, nodLD** coada, nodLD* nodSters)
{
	if (*cap == NULL || *coada == NULL || nodSters == NULL)
	{
		return 0;
	}

	if (*cap == nodSters)
	{
		(*coada)->next = (*cap)->next;
		(*cap)->next->prev = (*coada);
		free(nodSters->info.dataEmitere);
		free(nodSters->info.beneficiar);
		free(nodSters);

		return 0;
	}

	if (*coada == nodSters)
	{
		(*cap)->prev = (*coada)->prev;
		(*coada)->prev->next = (*cap);
		free(nodSters->info.dataEmitere);
		free(nodSters->info.beneficiar);
		free(nodSters);
		return 0;
	}

	nodLD* anterior = nodSters->prev;
	nodLD* urmator = nodSters->next;

	anterior->next = urmator;
	urmator->prev = anterior;

	free(nodSters->info.dataEmitere);
	free(nodSters->info.beneficiar);
	free(nodSters);

	return 0;

}

void cautaNod(nodLD** cap, nodLD** coada, float pragSuma)
{
	nodLD* temp = *cap;
	while (temp->next != *cap)
	{
		if (temp->info.sumaPlata < pragSuma)
		{
			nodLD* nodSters = temp;
			temp = temp->next;
			stergereNod(cap, coada, nodSters);
		}
		else {
			temp = temp->next;
		}
	}
	if (temp->info.sumaPlata < pragSuma)
	{
		nodLD* nodSters = temp;
		stergereNod(cap, coada, nodSters);
	}
}

int compareDate(char* datatemp, char* dataCriteriu)
{
	int z1, l1, a1;
	int z2, l2, a2;

	sscanf(datatemp, "%d/%d/%d", &z1, &l1, &a1);
	sscanf(dataCriteriu, "%d/%d/%d", &z2, &l2, &a2);

	if (a1 != a2)
		return a1 - a2;
	if (l1 != l2)
		return l1 - l2;
	if (z1 != z2)
		return z1 - z2;
}

void adaugareStiva(nodLD* cap, nodStiva** varf, char* dataCriteriu)
{
	nodLD* temp = cap;
	while (temp->next != cap)
	{
		if (compareDate(temp->info.dataEmitere,dataCriteriu)>0)
			push(varf, temp);
		temp = temp->next;
	}
	if (compareDate(temp->info.dataEmitere, dataCriteriu) > 0)
		push(varf, temp);
}

void main()
{
	nodLD* cap = NULL, * coada = NULL;
	factura fac;
	int nrNoduri;
	char buffer[20];
	FILE* f = fopen("lista_dubla.txt", "r");
	fscanf(f, "%d", &nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		fscanf(f, "%d", &fac.idFactura);
		fscanf(f, "%s", buffer);
		fac.dataEmitere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fac.dataEmitere, buffer);
		fscanf(f, "%s", buffer);
		fac.beneficiar = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fac.beneficiar, buffer);
		fscanf(f, "%f", &fac.sumaPlata);
		fscanf(f, "%d", &fac.nrZileScadenta);

		cap = inserareLD(cap, &coada, fac);
		free(fac.dataEmitere);
		free(fac.beneficiar);
	}

	printf("-->> TRAVERSARE LISTA DUBLA CIRCULARA '->' <<--\n");
	traversareLD(cap);

	printf("\n-->> TRAVERSARE LISTA DUBLA CIRCULARA '<-' <<--\n");
	traversareInversa(coada);

	printf("\n-->> SUMA ZILE SCANDENTE BENEFICIAR CUNOSCUT <<--\n");
	int sumaTotalZileScadente = 0;
	char* numeBeneficiar = (char*)malloc((strlen("Bogdan") + 1) * sizeof(char));
	strcpy(numeBeneficiar, "Bogdan");
	sumaZileScadente(cap, numeBeneficiar, &sumaTotalZileScadente);
	printf("Numarul total de zile pentru clientul %s este de %d.\n", numeBeneficiar, sumaTotalZileScadente);

	printf("\n-->> MODIFICARE SUMA PLATA DUPA ID FACTURA CUNOSCUT <<--\n");
	int idFac = 37;
	float sumaNoua = 1090.89;
	modifcicareSumaPlata(cap, sumaNoua, idFac);
	traversareLD(cap);

	printf("\n-->> STERGERE FACTURI DUPA PRAG SUMA PLATA <<--\n");
	float pragSuma = 100;
	cautaNod(&cap, &coada, pragSuma);
	traversareLD(cap);

	printf("\n-->> ADAUGARE FACTURI IN STIVA EMISE DUPA O ANUMITA DATA <<--\n");
	nodStiva* varf = NULL;
	char* dataCrietriu = (char*)malloc((strlen("09/09/2024")+1)*sizeof(char));
	strcpy(dataCrietriu, "09/09/2024");
	adaugareStiva(cap, &varf, dataCrietriu);
	traversareStiva(varf);

	printf("\n-->> DEZALOCARE STIVA <<--\n");
	int nrElemStiva = 0;
	while (pop(&varf, &fac) == 0)
	{
		nrElemStiva++;
	}
	
	printf("Au fost dezalocate %d noduri din stiva creata anterior!\n\n", nrElemStiva);

	dezalocareLD(cap);

	fclose(f);
}