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
	UCHAR c = move_get_p_tag(mov);
	LOC s = move_get_poz_src(mov);
	LOC d = move_get_poz_dst(mov);
	BITMAP b = ST_get_bitmap(cur, c) ^ BM_Make_coord(s.row, s.col);
	ST_set_bitmap(cur, c, b);
	if (ST_get_tag_Table_W(cur, d.row, d.col) == T_NA) {
		b = ST_get_bitmap(cur, c) | BM_Make_coord(d.row, d.col);
		ST_set_bitmap(cur, c, b);
		if (~(f_ENG_COL ^ f_ENG_ON_MOVE))
			ST_set_tag_Table_W(cur, d.row, d.col, (c + BMAP_BWP_OFF));
		else
			ST_set_tag_Table_W(cur, d.row, d.col, c);
		List list = ST_get_List_Table_P(cur, ~(f_ENG_COL ^ f_ENG_ON_MOVE), c);
		P_LOC l = find_nod_list(list, &s, fequ_loc);
		LOCp_set_both(l, d.row, d.col);
	} else {
		UCHAR adv = ST_get_tag_Table_W(cur, d.row, d.col);
		b = BM_Clear_piece_at_coord(ST_get_bitmap(cur, adv));
		ST_set_bitmap(cur, adv, b);
		b = ST_get_bitmap(cur, c);
		BM_Put_piece_at_coord(&b, d.row, d.col);
		ST_set_bitmap(cur, c, b);
		if (~(f_ENG_COL ^ f_ENG_ON_MOVE))
			ST_set_tag_Table_W(cur, d.row, d.col, (c + BMAP_BWP_OFF));
		else
			ST_set_tag_Table_W(cur, d.row, d.col, c);
		List list = ST_get_List_Table_P(cur, ~(f_ENG_COL ^ f_ENG_ON_MOVE), c - BMAP_TP_OFF);
		List list2 = delete_elem_list(&list, &d, fequ_loc);
		free_list(list, loc_free);
		P_LOC l = find_nod_list(list, &s, fequ_loc);
		LOCp_set_both(l, d.row, d.col);
	}
	b = ST_get_bitmap(cur, f_ENG_COL) ^ BM_Make_coord(s.row, s.col);
	ST_set_bitmap(cur, f_ENG_COL, b);

}

void flip_state(void) {

	f_ENG_COL = ~f_ENG_COL; // flips the flag

}

