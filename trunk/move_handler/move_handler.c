/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "move_handler.h"
#include "../Flags/flags.h"
#include "../Util/util.h"

#define NR_A_PO ( NR_A_P + BMAP_TP_OFF )

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */


MOVE determine_move ( STATE st_next) {

	STATE st_prev = cur_state_get();
	
	UCHAR my_pieces = f_ENG_COL;    //culoarea engineului

	UCHAR his_pieces = ~ my_pieces; //culoarea adversarului

	BITMAP my_pic_prev = ST_get_bitmap (st_prev, my_pieces ); //bitmapul starii mele curente

	BITMAP my_pic_next = ST_get_bitmap (st_next, my_pieces ); //bitmapul starii mele urmatoare
	
	MOVE mov = move_new ();	
	
	mov->what_col=f_ENG_COL;//setez in mutare culoarea on move

	List list_poz_moved_p;
	// Here list_poz_moved_p is the list with the initial pozitions of the moved piece

	//vector care seteaza 1 in my_pieces_moved[] daca se muta piesa care are indicele respectiv
	int my_pieces_moved [ NR_A_PO ];
	
	P_LOC loc;
	LOC poz_start;

	BITMAP where_moved; //bitmapul care determina pozitia in care se va muta piesa

	int i;
	
	for (i=BMAP_TP_OFF;i<NR_A_PO;++i) 
	
			my_pieces_moved [i] = BM_Compare_BMAPs ( my_pic_prev & ST_get_bitmap(st_prev, i )  , my_pic_next & ST_get_bitmap ( st_next , i ) );
		

	/*am setat in mov tot ce trebuie pentru rocada cu urmatoarele exceptii:
	 *
	 * alin: sa modifici caracterul special pentru diferitele tipuri de rocade in mov->m_tag (eu nu l'am stiut)
	 * in mov->set_p_rock am pus locatia turei de dupa rocada
	 */
	int which_piece;//which_piece va retine tipul piesei este in mutare de la o stare la alta

	if ( my_pieces_moved [ T_K ] && my_pieces_moved [ T_R ] ) {
		
			LOC lcastle; //locatia turei pe tabla

			mov->p_tag_pro=0; //nu se promoveaza nici o piesa


			which_piece=T_K;
			move_set_p_tag (mov , which_piece); //setez regele la mutare

			list_poz_moved_p = ST_get_List_Table_P ( st_prev , my_pieces , which_piece );
			//lista pentru starea curenta

			for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; )

						if (  ST_get_tag_Table_W ( st_next , LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == T_NA ) {

								move_set_poz_src ( mov ,  *loc);  // setez in mutare pozitia de plecare

								break;
						}
			
			where_moved = (~ ( my_pic_prev & ST_get_bitmap (st_prev, which_piece ) ) ) & ( my_pic_prev & ST_get_bitmap (st_next, which_piece ) ) );

			list_poz_moved_p = ST_get_List_Table_P ( st_next , my_pieces , which_piece );
			//lista pentru starea urmatoare

			for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; )

					if ( BM_Make_coord ( LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == where_moved ) {

							move_set_poz_dst ( mov ,  *loc); //setez in mutare pozitia finala a piesei

							if((mov->poz_dst->col - mov->poz_src->col)==2)	//rocada mica
							{
								mov->m_tag='m'; //nu stiu ce indicator are special moveul rocada mica..ma corecteaza alin

								lcastle->col=mov->poz_dst->col -1; //se afla pe coloana regelui la destinatie -1

								lcastle->row=mov->poz_dst->row;//se afla pe aceeasi linie cu regele,indiferent de culoare

								move_set_p_rock(mov,lcastle);//setez in move locatia finala a turei


							}
							else	//rocada mare
							{
								mov->m_tag='M';//nu stiu ce indicator are rocada mare,ma corecteaza alin

								lcastle->col=mov->poz_src->col;//se afla pe coloana sursa a regelui

								lcastle->row=mov->poz_dst->row;//se afla pe linia regelui,indiferent de culoare

								move_set_p_rock(mov,lcastle);//setez in move locatia finala a turei
							}

							break;
					}


			return 0;
	}
	
	if ( my_pieces_moved [T_P] ) {
		
		// TODO Mutare pion
		return 0;
	}
	

	/*----------------------------------------------------------------------------------------------------*/
	/*-------------------------------aici incep mutarile fara exceptii------------------------------------*/


	mov->p_tag_pro=0; //nu se promoveaza nici o piesa

	for ( i=BMAP_TP_OFF ; i< NR_A_PO ; ++i )
		if ( my_pieces_moved[i] ) which_piece = i;
	
	move_set_p_tag (mov , which_piece);  // setez in mutare tag_piece
	
	list_poz_moved_p = ST_get_List_Table_P ( st_prev , my_pieces , which_piece );
	
	for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; )
		
			if (  ST_get_tag_Table_W ( st_next , LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == T_NA ) {
				 
					move_set_poz_src ( mov ,  *loc);  // setez in mutare pozitia de plecare
					
					break;
			}
			
	
	where_moved = (~ ( my_pic_prev & ST_get_bitmap (st_prev, which_piece ) ) ) & ( my_pic_prev & ST_get_bitmap (st_next, which_piece ) ) );
	
	list_poz_moved_p = ST_get_List_Table_P ( st_next , my_pieces , which_piece );
	//lista pentru starea urmatoare


	for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; ) 
		
			if ( BM_Make_coord ( LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == where_moved ) {
				
					move_set_poz_dst ( mov ,  *loc);
					
					break;
			}
			
	move_set_m_tag ( mov, T_MOVE_NA );
	
	return mov;
}
	
	
	
					
	        
	
