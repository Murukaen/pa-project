#include <stdio.h>
#include "../../state_generator/state_generator.h"
#include "../../valid_moves/valid_moves.h"
#include "../../list/list.h"
#include "../../Init/init.h"

int main() {

	FILE * fout = fopen("./Test/test_valid_moves/test_valid_moves.out", "w");
	FILE * fin = fopen("./Test/test_valid_moves/test_valid_moves.in", "r");

	BITMAP rez;
	STATE st;
	List l;

	Init(INIT_ALL);

	st = state_read(fin);

	l = ST_get_List_Table_Location(st, 0, T_P);
	ST_set_cur_poz_in_list(st, l);
	P_LOC loc = LOC_new();
	LOCp_set_both(loc,4,1);

	ST_set_piece_to_move(st, T_P);

	state_print(st, fout);

	rez = VM_valid_moves(st, loc);
	BM_print(rez, fout);

	return 0;
}
