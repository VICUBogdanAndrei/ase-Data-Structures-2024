#define _CRT_SECURE_NO_WARNINGS

#include<malloc.h>
#include<stdio.h>



typedef struct
{
	int anFabricatie;
	char* marca;
	float pret;

}masina;

typedef struct
{
	masina** vect;//vector de pointer la masina
	int nrElem;
}hashT;

int functieHas(hashT tabela, char cheie[20])
{
	return cheie[0] % tabela.nrElem;
}

void inserareHash(hashT tabela, masina* m)
{
	int poz = functieHas(tabela, (*m).marca);
	if (tabela.vect[poz] == NULL)
		tabela.vect[poz] = m;
	else
	{
		int index = 1;
		while (poz + index < tabela.nrElem)
		{
			if (tabela.vect[poz + index] == NULL)
			{
				poz += index;
				tabela.vect[poz] = m;
				break;
			}
			else
				index++;
		}
	}
}

void traversareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL)
		{
			printf("\nPozitia = %d", i);
			printf("\nAn fabricatie =%d, Marca =%s, Pret=%5.2f", tabela.vect[i]->anFabricatie, tabela.vect[i]->marca, tabela.vect[i]->pret);

		}
}

void stergereHash(hashT tabela, char *denumire)
{
	int ok = 0;

	int pozitie = functieHas(tabela, denumire);

	for(int i=pozitie; i<tabela.nrElem && ok==0; i++)
		if (strcmp(tabela.vect[i]->marca, denumire) == 0)
		{
			free(tabela.vect[i]->marca);
			free(tabela.vect[i]);
			tabela.vect[i] = NULL;
			ok = 1;
		}
}

void copiereVector(hashT tabela, masina** masini, int* nr, float valMin, float valMax)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		if (tabela.vect[i] != NULL)
		{
			if (tabela.vect[i]->pret >= valMin && tabela.vect[i]->pret <= valMax)
			{
				masini[*nr] = (masina*)malloc(sizeof(masina));
				masini[*nr]->anFabricatie = tabela.vect[i]->anFabricatie;
				masini[*nr]->marca = (char*)malloc((strlen(tabela.vect[i]->marca) + 1) * sizeof(char));
				strcpy(masini[*nr]->marca, tabela.vect[i]->marca);
				masini[*nr]->pret = tabela.vect[i]->pret;
				(*nr)++;
			}
		}
	}
}

void dezalocareHash(hashT tabela)
{
	for (int i = 0; i < tabela.nrElem; i++)
		if (tabela.vect[i] != NULL)
		{
			free(tabela.vect[i]->marca);
			free(tabela.vect[i]);
		}
	free(tabela.vect);

}




void main()
{
	hashT tabela;
	tabela.nrElem = 31;
	tabela.vect = (masina*)malloc(tabela.nrElem * sizeof(masina));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	FILE* f = fopen("fisier.txt", "r");
	char buffer[20];
	masina* m;
	int nrMasini;
	fscanf(f, "%d", &nrMasini);
	for (int i = 0; i < nrMasini; i++)
	{
		m = (masina*)malloc(sizeof(masina));
		fscanf(f, "%d", &m->anFabricatie);
		fscanf(f, "%s", buffer);
		m->marca = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(m->marca, buffer);
		fscanf(f, "%f", &m->pret);

		inserareHash(tabela, m);

	}

	fclose(f);
	traversareHash(tabela);

	printf("\n---------------------\n");
	stergereHash(tabela, "Dodge");

	printf("\n---------------------\n");
	traversareHash(tabela);



	masina** masini = (masina**)malloc(sizeof(masina*));
	int nr = 0;
	copiereVector(tabela, masini, &nr, 10000, 20000);


	printf("\n---------------------\n");
	for (int i = 0; i < nr; i++)
	{
		printf("\nPozitia = %d", i);
		printf("\nAn fabricatie =%d, Marca =%s, Pret=%5.2f",masini[i]->anFabricatie,masini[i]->marca, masini[i]->pret);
	}
	printf("\n---------------------\n");


	dezalocareHash(tabela);
}