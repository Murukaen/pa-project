/* General description :
 *
 */

/* ----- System #includes ----- */

/* ----- Local #inlcudes ----- */

/* ---- Macro #define ---- */
typedef long long int BITMAP

/* --- Types --- */

/* --- Procedures --- */

/*citeste din fisierul All_moves.in toate mutarile posibile pentru toate piesele
 * (in afara de pioni) in vectorii dati ca parametru.
 * Ordinea parametrilor este : fisierul de intrare,rege, regina,tura,nebun,cal
 */
void Read_all_possible_moves(FILE*, BITMAP**, BITMAP**, BITMAP**, BITMAP**,
		BITMAP**);

/* citeste din fisierul Initial_positions pozitiile initiale ale pieselor
 * in fisier sunt scrise bitmapurile pieselor,in ordinea:
 * piese albe,rege alb, regina alba,tura alba, nebun alb,cal alb
 * imediat apoi aceleasi chestii pentru piesele negre
 */
void Read_initial_state(FILE*, BITMAP, BITMAP, BITMAP, BITMAP, BITMAP, BITMAP,
		BITMAP, BITMAP, BITMAP, BITMAP, BITMAP, BITMAP);
