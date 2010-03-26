/*
 * test_initial_state.c
 *
 *  Created on: Mar 26, 2010
 *      Author: Mihaytza
 */
#include <stdio.h>
#include <stdlib.h>
#include "../state/state.h"

int main() {

	FILE * fout = fopen("test_read_initial_state.out","w");
	STATE st = ST_new();
	update_state_init();
	state_print(st,fout);
	return 0;
}
