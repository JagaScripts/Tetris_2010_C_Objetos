
#ifndef TETRIS
#define TETRIS

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "rutines_w.c"
#include "GestioPuntuacions.c"
#include "GestioJoc.c"
#include "Peces.h"

// Constants pel Men� Principal
#define NIVELL '1'
#define JUGAR  '2'
#define PUNTUACIONS '3'
#define SORTIR '4'
#define TECLA_1 49								// PARA LA TECLA	1
#define TECLA_2 50								//		"			2
#define TECLA_3 51								//		"			3
#define TECLA_4 52								//		"			4	
#define TECLA_S_MINUS 83						//		"			s
#define TECLA_S_MAYUS 115						//		"			S

// Constants pel Nivell de dificultat
#define N_PRINCIPIANT 1
#define N_MITJA 2
#define N_EXPERT 3

char MostrarMenu();
int SeleccionarNivell();

#endif