#include <stdio.h>
#include <stdlib.h>
#include "../../state_generator/state_generator.h"
#include "../../update_state/update_state.h"
#include "../../read_from_file/read_from_file.h"
#include "../../cur_state/cur_state.h"
#include "../../bitmap/bitmap.h"
#include "../../Flags/flags.h"
#include "../../valid_moves/valid_moves.h"




int main(){

	FILE * fin = fopen("./Test/test_if_check/test_if_check.in","r");
	FILE * fout = fopen("./Test/test_if_check/test_if_check.out","w");

	STATE st;
	st = state_read(fin);

	VM_is_Check_if_piece_moves(st,ST_get_)

	return 0;
}
