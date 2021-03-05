#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


#include "tetris.h"
#include "rutines.h"
#include "GestioPuntuacions.h"
#include "GestioJoc.h"
#include "Peces.h"

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

		// Codi a completar

	}
	while (opcio != SORTIR);
	
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
