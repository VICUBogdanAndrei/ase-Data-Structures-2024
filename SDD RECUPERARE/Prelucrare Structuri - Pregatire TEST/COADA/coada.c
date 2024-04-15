#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<malloc.h>


typedef struct {
	int idProdus;
	char* numeProdus;
	float pret;
}produs;


typedef struct
{
	produs info;
	struct nodCoada* next;
}nodCoada;

typedef struct
{
	produs info;
	struct nodStiva* next;
}nodStiva;

void put(nodCoada** prim, nodCoada** ultim, produs p)
{
	nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));

	nou->info.idProdus = p.idProdus;
	nou->info.numeProdus = (char*)malloc((strlen(p.numeProdus) + 1) * sizeof(char));
	strcpy(nou->info.numeProdus, p.numeProdus);
	nou->info.pret = p.pret;

	nou->next = NULL;

	if (*prim == NULL || *ultim==NULL)
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

int get(nodCoada** prim, nodCoada** ultim, produs* val)
{
	if (*prim != NULL && *ultim != NULL)
	{
		(*val).idProdus = (*prim)->info.idProdus;
		(*val).numeProdus = (char*)malloc((strlen((*prim)->info.numeProdus) + 1) * sizeof(char));
		strcpy((*val).numeProdus, (*prim)->info.numeProdus);
		(*val).pret = (*prim)->info.pret;

		nodCoada* aux = *prim;
		*prim = (*prim)->next;
		free(aux->info.numeProdus);
		free(aux);

		return 0;
	}
}

void traversareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp != NULL)
	{
		printf("\nId Produs = %d, Nume Produs = %s, Pret = %5.2f",
			temp->info.idProdus, temp->info.numeProdus, temp->info.pret);
		temp = temp->next;
	}
}

void push(nodStiva** varf, produs p)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));

	nou->info.idProdus = p.idProdus;
	nou->info.numeProdus = (char*)malloc((strlen(p.numeProdus) + 1) * sizeof(char));
	strcpy(nou->info.numeProdus, p.numeProdus);
	nou->info.pret = p.pret;

	nou->next = NULL;

	if (*varf==NULL)
	{
		*varf = nou;
	}
	else
	{
		nou->next = *varf;
		(*varf) = nou;
	}
}

int pop(nodStiva** varf, produs* val)
{
	if (*varf!=NULL)
	{
		(*val).idProdus = (*varf)->info.idProdus;
		(*val).numeProdus = (char*)malloc((strlen((*varf)->info.numeProdus) + 1) * sizeof(char));
		strcpy((*val).numeProdus, (*varf)->info.numeProdus);
		(*val).pret = (*varf)->info.pret;

		nodCoada* aux = *varf;
		*varf = (*varf)->next;
		free(aux->info.numeProdus);
		free(aux);

		return 0;
	}
}

traversareStiva(nodStiva* varf)
{
	nodStiva* temp = varf;
	while (temp != NULL)
	{
		printf("\nId Produs = %d, Nume Produs = %s, Pret = %5.2f",
			temp->info.idProdus, temp->info.numeProdus, temp->info.pret);
		temp = temp->next;
	}
}

void main()
{
	produs p;
	nodCoada* prim= NULL, * ultim = NULL;
	nodCoada* prim2 = NULL, * ultim2 = NULL;
	nodStiva* varf = NULL, *varf2=NULL;
	int nrElem = 0;
	char buffer1[30];
	unsigned char buffer2;

	FILE* f = fopen("produse_coada.txt", "r");
	fscanf(f, "%d", &nrElem);
	for (int i = 0; i < nrElem; i++)
	{
		fscanf(f, "%d", &p.idProdus);
		fscanf(f, "%s", buffer1);
		p.numeProdus = (char*)malloc((strlen(buffer1) + 1) * sizeof(char));
		strcpy(p.numeProdus, buffer1);
		fscanf(f, "%f", &p.pret);

		put(&prim, &ultim, p);
		put(&prim2, &ultim2, p);
		push(&varf, p);
		free(p.numeProdus);
	}

	printf("\n\n----TRAVERSARE COADA----\n\n");
	traversareCoada(prim);

	printf("\n\n----TRANSFORMARE DIN COADA IN STIVA----");

	//e facuta si dezalocarea pentru coada
	while(get(&prim2,&ultim2,&p)==0)
	{
		push(&varf2, p);

	}

	printf("\n\n----TRAVERSARE STIVA FACUTA DIN COADA----");
	traversareStiva(varf2);

	printf("\n\n\tAFISARE STIVA LA DEZALOCARE:\n");
	//dezalocare stiva
	while (pop(&varf2, &p) == 0)
	{
		
		printf("\nId Produs = %d, Nume Produs = %s, Pret = %5.2f",
			p.idProdus, p.numeProdus, p.pret);
		free(p.numeProdus);
	}

	printf("\n\n\tAFISARE COADA LA DEZALOCARE:\n");
	//dezalocare coada
	while (get(&prim, &ultim, &p) == 0)
	{
		
		printf("\nId Produs = %d, Nume Produs = %s, Pret = %5.2f",
			p.idProdus, p.numeProdus, p.pret);
		free(p.numeProdus);
	}

	printf("\n\n----TRAVERSARE STIVA----\n\n");
	traversareStiva(varf);

	printf("\n\n\tAFISARE STIVA LA DEZALOCARE:\n");
	//dezalocare stiva
	while (pop(&varf, &p) == 0)
	{
		
		printf("\nId Produs = %d, Nume Produs = %s, Pret = %5.2f",
			p.idProdus, p.numeProdus, p.pret);
		free(p.numeProdus);
	}



	fclose(f);
}

