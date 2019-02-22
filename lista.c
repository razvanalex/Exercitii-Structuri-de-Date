#include<stdio.h>
#include<stdlib.h>

typedef struct celula {
	int info;
	struct celula *urm;
} TCelula, *TLista, **ALista;

int insListaSf(ALista l, int el)
{
	TLista aux;

	for (; *l != NULL; l = &(*l)->urm)
		if ((*l)->urm == NULL)
			break;

	aux = (TLista)malloc(sizeof(TCelula));
	if (!aux)
		return 0;
	aux->info = el;
	aux->urm = NULL;

	if (*l)
		(*l)->urm = aux;
	else *l = aux;
	
	return 1;
}

void printList(TLista l)
{
	for (; l != NULL; l=l->urm)
		printf("%d ", l->info);
}

void distrList(ALista l)
{
	TLista p = *l, aux;
	while(p)
	{
		aux = p;
		p = p->urm;
		free(aux);
	}
	*l = NULL;
}

/* 
   Sa se modifice o lista ai sa contine doar 
   elementele impare in ordine crescatoare. Prin 
   efect lateral returneaza numarul de elemente 
   ramase si cate elemente au fost sterse.
*/
void Mutare(ALista l, int *del, int *rem)
{
	TLista p = *l, aux, imp = NULL, ip, iant;
	*del = 0;
	*rem = 0;
	
	while (p)
	{
		aux = p;
		p = p->urm;	

		if (aux->info % 2 == 0)
		{	
			(*del)++;
			free(aux);
		}
		else
		{
			(*rem)++;
			if (!imp)
			{
				imp = aux;
				aux->urm = NULL;
			}
			else 
			{
				for (iant = NULL, ip = imp; ip; iant = ip, ip = ip->urm)
					if (ip->info > aux->info)
						break;
				if (!iant)
				{
					aux->urm = imp;
					imp = aux;
				}
				else 
				{
					aux->urm = iant->urm;
					iant->urm = aux;
				}
			}
		}
	}

	*l = imp;
}

/* Mutare elemente dupa o conditie */
int conditie(int a)
{
	return a % 2;
}

TLista Mutare2(ALista l, int(*cond)(int))
{
	TLista r = NULL, p = *l, ant = NULL, ultim;
	while (p)
	{
		if (cond(p->info))
		{
			if (!ant)
				*l = p->urm;
			else ant->urm = p->urm;

			if (!r)
			{
				r = p;
				ultim = r;
			}
			else 
			{
				ultim->urm = p;
				ultim = ultim->urm;
			}
			ultim->urm = NULL;
			
			if (ant)
				p = ant->urm;
			else p = *l;
		}
		else 
		{
			ant = p;
			p = p->urm;
		}
	}

	return r;
}



int main()
{
	TLista l = NULL;
	int x;

	while(scanf("%d", &x))
		insListaSf(&l, x);
	printList(l);
	
	/*int a, b;
	Mutare(&l, &a, &b);
	printf("\nAu fost sterse %d si au ramas %d.\n", a, b);
	printList(l);
	printf("\n");*/
	TLista r = Mutare2(&l, conditie);
	printList(r);
	printf("\n");
	printList(l);
	printf("\n");
	distrList(&l);
	return 0;
}
