#include <stdio.h>
#include <stdlib.h>
#include "../../state_generator/state_generator.h"
#include "../../update_state/update_state.h"
#include "../../read_from_file/read_from_file.h"
#include "../../cur_state/cur_state.h"
#include "../../bitmap/bitmap.h"
#include "../../Flags/flags.h"

int main() {

	FILE * fout = fopen("./Test/test_state_generator/test_st_generator.out",
			"w");
	FILE * fin = fopen("./Test/test_state_generator/stare_initiala.in", "r");
	if (fin == NULL) {
		printf("eroare deschidere fisier intrare");
		exit(0);
	}
	STATE st;

	/* Inits */
	BM_init();
	flags_init();
	ST_gen_init();

	/* END Inits */

	st = state_read(fin, 0);

	while(ST_gen(st) != NULL){
		state_print(st,fout);
	}
	printf("fara");

	return 0;
}
