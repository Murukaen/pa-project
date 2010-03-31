/* General description :
 * 
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */
#include "update_state.h"
#include "../read_from_file/read_from_file.h"
#include "../cur_state/cur_state.h"
#include "../state/state.h"
#include "../Flags/flags.h"
#include "../bitmap/bitmap.h"
#include "../list/list.h"
#include "../Util/util.h"
/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

void update_state_init(void) {

	cur_state_set(Read_initial_state());
}

void update_state(MOVE mov) {

	STATE cur = cur_state_get();
	UCHAR piesa = move_get_p_tag(mov);
	LOC src = move_get_poz_src(mov);
	LOC dst = move_get_poz_dst(mov);
	List list;
	BITMAP bm_piesa = ST_get_bitmap(cur, piesa) ^ BM_Make_coord(src.row, src.col);// eliminare piesa de la locul sursei
	ST_set_bitmap(cur, piesa, bm_piesa); // setare bitmap
	ST_set_tag_Table_What(cur, src.row, src.col, T_NA); // eliminare piesa din tabel
	if (ST_get_tag_Table_What(cur, dst.row, dst.col) == T_NA) { //verificare daca e captura
		bm_piesa = ST_get_bitmap(cur, piesa) | BM_Make_coord(dst.row, dst.col); // punem un 1 la locul destinatiei
		ST_set_bitmap(cur, piesa, bm_piesa); // setare bitmap
		if (!(f_ENG_COL ^ f_ENG_ON_MOVE)) { // gasirea culorii
			bm_piesa = ST_get_bitmap(cur, 1);
			BM_Clear_piece_at_coord(&bm_piesa, src.row, src.col); // scoatem piesa din bmap'ul culorii
			ST_set_bitmap(cur, 1, bm_piesa);
			ST_set_tag_Table_What(cur, dst.row, dst.col, (piesa + BWP_OFF)); // adaugam piesa la destinatie
			list = ST_get_List_Table_Location(cur, 1, piesa); // extragem lista
		} else {
			bm_piesa = ST_get_bitmap(cur, 0); // idem culoare = 1
			BM_Clear_piece_at_coord(&bm_piesa, src.row, src.col);
			ST_set_bitmap(cur, 0, bm_piesa);
			ST_set_tag_Table_What(cur, dst.row, dst.col, piesa);
			list = ST_get_List_Table_Location(cur, 0, piesa);
		}
		P_LOC loc = find_nod_list(list, &src, fequ_loc);
		LOCp_set_both(loc, dst.row, dst.col);
	} else { // e captura
		UCHAR adv = ST_get_tag_Table_What(cur, dst.row, dst.col); // tipul piesei adversarului
		bm_piesa = ST_get_bitmap(cur, adv);
		BM_Clear_piece_at_coord(&bm_piesa, src.row, src.col);
		ST_set_bitmap(cur, adv, bm_piesa); //
		bm_piesa = ST_get_bitmap(cur, piesa);
		BM_Put_piece_at_coord(&bm_piesa, dst.row, dst.col);
		ST_set_bitmap(cur, piesa, bm_piesa);
		if (!(f_ENG_COL ^ f_ENG_ON_MOVE)) {
			bm_piesa = ST_get_bitmap(cur, 1);
			BM_Clear_piece_at_coord(&bm_piesa, src.row, src.col);
			ST_set_bitmap(cur, 1, bm_piesa);
			ST_set_tag_Table_What(cur, dst.row, dst.col, (piesa + BWP_OFF));
			list = ST_get_List_Table_Location(cur,1 , piesa);
		} else {
			bm_piesa = ST_get_bitmap(cur, 0);
			BM_Clear_piece_at_coord(&bm_piesa, src.row, src.col);
			ST_set_bitmap(cur, 0, bm_piesa);
			ST_set_tag_Table_What(cur, dst.row, dst.col, piesa);
			list = ST_get_List_Table_Location(cur,0 , piesa);
		}
		delete_elem_list(list, &dst, fequ_loc, LOC_free);
		P_LOC l = find_nod_list(list, &src, fequ_loc);
		LOCp_set_both(l, dst.row, dst.col);
	}
	bm_piesa = ST_get_bitmap(cur, f_ENG_COL) ^ BM_Make_coord(src.row, src.col);
	ST_set_bitmap(cur, f_ENG_COL, bm_piesa);
	ST_set_cur_poz_in_list(cur, ST_get_List_Table_Location(cur, f_ENG_COL, piesa));
	ST_set_move_index(cur, 0);
	ST_set_piece_to_move(cur, T_N);
}

void flip_state(void) {

	f_ENG_COL = not(f_ENG_COL); // flips the flag
}

