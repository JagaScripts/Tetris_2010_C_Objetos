#include "tetris.h"


//===================================================================================
int main(int argc, char **argv)
{
	pantalla_t tauler;
	TipusJugador puntuacions[MAX_PUNTUACIONS];
	int nPuntuacions;
	int nivellInicial,punts,afegit;
	char opcio;
	
	nPuntuacions = LlegirPuntuacions(puntuacions);

	InitPantalla(&tauler);
	srand((unsigned)time(NULL));

	nivellInicial = N_MITJA;

	do
	{
		opcio = MostrarMenu();

		switch(opcio)						//PARA CADA CASO
		{
			case TECLA_1:
				system("cls");
				LlegirPuntuacions(puntuacions);
				MostrarPuntuacions(puntuacions,nPuntuacions);
				system("cls");
				break;
			case TECLA_2:
				system("cls");
				nivellInicial=SeleccionarNivel();
				system("cls");
				break;
			case TECLA_3:
				punts=Jugar(&tauler, nivellInicial);
				ActualitzarPuntuacions(puntuacions,nPuntuacions,punts);
				EscriurePuntuacions(puntuacions, nPuntuacions);
				system("cls");
				break;
			case TECLA_4:
				system("cls");
				opcio=PreguntaSalir();
				system("cls");
				break;
			case TECLA_S_MINUS:
			case TECLA_S_MAYUS:
				opcio=0;
				system("cls");
				break;
			default :
				system("cls");
				break;
		}

	}while (opcio != SORTIR);
	
	EscriurePuntuacions(puntuacions,nPuntuacions);

    return 0;
}

//===================================================================================
// NOM: MostrarMenu
//===================================================================================
// DESCRIPCI�: Mostra el men� i demana quina opci� es vol seleccionar. Nom�s retorna 
// quan es selecciona una opci� v�lida
//===================================================================================
// PAR�METRES:
//===================================================================================
// RETORN: opci� seleccionada
//===================================================================================
char MostrarMenu()
{
	char opcio;

	do
	{
		system("cls");
		printf ("MENU PRINCIPAL\n");
		printf ("1.- Seleccionar nivell dificultat\n");
		printf ("2.- Iniciar partida\n");
		printf ("3.- Mostra puntuacions\n");
		printf ("4.- Sortir\n");
		printf ("\nSelecciona una opcio\n");
		opcio = getch();
	} while ((opcio<'1')||(opcio>'4'));
	return opcio;
}

//===================================================================================
// NOM: SeleccionarNivell
//===================================================================================
// DESCRIPCI�: Permet seleccionar el nivell de dificultat inicial del joc. Nom�s 
// retorna si es selecciona un nivell v�lid
//===================================================================================
// PAR�METRES:
//===================================================================================
// RETORN: nivell seleccionat
//===================================================================================
int SeleccionarNivell()
{
	int nivell;
	do
	{
		system("cls");
		printf ("SELECCIONA EL NIVELL DE DIFICULTAT\n");
		printf ("1.- Principiant\n");
		printf ("2.- Nivell mitja\n");
		printf ("3.- Expert\n");
		nivell = getch()-'0';
	} while ((nivell<1)||(nivell>3));
	return nivell;
}

//Funci�n que pregunta si quieres salir y devueve la tecla pulsada.
int PreguntaSalir()
{
int Accion;
	printf("Estas segur que vols sortir? \n");
	printf("Prem s per si y n per no\n");
	fflush(stdin);									
	Accion=getch();
	
	return Accion;
}