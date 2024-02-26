#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>


typedef struct {
	int cod;
	char* titlu;
	float pret;
}carte;

typedef struct
{
	struct nodCoada* next;
	carte info;
}nodCoada;

typedef struct
{
	carte info;
	struct nodLista* next;
}nodLista;

nodLista* inserareNod(nodLista* cap, carte c)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->info.cod = c.cod;
	nou->info.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->info.titlu, c.titlu);
	nou->info.pret = c.pret;
	nou->next = NULL;
	if (cap == NULL)
	{
		cap = nou;
	}
	else {
		nodLista* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
		cap = temp;
	}
	return cap;
}

void traversareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		printf("\nCod = %d, Titlu = %s, Pret = %5.2f", temp->info.cod, temp->info.titlu, temp->info.pret);
		temp = temp->next;
	}
	free(temp);
}

void dezalocareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		nodLista* temp2 = temp->next;
		free(temp->info.titlu);
		free(temp);
		temp = temp2;
	}
	free(temp);
}

void put(nodCoada** prim, nodCoada** ultim, carte c)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
	nou->info.cod = c.cod;
	nou->info.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->info.titlu, c.titlu);
	nou->info.pret = c.pret;
	nou->next = NULL;
	if (*prim == NULL && *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else
	{
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

//adresa la c pentru ca isi schimba valorile
int get(nodCoada** prim, nodCoada** ultim, carte* c)
{
	if (prim != NULL && ultim != NULL)
	{
		(*c).cod = (*prim)->info.cod;
		(*c).titlu = (char*)malloc(strlen(((*prim)->info.titlu) + 1) * sizeof(char));
		strcpy((*c).titlu, (*prim)->info.titlu);
		(*c).pret = (*prim)->info.pret;
		nodCoada* temp = *prim;
		(*prim) = (*prim)->next;
		free(temp->info.titlu);
		free(temp);
		return 0;
	}
	else if (prim != NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void traversare(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp)
	{
		printf("\nCod = %d, Titlu = %s, Pret = %5.2f", temp->info.cod, temp->info.titlu, temp->info.pret);
		temp = temp->next;
	}
	free(temp);
}

void conversieCoadaVector(nodCoada** prim, nodCoada** ultim, carte* vect, int* nr)
{
	carte s;
	while (get(prim, ultim, &s) == 0)
	{
		vect[*nr] = s;
		(*nr)++;
	}
}

void conversieListaSimpla(nodLista** cap, nodCoada** prim, nodCoada** ultim)
{
	carte val;
	while (get(prim, ultim, &val) == 0)
	{
		inserareNod(cap, val);
	}
}


int main()
{
	int n;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	carte c;
	char buffer[30];
	nodCoada* prim = NULL, * ultim = NULL;
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d", &c.cod);
		fscanf(f, "%s", buffer);
		c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.titlu, buffer);
		fscanf(f, "%f", &c.pret);
		put(&prim, &ultim, c);
		//free(c.titlu);
	}
	fclose(f);
	traversare(prim);

	printf("\n\n--------------------------\n\n");

	int nr=0;
	carte* vect = (carte*)malloc(n * sizeof(carte));
	//get(&prim, &ultim, &c);
	//printf("Cartea cu id-ul %d a fost extrasa!", c.cod);
	printf("\n\n--------------------------\n\n");

	//conversieCoadaVector(&prim, &ultim, vect, &nr);
	//conversieCoadaVector(&prim, &ultim, &nr, vect);
	nodLista* cap = NULL;					
	conversieListaSimpla(&cap, &prim, &ultim);
	traversareLista(cap);

	/*for (int i = 0; i < nr; i++)
	{
		printf("\nCod = %d, Titlu = %s, Pret = %5.2f", vect[i].cod, vect[i].titlu, vect[i].pret);
	}*/
}