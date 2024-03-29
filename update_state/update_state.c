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
#include "../log/log.h"
/* ---- Macro #define ---- */
#define LOG_UPDATE_STATE_FILE "Log/update_state.log"
#define LOG_CURRENT_STATE_FILE "Log/current_state.log"

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* --- Procedures --- */

void update_state_init(void) {

	cur_state_set(Read_initial_state());
}

void update_state(STATE cur, MOVE mov) {

	UCHAR piesa = move_get_p_tag(mov);
	LOC src = move_get_poz_src(mov);
	LOC dst = move_get_poz_dst(mov);
	List list;
	int boo_pro = 0;
	UCHAR culoare;
	int boo_en = 0; // =1 daca este en passant
	BITMAP bm_piesa = ST_get_bitmap(cur, piesa) ^ BM_Make_coord(src.row, src.col);// eliminare piesa de la locul sursei
	ST_set_bitmap(cur, piesa, bm_piesa); // setare bitmap
	ST_set_tag_Table_What(cur, src.row, src.col, T_NA); // eliminare piesa din tabel
	int boo = ST_get_tag_Table_What(cur, dst.row, dst.col) == T_NA;
	if (move_get_p_tag(mov) == T_P) {
		if ((move_get_poz_src(mov).row != move_get_poz_dst(mov).row)) {
			boo = 0;
			if (ST_get_tag_Table_What(cur, dst.row, dst.col) == T_NA)
				boo_en = 1;
		} else {
			boo = 1;
		}
		if (move_get_m_tag(mov) == 1){
			boo_pro = 1;
		}else{
			boo_pro = 0;
		}
	}

	if (boo_pro){
		culoare = ST_get_col_on_move(cur);
		list = ST_get_List_Table_Location(cur, culoare, piesa);
		delete_elem_list(list, &src, fequ_loc, LOC_free);
		piesa = move_get_p_tag_pro(mov);
	}

	// Verificare daca este rocada

	if (move_get_m_tag(mov) && (piesa == T_K)) {
		LOC tura = move_get_p_rock(mov);
		culoare = ST_get_col_on_move(cur);
		BITMAP bm_piesa = ST_get_bitmap(cur, T_R) ^ BM_Make_coord(tura.row, tura.col);// eliminare piesa de la locul sursei (Tura)
		if (dst.row == 2) {
			BM_Put_piece_at_coord(&bm_piesa, 3, tura.col);
			ST_set_bitmap(cur, T_R, bm_piesa);
			bm_piesa = ST_get_bitmap(cur, culoare);
			BM_Clear_piece_at_coord(&bm_piesa, tura.row, tura.col); // scoatem piesa din bmap'ul culorii
			BM_Put_piece_at_coord(&bm_piesa, 3, tura.col);
			ST_set_bitmap(cur, culoare, bm_piesa);
			ST_set_tag_Table_What(cur, tura.row, tura.col, T_NA); // eliminare piesa din tabel
			if (culoare)
				ST_set_tag_Table_What(cur, 3, tura.col, (T_R + BWP_OFF)); // adaugam piesa la destinatie
			else
				ST_set_tag_Table_What(cur, 3, tura.col, T_R); // adaugam piesa la destinatie
			list = ST_get_List_Table_Location(cur, culoare, T_R); // extragem lista
			P_LOC loc = find_nod_list(list, &tura, fequ_loc);
			LOCp_set_both(loc, 3, tura.col);
		} else {
			BM_Put_piece_at_coord(&bm_piesa, 5, tura.col);
			ST_set_bitmap(cur, T_R, bm_piesa);
			bm_piesa = ST_get_bitmap(cur, culoare);
			BM_Clear_piece_at_coord(&bm_piesa, tura.row, tura.col); // scoatem piesa din bmap'ul culorii
			BM_Put_piece_at_coord(&bm_piesa, 5, tura.col);
			ST_set_bitmap(cur, culoare, bm_piesa);
			ST_set_tag_Table_What(cur, tura.row, tura.col, T_NA); // eliminare piesa din tabel
			if (culoare)
				ST_set_tag_Table_What(cur, 5, tura.col, (T_R + BWP_OFF)); // adaugam piesa la destinatie
			else
				ST_set_tag_Table_What(cur, 5, tura.col, T_R); // adaugam piesa la destinatie
			list = ST_get_List_Table_Location(cur, culoare, T_R); // extragem lista
			P_LOC loc = find_nod_list(list, &tura, fequ_loc);
			LOCp_set_both(loc, 5, tura.col);
		}
	}
	if (boo) { //verificare daca e captura
		bm_piesa = ST_get_bitmap(cur, piesa) | BM_Make_coord(dst.row, dst.col); // punem un 1 la locul destinatiei
		ST_set_bitmap(cur, piesa, bm_piesa); // setare bitmap
		culoare = ST_get_col_on_move(cur);
		bm_piesa = ST_get_bitmap(cur, culoare);
		BM_Clear_piece_at_coord(&bm_piesa, src.row, src.col); // scoatem piesa din bmap'ul culorii
		bm_piesa = bm_piesa | BM_Make_coord(dst.row, dst.col);
		ST_set_bitmap(cur, culoare, bm_piesa);
		if (culoare)
			ST_set_tag_Table_What(cur, dst.row, dst.col, (piesa + BWP_OFF)); // adaugam piesa la destinatie
		else
			ST_set_tag_Table_What(cur, dst.row, dst.col, piesa); // adaugam piesa la destinatie
		list = ST_get_List_Table_Location(cur, culoare, piesa); // extragem lista
		if (!boo_pro){
			P_LOC loc = (P_LOC) find_nod_list(list, &src, fequ_loc);
			LOCp_set_both(loc, dst.row, dst.col);
		}else{
			P_LOC pro = LOC_new();
			LOCp_set_both(pro, dst.row, dst.col);
			add_nod_list(list, pro);
		}
		ST_set_col_on_move(cur, not(culoare));
		ST_set_piece_to_move(cur, ANALYZED_PIECE );
		ST_set_move_index(cur, 0);

	} else { // e captura
		if (boo_en) { // en_passant
			culoare = ST_get_col_on_move(cur);
			LOC dst_en;
			if (culoare) {
				LOCp_set_both(&dst_en, dst.row - 1, dst.col);
			} else {
				LOCp_set_both(&dst_en, dst.row + 1, dst.col);
			}
			UCHAR adv;
			if (!culoare)
				adv = ST_get_tag_Table_What(cur, dst_en.row, dst_en.col) - BWP_OFF; // tipul piesei adversarului
			else
				adv = ST_get_tag_Table_What(cur, dst_en.row, dst_en.col); // tipul piesei adversarului
			bm_piesa = ST_get_bitmap(cur, adv);
			BM_Clear_piece_at_coord(&bm_piesa, dst_en.row, dst_en.col); // elimin piesa adversarului din bitmapul de pozitii ale piesei
			ST_set_bitmap(cur, adv, bm_piesa);
			bm_piesa = ST_get_bitmap(cur, !culoare);
			BM_Clear_piece_at_coord(&bm_piesa, dst_en.row, dst_en.col); // elimin piesa adversarului
			ST_set_bitmap(cur, !culoare, bm_piesa);
			bm_piesa = ST_get_bitmap(cur, piesa);
			BM_Put_piece_at_coord(&bm_piesa, dst.row, dst.col);
			ST_set_bitmap(cur, piesa, bm_piesa);
			bm_piesa = ST_get_bitmap(cur, culoare);
			BM_Clear_piece_at_coord(&bm_piesa, src.row, src.col); // scoatem piesa din bmap'ul culorii
			bm_piesa = bm_piesa | BM_Make_coord(dst.row, dst.col);
			ST_set_bitmap(cur, culoare, bm_piesa);
			if (culoare) {
				ST_set_tag_Table_What(cur, dst.row, dst.col, (piesa + BWP_OFF)); // adaugam piesa la destinatie
				ST_set_tag_Table_What(cur, dst_en.row, dst_en.col, T_NA);
			} else {
				ST_set_tag_Table_What(cur, dst.row, dst.col, piesa); // adaugam piesa la destinatie
				ST_set_tag_Table_What(cur, dst_en.row, dst_en.col, T_NA);
			}
			list = ST_get_List_Table_Location(cur, culoare, piesa);// extragem lista
			List list1 = ST_get_List_Table_Location(cur, !culoare, adv);
			delete_elem_list(list1, &dst_en, fequ_loc, LOC_free);
			P_LOC l = find_nod_list(list, &src, fequ_loc);
			LOCp_set_both(l, dst.row, dst.col);
			ST_set_piece_to_move(cur, ANALYZED_PIECE );
			ST_set_move_index(cur, 0);
			ST_set_col_on_move(cur, not(culoare));
		} else {
			culoare = ST_get_col_on_move(cur);
			UCHAR adv;
			if (!culoare)
				adv = ST_get_tag_Table_What(cur, dst.row, dst.col) - BWP_OFF; // tipul piesei adversarului
			else
				adv = ST_get_tag_Table_What(cur, dst.row, dst.col); // tipul piesei adversarului
			bm_piesa = ST_get_bitmap(cur, adv);
			BM_Clear_piece_at_coord(&bm_piesa, dst.row, dst.col); // elimin piesa adversarului din bitmapul de pozitii ale piesei
			ST_set_bitmap(cur, adv, bm_piesa);
			bm_piesa = ST_get_bitmap(cur, !culoare);
			BM_Clear_piece_at_coord(&bm_piesa, dst.row, dst.col); // elimin piesa adversarului
			ST_set_bitmap(cur, !culoare, bm_piesa);
			bm_piesa = ST_get_bitmap(cur, piesa);
			BM_Put_piece_at_coord(&bm_piesa, dst.row, dst.col);
			ST_set_bitmap(cur, piesa, bm_piesa);
			bm_piesa = ST_get_bitmap(cur, culoare);
			BM_Clear_piece_at_coord(&bm_piesa, src.row, src.col); // scoatem piesa din bmap'ul culorii
			bm_piesa = bm_piesa | BM_Make_coord(dst.row, dst.col);
			ST_set_bitmap(cur, culoare, bm_piesa);
			if (culoare)
				ST_set_tag_Table_What(cur, dst.row, dst.col, (piesa + BWP_OFF)); // adaugam piesa la destinatie
			else
				ST_set_tag_Table_What(cur, dst.row, dst.col, piesa); // adaugam piesa la destinatie
			list = ST_get_List_Table_Location(cur, culoare, piesa);// extragem lista
			List list1 = ST_get_List_Table_Location(cur, !culoare, adv);
			delete_elem_list(list1, &dst, fequ_loc, LOC_free);
			if (!boo_pro){
				P_LOC l = find_nod_list(list, &src, fequ_loc);
				LOCp_set_both(l, dst.row, dst.col);
			}else{
				P_LOC pro = LOC_new();
				LOCp_set_both(pro, dst.row, dst.col);
				add_nod_list(list, pro);
			}
			ST_set_piece_to_move(cur, ANALYZED_PIECE );
			ST_set_move_index(cur, 0);
			ST_set_col_on_move(cur, not(culoare));
		}
	}
	ST_set_cur_poz_in_list(cur, ST_get_List_Table_Location(cur, ST_get_col_on_move(cur), ANALYZED_PIECE));

	/* LOG */
	log_print("Updated State\n", LOG_UPDATE_STATE_FILE);
	log_print("Color on move:", LOG_UPDATE_STATE_FILE);
	char text[10];
	tag_to_text(ST_get_col_on_move(cur_state_get()), text);
	log_print(text, LOG_UPDATE_STATE_FILE);
	log_print_state_Table_What(cur_state_get(), LOG_UPDATE_STATE_FILE );
	log_print("~~~ Current State ~~~ \n", LOG_CURRENT_STATE_FILE);
	log_print_state(cur_state_get(), LOG_CURRENT_STATE_FILE, WRITE_TAG_ADD );
	/* END LOG */

}

void flip_state(void) {

	set_engine_col(not(get_engine_col())); // flips the flag
}
