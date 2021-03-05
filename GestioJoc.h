#ifndef GESTIOJOC
#define GESTIOJOC
#define NUM_PECES 3  
#define MAX_VIDES 3

// Temps m�xim d'espera a cada moviment del bucle per permetre la visualitzaci� de la pe�a
// en el nivell de dificultat m�s baix
#define TEMPS_MAX_ESPERA 150

// N� de moviments de teclat que es poden fer per cada moviment vertical de la pe�a 
// en el nivell de dificultat m�s baix
#define N_CICLES_TECLAT 6

// N� de moviments de la pe�a que impliquen rotaci� de la l�nia de joc
#define N_CICLES_ROTACIO 10
//===================================================================================
// Definici� de tecles
#define KEY_UP 72
#define KEY_DOWN_P 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_SPECIAL 224

// L�mits de punts per cadascun dels nivells
#define PUNTS_CANVI_NIVELL	1000
#define NIVELL_MAXIM 5

// Increment de punts
#define PUNTS_PESA	10
#define PUNTS_LINIA	100



int NumAleatori(int mx);
void ComprovarNivell(int puntsAnteriors,int puntsActuals,int *nivell);
int comprovarLinia(int *liniaJoc);
int ColocarPesa(int *liniaJoc,int posicioFinal,int *pesa);
void MovimentDreta(int *pesa,int *columna);
void MovimentEsquerra(int *pesa,int *columna);
int ControlTeclat(int *pesa,int *fila,int *columna,pantalla_t *tauler);
void RotarLiniaJoc(int *liniaJoc,pantalla_t *tauler);
int ControlCaigudaPesa(int *pesa,int nivell,int *liniaJoc,int *nCiclesRotacio,pantalla_t *tauler);
void InicialitzarLiniaJoc(int liniaJoc[]);
int GenerarPesa(int *pesa,int maxTamany);
int Jugar(pantalla_t *tauler,int nivell);

#endif