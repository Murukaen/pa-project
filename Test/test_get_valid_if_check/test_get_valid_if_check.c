#include <stdio.h>
#include <stdlib.h>
#include "../../state_generator/state_generator.h"
#include "../../update_state/update_state.h"
#include "../../read_from_file/read_from_file.h"
#include "../../cur_state/cur_state.h"
#include "../../bitmap/bitmap.h"
#include "../../Flags/flags.h"
#include "../../Init/init.h"
#include "../../Log/log.h"
#include "../../valid_moves/valid_moves.h"

int main() {

	FILE * fin = fopen(
			"./Test/test_get_valid_if_check/test_get_valid_if_check.in", "r");
	if (fin == NULL) {
		printf("eroare deschidere fisier intrare");
		exit(0);
	}
	STATE st;
	BITMAP rez;
	/* Inits */

	Init(INIT_ALL);

	st = state_read(fin);
	state_print(st,stdout);
	P_LOC pinned = LOC_new(), checking = LOC_new();

	LOCp_set_both(pinned, 4, 6);
	LOCp_set_both(checking, 4, 4);

	rez = VM_get_valid_if_check(st, pinned, checking);
	BM_print(rez, stdout);
	fclose(fin);
	return 0;
}
