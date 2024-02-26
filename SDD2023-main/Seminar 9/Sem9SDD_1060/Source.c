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
	int BF;
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
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, BF = %d",
			rad->inf.cod, rad->inf.denumire, rad->inf.pret, rad->BF);
		preordine(rad->left);
		preordine(rad->right);
	}
}

void inordine(nodArb* rad) //S R D
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, BF = %d",
			rad->inf.cod, rad->inf.denumire, rad->inf.pret, rad->BF);
		inordine(rad->right);
	}
}

void postordine(nodArb* rad) //S D R
{
	if (rad != NULL)
	{
		postordine(rad->left);
		postordine(rad->right);
		printf("\nCod=%d, Denumire=%s, Pret=%5.2f, BF = %d",
			rad->inf.cod, rad->inf.denumire, rad->inf.pret, rad->BF);
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

nodArb* stergeRad(nodArb* rad)
{
	nodArb* aux = rad;
	if (rad->left != NULL)
	{
		rad = aux->left;
		if (aux->right != NULL)
		{
			nodArb* max = aux->left;
			while (max->right != NULL)
				max = max->right;
			max->right = aux->right;
		}
	}
	else
		if (aux->right != NULL)
		{
			rad = aux->right;
		}
		else
			rad = NULL;
	free(aux->inf.denumire);
	free(aux);
	return rad;
}

nodArb* stergeNod(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie < rad->inf.cod)
			rad->left = stergeNod(rad->left, cheie);
		else
			if (cheie > rad->inf.cod)
				rad->right = stergeNod(rad->right, cheie);
			else
				rad = stergeRad(rad);
		return rad;
	}
	else
		return NULL;
}

int maxim(int a, int b)
{
	int max = a;
	if (max < b)
		max = b;
	return max;
}

int inaltimeArbore(nodArb* rad)
{
	if (rad != NULL)
		return 1 + maxim(inaltimeArbore(rad->left), inaltimeArbore(rad->right));
	else
		return 0;
}

void calculBF(nodArb* rad)
{
	if (rad != NULL)
	{
		rad->BF = inaltimeArbore(rad->right) - inaltimeArbore(rad->left);
		calculBF(rad->left);
		calculBF(rad->right);
	}
}

nodArb* rotatie_dreapta(nodArb* rad)
{
	printf("\nRotatie dreapta!");
	nodArb* nod1 = rad->left;
	rad->left = nod1->right;
	nod1->right = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga(nodArb* rad)
{
	printf("\nRotatie stanga!");
	nodArb* nod1 = rad->right;
	rad->right = nod1->left;
	nod1->left = rad;
	rad = nod1;
	return rad;
}

nodArb* rotatie_stanga_dreapta(nodArb* rad)
{
	printf("\nRotatie stanga-dreapta!");
	nodArb* nod1 = rad->left;
	nodArb* nod2 = nod1->right;
	nod1->right = nod2->left;
	nod2->left = nod1;
	rad->left = nod2->right;
	nod2->right = rad;
	rad = nod2;
	return rad;
}

nodArb* reechilibrare(nodArb* rad)
{
	calculBF(rad);
	nodArb* fiuSt = rad->left;
	nodArb* fiuDr = rad->right;
	if (rad->BF == -2 && fiuSt->BF == -1)
	{
		rad = rotatie_dreapta(rad);
		calculBF(rad);
	}
	else
		if (rad->BF == 2 && fiuDr->BF == 1)
		{
			rad = rotatie_stanga(rad);
			calculBF(rad);
		}
		else
			if (rad->BF == -2 && fiuSt->BF == 1)
			{
				rad = rotatie_stanga_dreapta(rad);
				calculBF(rad);
			}
	return rad;
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

		rad = reechilibrare(rad);
	}
	fclose(f);

	//calculBF(rad);

	printf("\n------------preordine------------\n");
	preordine(rad);
	printf("\n------------inordine------------\n");
	inordine(rad->left);
	printf("\n------------postordine------------\n");
	postordine(rad->right);

	//int numarFrunze = 0;
	//numarareNoduriFrunza(rad, &numarFrunze);
	//printf("\nNumar noduri frunza: %d", numarFrunze);

	//nodArb* nodCautat = cautare(rad, 35);
	//if (nodCautat != NULL)
	//	printf("\nNodul cautat are denumirea: %s", nodCautat->inf.denumire);
	//else
	//	printf("\nNu exista cheia cautata!");

	//int nr = 0;
	//produs* vect = (produs*)malloc(nrProd * sizeof(produs));
	//salvareVector(rad, vect, &nr, 7);
	//for (int i = 0; i < nr; i++)
	//	printf("\nCod=%d, Denumire=%s, Pret=%5.2f",
	//		vect[i].cod, vect[i].denumire, vect[i].pret);
	//free(vect);

	//rad = stergeRad(rad);
	////rad = stergeNod(rad, 20);
	////calculBF(rad);
	//printf("\n----------------preordine-----------\n");
	//preordine(rad);
	///*printf("\n----------------inordine-----------\n");
	//inordine(rad->left);
	//printf("\n----------------postordine-----------\n");
	//postordine(rad->right);*/

	//printf("\nInaltime arbore: %d", inaltimeArbore(rad));
	//printf("\nInaltime subarbore stang: %d", inaltimeArbore(rad->left));
	//printf("\nInaltime subarbore drept: %d", inaltimeArbore(rad->right));

	dezalocare(rad);
}