#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "GestioJoc.h"
#include "rutines.h"
#include "Peces.h"
#include "GestioPuntuacions.h"



//===================================================================================
// NOM: NumAleatori
//===================================================================================
// DESCRIPCI�:  Funci� per generar un n�mero aleatori entre 0 i max
//===================================================================================
// PAR�METRES:
// - mx: l�mit superior del n�mero aleatori a generar
//===================================================================================
int NumAleatori(int mx)
{
  int num;
  int max_size;

  max_size= mx > NUM_PECES ? NUM_PECES : mx;

  num = rand() % max_size + 1;  
	return num;
}




//===================================================================================
// NOM: ComprovarNivell
//===================================================================================
// DESCRIPCI�: Mira l'�ltim canvi de puntuaci� fa canviar el nivell de joc 
//===================================================================================
// PAR�METRES:
// - puntsAnteriors: puntauaci� abans d'actualitzar
// - puntsActuals: puntuaci� actualitzada
// - nivell: nivell actual del joc. S'actualitza al nou nivell si cal.
//===================================================================================
void ComprovarNivell(int puntsAnteriors,int puntsActuals,int *nivell)
{
	if (*nivell<NIVELL_MAXIM)
		if (puntsAnteriors/PUNTS_CANVI_NIVELL!=puntsActuals/PUNTS_CANVI_NIVELL)
			(*nivell)++;
}


//===================================================================================
// NOM: ComprovarLinia
//===================================================================================
// DESCRIPCI�: Mira si s'ha completat la l�nia inferior del joc.
//===================================================================================
// PAR�METRES:
// - liniaJoc: taula en qu� cada valor correspon a una de les posicions de la l�nia inferior
//===================================================================================
// RETORN: nombre m�xim de posicions lliures consecutives dins de la l�nia de joc. Si �s 0
// vol dir que la l�nia �s completa
//===================================================================================
int comprovarLinia(int *liniaJoc)
{
	int i;  // variable per a les iteracions
	int nLliures; //Nombre de posicions lliures seguides
	int nLliuresMax; // Nombre de posicions lliures seguides m�s gran de tota la l�nia


	// Codi a completar

}



//===================================================================================
// NOM: ColocarPesa
//===================================================================================
// DESCRIPCI�: Mira si la pe�a que ha arribat a la l�nia inferior es pot colocar o b�
// col�lisiona amb alguna de les peces ja colocades. Si no colisiona la coloca a la 
// posici� corresponent de la l�nia
//===================================================================================
// PAR�METRES:
// - liniaJoc: taula en qu� cada valor correspon a una de les posicions de la l�nia inferior
// - posicioFinal: columna que ocupa la pe�a quan arriba a la l�nia inferior
// - pesa: taula de 3 posicions per guardar els valors de la pe�a que s'est� despla�ant
//===================================================================================
// RETORN: valor l�gic que indica si la pe�a col�lisiona amb alguna de les ja colocades
// o no
//===================================================================================
int ColocarPesa(int *liniaJoc,int posicioFinal,int *pesa)
{
	int i,colisio;

	i=0;
	colisio=0;
	while ((i<TamanyPeces)&&(colisio==0))
	{
		if (pesa[i]!=0)
			if (liniaJoc[posicioFinal+i]!=0)
				colisio=1;
			else
			{
				liniaJoc[posicioFinal+i]=pesa[i];
				i++;
			}
		else
			i++;
	}
	return colisio;
}




//===================================================================================
// NOM: MovimentDreta
//===================================================================================
// DESCRIPCI�: Mou la pe�a una posici� cap a la dreta si �s possible segons els 
// l�mits de la pantalla i la forma de la pe�a
//===================================================================================
// PAR�METRES:
// - pesa: taula de 3 posicions per guardar els valors de la pe�a que s'est� despla�ant
// - columna: columna actual de la pe�a. S'actualitza amb el nou valor de la columna 
// si �s possible fer el moviment a la dreta
//===================================================================================
void MovimentDreta(int *pesa,int *columna)
{
	int limit;

	if (pesa[2]==0)
		limit=NCol-2;
	else 
		limit=NCol-3;
	if (*columna<limit)
		(*columna)++;
}


//===================================================================================
// NOM: MovimentEsquerra
//===================================================================================
// DESCRIPCI�: Mou la pe�a una posici� cap a l'esquerra si �s possible segons els 
// l�mits de la pantalla i la forma de la pe�a
//===================================================================================
// PAR�METRES:
// - pesa: taula de 3 posicions per guardar els valors de la pe�a que s'est� despla�ant
// - columna: columna actual de la pe�a. S'actualitza amb el nou valor de la columna 
// si �s possible fer el moviment a l'esquerra
//===================================================================================
void MovimentEsquerra(int *pesa,int *columna)
{
	int limit;

	if (pesa[0]==0)
		limit=-1;
	else 
		limit=0;
	if (*columna>limit)
		(*columna)--;
}



//===================================================================================
// NOM: ControlTeclat
//===================================================================================
// DESCRIPCI�: Detecta si s'ha pressionat alguna tecla i actua en funci� de la tecla
// pressionada
//===================================================================================
// PAR�METRES:
// - pesa: taula de 3 posicions per guardar els valors de la pe�a que s'est� despla�ant
// - fila: fila actual de la pe�a. S'actualitza amb el nou valor de la fila despr�s de
// pressionar alguna tecla
// - columna: columna actual de la pe�a. S'actualitza amb el nou valor de la columna 
// despr�s de pressionar alguna tecla
// - tauler: estructura que controla la visualitzaci� per pantalla
//===================================================================================
// RETORN: valor l�gic que indica si s'ha pressionat la tecla ESC per finalitzar el joc
//===================================================================================
int ControlTeclat(int *pesa,int *fila,int *columna,pantalla_t *tauler)
{
	unsigned char tecla;
	int teclaEspecial;
	int fiJoc;

	fiJoc=0;
	if (_kbhit())
    {
		tecla=getch();
        if (tecla==KEY_SPECIAL) 
		{
			teclaEspecial=1; 
			tecla=getch();
		}
        else teclaEspecial = 0;
		
		fflush(stdin);
        switch (tecla)
        {
		case KEY_LEFT:
			MovimentEsquerra(pesa,columna); 
            break;
        case KEY_RIGHT:
            MovimentDreta(pesa,columna); 
            break;
        case 'p':
		case KEY_DOWN_P:
            if (teclaEspecial) 
            {
				*fila=NFil-1;
            }
			else
			{
         		// Fem pausa:
				MostraMSG(tauler,"Pausa. Prem qualsevol tecla per continuar");
				getch();
				system("cls");
				MostraTauler(tauler);
			}
            break;
		 case KEY_ESC:
			 fiJoc=1;
			 break;
         }
	}
	return fiJoc;
}

//===================================================================================
// NOM: RotarLiniaJoc
//===================================================================================
// DESCRIPCI�: Fa el despla�ament lateral de la l�nia de joc inferior
//===================================================================================
// PAR�METRES:
// - liniaJoc: taula per marcar l'ocupaci� de cada posici� de la l�nia.
// - tauler: estructura que controla la visualitzaci� per pantalla
//===================================================================================
void RotarLiniaJoc(int *liniaJoc,pantalla_t *tauler)
{
	int i,aux;

	EsborraLinia(tauler);
	aux=liniaJoc[NCol-1];
	for (i=NCol-1;i>0;i--)
		liniaJoc[i]=liniaJoc[i-1];
	liniaJoc[0]=aux;
	MostraLinia(tauler,liniaJoc);
}

//===================================================================================
// NOM: ControlCaigudaPesa
//===================================================================================
// DESCRIPCI�: Controla el moviment d'una pe�a des que �s generada fins que arriba a 
// la l�nia inferior
//===================================================================================
// PAR�METRES:
// - pesa: taula de 3 posicions per guardar els valors de la pe�a
// - nivell: nivell de dificultat del joc. Controla la velocitat del joc i el moviment
// de rotaci� de la l�nia inferior
// - liniaJoc: taula per marcar l'ocupaci� de cada posici� de la l�nia.
// - nCiclesRotacio: n� de cicles actuals per comptar quan s'ha de depla�ar la l�nia inferior
// del joc. Es modifica dins de la funci�
// - tauler: estructura que controla la visualitzaci� per pantalla
//===================================================================================
// RETORN: Posici� final de la pe�a quan arriba a la l�nia inferior. Retorna -2 si 
// l'usuari prem 'ESC' per finalitzar la partida
//===================================================================================
int ControlCaigudaPesa(int *pesa,int nivell,int *liniaJoc,int *nCiclesRotacio,pantalla_t *tauler)
{
	int fila,columna;
	int nCiclesTeclat,fiJoc,tempsEspera;

	fila=0;
	columna=(int)ceil(NCol/2);
	fiJoc=0;
	tempsEspera=TEMPS_MAX_ESPERA/nivell;
	nCiclesTeclat=N_CICLES_TECLAT-nivell;
	do
    {
		MostraPesa(tauler,pesa,fila,columna);
	    Sleep(tempsEspera);          
		EsborraPesa(tauler,pesa,fila,columna);
		fiJoc=ControlTeclat(pesa,&fila,&columna,tauler);
		nCiclesTeclat--;
        if (nCiclesTeclat==0)
		{
			nCiclesTeclat=N_CICLES_TECLAT/nivell;
			fila++;
			(*nCiclesRotacio)--;
			if (*nCiclesRotacio==0)
			{
				*nCiclesRotacio=N_CICLES_ROTACIO;
				RotarLiniaJoc(liniaJoc,tauler);
			}
		}
    }
	while ((fila<NFil-1) && (fiJoc==0));
	if (fiJoc==0)
		return columna;
	else 
		return -2;
}


//===================================================================================
// NOM: InicialitzarLiniaJoc
//===================================================================================
// DESCRIPCI�: Inicialitza la l�nia de baix del joc posant tots els valors de la taula
// a 0 per indicar que estat tots buits. A mesura que es vagi omplint la l�nia els 
// valors corresponents a poscions ocupades passaran a tenir valor 1.
//===================================================================================
// PAR�METRES:
// - liniaJoc: taula per marcar l'ocupaci� de cada posici� de la l�nia.
//===================================================================================
void InicialitzarLiniaJoc(int liniaJoc[])
{
	int i;

	for (i=0; i<NCol; i++)
		liniaJoc[i]=0;
}


//===================================================================================
// NOM: GenerarPesa
//===================================================================================
// DESCRIPCI�: Genera aleat�riament un dels tipus de peces
//===================================================================================
// PAR�METRES:
// - pesa: taula de 3 posicions per guardar els valors de la pe�a generada
// - maxTamany: tamany m�xim de la pe�a que es pot generar perqu� c�piga en els espais 
// lliures de la l�nia de joc
//===================================================================================
// RETORN: Tipus de la pe�a generada
//===================================================================================
int GenerarPesa(int *pesa,int maxTamany)
{
	int tipusPesa,i;

	if (maxTamany>1)
		tipusPesa=NumAleatori(maxTamany);
	else
		tipusPesa=1;

	switch(tipusPesa)
	{
		// pe�a P �������������������������������������������������������������������
		case 1:	
			for (i=0; i<TamanyPeces; i++)
				pesa[i]=P[i];
            break;
		// pe�a S �������������������������������������������������������������������
		case 2:
			for (i=0; i<TamanyPeces; i++)
				pesa[i]=S[i];
			break;
		// pe�a L �������������������������������������������������������������������
		case 3:
			for (i=0; i<TamanyPeces; i++)
				pesa[i]=L[i];
			break;
	}
	return tipusPesa;
}


//===================================================================================
// NOM: Jugar
//===================================================================================
// DESCRIPCI�: Permet jugar una partida, des de l'inici fins al final
//===================================================================================
// PAR�METRES:
// - tauler: estructura que controla la visualitzaci� per pantalla
// - nivellInicial: nivell inicial de dificultat del joc
//===================================================================================
// RETORN: Puntuaci� aconseguida al final de la partida
//===================================================================================
int Jugar(pantalla_t *tauler,int nivell)
{
	int nPunts,nVides,nLliures,maxTamanyPesa,posicioFinal,colisio,puntsAnteriors;
	int nCiclesRotacio;
	int liniaJoc[NCol];
	int pesa[TamanyPeces];
	char jugador[MAX_NOM]="jugador";

	system("cls");
	MostraTauler(tauler);
	InicialitzarLiniaJoc(liniaJoc);
	nCiclesRotacio=N_CICLES_ROTACIO;
	nPunts=0;
	puntsAnteriors=0;
	nVides=MAX_VIDES;
	maxTamanyPesa=TamanyPeces;
	MostraPartida(tauler,jugador,nPunts,nVides);

	do
	{
		// Codi a completar: Generar la pe�a

		posicioFinal=ControlCaigudaPesa(pesa,nivell,liniaJoc,&nCiclesRotacio,tauler);
		if (posicioFinal>=-1)
		{
			EsborraLinia(tauler,liniaJoc);
			colisio=ColocarPesa(liniaJoc,posicioFinal,pesa);
			MostraLinia(tauler,liniaJoc);

			if (colisio)
			{
				// Codi a completar: col�lisi� de la pe�a amb peces ja colocades a la l�nia de joc
			}
			else
			{
				nPunts+=PUNTS_PESA;
				nLliures=comprovarLinia(liniaJoc);
				if (nLliures==0)
				{
					nPunts+=PUNTS_LINIA;
					InicialitzarLiniaJoc(liniaJoc);
					nCiclesRotacio=N_CICLES_ROTACIO;
					EsborraLinia(tauler);
					maxTamanyPesa=TamanyPeces;
				}
				else
					if (nLliures<maxTamanyPesa)
						maxTamanyPesa=nLliures;
				ComprovarNivell(puntsAnteriors,nPunts,&nivell);
				puntsAnteriors=nPunts;
			}
		}

		// Codi a completar: mostrar la puntuaci� i el n� de vides per pantalla

	}
	while ((posicioFinal>=-1) && (nVides>0));
	return nPunts;
}