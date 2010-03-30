/*
 * test_initial_state.c
 *
 *  Created on: Mar 26, 2010
 *      Author: Mihaytza
 */
#include <stdio.h>
#include <stdlib.h>
#include "../../state/state.h"
#include "../../update_state/update_state.h"
#include "../../cur_state/cur_state.h"
#include "../../bitmap/bitmap.h"

int main() {

	BM_init ();
	
	FILE * fout = fopen("Test/test_initial_state/Initial_State.out","w");
	update_state_init();
	state_print( cur_state_get() ,fout);
	fclose(fout);

	return 0;
}
