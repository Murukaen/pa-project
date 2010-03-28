#include <stdio.h>
#include <stdlib.h>
#include "../../state_generator/state_generator.h"
#include "../../update_state/update_state.h"
#include "../../read_from_file/read_from_file.h"
#include "../../cur_state/cur_state.h"
#include "../../bitmap/bitmap.h"
#include "../../Flags/flags.h"

int main() {

	FILE * fout = fopen("./Test/test_state_generator/test_st_generator.out", "w");
	STATE st = ST_new();
	STATE new = ST_new();
	BM_init();
	flags_init();
	update_state_init();
	st = cur_state_get();
	state_print(st, fout);
	new = ST_gen(st);
	state_print(new, fout);
	printf("fara");


	return 0;
}
