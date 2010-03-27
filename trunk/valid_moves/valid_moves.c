#include "valid_moves.h"


BITMAP	VM_valid_pos(BITMAP posibile, BITMAP piese_albe){

	BITMAP rez = posibile & (~piese_albe);

	return rez;
}
