/* General description :
 *
 */

/* ----- System #includes ----- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ----- Local #inlcudes ----- */
#include "san_conv.h"
#include "../valid_moves/valid_moves.h"
#include "../Log/log.h"

/* ---- Macro #define ---- */
#define LOG_SAN_CONV_FILE "Log/san_conv.log"

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

/* Prototip is_check */

int is_check(MOVE m, STATE cur){
	return 0;
}

/* Prototip is_check_mate */

int is_check_mate(MOVE m, STATE cur){
	return 0;
}

/* Prototip validate_move */

int validate_move(MOVE m, STATE cur){
	//UCHAR piesa = move_get_p_tag(m);
	LOC l = move_get_poz_dst(m);
	LOC s = move_get_poz_src(m);
	/* LOG */
	/*
	log_print ( "Row" ,  LOG_SAN_CONV_FILE );
	log_print_integer ( s.row ,  LOG_SAN_CONV_FILE );
	log_print ( "Col" , LOG_SAN_CONV_FILE );
	log_print_integer ( s.col ,  LOG_SAN_CONV_FILE );
	log_print_bitmap ( VM_valid_moves ( cur , &s ) , LOG_SAN_CONV_FILE );
	*/
	/* END LOG */
	return BM_Make_coord(l.row, l.col) & VM_valid_moves ( cur , &s ) & ~(ST_get_bitmap(cur, ST_get_col_on_move ( cur ))) ? 1 : 0;
}


/* Conversie UCHAR - SAN */

char aux_get_pieces(UCHAR c) {
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
	default:
		return ' ';
	}
}

/* Asociez fiecarei litere de pe tabla de sah o valoare*/

char convertToLetters(int a) {
	switch (a) {
	case 0:
		return 'a';
	case 1:
		return 'b';
	case 2:
		return 'c';
	case 3:
		return 'd';
	case 4:
		return 'e';
	case 5:
		return 'f';
	case 6:
		return 'g';
	default:
		return 'h';
	}
}

/* Conversie pentru coloane + verificare dak litera este coloana*/

char convertFromLetters(char a) {
	switch (a) {
	case 'a':
		return 1;
	case 'b':
		return 2;
	case 'c':
		return 3;
	case 'd':
		return 4;
	case 'e':
		return 5;
	case 'f':
		return 6;
	case 'g':
		return 7;
	case 'h':
		return 8;
	default:
		return 0;
	}
}

/* Verificam daca mutarea este o captura */

int is_capture(MOVE h, STATE cur) {
	if (move_get_p_tag(h) == T_P)
		return (move_get_poz_src(h).row != move_get_poz_dst(h).row) ? 1 : 0;
	BITMAP b = ST_get_bitmap(cur, ST_get_col_on_move ( cur ));
	LOC l = move_get_poz_dst(h);
	BITMAP d = BM_Make_coord(l.row, l.col);
	return (b & d) ? 1 : 0;
}

/* Refolosire de cod */
void set_flags(int j, char* msg, STATE cur, MOVE h) {
	char c;
	LOC l = move_get_poz_dst(h);
	if (is_capture(h, cur)) {
		msg[j++] = 'x';
	}
	sprintf(&c, "%d", l.col+1);
	msg[j++] = convertToLetters(l.row);
	msg[j++] = c;
	if (is_check(h, cur)) {
		msg[j++] = '+';
	}
	if (is_check_mate(h, cur)) {
		msg[j++] = '#';
	}
	if (move_get_m_tag(h)) {
		msg[j++] = '=';
		msg[j++] = aux_get_pieces(move_get_p_tag_pro(h));
	}
}

/* Convdersie SAN - UCHAR */

UCHAR get_piece(char c) {
	switch (c) {
	case 'K':
		return T_K;
	case 'Q':
		return T_Q;
	case 'B':
		return T_B;
	case 'N':
		return T_N;
	case 'R':
		return T_R;
	default:
		return 0;
	}
}

/* Verificare daca exista dezambiguizare */

int is_dezambiguu(char* c) {
	int i, boo1 = 0, boo2 = 0;
	for (i = 0; i < strlen(c); i++) {
		if (convertFromLetters(c[i])) {
			boo1++;
		}
		if (isdigit(c[i])) {
			boo2++;
		}
	}
	if (boo1 > boo2) {
		return boo1 % 2;
	} else {
		return boo2 % 2;
	}
}

/* Alegere piesa corecta - dezambiguizare */

char correct_piece(UCHAR lp, UCHAR cp, UCHAR ld, UCHAR cd, UCHAR piesa,
		STATE cur) {
	UCHAR lk, ck;
	UCHAR lg, cg;
	int k;
	LOC l;
	LOC d;
	int boo = 1;
	BITMAP s = ST_get_bitmap(cur, piesa) & ST_get_bitmap(cur, ST_get_col_on_move ( cur ));
	BM_Clear_piece_at_coord(&s, lp, cp);


	/* Pt. fiecare element din b verificam daca se poate muta pe poz d */

	while (s) {
		k = BM_Get_first_elem(s);
		lk = k / 8, ck = k % 8;
		MOVE m = move_new();
		move_set_p_tag(m, piesa);
		LOCp_set_both(&l, lk, ck);
		move_set_poz_src(m, l);
		LOCp_set_both(&d, ld, cd);
		move_set_poz_dst(m, d);

		if (validate_move(m,cur)) {
			lg = lk;
			cg = ck;
			boo = 0;
		}
		if (!boo) {
			if (cp == cg){
				move_free(m);
				return convertToLetters(lp);
			}
			else {
				char c;
				sprintf(&c, "%d", cp + 1);
				move_free(m);
				return c;
			}
		} else{
			move_free(m);
			BM_Clear_piece_at_coord(&s, lk, ck);
		}
	}
	return 'Z';

}

/* Gasirea piesei care trebuie mutata */

LOC gasire_piesa(STATE cur, int cg, int lg, LOC l, UCHAR c) {
	BITMAP b = ST_get_bitmap(cur, c) & ST_get_bitmap (cur, ST_get_col_on_move(cur));
	LOC d;
	UCHAR k, lk, ck;
	int bool = 0, booc = 0;
	if (cg == 255)
		booc = 1;
	if (lg == 255)
		bool = 1;
	while (b) {
		k = BM_Get_first_elem(b);
		lk = k / 8;
		ck = k % 8;
		if (cg == ck)
			booc = 1;
		if (lg == lk)
			bool = 1;
		MOVE m = move_new();
		move_set_p_tag(m, c);
		move_set_poz_dst(m, l);
		LOCp_set_both(&d, lk, ck);
		move_set_poz_src(m, d);

		if (validate_move(m, cur )) {
			if (bool && booc){
				move_free(m);
				return d;
			}else{
				move_free(m);
			}
		}else{
			move_free(m);
		}

		BM_Clear_piece_at_coord(&b, lk, ck);
	}
	return d;
}

/* --- Procedures --- */

char* Move_to_SAN(MOVE s) {
	
	if (move_get_m_tag(s) && (move_get_p_tag(s) == T_K)) {
		if (move_get_p_rock(s).row == 3){
			char *msg = (char*) malloc(5 * sizeof(char));
			msg = "O-O-O";
			return msg;
		}else{
			char *msg = (char*) malloc(3 * sizeof(char));
			msg = "O-O";
			return msg;
		}
	} else {
		char aux;
		int j = 0; //contorul pt crearea mesajul SAN
		STATE cur = cur_state_get();
		LOC src = move_get_poz_src(s); //Aflarea sursei
		UCHAR lp = src.row;
		UCHAR cp = src.col;
		LOC dst = move_get_poz_dst(s); //Aflarea destinatiei
		UCHAR ld = dst.row;
		UCHAR cd = dst.col;
		UCHAR piesa = move_get_p_tag(s);
		char *msg = (char*) malloc(10 * sizeof(char));

		/* Generarea notatiei SAN pt fiecare tip de piesa */

		if (piesa == T_P) {
			aux = correct_piece(lp, cp, ld, cd, piesa, cur);
			if (aux != 'Z')
				msg[j++] = aux;
			set_flags(j, msg, cur, s);
		}
		if (piesa == T_N) {
			msg[j++] = 'N';
			aux = correct_piece(lp, cp, ld, cd, piesa, cur);
			if (aux != 'Z')
				msg[j++] = aux;
			set_flags(j, msg, cur, s);
		}
		if (piesa == T_B) {
			msg[j++] = 'B';
			aux = correct_piece(lp, cp, ld, cd, piesa, cur);
			if (aux != 'Z')
				msg[j++] = aux;
			set_flags(j, msg, cur, s);
		}
		if (piesa == T_R) {
			msg[j++] = 'R';
			aux = correct_piece(lp, cp, ld, cd, piesa, cur);
			if (aux != 'Z')
				msg[j++] = aux;
			set_flags(j, msg, cur, s);
		}
		if (piesa == T_Q) {
			msg[j++] = 'Q';
			aux = correct_piece(lp, cp, ld, cd, piesa, cur);
			if (aux != 'Z')
				msg[j++] = aux;
			set_flags(j, msg, cur, s);
		}
		if (piesa == T_K) {
			msg[j++] = 'K';
			aux = correct_piece(lp, cp, ld, cd, piesa, cur);
			if (aux != 'Z')
				msg[j++] = aux;
			set_flags(j, msg, cur, s);
		}
		/* RAZVAN A SCRIS AICI: :), MIHAI SE UITA */
		char text[10];
		if(msg[0] == 'x' ) {
			
			text[0] = row_to_letter ( lp );
			text[1] = '\0';
			strcat(text , msg);
			strcpy (msg , text );
		}
		
		return msg;
	}
}

MOVE SAN_to_Move(char* s, STATE cur) {
	MOVE m = move_new();
	if (strcmp(s, "O-O") == 0 || strcmp(s, "o-o") == 0 || strcmp(s, "0-0") == 0) {
		if (!ST_get_col_on_move(cur)) {
			LOC src;
			LOCp_set_both(&src, 4, 0);
			move_set_poz_src(m, src);
			LOC dst;
			LOCp_set_both(&dst, 6, 0);
			move_set_poz_dst(m, dst);
			LOC castle;
			LOCp_set_both(&castle, 5, 0);
			move_set_p_rock(m, castle);
			move_set_m_tag(m, 1);
			move_set_p_tag(m, T_K);
		} else {
			LOC src;
			LOCp_set_both(&src, 4, 7);
			move_set_poz_src(m, src);
			LOC dst;
			LOCp_set_both(&dst, 6, 7);
			move_set_poz_dst(m, dst);
			LOC castle;
			LOCp_set_both(&castle, 5, 7);
			move_set_p_rock(m, castle);
			move_set_m_tag(m, 1);
			move_set_p_tag(m, T_K);
		}
		return m;
	}
	if (strcmp(s, "O-O-O") == 0 || strcmp(s, "o-o-o") == 0
			|| strcmp(s, "0-0-0") == 0) {
		if (!ST_get_col_on_move(cur)) {
			LOC src;
			LOCp_set_both(&src, 4, 0);
			move_set_poz_src(m, src);
			LOC dst;
			LOCp_set_both(&dst, 2, 0);
			move_set_poz_dst(m, dst);
			LOC castle;
			LOCp_set_both(&castle, 3, 0);
			move_set_p_rock(m, castle);
			move_set_m_tag(m, 1);
			move_set_p_tag(m, T_K);
		} else {
			LOC src;
			LOCp_set_both(&src, 4, 7);
			move_set_poz_src(m, src);
			LOC dst;
			LOCp_set_both(&dst, 2, 7);
			move_set_poz_dst(m, dst);
			LOC castle;
			LOCp_set_both(&castle, 3, 7);
			move_set_p_rock(m, castle);
			move_set_m_tag(m, 1);
			move_set_p_tag(m, T_K);
		}
	} else {
		if (get_piece(s[0])) {
			int j = 1;
			UCHAR lg = 255, cg = 255, lp, cp;
			move_set_p_tag(m, get_piece(s[0]));

			if (!is_dezambiguu(s)) {
				if (isdigit(s[j])) {
					j++;
					cg = s[j-1]-'1';
				} else {
					j++;
					lg = convertFromLetters(s[j - 1]) - 1;
				}
			}
			if (s[j] == 'x') {
				j++;
			}
			lp = convertFromLetters(s[j++]) - 1;
			cp = s[j++]-'1';
			LOC l;
			l.row = lp;
			l.col = cp;
			move_set_poz_dst(m, l);
			LOC h = gasire_piesa(cur, cg, lg, l, get_piece(s[0]));
			move_set_poz_src(m, h);
		} else {
			int j = 0;
			UCHAR lg = 255, cg = 255, lp, cp;
			move_set_p_tag(m, get_piece(s[0]));

			if (!is_dezambiguu(s)) {
				if (isdigit(s[j])) {
					j++;
					cg = s[j-1]-'1';
				} else {
					j++;
					lg = convertFromLetters(s[j - 1]) - 1;
				}
			}
			if (s[j] == 'x') {
				j++;
			}
			lp = convertFromLetters(s[j++]) - 1;
			cp = s[j++]-'1';
			LOC l;
			l.row = lp;
			l.col = cp;
			move_set_poz_dst(m, l);
			LOC h = gasire_piesa(cur, cg, lg, l, T_P);
			move_set_poz_src(m, h);
			move_set_p_tag ( m , T_P);
			if (s[j++] == '='){
				move_set_m_tag(m, 1);
				move_set_p_tag_pro(m, get_piece(s[j]));
			}
		}
	}
	return m;
}
