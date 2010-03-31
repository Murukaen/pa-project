/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "move_handler.h"
#include "../cur_state/cur_state.h"
#include "../Flags/flags.h"
#include "../Util/util.h"


/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */


MOVE determine_move ( STATE st_next ) {

	STATE st_prev = cur_state_get();
	
	UCHAR my_pieces = ST_get_col_on_move ( st_prev );    //culoarea engineului


	UCHAR his_pieces = not(my_pieces); //culoarea adversarului

	BITMAP my_pic_prev = ST_get_bitmap (st_prev, my_pieces ); //bitmapul starii mele curente
	
	BITMAP his_pic_next= ST_get_bitmap (st_next, his_pieces );
	
	BITMAP my_pic_next = ST_get_bitmap (st_next, my_pieces ); //bitmapul starii mele urmatoare

	MOVE mov = move_new ();	
	
	move_set_what_col ( mov , my_pieces );//setez in mutare culoarea on move

	List list_poz_moved_p;
	// Here list_poz_moved_p is the list with the initial pozitions of the moved piece

	//vector care seteaza 1 in my_pieces_moved[] daca se muta piesa care are indicele respectiv
	int my_pieces_moved [ SIZE_BMAP ];
	
	P_LOC loc;
	LOC poz_start;

	BITMAP where_moved; //bitmapul care determina pozitia in care se va muta piesa

	int i;

	for (i=PIECES_OFF;i<SIZE_BMAP;++i)
	{
			my_pieces_moved [i] =!( BM_Compare_BMAPs ( my_pic_prev & ST_get_bitmap(st_prev, i )  , my_pic_next & ST_get_bitmap ( st_next , i ) ) );
			
			
		}

	int which_piece;  //which_piece va retine tipul piesei este in mutare de la o stare la alta

	/*-------------------------ROCADA---------------------------*/


	if ( my_pieces_moved [ T_K ] && my_pieces_moved [ T_R ] ) {
		
			printf("ROCADAAAAAAAA\n");
			fflush(stdout);
			LOC lcastle; //locatia turei pe tabla

			move_set_p_tag_pro ( mov , 0 ); //nu se promoveaza nici o piesa


			which_piece=T_K;
			move_set_p_tag (mov , which_piece); //setez regele la mutare
		
			list_poz_moved_p = ST_get_List_Table_Location ( st_prev , my_pieces , which_piece );
			//lista pentru starea curenta

			for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) )

						if (  ST_get_tag_Table_What ( st_next , LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == T_NA ) {

								move_set_poz_src ( mov ,  *loc);  // setez in mutare pozitia de plecare

								break;
						}
		
		    where_moved = ((my_pic_next & ST_get_bitmap(st_next,which_piece)) & (~(my_pic_prev & ST_get_bitmap(st_prev,which_piece))));

			list_poz_moved_p = ST_get_List_Table_Location ( st_next , my_pieces , which_piece );
			//lista pentru starea urmatoare

			for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; loc = (P_LOC) first_nod_list ( &list_poz_moved_p ))

					if ( BM_Make_coord ( LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == where_moved ) {

							move_set_poz_dst ( mov ,  *loc); //setez in mutare pozitia finala a piesei
							
							if((move_get_poz_dst( mov ).row) == 6)	//rocada mica
							{
								printf("ROCADAAAA MICAAAAA\n");
								fflush(stdout);
								move_set_m_tag (mov,1); //indicator rocada mica

								lcastle.row=move_get_poz_dst(mov).row +1; //se afla pe coloana regelui la destinatie +1

								lcastle.col=move_get_poz_dst(mov).col;//se afla pe aceeasi linie cu regele,indiferent de culoare

								move_set_p_rock(mov,lcastle);//setez in move locatia finala a turei
								

							}
							else	//rocada mare
							{
								printf("ROCADAAA MAREEEE\n");
								
								move_set_m_tag (mov,1);//nu stiu ce indicator are rocada mare,ma corecteaza alin
									
								lcastle.row = move_get_poz_src ( mov ) .row -1;//se afla pe coloana sursa a regelui -1

								lcastle.col = move_get_poz_src ( mov ). col;//se afla pe linia regelui,indiferent de culoare

								move_set_p_rock(mov,lcastle);//setez in move locatia finala a turei
							
							}

							break;
					}


			return mov;
	}
	/*------------------------------MUTARI PIONI + PROMOVARE ---------------------*/
	
	if ( my_pieces_moved [T_P] ) {
		
		printf("PIONU MUTAAAA\n");
		fflush(stdout);
		
		which_piece=T_P;
		
		move_set_p_tag (mov , which_piece);  // setez in mutare tag_piece
		
		list_poz_moved_p = ST_get_List_Table_Location ( st_prev , my_pieces , which_piece );
	
		for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; loc = (P_LOC) first_nod_list ( &list_poz_moved_p ))
		
			if (  ST_get_tag_Table_What ( st_next , LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == T_NA )
			 {
				 
					move_set_poz_src ( mov ,  *loc);  // setez in mutare pozitia de plecare
					
					if ( my_pieces == 0 )
					{			
								if((move_get_poz_src(mov).col == 6)) //promovare
									move_set_m_tag ( mov , 1 );
								else
									move_set_m_tag ( mov , 0 ); //nu promoveaza
					}			
					else
								if((move_get_poz_src(mov).col == 1)) //promovare
									move_set_m_tag ( mov , 1 );
								else
									move_set_m_tag( mov , 0 ); //nu promoveaza
					
						
									
					break;
			}
	/*-----------------------------mutare fara promovare-------------------------------------*/
			
	if(move_get_m_tag(mov)== 0)		
	{		
			
		where_moved = ((my_pic_next & ST_get_bitmap(st_next,which_piece)) 
				 & (~(my_pic_prev & ST_get_bitmap(st_prev,which_piece))));
	
		list_poz_moved_p = ST_get_List_Table_Location ( st_next , my_pieces , which_piece ); //lista pentru starea urmatoare
		for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; loc = (P_LOC) first_nod_list ( &list_poz_moved_p )) 
		
				if ( BM_Make_coord ( LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == where_moved )
				 {
						move_set_poz_dst ( mov ,  *loc);
						break;
				}
	return mov;			
	}			
	
	/*----------------------------------------aici promoveaza----------------------------------------------*/
	
	UCHAR dreapta,mijloc,stanga,next_dreapta,next_mijloc,next_stanga;
	move_set_p_tag_pro(mov,T_Q);
	
	/*---------------------------joc cu piesele albe=> pionul merge in sus---------------------------------*/
	if(my_pieces==0)
	{
		dreapta=ST_get_tag_Table_What(st_prev,move_get_poz_src(mov).col+1,7);
		stanga=ST_get_tag_Table_What(st_prev,move_get_poz_src(mov).col-1,7);
		mijloc=ST_get_tag_Table_What(st_prev,move_get_poz_src(mov).col,7);
		next_dreapta=ST_get_tag_Table_What(st_next,move_get_poz_src(mov).col+1,7);
		next_stanga=ST_get_tag_Table_What(st_next,move_get_poz_src(mov).col-1,7);
		next_mijloc=ST_get_tag_Table_What(st_next,move_get_poz_src(mov).col,7);
		
		if( next_dreapta == T_Q && dreapta != T_Q)
		{
				loc->col=move_get_poz_src(mov).col+1;
				loc->row=7;
				move_set_poz_dst ( mov ,  *loc);
				return mov;
		}
		if( next_stanga == T_Q && stanga != T_Q)
		{
				loc->col=move_get_poz_src(mov).col-1;
				loc->row=7;
				move_set_poz_dst ( mov ,  *loc);
				return mov;
		}			
		if( mijloc == T_Q && mijloc != T_Q)
		{
				loc->col=move_get_poz_src(mov).col;
				loc->row=7;
				move_set_poz_dst ( mov ,  *loc);
				return mov;
		}	
		
				
	}
	/*--------------------------------------joc cu piesele negre=>pionul merge in jos--------------------------------*/
	else
	{
		dreapta=ST_get_tag_Table_What(st_prev,move_get_poz_src(mov).col+1,0);
		stanga=ST_get_tag_Table_What(st_prev,move_get_poz_src(mov).col-1,0);
		mijloc=ST_get_tag_Table_What(st_prev,move_get_poz_src(mov).col,0);
		next_dreapta=ST_get_tag_Table_What(st_next,move_get_poz_src(mov).col+1,0);
		next_stanga=ST_get_tag_Table_What(st_next,move_get_poz_src(mov).col-1,0);
		next_mijloc=ST_get_tag_Table_What(st_next,move_get_poz_src(mov).col,0);	
		
		if( next_dreapta == T_Q && dreapta != T_Q)
		{
				loc->col=move_get_poz_src(mov).col+1;
				loc->row=0;
				move_set_poz_dst ( mov ,  *loc);
				return mov;
		}
		if( next_stanga == T_Q && stanga != T_Q)
		{
				loc->col=move_get_poz_src(mov).col-1;
				loc->row=0;
				move_set_poz_dst ( mov ,  *loc);
				return mov;
		}			
		if( mijloc == T_Q && mijloc != T_Q)
		{
				loc->col=move_get_poz_src(mov).col;
				loc->row=0;
				move_set_poz_dst ( mov ,  *loc);
				return mov;
		}	
		
	}	
		
		return mov;
	}
	

	/*----------------------------------------------------------------------------------------------------*/
	/*-------------------------------aici incep mutarile fara exceptii------------------------------------*/
	
	

	move_set_m_tag ( mov , 0 ); //nu se promoveaza nici o piesa

	for ( i=PIECES_OFF ; i< SIZE_BMAP ; ++i )
		if ( my_pieces_moved[i] ) which_piece = i;
	
	move_set_p_tag (mov , which_piece);  // setez in mutare tag_piece
	
	list_poz_moved_p = ST_get_List_Table_Location ( st_prev , my_pieces , which_piece );
	
	for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; loc = (P_LOC) first_nod_list ( &list_poz_moved_p ))
		
			if (  ST_get_tag_Table_What ( st_next , LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == T_NA ) {
				 
					move_set_poz_src ( mov ,  *loc);  // setez in mutare pozitia de plecare
					
					break;
			}
			
	
	where_moved = ((my_pic_next & ST_get_bitmap(st_next,which_piece)) & (~(my_pic_prev & ST_get_bitmap(st_prev,which_piece))));
	
	list_poz_moved_p = ST_get_List_Table_Location ( st_next , my_pieces , which_piece );
	//lista pentru starea urmatoare
	for ( loc = (P_LOC) first_nod_list ( &list_poz_moved_p ) ; loc ; loc = (P_LOC) first_nod_list ( &list_poz_moved_p )) 
		
			if ( BM_Make_coord ( LOC_get_row ( loc ) , LOC_get_col ( loc ) ) == where_moved ) {
				
					move_set_poz_dst ( mov ,  *loc);
					
					break;
			}
			
	move_set_m_tag ( mov, 0);
	
	return mov;
}
	
	
	
					
	        
	
