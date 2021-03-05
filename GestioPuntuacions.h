#ifndef GESTIONPUNTUACIONES
#define GESTIONPUNTUACIONES

#define MAX_NOM 50
#define MAX_DATA 11

// Definici� del tipus Jugador
typedef struct
{
	char nom[MAX_NOM];
	int puntuacio;
	char data[MAX_DATA];
} TipusJugador;

#define MAX_PUNTUACIONS 5

int LlegirPuntuacions(TipusJugador puntuacions[]);
void DemanarDadesJugador(TipusJugador *jugador);
int ActualitzarPuntuacions(TipusJugador puntuacions[],int *nPuntuacions,int punts);
void MostrarPuntuacions(TipusJugador puntuacions[],int nPuntuacions);
void EscriurePuntuacions(TipusJugador puntuacions[],int nPuntuacions);

#endif