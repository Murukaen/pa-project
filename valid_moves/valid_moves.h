#ifndef VALID_MOVES_H_
#define VALID_MOVES_H_

#include "../bitmap/bitmap.h"
#include "../state/state.h"
#include "../Util/util.h"
#include "../state_generator/state_generator.h"

typedef struct int_loc {
	int row;
	int col;
} ILOC;

BITMAP VM_valid_pos(BITMAP, BITMAP);

/* daca regele e in sah, pune in parametrii numaru de piese care dau sah si locul acesteia(daca e doar una). Intoarce un bitmap cu 1 pe pozitiile care scot regele din sah*/
BITMAP VM_is_Check(STATE start_state, int* nr_of_pieces_checking,
		P_LOC checking_piece);

/*verifica daca in urma mutarii piesei de la LOC se intra in sah,daca se intra in sah, pune in ultimul argument locatia piesei care ar da sah
 * 1 true 0 false */
UCHAR VM_is_Check_if_piece_moves(STATE, P_LOC piesa_la_mutare,
		P_LOC cine_da_sah);

BITMAP VM_get_valid_if_check(STATE, P_LOC piesa_la_mutare, P_LOC cine_da_sah);

// daca e invalida mutarea returneaza 1,daca e ok 0
int VM_validate_King_move(STATE, ILOC);

BITMAP VM_valid_moves(STATE, P_LOC);

#endif /* VALID_MOVES_H_ */
