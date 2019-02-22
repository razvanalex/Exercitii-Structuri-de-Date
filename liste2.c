#include<stdio.h>
#include<stdlib.h>

typedef struct celula2 {
	void *info;
	struct celula2 *ant, *urm;
} TCelula2, *TLDI, **ALDI;

TLDI Init()
{
	TLDI l = (TLDI)malloc(sizeof(TCelula2));
	if (!l)
		return NULL;
	
	l->info = NULL;
	l->urm = l;
	l->ant = l;
	return l;
}

int insSf(TLDI l, void *ae)
{
		TLDI aux =(TLDI)malloc(sizeof(TCelula2));
		if (!aux)
			return 0;

		aux->info = ae;
		aux->urm = l;
		aux->ant = l->ant;
		l->ant->urm = aux;
		l->ant = aux;

		return 1;
}

void reset(TLDI l, void(*elib)(void*))
{
	TLDI p = l->urm, aux;

	while (p != l)
	{
		p->ant->urm = p->urm;
		p->urm->ant = p->ant;
		aux = p;
		p = p->urm;
		elib(aux->info);
		free(aux);
	}
}

void DistrLDI(ALDI l, void(*elib)(void*))
{
	reset(*l, elib);
	free(*l);
	*l = NULL;
}

void afi(void *a)
{
	printf("%d ", *(int*)a);
}

void printLDI(TLDI l, void(*fafi)(void*))
{
	TLDI p;
	for (p = l->urm; p != l; p = p->urm)
		fafi(p->info);
	printf("\n");
}

// mutare elemente de pe pozitie impara
TLDI Muta(TLDI s)
{
	int index = 1;
	TLDI p = s->urm, r, aux;
	r = Init();
	if (!r)
		return NULL;

	while (p != s)
	{
		if (index % 2 == 1)
		{
			aux = p->urm;
			p->ant->urm = p->urm;
			p->urm->ant = p->ant;
			
			p->urm = r;
			p->ant = r->ant;
			r->ant->urm = p;
			r->ant = p;
			p = aux;
		}
		else 
		{
			p = p->urm;
		}
		index++;
	}

	return r;
}

// elimina element egal cu ceva
int cmp(void *a, void *b)
{
	return *(int*)a - *(int*)b;	
}

void* Elimina(TLDI s, void *ae, int(*cmp)(void*, void*))
{
	TLDI p = s->urm;
	void *adr = NULL;
	for (; p != s; p = p->urm)
		if (!cmp(p->info, ae))
		{
			p->ant->urm = p->urm;
			p->urm->ant = p->ant;
			
			adr = p->info;
			free(p);
			return adr;
		}
	
	return adr;
}

int main()
{
	int *x;
	TLDI l = Init();
	if (!l)
		return -1;

	while(printf("Introduceti un element: ") && 
		(x = (int*)malloc(sizeof(int))) && scanf("%d", x))
	{
		insSf(l, x);
	}
	printLDI(l, afi);
	
	/*TLDI r = Muta(l);
	printf("l=");
	printLDI(l, afi);
	printf("r=");
	printLDI(r, afi);*/
	char ch = 'd';
	ch = getchar();
	
	int ceva;
	printf("\nCe se elimina? "); scanf("%d", &ceva);
	void *ae = Elimina(l, &ceva, cmp);
	if (ae)
		printf("\nS-a eliminat %d din lista. Noua lista = ", *(int*)ae);
	printLDI(l, afi);

	free(x);
	free(ae);
	//DistrLDI(&r, free);
	DistrLDI(&l, free);
	return 0;	
}
