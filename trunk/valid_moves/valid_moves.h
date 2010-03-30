#ifndef VALID_MOVES_H_
#define VALID_MOVES_H_

#include "../bitmap/bitmap.h"
#include "../state/state.h"
#include "../Util/util.h"
#include "../state_generator/state_generator.h"


BITMAP VM_valid_pos(BITMAP,BITMAP);

/*verifica daca in urma mutarii piesei de la LOC se intra in sah
 * 1 true 0 false */
UCHAR VM_is_Check_if_piece_moves(STATE,P_LOC);

// functie vm_is_check to do

#endif /* VALID_MOVES_H_ */
