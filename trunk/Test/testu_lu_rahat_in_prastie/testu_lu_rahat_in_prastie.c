#include <stdio.h>
#include <stdlib.h>

/* ----- Local #inlcudes ----- */
#include "../../Init/init.h"
#include "../../xboard_com/xboard_com.h"
#include "../../Flags/flags.h"
#include "../../Log/log.h"
#include "../../bitmap/bitmap.h"
#include "../../state/state.h"
#include "../../move/move.h"
#include "../../decision/decision.h"
#include "../../cur_state/cur_state.h"
#include "../../move_handler/move_handler.h"
#include "../../state_generator/state_generator.h"
#include "../../update_state/update_state.h"

/* ---- Macro #define ---- */
int main(void) {

	int i = 1;
	f_ENG_COL = 1;
	i++;
	BM_init();

	printf("MAIN: f_ENG_COL: %d\n", f_ENG_COL);

	return 0;
}
