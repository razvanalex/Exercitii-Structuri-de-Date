#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "TCoada.h"
#include "TStiva.h"

/* numar maxim elemente coada / stiva */
#define MAX 256 

typedef struct
{ 
	int x, y;
} TPct;

int GenereazaCoadaPct(void* c, size_t N, int v1, int v2)
{ 
  	int n = 0;
  	TPct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1; 
    	p.y = rand() % (v2-v1+1) + v1;
  
		if (!IntrQ(c, &p)) 
			return n;
		n++;
  	}
  	return n;
}

int GenereazaStivaPct(void* c, size_t N, int v1, int v2)
{ 
	int n = 0;
  	TPct p;

  	srand(time(NULL));
  	for(; N > 0; N--)
  	{
    	p.x = rand() % (v2-v1+1) + v1; 
    	p.y = rand() % (v2-v1+1) + v1;
  
		if (!Push(c, &p)) 
			return n;
		n++;
  	}
  	return n;
}

/* afiseaza coada */
void AfiQ(char antet[], TF1 AfiElem, void *a)
{ 
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */
	printf ("%s", antet);          	/* afiseaza antetul */
  	if (VidaQ (a))
      printf ("Coada vida!");
  	else
      PrelQ (a, AfiElem);       	/* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}

/* afiseaza stiva */
void AfiS(char antet[], TF1 AfiElem, void *a) 
{
	/* afiseaza antet si apoi aplica functia de afisare AfiElem tuturor elementelor */ 
	printf ("%s", antet);          /* afiseaza antetul */
	if (VidaS (a))
    	printf ("Stiva vida!");
  	else
      	Prel_B_V (a, AfiElem);       /* afiseaza elementele in ordinea introducerii */
  	printf("\n");
}

int AfiPct(void *a)
{ 
	printf("[%d %d] ", (*(TPct*)a).x, (*(TPct*)a).y); 
	return 1;
}

void* Copie(void *q)
{
	void *aux, *s, *qaux;
	TPct ae;

	aux = InitS(sizeof(TPct), MAX);
	if (!aux)
		return NULL;
	
	qaux = InitQ(sizeof(TPct), MAX);
	if (!qaux)
		return NULL;

	s = InitS(sizeof(TPct), MAX);
	if (!s)
		return NULL;


	while(ExtrQ(q, &ae))
	{
		TPct pct;
		IntrQ(qaux, &ae);
		memcpy(&pct, &ae, sizeof(TPct));
		Push(aux, &pct);
	}
	
	while(Pop(aux, &ae))
		Push(s, &ae);
	while (ExtrQ(qaux, &ae))
		IntrQ(q, &ae);

	DistrS(&aux);
	DistrQ(&qaux);

	return s;
}

typedef int(*TFCond)(void*);

int cnd(void *a)
{
	if (((TPct*)a)->x > 0 && ((TPct*)a)->y > 0)
		return 1;
	return 0;
}

float FS(void *s, TFCond cond)
{
	float suma = 0, count = 0;
	TPct x;
	void *aux = InitS(sizeof(TPct), MAX);
	if (!aux)
		return -1;
	
	while (Pop(s, &x))
	{
		count++;
		if (cond(&x))
			suma++;
		Push(aux, &x);
	}

	while(Pop(aux, &x))
		Push(s, &x);

	DistrS(&aux);
	return suma / count;
}

float FC(void *q, TFCond cond)
{
	float suma = 0, count = 0;
	TPct x;
	void *aux = InitQ(sizeof(TPct), MAX);
	if(!aux)
		return -1;
	
	while (ExtrQ(q, &x))
	{
		count++;
		if(cond(&x))
			suma++;
		IntrQ(aux, &x);
	}

	while(ExtrQ(aux, &x))
		IntrQ(q, &x);

	DistrQ(&aux);
	return suma / count;
}

int main()
{ 
	void *c, *s;
  	int lgc, lgs;

  	c = InitQ(sizeof(TPct),MAX);
	if (!c) 
		return 1;

  	s = InitS(sizeof(TPct),MAX);
	if (!s) 
	{
		DistrQ(&c); 
		return 1;
	}

  	lgc = GenereazaCoadaPct(c, 8, -5, 5);
  	lgs = GenereazaStivaPct(s, 6, 8, 14);
  
	printf("\nCoada cu %d elemente\n", lgc);
  	AfiQ("Elemente coada:\n", AfiPct, c);
  	printf("\n\nStiva cu %d elemente\n", lgs);
   	AfiS("Elemente stiva (baza -> varf):\n", AfiPct, s);

 	/* apeluri functii */
	void *asd = Copie(c);
	AfiS("Elementele stivei noi:\n", AfiPct, asd);
  	AfiQ("Elemente coada:\n", AfiPct, c);
  	
	printf("\n\nStiva cu %d elemente\n", lgs);
	
	printf("\n%f\n", FC(c, cnd));

	DistrS(&s);
  	DistrQ(&c);
  	return 0;
}

