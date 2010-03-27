/*
 * test.c
 *
 *  Created on: Mar 27, 2010
 *      Author: mihai
 */
#include <stdio.h>
#include "../state/state.h"
#include "../bitmap/bitmap.h"
#include "read_from_file.h"


int main(){

	BM_init();
	FILE * fout = fopen("test_readffile.txt","w");


	STATE st = ST_new();
	st = Read_initial_state();
	state_print(st,fout);
	printf("fara");
	return 0;
}
