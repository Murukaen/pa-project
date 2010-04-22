/* General description :
 *
 */

/* ----- System #includes ----- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ----- Local #inlcudes ----- */
#include "../state/state.h"
#include "../bitmap/bitmap.h"
#include "read_from_file.h"
#include "../list/list.h"
#include "../Util/util.h"
#include "../Flags/flags.h"
#include "../transp_table/transp_table.h"

/* ---- Macro #define ---- */
#define FILE_INITIAL_STATE "Database/initial_state.in"

/* --- Types --- */

/* --- Procedures --- */

void Read_all_possible_moves(BITMAP Moves[5][8][8]) {

	FILE * fin = fopen("Database/All_moves.in", "rb");
	if (fin == NULL) {
		printf("Eroare la deschiderea fisierului All_moves.in");
		exit(0);
	}

	int i, j;

	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			
			fread(&Moves[0][i][j], 8, 1, fin);
			fread(&Moves[1][i][j], 8, 1, fin);
			fread(&Moves[2][i][j], 8, 1, fin);	
			fread(&Moves[3][i][j], 8, 1, fin);
			fread(&Moves[4][i][j], 8, 1, fin);	
		}
	}

	fclose(fin);
}

STATE Read_initial_state( void ) {

	/* Read from file */
	FILE *fin = fopen (FILE_INITIAL_STATE , "r");
	STATE S = state_read ( fin ); // !!! Initial color on move is white
	fclose(fin);
	/* END Read from file */

	/* Return read State */
	return S;
}

void print_all_possible_moves(FILE * fout, BITMAP Moves[5][8][8]) {

	int i, j, k;
	char text[10];
	for (i = 0; i < 5; i++) {
		
		tag_to_text ( i + PIECES_OFF , text );
		for (j = 0; j < 8; j++) {
			for (k = 0; k < 8; k++) {
				
				fprintf(fout ,"%s (%c %c)\n" , text , row_to_letter(j) , col_to_letter(k) );
				BM_print(Moves[i][j][k], fout);
				fprintf(fout, "\n");
			}
		}
	}
}
void Read_openings(FILE *f){

	/*  TODO:
	 *  State new_initial_state(void) care returneaza o tabla la inceputul jocului
	 *  void update_state(State,SAN_to_move(char *)) care face update la orice stare State cu mutarea char*
	 *  void tt_add_opening(State) adauga State in hash (daca nu mai exista deja in hash)
	 */


		int i,k=0,j=0,h;
		char *elem,*buffer;
		elem=(char*)malloc(10*sizeof(char));	//elem va fii fiecare mutare in parte de pe linie
		buffer=(char*)malloc(1000*sizeof(char)); //buffer va fii fiecare linie in parte
		strcpy(elem,"");
		State Sinit;
		Sinit=new_initial_state();//functie care returneaa o tabla la inceput de joc

		while(j<=100)	//citesc doar primele 100 de linii din fisier pentru etapa3
		{
			j++;
			fgets(buffer,1000,f); //citesc linia
			k=0;
			for(i=0;i<=strlen(buffer);i++)
			{
				if(buffer[i]==' ' || buffer[i]=="\n") {
									update_state(Sinit,SAN_to_move(elem)); //fac update la starea curenta cu mutarea curenta
									tt_add_opening(Sinit); //adaug starea rezultata in hash
									k=0;
									strcpy(elem,"");
									}
				else
					elem[k++]=buffer[i];
			}
			update_state(Sinit,SAN_to_move(elem)); //fac update pentru ultimul element de pe linie
								//care nu va intra in iful forului de mai sus
			tt_add_opening(Sinit); //adaug in hash
			Sinit=new_initial_state(); //refac starea la starea initiala pentru a trece la urmatoarea linie
			k=0;
			strcpy(elem,"");
		}

}





