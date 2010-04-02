#include <stdio.h>
#include "../../state_generator/state_generator.h"
#include "../../valid_moves/valid_moves.h"
#include "../../list/list.h"
#include "../../Init/init.h"

int main() {

	FILE * fout = fopen("./Test/test_valid_moves/test_valid_moves.out", "w");
	FILE * fin = fopen("./Test/test_valid_moves/test_valid_moves.in", "r");

	int rez;
	STATE st;
	List l;

	Init(INIT_ALL);

	st = state_read(fin);

	P_LOC loc = LOC_new();
	LOCp_set_both(loc,4,6);


	//state_print(st, fout);

	rez = VM_is_Check_if_piece_moves(st, loc);
	printf ( "Rez:%d\n" , rez );

	return 0;
}
