/*
 * General description :
 *
 */

#ifndef _SAN_H
#define _SAN_H

/* ----- System #includes ----- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ----- Local #inlcudes ----- */

#include "../state/state.h"
#include "../bitmap/bitmap.h"
#include "../cur_state/cur_state.h"
#include "../Util/util.h"
#include "../move/move.h"
#include "../state_generator/state_generator.h"
#include "../Flags/flags.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */

/* Desc:
 * Transforma mutarea din standard intern in SAN
 * Input:1: MOVE
 * Output:1: string
 */

char * Move_to_SAN (MOVE);

/* Desc:
 * Transforma mutarea din san in standard intern
 * Input:1: string
 * Output:1: MOVE
 */

MOVE SAN_to_Move (char*);

#endif /* SAN_H_ */
