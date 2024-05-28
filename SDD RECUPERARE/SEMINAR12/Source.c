#include<stdio.h>
#include<malloc.h>
#pragma warning(disable:4996)

typedef struct
{
	int nrFactura;
	char* dataEmitere;
	char* beneficiar;
	float sumaDePlata;
	int nrZileScadenta;
}factura;
//definiti structtura factura ce contine urmatoarele atribute, list as afie traversat ain ambele sensuri

typedef struct
{
	factura inf;
	struct nodls* next, * prev;
}nodls;

nodls* inserareNod(nodls* cap, nodls** coada, factura f)
{
	nodls* nou = (nodls*)malloc(sizeof(nodls));
	nou->inf.nrFactura = f.nrFactura;
	nou->inf.dataEmitere = (char*)malloc((strlen(f.dataEmitere) + 1) * sizeof(char));
	strcpy(nou->inf.dataEmitere, f.dataEmitere);
	nou->inf.beneficiar = (char*)malloc((strlen(f.beneficiar) + 1) * sizeof(char));
	strcpy(nou->inf.beneficiar, f.beneficiar);
	nou->inf.sumaDePlata = f.sumaDePlata;
	nou->inf.nrZileScadenta = f.nrZileScadenta;
	nou->next = NULL;
	nou->prev = NULL;
	if (cap == NULL)
	{
		cap = nou;
		nou->next = cap;
		nou->prev = cap;
		*coada = nou;
	}
	else
	{
		nodls* temp = cap;
		while (temp->next != cap)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
		(*coada)->next = cap;
		cap->prev = *coada;
	}
	return cap;
}


void traversare(nodls* cap)
{
	nodls* temp = cap;
	while (temp->next != cap)
	{
		printf("\nNumar factura=%d, Data emitere=%s, Beneficiar=%s, Suma de plata=%5.2f, Numar zile scadenta=%d",
			temp->inf.nrFactura, temp->inf.dataEmitere, temp->inf.beneficiar, temp->inf.sumaDePlata, temp->inf.nrZileScadenta);
		temp = temp->next;
	}
	printf("\nNumar factura=%d, Data emitere=%s, Beneficiar=%s, Suma de plata=%5.2f, Numar zile scadenta=%d",
		temp->inf.nrFactura, temp->inf.dataEmitere, temp->inf.beneficiar, temp->inf.sumaDePlata, temp->inf.nrZileScadenta);
}

void traversareInversa(nodls* coada)
{
	nodls* temp = coada;
	while (temp->next != coada)
	{
		printf("\nNumar factura=%d, Data emitere=%s, Beneficiar=%s, Suma de plata=%5.2f, Numar zile scadenta=%d",
			temp->inf.nrFactura, temp->inf.dataEmitere, temp->inf.beneficiar, temp->inf.sumaDePlata, temp->inf.nrZileScadenta);
		temp = temp->next;
	}
	printf("\nNumar factura=%d, Data emitere=%s, Beneficiar=%s, Suma de plata=%5.2f, Numar zile scadenta=%d",
		temp->inf.nrFactura, temp->inf.dataEmitere, temp->inf.beneficiar, temp->inf.sumaDePlata, temp->inf.nrZileScadenta);

}

void dezalocare(nodls* cap)
{
	nodls* temp = cap;
	while (temp->next != cap)
	{
		nodls* temp2 = temp->next;
		free(temp->inf.dataEmitere);
		free(temp->inf.beneficiar);
		free(temp);
		temp = temp2;
	}
	free(temp->inf.dataEmitere);
	free(temp->inf.beneficiar);
	free(temp);
}

void sumaFacturiBeneficiar(nodls* cap, char* beneficiar, float* suma)
{
	nodls* temp = cap;
	while (temp->next != cap)
	{
		if (strcmp(temp->inf.beneficiar, beneficiar) == 0)
			*suma += temp->inf.sumaDePlata;
		temp = temp->next;
	}
	if (strcmp(temp->inf.beneficiar, beneficiar) == 0)
		*suma += temp->inf.sumaDePlata;
}

void modificareDate(nodls* cap, nodls* coada, int nrFactura, float valoareFactura)
{
	nodls* temp = cap;
	while (temp->next != cap)
	{
		if (temp->inf.nrFactura == nrFactura)
			temp->inf.sumaDePlata = valoareFactura;
		temp = temp->next;
	}
}

void stergereNod(nodls** cap, nodls** coada, nodls *NodSters)
{
	if (*cap == NULL || NodSters == NULL || *coada == NULL)
	{
		return 0;
	}

	if (*cap == NodSters)
	{
		*cap = (*cap)->next;
		if (*cap != NULL)
			(*cap)->prev = NULL;

		free(NodSters->inf.dataEmitere);
		free(NodSters->inf.beneficiar);
		free(NodSters);

		return 0;
	}

	if (*coada == NodSters)
	{
		*coada = (*coada)->prev;
		(*coada)->next = NULL;

		free(NodSters->inf.dataEmitere);
		free(NodSters->inf.beneficiar);
		free(NodSters);

		return 0;
	}

	nodls* urmator = NodSters->next;
	nodls* anterior = NodSters->prev;

	anterior->next = urmator;
	urmator->prev = anterior;

	free(NodSters->inf.dataEmitere);
	free(NodSters->inf.beneficiar);
	free(NodSters);

	return 0;
}



void stergereFactura(nodls** cap, nodls** coada, int limitaScadenta)
{
	nodls* temp = *cap;
	while (temp->next != *cap)
	{
		if (temp->inf.nrZileScadenta<limitaScadenta)
		{
			nodls* NodSters = temp;
			temp = temp->next;
			stergereNod(cap, coada, NodSters);
		}
		else {
			temp = temp->next;
		}
	}
	if (temp->inf.nrZileScadenta < limitaScadenta)
	{
		nodls* NodSters = temp;
		temp = temp->next;
		stergereNod(cap, coada, NodSters);
	}
}

void salvareVector(nodls* cap, nodls* coada, factura* vect, int* nrElem, char* dataLimita)
{
	nodls* temp = cap;
	while (temp->next != cap)
	{
		if (strcmp(temp->inf.dataEmitere, dataLimita) > 0)
		{
			vect[*nrElem].nrFactura = temp->inf.nrFactura;
			vect[*nrElem].nrZileScadenta = temp->inf.nrZileScadenta;
			vect[*nrElem].dataEmitere = (char*)malloc((strlen(temp->inf.dataEmitere)+1*sizeof(char));
		}
	}
}
void main()
{
	int nrFacturi;
	factura fa;
	char buffer[20];
	nodls* cap = NULL, * coada = NULL;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrFacturi);
	for (int i = 0; i < nrFacturi; i++)
	{
		fscanf(f, "%d", &fa.nrFactura);
		fscanf(f, "%s", buffer);
		fa.dataEmitere = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fa.dataEmitere, buffer);
		fscanf(f, "%s", buffer);
		fa.beneficiar = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(fa.beneficiar, buffer);
		fscanf(f, "%f", &fa.sumaDePlata);
		fscanf(f, "%d", &fa.nrZileScadenta);
		cap = inserareNod(cap, &coada, fa);
		free(fa.dataEmitere);
		free(fa.beneficiar);
	}
	fclose(f);

	traversare(cap);
	printf("\n---------------------\n");
	traversare(coada);
	printf("\n-------------------\n");

	float sumaTotala = 0;
	sumaFacturiBeneficiar(cap, "Vicu", &sumaTotala);

	printf("\n----------\n");
	printf("\nSuma facturilor este = %5.2f", sumaTotala);
	printf("\n-----MODIFICARE SUMA FACTURA-----\n");
	modificareDate(cap, coada, 31, 35.45);

	traversare(cap);
	printf("\n-----STERGERE FACTURA-----\n");
//	stergereFactura(&cap, &coada, 2);
	traversare(cap);


	dezalocare(cap);

}