#include <conio.h>

#include "rutines.h"




//===================================================================================
// NOM: Gotoxy
//===================================================================================
// DESCRIPCI�: Permet posar el cursor en una posicio donada
//===================================================================================
// PAR�METRES:
// - c: columna de la pantalla
// - f: fila de la pantalla
// - screen: estructura que controla la visualitzaci� per pantalla
//===================================================================================
void gotoxy(int c,int f,HANDLE screen)
{
 COORD position = { c, f };
 SetConsoleCursorPosition(screen,position);
}


//===================================================================================
// NOM: TextColor
//===================================================================================
// DESCRIPCI�: Funcio per canviar els colors de texte i fons de la consola DOS
//===================================================================================
// PAR�METRES:
// - fontcolor: color del text
// - backgroundcolor color del fons
// - screen: estructura que controla la visualitzaci� per pantalla
//===================================================================================
void TextColor(int fontcolor,int backgroundcolor,HANDLE screen)
{
   unsigned short color_attribute;
   color_attribute = backgroundcolor;
   color_attribute = _rotl(color_attribute,4) | fontcolor;
   SetConsoleTextAttribute(screen,color_attribute);
}

//===================================================================================
// NOM: InitPantalla
//===================================================================================
// DESCRIPCI�: Funcio que inicialitza estructures per visualitzar el tauler de joc
//===================================================================================
// PAR�METRES:
// - tauler: estructura que controla la visualitzaci� per pantalla
//===================================================================================
void InitPantalla( pantalla_t *tauler )
{
	CONSOLE_CURSOR_INFO ConCurInf;
	tauler->screen = GetStdHandle(STD_OUTPUT_HANDLE);   
	
	// ------------------------------------------------------------------------------
	// Les peces estan representades dins la matriu peces, i cadascuna esta codificada
	// amb un valor entre 0 i 7, que coincideix amb l'index del seg�ent vector que 
	// n'especifica el color.
	// 
	// index 0 -> No hi ha pe�a.
	// index 1 -> Color de fons de la pe�a P.
	// index 2 -> Color de fons de la pe�a S.
	// index 3 -> Color de fons de la pe�a L.

	
	tauler->CL[0] = BLACK;
    tauler->CL[1] = LIGHTMAGENTA;
    tauler->CL[2] = GREEN;
    tauler->CL[3] = YELLOW;
	
	
	// ------------------------------------------------------------------------------
	// Amaguem el cursor:	         
	ConCurInf.dwSize = 10; 
    ConCurInf.bVisible = FALSE;
    SetConsoleCursorInfo(tauler->screen,&ConCurInf);

	// ------------------------------------------------------------------------------
	// Iniciem el Joc
	printf("Maximitza la pantalla i prem una tecla....");
	getch();
	system("cls");
}


//===================================================================================
// NOM: MostraTauler
//===================================================================================
// DESCRIPCI�: Funcio que permet mostrar el tauler de joc.
//===================================================================================
// PAR�METRES:
// - tauler: estructura que controla la visualitzaci� per pantalla
//===================================================================================
void MostraTauler( pantalla_t *tauler)
{
	// ------------------------------------------------------------------------------
	// FORMAT TAULELL:
	//
	// El vector FT (Format Taulell) cont� a cada posici� el codi d'un determinat 
	// car�cter ASCII. Si modifiquem els valors  d'aquest vector, l'aparen�a del
	// taulell, tamb� variar�.
	//	
	// index 0 -> Contorn lateral.
	// index 1 -> Cantonada inferior esquerre.
	// index 2 -> Cantonada inferior dreta.
	// index 3 -> Contorn inferior.
	int FT[4]={186,200,205,188};	
	
	// ------------------------------------------------------------------------------
	// Altres variables:
	int f,c;
	HANDLE  screen= tauler->screen;
	
	TextColor(LIGHTGREY,BLACK,screen);
	// ------------------------------------------------------------------------------	
	// pintem les col�lumnes
	for(f=0;f<NFil;f++)
	{
		gotoxy(DespC,DespF+f,screen);
		printf("%c",FT[0]);

		gotoxy(DespC+NCol+1,DespF+f,screen);		
		printf("%c",FT[0]);
	}

    //pintem la cantonada esquerra
	gotoxy(DespC,DespF+NFil,screen);
	printf("%c",FT[1]);

    //pintem la barra d'abaix
	for(c=0;c<NCol;c++)
		printf("%c",FT[2]);
	
	//pintem la cantonada dreta
	printf("%c",FT[3]);

	// ------------------------------------------------------------------------------	
	// pintem les linies del menu
	gotoxy(DespC,DespF+NFil+2,screen);
	for(c=0;c<NCol+2;c++)
		printf("%c",FT[2]);

	gotoxy(DespC,DespF+NFil+4,screen);
	for(c=0;c<NCol+2;c++)
		printf("%c",FT[2]);

}


//===================================================================================
// NOM: MostraMSG
//===================================================================================
// DESCRIPCI�: Funcio que permet mostrar un missatge sobre el 
// tauler de joc. 
//===================================================================================
// PAR�METRES:
// - tauler: estructura que controla la visualitzaci� per pantalla
// - msg: cadena de car�cters amb el missatge a visualitzar
//===================================================================================
// RETORN: enter amb el codi de la tecla que s'ha pressionat despr�s de mostrar el missatge
//===================================================================================
int MostraMSG(pantalla_t *tauler, char *msg)
{
	HANDLE screen = tauler->screen;
	int i,L,C,CC,CF;

	L=strlen(msg); // Longitud de la cadena.
	C=(int)ceil(L/2);  // Punt mig de la cadena.

	CF=(int)floor(NFil/2);
	CC=(int)floor(NCol/2);

	TextColor(RED,BLACK,screen);
	gotoxy(DespC+CC-C,DespF+CF-1,screen);
	for(i=0;i<L+2;i++)
		printf(" ");
	gotoxy(DespC+CC-C,DespF+CF,screen);
	printf(" %s ",msg);
	gotoxy(DespC+CC-C,DespF+CF+1,screen);
	for(i=0;i<L+2;i++)
		printf(" ");
	
	return getch();
}


//===================================================================================
// NOM: MostraPesa
//===================================================================================
// DESCRIPCI�: Funcio que permet mostrar una pe�a en una posici� del tauler. 
//===================================================================================
// PAR�METRES:
// - tauler: estructura que controla la visualitzaci� per pantalla
// - peca: array de 3 posicions amb els valors de la pe�a
// - f: fila de pantalla on posar la pe�a
// - c: columna de la pantalla on posar la pe�a (extrem esquerre de la pe�a)
//===================================================================================
void MostraPesa( pantalla_t *tauler,  int peca[TamanyPeces], int f, int c)
{

	int *CL= tauler->CL;

	// ------------------------------------------------------------------------------
	// Altres variables:
	int i;
	HANDLE  screen= tauler->screen;

	for(i=0;i<TamanyPeces;i++)
	{
		if (peca[i]!=0)
		{
			gotoxy(DespC+c+i+1,DespF+f,screen);			
			TextColor(CL[peca[i]],BLACK,screen);
			printf("%c",177);
		}
    }
}

//===================================================================================
// NOM: EsborraPesa
//===================================================================================
// DESCRIPCI�: Funcio que permet esborrar una pe�a d'una posici� del tauler. 
//===================================================================================
// PAR�METRES:
// - tauler: estructura que controla la visualitzaci� per pantalla
// - peca: array de 3 posicions amb els valors de la pe�a
// - f: fila de pantalla on est� la pe�a
// - c: columna de la pantalla on est� la pe�a (extrem esquerre de la pe�a)
//===================================================================================
void EsborraPesa( pantalla_t *tauler,  int peca[TamanyPeces], int f, int c)
{

	int *CL= tauler->CL;

	// ------------------------------------------------------------------------------
	// Altres variables:
	int i;
	HANDLE  screen= tauler->screen;

	for(i=0;i<TamanyPeces;i++)
	{
		if (peca[i]!=0)
		{
			gotoxy(DespC+c+i+1,DespF+f,screen);			
			TextColor(CL[0],BLACK,screen);
			printf("%c",177);
		}
    }
}


//===================================================================================
// NOM: MostraPartida
//===================================================================================
// DESCRIPCI�: Mostra per pantalla el nom del jugador, la puntuaci� actual i el n� de 
// vides
//===================================================================================
// PAR�METRES:
// - tauler: estructura que controla la visualitzaci� per pantalla
// - Jugador: cadena de car�cters amb el nom del jugador
// - Puntuacio: punts del jugador
// - Vides: n� de vides del jugador
//===================================================================================
void MostraPartida(pantalla_t* tauler, char *Jugador, int Puntuacio, int Vides)
{
	HANDLE  screen= tauler->screen;	
	
	// Mostrem el nom del jugador i la puntuaci�:
	gotoxy(DespC+1,DespF+NFil+1,screen);
	TextColor(LIGHTGREY,BLACK,screen);
	printf("PLAYER: ");
	TextColor(RED,BLACK,screen);
	printf("%s\n",Jugador);
	
	
	gotoxy(DespC+1,DespF+NFil+3,screen);
	TextColor(LIGHTGREY,BLACK,screen);
	printf("SCORE: ");
	TextColor(RED,BLACK,screen);
	printf(" %d VIDA: %d\n",Puntuacio,Vides);
	TextColor(LIGHTGREY,BLACK,screen);
}

//===================================================================================
// NOM: MostraLinia
//===================================================================================
// DESCRIPCI�: Funcio que permet mostrar la l�nia de peces a baix del tauler
//===================================================================================
// PAR�METRES:
// - tauler: estructura que controla la visualitzaci� per pantalla
// - linia: array amb els valors de la pe�a colocata a la l�nia inferior del tauler
//===================================================================================
void MostraLinia( pantalla_t *tauler, int linia[NCol])
{
     int j;
    int *CL= tauler->CL;

	// ------------------------------------------------------------------------------
	// Dibuixem les peces:
    gotoxy(DespC+1,DespF+NFil-1,tauler->screen);
	for(j=0;j<NCol;j++)
	{         			
         TextColor(CL[linia[j]],BLACK,tauler->screen);
         printf("%c",177);
    }

}


//===================================================================================
// NOM: EsborraLinia
//===================================================================================
// DESCRIPCI�: Funcio que permet esborrar la l�nia de peces a baix del tauler
//===================================================================================
// PAR�METRES:
// - tauler: estructura que controla la visualitzaci� per pantalla
//===================================================================================
void EsborraLinia( pantalla_t *tauler)
{
     int j;
    int *CL= tauler->CL;

	// ------------------------------------------------------------------------------
	// Dibuixem les peces:
    gotoxy(DespC+1,DespF+NFil-1,tauler->screen);
	for(j=0;j<NCol;j++)
	{         			
         TextColor(CL[0],BLACK,tauler->screen);
         printf("%c",177);
    }

}
