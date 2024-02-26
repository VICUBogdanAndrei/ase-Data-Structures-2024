#include<stdio.h>
#include<malloc.h>

typedef struct
{
	int codCurs;
	char* denumire;
	int nrCredite;
} curs;

typedef struct
{
	curs inf;
	struct nodArb* left, *right;
} nodArb;

typedef struct
{
	curs inf;
	struct nodLista* next;
} nodLista;

nodArb* creareNod(curs c, nodArb *st, nodArb *dr)
{
	nodArb* nou = (nodArb*)malloc(sizeof(nodArb));
	nou->inf.codCurs = c.codCurs;
	nou->inf.denumire = (char*)malloc((strlen(c.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, c.denumire);
	nou->inf.nrCredite = c.nrCredite;
	nou->left = st;
	nou->right = dr;
	return nou;
}

nodArb* inserareNod(nodArb* rad, curs c)
{
	if (rad != NULL)
	{
		if (c.codCurs < rad->inf.codCurs)
		{
			rad->left = inserareNod(rad->left, c);
			return rad;
		}
		else
			if (c.codCurs > rad->inf.codCurs)
			{
				rad->right = inserareNod(rad->right, c);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(c, NULL, NULL);
}

//RSD
void preordine(nodArb* rad)
{
	if (rad != NULL)
	{
		printf("\nCod curs=%d, Denumire = %s, Nr. credite = %d",
			rad->inf.codCurs, rad->inf.denumire, rad->inf.nrCredite);
		preordine(rad->left);
		preordine(rad->right);
	}
}

//SRD
void inordine(nodArb* rad)
{
	if (rad != NULL)
	{
		inordine(rad->left);
		printf("\nCod curs=%d, Denumire = %s, Nr. credite = %d",
			rad->inf.codCurs, rad->inf.denumire, rad->inf.nrCredite);
		inordine(rad->right);
	}
}

//SDR
void postordine(nodArb* rad)
{
	if (rad != NULL)
	{
		postordine(rad->left);
		postordine(rad->right);
		printf("\nCod curs=%d, Denumire = %s, Nr. credite = %d",
			rad->inf.codCurs, rad->inf.denumire, rad->inf.nrCredite);
	}
}

void dezalocare(nodArb* rad)
{
	/*if (rad != NULL)
	{
		dezalocare(rad->left);
		dezalocare(rad->right);
		free(rad->inf.denumire);
		free(rad);
	}*/
	if (rad != NULL)
	{
		nodArb* st = rad->left;
		nodArb* dr = rad->right;
		free(rad->inf.denumire);
		free(rad);
		dezalocare(st);
		dezalocare(dr);
	}
}

void cateNoduriFrunzaSunt(nodArb* rad, int* nr)
{
	if (rad != NULL)
	{
		//prelucrare
		if (rad->left == NULL && rad->right == NULL)
			(*nr)++;
		cateNoduriFrunzaSunt(rad->left, nr);
		cateNoduriFrunzaSunt(rad->right, nr);
	}
}

void cursuriNrCredite(nodArb* rad, curs* vect, int* nr, int prag)
{
	if (rad != NULL)
	{
		if (rad->inf.nrCredite >= prag)
		{
			vect[*nr] = rad->inf;
			(*nr)++;
		}
		cursuriNrCredite(rad->left, vect, nr, prag);
		cursuriNrCredite(rad->right, vect, nr, prag);
	}
}

nodArb* cautare(nodArb* rad, int cheie)
{
	if (rad != NULL)
	{
		if (cheie == rad->inf.codCurs)
			return rad;
		else
			if (cheie < rad->inf.codCurs)
				return cautare(rad->left, cheie);
			else
				return cautare(rad->right, cheie);
	}
	else
		return NULL;
}

nodLista* inserareNodLista(nodLista* cap, curs c)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->inf.codCurs = c.codCurs;
	nou->inf.denumire = (char*)malloc((strlen(c.denumire) + 1) * sizeof(char));
	strcpy(nou->inf.denumire, c.denumire);
	nou->inf.nrCredite = c.nrCredite;
	nou->next = NULL;
	if (cap == NULL)
		cap = nou;
	else
	{
		nodLista* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

void traversareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		printf("\nCod curs=%d, Denumire = %s, Nr. credite = %d",
			temp->inf.codCurs, temp->inf.denumire, temp->inf.nrCredite);
		temp = temp->next;
	}
}

void dezalocareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		nodLista* temp2 = temp->next;
		free(temp->inf.denumire);
		free(temp);
		temp = temp2;
	}
}

void salvareListaNrCredite(nodArb* rad, nodLista** cap, int prag)
{
	if (rad != NULL)
	{
		if (rad->inf.nrCredite >= prag)
			*cap = inserareNodLista(*cap, rad->inf);
		salvareListaNrCredite(rad->left, cap, prag);
		salvareListaNrCredite(rad->right, cap, prag);
	}
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
		return 1 + maxim(inaltimeArbore(rad->left),
			inaltimeArbore(rad->right));
	else
		return 0;
}

void main()
{
	nodArb* rad = NULL;
	curs c;
	char buffer[20];
	int nrCursuri;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &nrCursuri);
	for (int i = 0; i < nrCursuri; i++)
	{
		fscanf(f, "%d", &c.codCurs);
		fscanf(f, "%s", buffer);
		c.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.denumire, buffer);
		fscanf(f, "%d", &c.nrCredite);
		rad = inserareNod(rad, c);
		free(c.denumire);
	}
	fclose(f);

	printf("\n----------------preordine-----------\n");
	preordine(rad);
	printf("\n----------------inordine-----------\n");
	inordine(rad);
	printf("\n----------------postordine-----------\n");
	postordine(rad);

	int numarFrunze = 0;
	cateNoduriFrunzaSunt(rad, &numarFrunze);
	printf("\nArborele are %d frunze", numarFrunze);

	int nr = 0;
	curs* vect = (curs*)malloc(nrCursuri * sizeof(curs));
	cursuriNrCredite(rad, vect, &nr, 4);
	for (int i = 0; i < nr; i++)
		printf("\nCod curs=%d, Denumire = %s, Nr. credite = %d",
			vect[i].codCurs, vect[i].denumire, vect[i].nrCredite);
	free(vect);

	nodArb* nodCautat = cautare(rad, 20);
	if (nodCautat != NULL)
		printf("\nCursul cautat se numeste %s", nodCautat->inf.denumire);
	else
		printf("\nCursul cautat nu exista!");

	printf("\n-----------Lista------------\n");
	nodLista* cap = NULL;
	salvareListaNrCredite(rad, &cap, 4);
	traversareLista(cap);
	dezalocareLista(cap);

	printf("\nInaltime arbore: %d", inaltimeArbore(rad));
	printf("\nInaltime subarbore stang: %d", inaltimeArbore(rad->left));
	printf("\nInaltime subarbore drept: %d", inaltimeArbore(rad->right));

	dezalocare(rad);
}
