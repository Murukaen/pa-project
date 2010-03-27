/*
 * test_all_possible_moves.c
 *
 *  Created on: Mar 27, 2010
 *      Author: mihai
 */

#include <stdio.h>
#include "../../bitmap/bitmap.h"
#include "../../read_from_file/read_from_file.h"

int main() {

	FILE *fout = fopen("./Test/test_all_possible_moves/allmoves.out", "w");
	BITMAP Moves[5][8][8];
	BM_init();
	Read_all_possible_moves(Moves);
	print_all_possible_moves(fout,Moves);
	printf("fara");
	return 0;
}
