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
	
	UCHAR my_pieces = f_ENG_COL;
	UCHAR his_pieces = ~ my_pieces;
	BITMAP my_pic_prev = ST_get_bitmap (st_prev, my_pieces );
	BITMAP my_pic_next = ST_get_bitmap (st_next, my_pieces );
	
	MOVE mov = move_new ();	
	
	int my_pieces_moved [ NR_A_PO ];
	
	int i;
	
	for (i=BMAP_TP_OFF;i<NR_A_PO;++i) 
	
			my_pieces_moved [i] = BM_Compare_BMAPs ( my_pic_prev & ST_get_bitmap(st_prev, i )  , my_pic_next & ST_get_bitmap ( st_next , i ) );
		
	if ( my_pieces_moved [ T_K ] && my_pieces_moved [ T_R ] ) {
		
			// TODO ROCADA
			
			return 0;
	}
	
	if ( my_pieces_moved [T_P] ) {
		
		// TODO Mutare pion
		return 0;
	}
	
	int which_piece;
	
	for ( i=BMAP_TP_OFF ; i< NR_A_PO ; ++i )
		if ( my_pieces_moved[i] ) which_piece = i;
	
	move_set_p_tag (mov , which_piece);  // setez in mutare tag_piece
	
	List list_poz_moved_p = ST_get_List_Table_P ( st_prev , my_pieces , which_piece );
	
	// Here list_poz_moved_p is the list with the initial pozitions of the moved piece 
	
	P_LOC loc;
	LOC poz_start;
	
	for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; )
		
			if (  ST_get_tag_Table_W ( st_next , LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == T_NA ) {
				 
					move_set_poz_src ( mov ,  *loc);  // setez in mutare pozitia de plecare
					
					break;
			}
			
	
	BITMAP where_moved = (~ ( my_pic_prev & ST_get_bitmap (st_prev, which_piece ) ) ) & ( my_pic_prev & ST_get_bitmap (st_next, which_piece ) ) );
	
	list_poz_moved_p = ST_get_List_Table_P ( st_next , my_pieces , which_piece );
	for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; ) 
		
			if ( BM_Make_coord ( LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == where_moved ) {
				
					move_set_poz_dst ( mov ,  *loc);
					
					break;
			}
			
	move_set_m_tag ( mov, T_MOVE_NA );
	
	return mov;
}
	
	
	
					
	        
	
