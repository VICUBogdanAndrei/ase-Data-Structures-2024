#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>


typedef struct {
	unsigned int id;
	char* denumire;
	unsigned char numarCamereRezervate;
	char* numeClient;
	float sumaPlata;
}rezervare;

typedef struct {
	rezervare info;
	struct nodls* next;
}nodls;

typedef struct {
	rezervare info;
	struct nodarb* left, * right;
}nodarb;

nodarb* creare(nodarb* stanga, nodarb* dreapta, rezervare r)
{
	nodarb* nou = (nodarb*)malloc(sizeof(nodarb));
	nou->info.id = r.id;
	nou->info.denumire = (char*)malloc((strlen(r.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, r.denumire);
	nou->info.numarCamereRezervate = r.numarCamereRezervate;
	nou->info.numeClient = (char*)malloc((strlen(r.numeClient) + 1) * sizeof(char));
	strcpy(nou->info.numeClient, r.numeClient);
	nou->info.sumaPlata = r.sumaPlata;
	nou->left = stanga;
	nou->right = dreapta;
}

nodarb* inserareRecursiv(nodarb* rad, rezervare r)
{
	if (rad != NULL)
	{
		if (r.id < rad->info.id)
		{
			rad->left = inserareRecursiv(rad->left, r);
			return rad;
		}
		else
			if (r.id > rad->info.id)
			{
				rad->right = inserareRecursiv(rad->right, r);
				return rad;
			}
			else return rad;
	}
	else
		return creare(NULL, NULL, r);
}

void preordine(nodarb* rad)
{
	if (rad != NULL)
	{
		printf("\nID = %d, Denumire Hotel = %s, Numar Camere rezervare = %d, Nume CLient = %s, Suma de plata = %5.2f", rad->info.id, rad->info.denumire, rad->info.numarCamereRezervate, rad->info.numeClient, rad->info.sumaPlata);
		preordine(rad->left);
		preordine(rad->right);
	}
}

void inordine(nodarb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nID = %d, Denumire Hotel = %s, Numar Camere rezervare = %d, Nume CLient = %s, Suma de plata = %5.2f", rad->info.id, rad->info.denumire, rad->info.numarCamereRezervate, rad->info.numeClient, rad->info.sumaPlata);
		inordine(rad->right);
	}
}

void postordine(nodarb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->left);
		postordine(rad->right);
		printf("\nID = %d, Denumire Hotel = %s, Numar Camere rezervare = %d, Nume CLient = %s, Suma de plata = %5.2f", rad->info.id, rad->info.denumire, rad->info.numarCamereRezervate, rad->info.numeClient, rad->info.sumaPlata);
	}
}

nodarb* cautare(nodarb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie == rad->info.id)
			return rad;
		else
			if (cheie < rad->info.id)
				return cautare(rad->left, cheie);
			else
				if (cheie > rad->info.id)
					return cautare(rad->right, cheie);
	}
	else
		return NULL;
}

void dezalocare(nodarb* rad)
{
	if (rad != NULL)
	{
		nodarb* st = rad->left;
		nodarb* dr = rad->right;
		free(rad->info.denumire);
		free(rad->info.numeClient);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

void main()
{
	FILE* f = fopen("fisier.txt", "r");
	int n;
	fscanf(f, "%d", &n);
	rezervare r;
	char buffer[30];
	nodarb* rad = NULL;
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &r.id);
		fscanf(f, "%s", buffer);
		r.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(r.denumire, buffer);
		fscanf(f, "%d", &r.numarCamereRezervate);
		fscanf(f, "%s", buffer);
		r.numeClient = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(r.numeClient, buffer);
		fscanf(f, "%f", &r.sumaPlata);
		rad = inserareRecursiv(rad, r);
	}
	fclose(f);
	preordine(rad);
	printf("\n\n------------------\n\n");

	inordine(rad);
	printf("\n\n------------------\n\n");

	postordine(rad);
	printf("\n\n------------------\n\n");

}
