#include "san_conv.h"

char get_pieces(UCHAR c) {
	switch (c) {
	case T_K:
		return 'K';
	case T_Q:
		return 'Q';
	case T_B:
		return 'B';
	case T_N:
		return 'N';
	case T_R:
		return 'R';
	case T_P:
		return 'P';
	default :
		return ' ';
	}
}
