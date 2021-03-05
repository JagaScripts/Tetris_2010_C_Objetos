#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "GestioPuntuacions.h"


//===================================================================================
// NOM: LlegirPuntuacions
//===================================================================================
// DESCRIPCI�: Funcio que llegeix les puntuacions del fitxer "Puntuacions.txt" i les 
// guarda a una taula.
//===================================================================================
// PAR�METRES:
// - puntuacions: taula per guardar les puntuacions que es llegeixen
//===================================================================================
// RETORN: nombre de puntuacions que s'han llegit del fitxer (m�xim 5)
//===================================================================================
int LlegirPuntuacions(TipusJugador puntuacions[])
{
	FILE *fitxer;
	int nPuntuacions = 0;
	char nom[MAX_NOM];

	fitxer = fopen("Puntuacions.txt","r");
	if (fitxer != NULL)
	{
		fgets(nom,MAX_NOM,fitxer);
		while ((!feof(fitxer))&&(nPuntuacions<MAX_PUNTUACIONS))
		{
			nom[strlen(nom)-1]='\0';
			strcpy(puntuacions[nPuntuacions].nom,nom);
			fscanf(fitxer,"%d\n",&puntuacions[nPuntuacions].puntuacio);
			fgets(puntuacions[nPuntuacions].data,MAX_DATA,fitxer);
			nPuntuacions++;
			fgets(nom,MAX_NOM,fitxer);
		}
		fclose(fitxer);
	}
	return nPuntuacions;
}


//===================================================================================
// NOM: DemanarDadesJugador
//===================================================================================
// DESCRIPCI�: Demana el nom del jugador i la data de la partida
//===================================================================================
// PAR�METRES:
// - jugador: registre per guardar les dades
//===================================================================================
void DemanarDadesJugador(TipusJugador *jugador)
{
	system("cls");
	printf ("Introdueix el nom del jugador: ");
	gets (jugador->nom);
	printf ("Introdueix la data de la partida (dd/mm/aaaa): ");
	gets (jugador->data);
}

//===================================================================================
// NOM: ActualitzarPuntuacions
//===================================================================================
// DESCRIPCI�: Compara una nova puntuaci� amb les existents i si �s 
// millor que alguna d'elles l'afegeix a la taula de puntuacions seguint l'ordre 
//===================================================================================
// PAR�METRES:
// - puntuacions: taula que guarda les puntuacions
// - nPuntuacions: N� de registres a la taula de puntuacions. Pot ser modificat dins
//   del procediment
// - punts: Nova puntuaci� que es vol afegir a la taula
//===================================================================================
// RETORN: 1 si s'ha afegit la nova puntuaci�. 0 si no s'ha afegit
//===================================================================================
int ActualitzarPuntuacions(TipusJugador puntuacions[],int *nPuntuacions,int punts)
{
	int i,j,afegit;

	afegit = (*nPuntuacions==0);
	i = 0;
	while ((!afegit) && (i<*nPuntuacions))
	{
		if (punts > puntuacions[i].puntuacio)
			afegit = 1;
		else
			i++;
	}
	if ((afegit)||(*nPuntuacions<MAX_PUNTUACIONS))
	{
		if (*nPuntuacions < MAX_PUNTUACIONS)
			(*nPuntuacions)++;
		// Despla�ar totes les puntuacions menors una posici� dins de la taula
		j=*nPuntuacions-1;
		while (j>i)
		{
			puntuacions[j] = puntuacions[j-1];
			j--;
		}
		puntuacions[i].puntuacio = punts;
		DemanarDadesJugador(&puntuacions[i]);
	}
	return afegit;
}

//===================================================================================
// NOM: MostrarPuntuacions
//===================================================================================
// DESCRIPCI�: Mostra per pantalla la llista de millors puntuacions
//===================================================================================
// PAR�METRES:
// - puntuacions: taula que guarda les puntuacions
// - nPuntuacions: N� de registres a la taula de puntuacions. 
//===================================================================================
void MostrarPuntuacions(TipusJugador puntuacions[],int nPuntuacions)
{
	int i;

	system("cls");
	printf ("LLISTA DE PUNTUACIONS\n");
	for (i=0; i<nPuntuacions; i++)
		printf ("%d.- %s %d %s\n", i+1, puntuacions[i].nom, puntuacions[i].puntuacio, puntuacions[i].data);
	printf ("Prem una tecla per continuar");
	getch();
}

//===================================================================================
// NOM: EscriurePuntuacions
//===================================================================================
// DESCRIPCI�: Funcio que guarda les puntuacions al fitxer "Puntuacions.txt" 
//===================================================================================
// PAR�METRES:
// - puntuacions: taula per guardar les puntuacions que es llegeixen
// - nPuntuacions: N� de registres a la taula de puntuacions.
//===================================================================================
void EscriurePuntuacions(TipusJugador puntuacions[],int nPuntuacions)
{
	FILE *fitxer;
	int i;

	// Codi a completar

	if (fitxer != NULL)
	{
		for (i=0; i<nPuntuacions; i++)
		{
			fputs(puntuacions[i].nom,fitxer);
			fprintf(fitxer,"\n");			
			fprintf(fitxer,"%d\n",puntuacions[i].puntuacio);
			fputs(puntuacions[i].data,fitxer);
		}
	}
	fclose(fitxer);
}
