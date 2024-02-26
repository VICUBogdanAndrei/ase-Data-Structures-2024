#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

typedef struct {
	char* nume;
	int aparitii;
}beneficiar;

typedef struct {
	unsigned int nrVoucher;
	char* numeBeneficiar;
	char* dataExpirare;
	float valoare;
}voucher;

typedef struct {
	voucher info;
	struct nodld* prev, * next;
}nodld;

nodld* inserareNod(nodld* cap, nodld** coada, voucher v)
{
	nodld* nou = (nodld*)malloc(sizeof(nodld));
	nou->info.nrVoucher = v.nrVoucher;
	nou->info.numeBeneficiar = (char*)malloc((strlen(v.numeBeneficiar) + 1) * sizeof(char));
	strcpy(nou->info.numeBeneficiar, v.numeBeneficiar);
	nou->info.dataExpirare = (char*)malloc((strlen(v.dataExpirare) + 1) * sizeof(char));
	strcpy(nou->info.dataExpirare, v.dataExpirare);
	nou->info.valoare = v.valoare;
	nou->next = NULL;
	nou->prev = NULL;
	
	if (cap == NULL)
	{
		cap = nou;
		nou->next = cap;
		nou->prev = cap;
		(*coada) = nou;
	}
	else
	{
		nodld* temp = cap;
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

void traversare(nodld* cap)
{
	nodld* temp = cap;
	while (temp->next != cap)
	{
		printf("\nNumar Voucher = %d, Nume Beneficiar = %s, Data Expirare = %s, Valoare = %5.2f", 
			temp->info.nrVoucher, temp->info.numeBeneficiar, temp->info.dataExpirare, temp->info.valoare);
		temp = temp->next;
	}
	printf("\nNumar Voucher = %d, Nume Beneficiar = %s, Data Expirare = %s, Valoare = %5.2f",
		temp->info.nrVoucher, temp->info.numeBeneficiar, temp->info.dataExpirare, temp->info.valoare);
}

void traversareInversa(nodld* coada)
{
	nodld* temp = coada;
	while (temp->prev != coada)
	{
		printf("\nNumar Voucher = %d, Nume Beneficiar = %s, Data Expirare = %s, Valoare = %5.2f",
			temp->info.nrVoucher, temp->info.numeBeneficiar, temp->info.dataExpirare, temp->info.valoare);
		temp = temp->prev;
	}
	printf("\nNumar Voucher = %d, Nume Beneficiar = %s, Data Expirare = %s, Valoare = %5.2f",
		temp->info.nrVoucher, temp->info.numeBeneficiar, temp->info.dataExpirare, temp->info.valoare);

}

void valoareVoucher(nodld* cap, char luna[])
{
	
	if (cap == NULL)
		printf("NU exista inregistrari");
	else
	{
		nodld* temp = cap;
		while (temp != cap)
		{
			if (luna[0] == temp->info.dataExpirare[3] && luna[1] == temp->info.dataExpirare[4])
			{
				printf("\nNumarul voucherului %d: %5.2f", temp->info.nrVoucher, temp->info.valoare);
			}
			temp = temp->next;
		}
		if (luna[0] == temp->info.dataExpirare[3] && luna[1] == temp->info.dataExpirare[4])
		{
			printf("\nNumarul voucherului %d: %5.2", temp->info.nrVoucher, temp->info.valoare);
		}
	}
}

void beneficiariVector(nodld* cap, beneficiar** vect, int* nr)
{
	if (cap != NULL)
	{
		(*nr) = 0;
		nodld* temp = cap;
		while (temp->next != cap)
		{
			int ok = 0;
			for (int i = 0; i < (*nr) && ok==0; i++)
				if (strcmp(vect[i]->nume, temp->info.numeBeneficiar) == 1) ok = 1;
			if (ok == 0)
			{
				vect[*nr]->nume = (char*)malloc((strlen(temp->info.numeBeneficiar) + 1) * sizeof(char));
				strcpy(vect[*nr]->nume, temp->info.numeBeneficiar);
				vect[*nr]->aparitii = 0;
				(*nr)++;
			}
			temp = temp->next;
		}
		int ok = 0;
		for (int i = 0; i < (*nr) && ok == 0; i++)
			if (strcmp(vect[i]->nume, temp->info.numeBeneficiar) == 1) ok = 1;
		if (ok == 0)
		{
			vect[*nr]->nume = (char*)malloc((strlen(temp->info.numeBeneficiar) + 1) * sizeof(char));
			strcpy(vect[*nr]->nume, temp->info.numeBeneficiar);
			vect[*nr]->aparitii = 0;
		}
	}
}

void nrAparitii(nodld* cap, beneficiar** vect, int nr)
{
	if (cap != NULL)
	{
		nodld* temp = cap;
		while (temp->next != cap)
		{
			for (int i = 0; i < nr; i++)
				if (strcmp(vect[i]->nume, temp->info.numeBeneficiar)) vect[i]->aparitii++;
			temp = temp->next;
		}
		for (int i = 0; i < nr; i++)
			if (strcmp(vect[i]->nume, temp->info.numeBeneficiar)) vect[i]->aparitii++;
	}
}

void conversieVector(nodld* cap, voucher** var, int* nr, float prag)
{
	if (cap != NULL)
	{
		(*nr) = 0;
		nodld* temp = cap;
		while (temp->next!=cap)
		{
			if (temp->info.valoare > prag)
			{
				var[*nr]->nrVoucher = temp->info.nrVoucher;
				var[*nr]->numeBeneficiar = (char*)malloc((strlen(temp->info.numeBeneficiar) + 1) * sizeof(char));
				strcpy(var[*nr]->numeBeneficiar, temp->info.numeBeneficiar);
				var[*nr]->dataExpirare = (char*)malloc((strlen(temp->info.dataExpirare) + 1) * sizeof(char));
				strcpy(var[*nr]->dataExpirare, temp->info.dataExpirare);
				var[*nr]->valoare = temp->info.valoare;
				(*nr)++;
			}
			temp = temp->next;
		}
		if (temp->info.valoare > prag)
		{
			var[*nr]->nrVoucher = temp->info.nrVoucher;
			var[*nr]->numeBeneficiar = (char*)malloc((strlen(temp->info.numeBeneficiar) + 1) * sizeof(char));
			strcpy(var[*nr]->numeBeneficiar, temp->info.numeBeneficiar);
			var[*nr]->dataExpirare = (char*)malloc((strlen(temp->info.dataExpirare) + 1) * sizeof(char));
			strcpy(var[*nr]->dataExpirare, temp->info.dataExpirare);
			var[*nr]->valoare = temp->info.valoare;
			(*nr)++;
		}
	}
}

void ordonareVector(voucher** v, int nr)
{
	for(int i=0;i<nr-1;i++)
		for(int j=i+1;j<nr;j++)
			if (v[j]->valoare > v[j + 1]->valoare)
			{
				voucher* temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
}

void dezalocareLista(nodld* cap)
{
	if (cap != NULL)
	{
		nodld* temp = cap;
		while (temp->next != cap)
		{
			nodld* temp2 = temp->next;
			free(temp->info.numeBeneficiar);
			free(temp->info.dataExpirare);
			free(temp);
			temp = temp2;
		}
		free(temp->info.numeBeneficiar);
		free(temp->info.dataExpirare);
		free(temp);
	}
}
void dezalocareVectorVoucher(voucher* v, int nr)
{
	for (int i = 0; i < nr; i++)
	{
		free(v[i].numeBeneficiar);
		free(v[i].dataExpirare);
	}
	free(v);
}

void dezalocareVectorAparitii(voucher* v, int nr)
{
	for (int i = 0; i < nr; i++)
		free(v[i].numeBeneficiar);
	free(v);
}
void main()
{
	FILE* f = fopen("fisier.txt", "r");
	int n;
	fscanf(f, "%d", &n);
	char buffer1[30];
	char buffer2[30];
	voucher v;
	nodld* cap = NULL;
	nodld* coada = NULL;
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &v.nrVoucher);
		fscanf(f, "%s", buffer1);
		v.numeBeneficiar = (char*)malloc((strlen(buffer1) + 1) * sizeof(char));
		strcpy(v.numeBeneficiar, buffer1);
		fscanf(f, "%s", buffer2);
		v.dataExpirare = (char*)malloc((strlen(buffer2) + 1) * sizeof(char));
		strcpy(v.dataExpirare, buffer2);
		fscanf(f, "%f", &v.valoare);

		cap = inserareNod(cap, &coada, v);

	}
	fclose(f);

	traversare(cap);

	printf("\n\n---------------------\n\n");

	traversareInversa(coada);
	char buffer[4];
	//char* luna = (char*)malloc((strlen(buffer)+1) * sizeof(char));
	printf("\n\n---------------------\n\n");
	printf("Luna = ");
	scanf("%s", buffer);
	//strcpy(luna, buffer);
	valoareVoucher(cap, buffer);
	
}