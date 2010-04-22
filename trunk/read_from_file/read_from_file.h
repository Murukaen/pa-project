/* General description :
 *
 */

#ifndef READ_FROM_FILE_H
#define READ_FROM_FILE_H

/* ----- System #includes ----- */
#include <stdio.h>

/* ----- Local #inlcudes ----- */
#include "../bitmap/bitmap.h"
#include "../state/state.h"
#include "../state_generator/state_generator.h"

/* ---- Macro #define ---- */


/* --- Types --- */

/* --- Procedures --- */

/*citeste din fisierul All_moves.in toate mutarile posibile pentru toate piesele
 * (in afara de pioni) in vectorii dati ca parametru.
 * Ordinea parametrilor este : fisierul de intrare,rege, regina,tura,nebun,cal
 */
void Read_all_possible_moves(BITMAP[5][8][8]);

void print_all_possible_moves(FILE * ,BITMAP[5][8][8]);

/* citeste din fisierul Initial_positions pozitiile initiale ale pieselor
 * in fisier sunt scrise bitmapurile pieselor,in ordinea:
 * piese albe,piese negre,regi regine,ture,nebuni,caii,pionii 
 */
STATE Read_initial_state( void );

/* citeste din fisierul de database si adauga la hashtable*/
/*are argument fisierul din care citeste*/
void Read_openings(FILE *);


#endif
