#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//RECHERCHE EN LARGEUR //
typedef struct
{
     int x,y;
}etat;

typedef struct Noeud
{
    struct Noeud *suivant;
    etat Etat;
}noeud;

typedef struct
{
    noeud *debut, *fin;
}liste;

liste listeNoeuds;

int n;

void Inserer(etat e,liste *L)
{
    noeud *ne;
    ne=(noeud*)malloc(sizeof(noeud));
    ne->Etat = e;
    ne->suivant = NULL;
    if (L->debut == NULL) L->debut =ne;
    else L->fin->suivant=ne;
    L->fin=ne;
}

int Vide(liste L)
{
    if (L.debut) return 0;
    return 1;
}

/*etat Extraire(liste *L)
{
    etat e;
    e=L->debut->Etat;
    if (L->debut->suivant) L->debut=L->debut->suivant;
    else L->debut=L->fin=NULL;
    return e;
}*/

etat Extraire(liste *L0) //a revoir
{etat e;
noeud *p;
liste L;
L=*L0;
p=L.debut;
if (p==L.fin)  L.fin=NULL;
e=p->Etat;
L.debut=p->suivant;
free(p);
*L0=L;
return e;
}


int Appartient(etat e, liste L)
{
    noeud *p;

    for(p=L.debut;p!=NULL;p=p->suivant)
        if((p->Etat.x==e.x)&& (p->Etat.y==e.y))  return 1;
    return 0;
}

int etatSolution(etat e)
{
    if (e.x==2)
        return 1;
    return 0;
}

void genereSuccesseurs(etat et)
{
	int m,x0,y0;
	x0=et.x;
	y0=et.y;
	etat e;
	if(x0<4)
	{
		e.x=4;
		e.y=y0;

		Inserer(e,&listeNoeuds);
	}
	if(x0>0)
	{
		e.x=0;
		e.y=y0;

		Inserer(e,&listeNoeuds);
	}
	if(y0<3)
	{

		e.y=3;
		e.x=x0;
		Inserer(e,&listeNoeuds);
	}
	if(y0>0)
	{
		e.y=0;
		e.x=x0;

		Inserer(e,&listeNoeuds);
	}

	if((x0>0)&&(y0<3))
	{
		m=fmin(x0,3-y0);
		e.x=x0-m;
		e.y=y0+m;
		Inserer(e,&listeNoeuds);
	}
	if((y0>0)&&(x0<4))
	{
		m=fmin(4-x0,y0);
		e.x=x0+m;
		e.y=y0-m;
		Inserer(e,&listeNoeuds);
	}
}

void RechercheLargeur(etat etatInitial, etat etatFinal, void genereSuccesseurs())
{
    liste NoeudsDejaTraites;
    etat etatCourant;
    listeNoeuds.debut = listeNoeuds.fin = NULL;
    Inserer(etatInitial,&listeNoeuds);
    NoeudsDejaTraites.debut= NoeudsDejaTraites.fin =NULL;
    while(!Vide(listeNoeuds))
    {

        etatCourant=Extraire(&listeNoeuds);
        n++;
        if(etatSolution(etatCourant))
        {
            printf("\nSucces ! Arret sur le noeud : (%d,%d)\n\n Nombre de noeuds explores : %d\n",etatCourant.x, etatCourant.y, n);
            exit(0);
        }
        else if (!Appartient(etatCourant,NoeudsDejaTraites))
        {
            genereSuccesseurs( etatCourant);
            Inserer(etatCourant, &NoeudsDejaTraites);
        }
    }
    puts("\nPas de Solution");
}


int main()
{
    etat etatInitial={0,0},etatFinal={2,3};
    RechercheLargeur(etatInitial,etatFinal,genereSuccesseurs);

    return 0;
}

