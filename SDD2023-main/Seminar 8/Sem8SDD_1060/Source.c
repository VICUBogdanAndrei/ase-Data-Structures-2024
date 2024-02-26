#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int cod;
	char* denumire;
	float pret;
} produs;

typedef struct
{
	produs inf;
	struct nodArb* left, *right;
} nodArb;

nodArb* creareNod(produs p, nodArb* st, nodArb* dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.cod = p.cod;
	nou->inf.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, p.denumire);
	nou->inf.pret = p.pret;
	nou->left = st;
	nou->right = dr;
	return nou;
}

nodArb* inserareNod(nodArb* rad, produs p)
{
	if (rad != NULL)
	{
		if (p.cod < rad->inf.cod)
		{
			rad->left = inserareNod(rad->left, p);
			return rad;
		}
		else
			if (p.cod > rad->inf.cod)
			{
				rad->right = inserareNod(rad->right, p);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(p, NULL, NULL);
}

void preordine(nodArb* rad) //R S D
{
	if (rad != NULL)
	{
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f",
			rad->inf.cod, rad->inf.denumire, rad->inf.pret);
		preordine(rad->left);
		preordine(rad->right);
	}
}

void inordine(nodArb* rad) //S R D
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f",
			rad->inf.cod, rad->inf.denumire, rad->inf.pret);
		inordine(rad->right);
	}
}

void postordine(nodArb* rad) //S D R
{
	if (rad != NULL)
	{
		postordine(rad->left);
		postordine(rad->right);
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f",
			rad->inf.cod, rad->inf.denumire, rad->inf.pret);
	}
}

void dezalocare(nodArb *rad)
{
	/*if (rad != NULL)
	{
		nodArb* stanga = rad->left;
		nodArb* dreapta = rad->right;
		free(rad->inf.denumire);
		free(rad);
		dezalocare(stanga);
		dezalocare(dreapta);
	}*/
	if (rad != NULL)
	{
		free(rad->inf.denumire);
		dezalocare(rad->left);
		dezalocare(rad->right);
		free(rad);
	}
}

void numarareNoduriFrunza(nodArb* rad, int* nr)
{
	if (rad != NULL)
	{
		if (rad->left == NULL && rad->right == NULL)
			(*nr)++;
		numarareNoduriFrunza(rad->left, nr);
		numarareNoduriFrunza(rad->right, nr);
	}
}

void salvareVector(nodArb* rad, produs* vect, int* nr, float prag)
{
	if (rad != NULL)
	{
		if (rad->inf.pret >= prag)
		{
			vect[*nr] = rad->inf;
			(*nr)++;
		}
		salvareVector(rad->left, vect, nr, prag);
		salvareVector(rad->right, vect, nr, prag);
	}
}

nodArb* cautare(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (rad->inf.cod == cheie)
			return rad;
		else
			if (cheie < rad->inf.cod)
				return cautare(rad->left, cheie);
			else
				return cautare(rad->right, cheie);
	}
	else 
		return NULL;
}

void main()
{
	int nrProd;
	produs p;
	char buffer[20];
	nodArb* rad = NULL;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrProd);
	for (int i = 0; i < nrProd; i++)
	{
		fscanf(f, "%d", &p.cod);
		fscanf(f, "%s", buffer);
		p.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.denumire, buffer);
		fscanf(f, "%f", &p.pret);
		rad = inserareNod(rad, p);
		free(p.denumire);
	}
	fclose(f);

	printf("\n------------preordine------------\n");
	preordine(rad);
	printf("\n------------inordine------------\n");
	inordine(rad);
	printf("\n------------postordine------------\n");
	postordine(rad);

	int numarFrunze = 0;
	numarareNoduriFrunza(rad, &numarFrunze);
	printf("\nNumar noduri frunza: %d", numarFrunze);

	nodArb* nodCautat = cautare(rad, 35);
	if (nodCautat != NULL)
		printf("\nNodul cautat are denumirea: %s", nodCautat->inf.denumire);
	else
		printf("\nNu exista cheia cautata!");

	int nr = 0;
	produs* vect = (produs*)malloc(nrProd * sizeof(produs));
	salvareVector(rad, vect, &nr, 7);
	for (int i = 0; i < nr; i++)
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f",
			vect[i].cod, vect[i].denumire, vect[i].pret);
	free(vect);

	dezalocare(rad);
}