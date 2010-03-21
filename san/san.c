/* General description :
 *
 */

/* ----- System #includes ----- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ----- Local #inlcudes ----- */
#include "san.h"

/* ---- Macro #define ---- */

/* --- Types --- */

/* --- Globals --- */

/* --- Auxiliary Procedures --- */

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
	BITMAP b = ST_get_bitmap(cur, T_BP);
	LOC l = move_get_poz_dst(h);
	BITMAP d = BM_Make_coord(loc_get_row(l), loc_get_column(l));
	return (b & d) ? 1 : 0;
}

/* Refolosire de cod */
void set_flags(int j, char* msg, STATE cur, MOVE h) {
	char c;
	LOC l = move_get_poz_dst(h);
	if (is_capture(h, cur)) {
		msg[*j++] = 'x';
	}
	sprintf(&c,"%d",loc_get_row(l));
	msg[j++] = c;
	msg[j++] = convertToLetters(loc_get_column(l));
	if (is_check(h, cur)) {
		msg[j++] = '+';
	}
	if (is_check_mate(h, cur)) {
		msg[j++] = '#';
	}
	if (move_get_p_tag_pro(h)) {
		msg[j++] = '=';
		msg[j++] = get_pieces(move_get_p_tag_pro(h));
	}
}

/* Conversie UCHAR - SAN */

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
	case 'P':
		return T_P;
	}
}

/* Verificare daca exista dezambiguizare */

int is_dezambiguu(char* c) {
	int i, boo1 = 0, boo2 = 0;
	for (i = 0; i < strlen(c); i++) {
		if (convertFromLetters(c[i])) {
			boo1++;
		}
		if (isDigit(c[i])) {
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

	BITMAP s = ST_get_bitmap(cur, piesa);
	BM_Clear_piece_at_coord(&s, lp, cp);

	/* Pt. fiecare element din b verificam daca se poate muta pe poz d */

	while (s) {
		UCHAR lg, cg;
		int boo = 1;
		int k = BM_Get_first_elem(s);
		UCHAR lk = k / 8, ck = k % 8;
		MOVE m = move_new();
		move_set_p_tag(m, piesa);
		LOC l;
		LOC_set_both(l, lk, ck);
		move_set_poz_src(m, l);
		LOC d = loc_new();
		LOC_set_both(d, ld, cd);
		move_set_poz_dst(m, d);

		if (validate_move(m)) {
			lg = lk;
			cg = ck;
			boo = 0;
		}
		if (!boo) {
			if (lc == lg)
				return convertToLetters(cp);
			else{
				char c;
				sprintf (&c,"%d",lp + 1);
			}
		} else
			BM_Clear_piece_at_coord(&s, lk, ck);
	}
	return 'Z';

}

/* --- Procedures --- */

char* toSAN(MOVE s) {
	if (s->m_tag) {
		char *msg = (char*) malloc(5 * sizeof(char));
		msg = "O-O-O";
		return msg;
	} else if (s->m_tag) {
		char *msg = (char*) malloc(3 * sizeof(char));
		msg = "O-O";
		return msg;
	} else {
		char aux;
		int j = 0; //contorul pt crearea mesajul SAN
		STATE cur = cur_state_get();
		LOC src = move_get_poz_src(s); //Aflarea sursei
		UCHAR lp = loc_get_row(src);
		UCHAR cp = loc_get_col(src);
		LOC dst = move_get_poz_dst(s); //Aflarea destinatiei
		UCHAR ld = loc_get_row(dst);
		UCHAR cd = loc_get_col(dst);
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
		return msg;
	}
}

MOVE from_SAN(char* s) {
	MOVE m = move_new();
	int j = 0;
	STATE cur = cur_state_get();
	if (strcmp(s, "O-O") == 0 || strcmp(s, "o-o") == 0 || strcmp(s, "0-0") == 0) {
		if (side == white) {
			LOC l = LOC_set_both(0, 0);
			move_set_p_rock(m, l);
			move_set_m_tag(m, T_MOV_CST);
		} else {
			LOC l = LOC_set_both(7, 7);
			move_set_p_rock(m, l);
			move_set_m_tag(m, T_MOV_CST);
		}
		return mutari;
	}
	if (strcmp(s, "O-O-O") == 0 || strcmp(s, "o-o-o") == 0
			|| strcmp(s, "0-0-0") == 0) {
		BITMAP* mutari = (BITMAP*) malloc(4 * sizeof(BITMAP));
		if (side == white) {
			LOC l = LOC_set_both(0, 7);
			move_set_p_rock(m, l);
			move_set_m_tag(m, T_MOV_CST);
		} else {
			LOC l = LOC_set_both(7, 0);
			move_set_p_rock(m, l);
			move_set_m_tag(m, T_MOV_CST);
		}
		else
		{
			if (get_piece(s[0]))
			{
				UCHAR lg, cg;
				int k = BM_Get_first_elem(s);
				UCHAR lk = k / 8, ck = k % 8;
				MOVE m = move_new ();
				move_set_p_tag ( m , piesa );
				LOC l;
				LOC_set_both ( l , lk , ck );
				move_set_poz_src ( m, l );
				LOC d = loc_new();
				LOC_set_both ( d, ld, cd );
				move_set_poz_dst ( m, d );

				if (is_dezambiguu(s))
				{
					if (isDigit(s[1]))
					{
						j++;
						lp = atoi(s[1]);
					}
					else
					{
						j++;
						cp = convertFromLetters(s[1]);
					}
				}
				else
				{

				}
				if (s[j] == 'x')
				{
					j++;
				}
				cp = convertFromLetters(s[j++]) - 1;
				lp = atoi(s[j++]);
				if (s[j++] == '=')
				{
					m.set_m_tag(T_MOV_PRO);
					m.set_p_tag_pro(get_piece(s[j]));
				}
			}
			else
			{
				move_set_p_tag (T_P);
				int cp, lp;
				move_set_p_tag (get_piece(s[0]));
				j++;
				if (is_dezambiguu(s))
				{
					if (isDigit(s[1]))
					{
						j++;
						lp = atoi(s[1]);
					}
					else
					{
						j++;
						cp = convertFromLetters(s[1]);
					}
				}
				if (s[j] == 'x')
				{
					j++;
				}
				cp = convertFromLetters(s[j++]) - 1;
				lp = atoi(s[j++]);
				if (s[j++] == '=')
				{
					m.set_m_tag(T_MOV_PRO);
					m.set_p_tag_pro(get_piece(s[j]));
				}
			}
			return m;

		}
	}
}

int main() {
	return 0;
}
