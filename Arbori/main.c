#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct nod 
{
	int info;
	struct nod *st, *dr;
} TNod, *TArb, **AArb;

#include "auxarb.c"

TArb CreazaFrunza(int x)
{
	TArb r = (TArb)malloc(sizeof(TNod));
	if (!r)
		return NULL;
	
	r->info = x;
	r->st = NULL;
	r->dr = NULL;

	return r;
}

int insArb(AArb a, int x)
{
	if (*a == NULL)
	{
		*a = CreazaFrunza(x);
		if (!*a)
			return 0;
		return 1;
	}
	
	TArb p;
	while (*a)
	{
		p = *a;
		if (x < (*a)->info)
			a = &(*a)->st;
		else a = &(*a)->dr;
	}
	
	TArb f = CreazaFrunza(x);
	if (!f)
		return 0;

	if (x < p->info)
		p->st = f;
	else p->dr = f;

	return 1;
}

void AfiA(TArb a)
{
	if (!a)
		return;
	
	if (a->st)
		AfiA(a->st);
	printf("%d ", a->info);
	if (a->dr)
		AfiA(a->dr);
}

void DistrA(AArb a)
{
	if (!a)
		return;
	
	if ((*a)->st)
		DistrA(&(*a)->st);
	if ((*a)->dr)
		DistrA(&(*a)->dr);
	
	free(*a);
	*a = NULL;
}

// nr de noduri pare de pe un anumit nivel
int nrNodPar(TArb a, int niv, int crt)
{
	if (!a)
		return 0;
	int suma = 0;

	if (a->st)
		suma = nrNodPar(a->st, niv, crt++);
	if (a->dr)
		suma += nrNodPar(a->dr, niv, crt++);
	
	if (crt == niv)
		if (a->info % 2 == 0)
			suma++;
	
	return suma;
}

void insABC(AArb a, int n, int crt, int x)
{
	if (crt > n)
		return;
	
	if (!*a)
		*a = CreazaFrunza(x);
	else if ((*a)->info < x)
		insABC(&(*a)->st, n, crt++, x);
	else insABC(&(*a)->dr, n, crt++, x);
}

TArb CitABC(int n)
{
	int x;
	TArb a = NULL;
	while (scanf("%d", &x))
	{
		insABC(&a, n, 1, x);
	}
	return a;
}

int main()
{
	TArb a = NULL;
	int x;

	while (scanf("%d", &x))
		insArb(&a, x);

	AfiArb(a);
	printf("\n");

	printf("%d", nrNodPar(a, 5, 1));

	DistrA(&a);
	return 0;
}
