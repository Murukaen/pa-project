#include <stdio.h>
#include "../../state/state.h"
#include "../../bitmap/bitmap.h"
#include "../../read_from_file/read_from_file.h"
#include "../../Flags/flags.h"


int main(){

	FILE * fout = fopen("./Test/test_read_from_file/test_readffile.out","w");
	flags_init ();
	STATE st = ST_new();
	st = Read_initial_state();
	state_print(st,fout);
	printf("fara");
	return 0;
}
