/*
 * General description :
 *
 */

#ifndef SAN_H_
#define SAN_H_

/* ----- System #includes ----- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ----- Local #inlcudes ----- */

#include "../state/state.h"
#include "../bitmap/bitmap.h"
#include "../cur_state/cur_state.h"
#include "../util/util.h"
#include "../move/move.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Procedures --- */
char * toSAN(MOVE);


#endif /* SAN_H_ */
