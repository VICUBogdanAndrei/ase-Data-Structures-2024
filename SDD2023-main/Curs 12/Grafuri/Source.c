#include <stdio.h>
#include <malloc.h>

typedef struct
{
	int id;
	char* denumire;
} localitate;

typedef struct nodLP;

typedef struct nodLS
{
	struct nodLP* info;
	struct nodLS* next;
} nodLS;

typedef struct nodLP
{
	localitate info;
	struct nodLS* vecini;//lista de vecini
	struct nodLP* next;
} nodLP;

nodLP* inserareLP(nodLP* cap, localitate s)
{
	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->info.id = s.id;
	nou->info.denumire = (char*)malloc((strlen(s.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, s.denumire);
	nou->vecini = NULL;
	nou->next = NULL;
	if (cap==NULL)
	{
		cap = nou;
	}
	else
	{
		nodLP* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

nodLS* inserareLS(nodLS* cap, nodLP* info)
{
	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info = info;
	nou->next = NULL;
	if (cap==NULL)
	{
		cap = nou;
	}
	else
	{
		nodLS* temp = cap;
		while (temp->next)
			temp = temp->next;
		temp->next = nou;
	}
	return cap;
}

nodLP* cautareDupaId(nodLP* cap, int id)
{
	nodLP* temp = cap;
	while (temp && temp->info.id != id)
	{
		temp = temp->next;
	}
	return temp;
}

void inserareArcInGraf(nodLP* graf, int idStart, int idStop)
{
	if (graf)
	{
		nodLP* nodStart = cautareDupaId(graf, idStart);
		nodLP* nodStop = cautareDupaId(graf, idStop);
		if (nodStart && nodStop)
		{
			nodStart->vecini = inserareLS(nodStart->vecini, nodStop);//daca este orientat
			nodStop->vecini = inserareLS(nodStop->vecini, nodStart);
		}
	}
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		nodLP* aux = temp->info;
		printf("    %d.%s\n", aux->info.id + 1, aux->info.denumire);
		temp = temp->next;
	}
}

void traversareLP(nodLP* cap)
{
	nodLP* temp = cap;
	while (temp)
	{
		printf("%d.%s are urmatorii vecini: \n", temp->info.id + 1, temp->info.denumire);
		traversareLS(temp->vecini);
		temp = temp->next;
	}
}

//pt parcurgere in adancime
typedef struct NodStiva
{
	int id;
	struct NodStiva* next;
} NodStiva;

NodStiva* push(NodStiva* varf, int id)
{
	NodStiva* nou = (NodStiva*)malloc(sizeof(NodStiva));
	nou->id = id;
	nou->next = NULL;
	if (varf == NULL)
		varf = nou;
	else
	{
		nou->next = varf;
		varf = nou;
	}
	return varf;
}

int pop(NodStiva** varf)
{
	if (*varf)
	{
		int id = (*varf)->id;
		NodStiva* temp = *varf;
		*varf = (*varf)->next;
		free(temp);
		return id;
	}
	else
	{
		return -1;
	}
}

//parcurgere in adancime
void parcurgereAdancime(nodLP* graf, int idNodStart, int nrNoduri)
{
	if (graf)
	{
		NodStiva* varf = NULL;
		int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);
		for (int i = 0; i < nrNoduri; i++)
		{
			vizitate[i] = 0;
		}

		varf = push(varf, idNodStart);
		vizitate[idNodStart] = 1;

		while (varf)
		{
			int idNodCurent = pop(&varf);

			nodLP* nodCurent = cautareDupaId(graf, idNodCurent);
			printf("%d.%s\n", nodCurent->info.id + 1, nodCurent->info.denumire);

			nodLS* temp = nodCurent->vecini;
			while (temp)
			{
				if (vizitate[temp->info->info.id] == 0)
				{
					varf = push(varf, temp->info->info.id);
					vizitate[temp->info->info.id] = 1;
				}
				temp = temp->next;
			}
		}
	}
}
//PARCURGERE IN LATIME
typedef struct NodCoada
{
	int id;
	struct NodCoada* next;
} NodCoada;

void put(NodCoada** prim, NodCoada** ultim, int id)
{
	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
	nou->id = id;
	nou->next = NULL;

	if (*prim == NULL || *ultim == NULL)
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

int get(NodCoada** prim, NodCoada** ultim, int* id)
{
	if (*prim != NULL && *ultim != NULL)
	{
		*id = (*prim)->id;
		NodCoada* temp = *prim;
		*prim = (*prim)->next;
		free(temp);
		return 0;
	}
	else
	{
		if (*prim == NULL)
			*ultim = NULL;
		return -1;
	}
}

void parcurgereLatime(nodLP* graf, int idNodStart, int nrNoduri)
{
	if (graf)
	{
		NodCoada* prim = NULL, * ultim = NULL;
		int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);
		for (int i = 0; i < nrNoduri; i++)
		{
			vizitate[i] = 0;
		}
		put(&prim, &ultim, idNodStart);
		vizitate[idNodStart] = 1;

		while (prim && ultim)
		{
			int idNodCurent;
			get(&prim, &ultim, &idNodCurent);

			nodLP* nodCurent = cautareDupaId(graf, idNodCurent);
			printf("%d.%s\n", nodCurent->info.id + 1, nodCurent->info.denumire);

			nodLS* temp = nodCurent->vecini;
			while (temp)
			{
				nodLP* aux = temp->info;
				if (vizitate[aux->info.id] == 0)
				{
					put(&prim, &ultim, aux->info.id);
					vizitate[aux->info.id] = 1;
				}
				temp = temp->next;
			}
		}

	}
}

void dezalocareLS(nodLS* cap) {
	nodLS* temp = cap;
	while (temp) {
		nodLS* temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
}

void dezalocareLP(nodLP* cap) {
	nodLP* temp = cap;
	while (temp) {
		nodLP* temp2 = temp->next;
		if (temp->vecini)
			dezalocareLS(temp->vecini);
		printf("\nAm sters %s", temp->info.denumire);
		free(temp->info.denumire);
		free(temp);
		temp = temp2;
	}
}

void main()
{
	FILE* f = fopen("fisier.txt", "r");
	nodLP* graf = NULL;
	int nrNoduri;
	char buffer[20];
	fscanf(f, "%d", &nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		//id-ul va fi i-ul, numele citit de la tastatura
		localitate loc;
		loc.id = i;
		fscanf(f, "%s", buffer);
		loc.denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
		strcpy(loc.denumire, buffer);
		graf = inserareLP(graf, loc);
	}

	//inserare arce(vecinii pt fiecare nod)
	int nrArce = 0;
	fscanf(f, "%d", &nrArce);
	for (int i = 0; i < nrArce; i++)
	{
		int idStart;
		fscanf(f, "%d", &idStart);
		int idStop;
		fscanf(f, "%d", &idStop);
		inserareArcInGraf(graf, idStart, idStop);
	}
	fclose(f);

	traversareLP(graf);
	
	printf("\nParcurgere in adancime de la nodul 1:\n");
	parcurgereAdancime(graf, 0, nrNoduri);

	printf("\nParcurgere in latime de la nodul 1:\n");
	parcurgereLatime(graf, 0, nrNoduri);

	dezalocareLP(graf);
}