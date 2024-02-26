#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<malloc.h>
#include <string.h>

//arbore binar


typedef struct
{
	int cod;
	char* nume;
	float medie;
} student;

typedef struct
{
	student info;
	struct nodarb* left, * right;
} nodarb;


nodarb* creare(student s, nodarb* stanga, nodarb* dreapta)
{
	nodarb* nou = (nodarb*)malloc(sizeof(nodarb));
	nou->info.cod = s.cod;
	nou->info.nume = (char*)malloc((strlen(s.nume) + 1) * sizeof(char));
	strcpy(nou->info.nume, s.nume);
	nou->info.medie = s.medie;
	nou->left = stanga;
	nou->right = dreapta;
	return nou;
}

nodarb* inserareRecursiv(student s, nodarb* rad)
{
	if (rad != NULL)
	{
		if (s.cod < rad->info.cod)
		{
			rad->left = inserareRecursiv(s, rad->left);
			return rad;
		}
		else
			if (s.cod > rad->info.cod)
			{
				rad->right = inserareRecursiv(s, rad->right);
				return rad;
			}
			else return rad;
	}
	else
		return creare(s, NULL, NULL);
}

//parcurgeri arbore binar

//PREORDINE - RSD
void preordine(nodarb* rad)
{
	if (rad != NULL)
	{
		printf("\n Cod = %d, Nume = %s, Medie = %5.2f", rad->info.cod, rad->info.nume, rad->info.medie);
		preordine(rad->left);
		preordine(rad->right);
	}
}

//INORDINE - SRD
void inordine(nodarb* rad)
{
	if(rad!=NULL)
	{ 
		inordine(rad->left);
		printf("\n Cod = %d, Nume = %s, Medie = %5.2f", rad->info.cod, rad->info.nume, rad->info.medie);
		inordine(rad->right);
	}
}

//POSTORDINE - SDR
void postordine(nodarb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->left);
		postordine(rad->right);
		printf("\n Cod = %d, Nume = %s, Medie = %5.2f", rad->info.cod, rad->info.nume, rad->info.medie);
	}
}

void dezalocare(nodarb* rad)
{
	if (rad != NULL)
	{
		nodarb* st = rad->left;
		nodarb* dr = rad->right;
		free(rad->info.nume);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

nodarb* cautare(nodarb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie == rad->info.cod)
			return rad;
		else
			if (cheie < rad->info.cod)
				return cautare(rad->left, cheie);
			else
				if (cheie > rad->info.cod)
					return cautare(rad->right, cheie);
	}
	else
		return NULL;
}

int maxim(int a, int b)
{
	int max=a;
	if (max < b)
		max = b;
	return max;
}

int nrNiveluri(nodarb* rad)
{
	if (rad != NULL)
	{
		int stanga = nrNiveluri(rad->left);
		int dreapta = nrNiveluri(rad->right);
		return 1 + maxim(stanga, dreapta);
	}
	else
		return 0;

}

void salvareNoduriFrunzaVector(nodarb* rad, student* vect, int* nr)
{
	if (rad != NULL)
	{
		if (rad->left == NULL && rad->right == NULL)
		{
			vect[*nr].cod = rad->info.cod;
			vect[*nr].nume = (char*)malloc((strlen(rad->info.nume) + 1) * sizeof(char));
			strcpy(vect[*nr].nume, rad->info.nume);
			vect[*nr].medie = rad->info.medie;
			(*nr)++;
		}
		salvareNoduriFrunzaVector(rad->left, vect, nr);
		salvareNoduriFrunzaVector(rad->right, vect, nr);
	}
}

void conversieArboreVector(nodarb* rad, student* vect, int* nr)
{
	if (rad != NULL)
	{
		vect[*nr].cod = rad->info.cod;
		vect[*nr].nume = (char*)malloc((strlen(rad->info.nume) + 1) * sizeof(char));
		strcpy(vect[*nr].nume, rad->info.nume);
		vect[*nr].medie = rad->info.medie;
		(*nr)++;

		conversieArboreVector(rad->left, vect, nr);
		conversieArboreVector(rad->right, vect, nr);
	}
}
nodarb* stergereRad(nodarb* rad)
{
	nodarb* aux = rad;
	if (aux->left != NULL)
	{
		rad = aux->left;
		if (aux->right != NULL)
		{
			nodarb* temp = aux->left;
			while (temp->right)
				temp = temp->right;
			temp->right = aux->right;
		}
	}
	else
		if (aux->right != NULL)
			rad = aux->right;
		else
			rad = NULL;
	free(aux->info.nume);
	free(aux);
	return rad;
}

nodarb* stergereNod(nodarb* rad, int cheie)
{
	if (rad == NULL)
		return NULL;
	else
		if (rad->info.cod == cheie)
		{
			rad = stergereRad(rad);
			return rad;
		}
		else
			if (cheie < rad->info.cod)
			{
				rad = stergereNod(rad->left, cheie);
				return rad;
			}
			else
			{
				rad = stergereNod(rad->right, cheie);
				return rad;
			}
}


void main()
{
	FILE* f = fopen("fisier.txt", "r");
	int n;
	fscanf(f, "%d", &n);
	nodarb* rad = NULL;
	student s;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &s.cod);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(s.nume, buffer);
		fscanf(f, "%f", &s.medie);
		rad = inserareRecursiv(s, rad);
	}

	fclose(f);

	printf("PREORDINE:");
	preordine(rad);
	printf("\n--------------------\n");
	inordine(rad);
	printf("\n--------------------\n");
	postordine(rad);

}