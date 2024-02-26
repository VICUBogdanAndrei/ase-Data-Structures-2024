#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct {
	unsigned int codProiect;
	char* titluProiect;
	char* beneficiar;
	unsigned char nrExecutanti;
	float bugetAlocat;
}Proiect;

typedef struct {
	Proiect info;
	nodLista* next;
}nodLista;

typedef struct {
	nodLista** lista;
	int size;
}hashT;

int functieHash(hashT tabela, char* cheie) //tabela pentru a ne lua size-ul hash-table-ului; cheia trb sa aiba tipul dupa care se doreste aflarea indicelui din HT
{
	return strlen(cheie) % tabela.size; //sunt mai multe variante de calcul in functie de tipul de date trimise (cheie)
}

//functia de inserare
void inserare(hashT tabela, Proiect nod) //parametrii: tabela si NODUL ce va fi introdus in HashTable, cu tipul de data aferent; va face parte dintr-o lista pe pozitia desemnata de functia hash
{
	//trebuie declarata o pozitie, ajutatoare pentru functia hash
	int pozitie = 0;
	if (tabela.lista != NULL)
	{ //se verifica ca tabela de dispersie/hashtable sa nu fie NULA
		pozitie = functieHash(tabela, nod.beneficiar);
		//se apeleaza functia hash pentru a determina pozitia unde trebuie introdus nodul

		//DE AICI SE FACE SIMILAR CA LA LISTE
		//declar un nou nod si copiez datele utile din nodul parametru in noul nod, de introdus in hashTable / tabela de dispersie
		nodLista* nou = (nodLista*)malloc(sizeof(nodLista)); //alocare memorie nod nou
		nou->info.codProiect = nod.codProiect;
		nou->info.titluProiect = (char*)malloc(sizeof(char) * (strlen(nod.titluProiect) + 1));
		strcpy(nou->info.titluProiect, nod.titluProiect);
		nou->info.beneficiar = (char*)malloc(sizeof(char) * (strlen(nod.beneficiar) + 1));
		strcpy(nou->info.beneficiar, nod.beneficiar);
		nou->info.nrExecutanti = nod.nrExecutanti;
		nou->info.bugetAlocat = nod.bugetAlocat;

		nou->next = NULL; //pentru a nu lua adrese reziduale

		//SE VERIFICA EXISTENTA UNUI ALT NOD PE POZITIA RETURNATA DE FUNCTIA HASH
		if (tabela.lista[pozitie] == NULL)
		{
			//in cazul in care nu exista deja un alt elem pe pozitia respectiva
			//NOD-ul pe care il introducem ar fi primul element din lista de pe pozitia respectiva a HASHTABLE

			tabela.lista[pozitie] = nou; // nodul de pe pozitia POZITIE din HashTable va lua valoarea nodului NOU
		}
		else
		{
			//in cazul in care exista deja un nod sau mai multe pe pozitia respectia
			//parcurgem lista de la adresa de pe pozitie pana la FINAL, unde vom introduce nodul

			//pentru a parcurge lista avem nevoie de o variabila temporala de tipul nodului de lista component al HashMap

			nodLista* temp = tabela.lista[pozitie];
			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = nou; // noul nod a fost inserat la finalul listei de pe pozitia POZITIE din HashTable
		}

	}
}

void traversareLista(nodLista* inceputLista)
{
	nodLista* temp = inceputLista;
	while (temp)
	{
		printf("\nCod proiect: %d \t Titlu Proiect: %s \t Beneficiar: %s \t Nr. executanti: %d \t Buget Local: %6.2f", temp->info.codProiect, temp->info.titluProiect, temp->info.beneficiar, temp->info.nrExecutanti, temp->info.bugetAlocat);
		temp = temp->next;
	}
}

void traversareHash(hashT tabela)
{
	if (tabela.lista != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
		{
			if (tabela.lista[i] != NULL)
			{
				printf("\n\tPozitia %d", i);
				traversareLista(tabela.lista[i]);
			}
		}
	}
}


void main()
{
	FILE* f = fopen("fisier.txt", "r");
	
	int n;
	fscanf(f, "%d", &n);

	Proiect p;
	hashT tabela;

	tabela.size = 100;
	tabela.lista = (nodLista**)malloc(sizeof(nodLista*));

	//dupa ce am alocat memoria, trebuie sa initializam tabela de dispersie ca fiind NULA pe toate pozitiile
	for (int i = 0; i < tabela.size; i++) {
		tabela.lista[i] = NULL;
	}

	char buffer[30]; //ca sa pot citi siruri de caractere din fisier

	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &p.codProiect);
		fscanf(f, "%s", buffer);
		p.titluProiect = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(p.titluProiect, buffer);
		fscanf(f, "%s", buffer);
		p.beneficiar = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(p.beneficiar, buffer);
		fscanf(f, "%d", &p.nrExecutanti);
		fscanf(f, "%f", &p.bugetAlocat);

		inserare(tabela, p);
	}

	fclose(f);
	//traversareHash(tabela);

}
