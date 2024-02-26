#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int cod;
	char* titlu;
	float pret;
}carte;

typedef struct
{
	struct nodStiva* next;
	carte info;
}nodStiva;

typedef struct {
	struct nodLista* next;
	carte info;
}nodLista;

void push(nodStiva** varf, carte c)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->info.cod = c.cod;
	nou->info.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->info.titlu, c.titlu);
	nou->info.pret = c.pret;
	nou->next = NULL;
	if (*varf == NULL)
	{
		*varf = nou;
	}
	else {
		nou->next = *varf;
		*varf = nou;
	}
}

//carte pop(nodStiva** varf)
//{
//	carte carte;
//	if (*varf != NULL)
//	{
//		carte = (*varf)->info;
//		nodStiva* temp = *varf;
//		*varf = (*varf)->next;
//		free(temp);
//	}
//	else {
//		carte.cod = -1;
//		carte.titlu = "";
//		carte.pret = 0;
//	}
//	return carte;
//}

int pop(nodStiva** varf, carte* val)
{
	if (*varf == NULL)
		return -1;
	else {
		(*val).cod = (*varf)->info.cod;
		(*val).titlu = (char*)malloc((strlen((*varf)->info.titlu) + 1) * sizeof(char));
		strcpy((*val).titlu,(*varf)->info.titlu);
		(*val).pret = (*varf)->info.pret;
		nodStiva* temp = *varf;
		(*varf) = (*varf)->next;
		free((temp)->info.titlu);
		free(temp);
		return 0;
	}
}

nodLista* inserareNod(nodLista* cap, carte c)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->info.cod = c.cod;
	nou->info.titlu = (char*)malloc((strlen(c.titlu) + 1) * sizeof(char));
	strcpy(nou->info.titlu, c.titlu);
	nou->info.pret = c.pret;
	nou->next = NULL;
	if (cap == NULL)
		cap = nou;
	else {
		nodLista* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		cap = temp;
	}
}

void traversareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		printf("\nCod = %d, Titlu = %s, Pret = %5.2f", temp->info.cod, temp->info.titlu, temp->info.pret);
		temp = temp->next;
	}
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

void conversieStivaListaSimpla(nodLista** cap, nodStiva** varf)
{
	carte val;
	while (pop(varf, &val) == 0)
	{
		inserareNod(cap, val);
	}
}

void traversare(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp)
	{
		printf("\nCod = %d, Titlu = %s, Pret = %5.2f", temp->info.cod, temp->info.titlu, temp->info.pret);
		temp = temp->next;
	}
}


//void dezalocare(nodStiva** varf)
//{
//	nodStiva* temp = *varf;
//	while (temp)
//	{
//		nodStiva* temp2 = temp->next;
//		free(temp->info.titlu);
//		free(temp);
//		temp = temp2;
//	}
//	free(temp);
//}



void main()
{
	FILE* f = fopen("fisier.txt", "r");
	int n;
	char buffer[30];
	nodStiva* varf = NULL;
	carte c;
	fscanf(f, "%d", &n);
	for (int i = 0; i < n; i++)
	{
		
		fscanf(f,"%d", &c.cod);
		fscanf(f," %s", buffer);
		c.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(c.titlu, buffer);
		fscanf(f,"%f", &c.pret);
		push(&varf, c);
	}

	traversare(varf);
	carte val;
	printf("\n\n--------------------------\n");
	//val = pop(&varf);
	pop(&varf, &val);
	printf("Cartea cu id-ul %d a fost extrasa!", val.cod);
	
	printf("\n\n--------------------------\n");

	traversare(varf);

	printf("\n\n--------------------------\n");
	printf("Conversia in Lista: \n\n");
	nodLista* cap = NULL;
	conversieStivaListaSimpla(&cap, &varf);
	traversareLista(cap);

	dezalocareLista(cap);

}