#include <stdio.h>
#include <stdlib.h>
#include "../../state_generator/state_generator.h"
#include "../../update_state/update_state.h"
#include "../../read_from_file/read_from_file.h"
#include "../../cur_state/cur_state.h"
#include "../../bitmap/bitmap.h"
#include "../../Flags/flags.h"
#include "../../Init/init.h"
#include "../../log/log.h"

#define LOG_TEST_FILE "Log/test.log"

int main() {

	/*
	FILE * fout = fopen("./Test/test_state_generator/test_st_generator.out",
			"w");
	*/
	FILE * fin = fopen("./Test/test_state_generator/stare_initiala.in", "r");
	if (fin == NULL) {
		printf("eroare deschidere fisier intrare");
		exit(0);
	}
	STATE st;

	/* Inits */

	Init(INIT_ALL);

	/* END Inits */

	st = state_read(fin);
	STATE son;
	for(son=ST_gen(st);son;log_print_state_Table_What(son , LOG_TEST_FILE), son=ST_gen(st));
	
	return 0;
}
