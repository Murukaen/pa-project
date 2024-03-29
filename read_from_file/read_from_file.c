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
#include "../san_conv/san_conv.h"
#include "../update_state/update_state.h"

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
void Read_openings(){

		FILE *f=fopen("Database/database.txt","r");
		int i,k,j;
		UCHAR ec=get_engine_col();
		char *elem,*buffer;
		MOVE m;
		elem=(char*)malloc(10*sizeof(char));	//elem va fii fiecare mutare in parte de pe linie
		buffer=(char*)malloc(1000*sizeof(char)); //buffer va fii fiecare linie in parte
		strcpy(elem,"");
		STATE Sinit;
		Sinit=Read_initial_state();//functie care returneaa o tabla la inceput de joc
		state_print(Sinit,stdout);
		j=0;
		while(j<=5)	//citesc doar primele 100 de linii din fisier pentru etapa3
		{
			j++;    //j reprezinta linia la care ma aflu
			fgets(buffer,1000,f); //citesc linia

			/*initializari pentru fiecare inceput de linie */
			k=0;
			ec=get_engine_col();

			/*parcurgere buffer*/
			for(i=0;i<strlen(buffer)-1;i++)
			{
					
				if(buffer[i]==' ' || i==strlen(buffer)-2) 
				{
				 	/*daca gasesc spatiu sau am ajuns la sfarsitul liniei pana in \n*/
				 	/*inversez culoarea on move pentru fiecare move nou*/
					if(ec==0) 
						ec=1;
					else ec=0;
					/*fac trimm tuturor caracterelor necorespunzatoare*/
					elem[k]='\0'; 
					
					printf("dimens %d string %s-\n",k,elem);
					fflush(stdout);
					
					/*m reprezinta moveul convertit string->SAN*/
					m=SAN_to_Move(Sinit,elem);
					/*setez in move culoarea care face mutarea*/
					move_set_what_col(m,ec);
					/*printare mutare*/
					move_print(m,stdout); 
				//	update_state(Sinit,SAN_to_Move(Sinit, elem)); //fac update la starea curenta cu mutarea curenta
				//	tt_add_opening ( Sinit ); //adaug starea rezultata in hash

					k=0;
				//	ST_set_col_on_move(Sinit,ec);
					printf("\nsucki mucki suge curu\n");
					fflush(stdout);
					
					/*sterg continut elem*/
					strcpy(elem,"");
				}
				/*formez fiecare mutare in parte*/
				else
					elem[k++]=buffer[i];
				
			}
		//	update_state(Sinit,SAN_to_Move(Sinit, elem)); //fac update pentru ultimul element de pe linie
								      //care nu va intra in iful forului de mai sus

			/*adaug in hash*/
			tt_add_opening ( Sinit );
			/*refac starea la starea initiala pentru a trece la urmatoarea linie*/
			Sinit=Read_initial_state(); 
			strcpy(elem,"");
		}
		fclose(f);
		return;

}





