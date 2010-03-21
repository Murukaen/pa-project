/* Implementarea TAD lista simplu inlantuita
 */

#ifndef _LIST_H
#define _LIST_H

/* Types : */

#ifndef _KEY
#define _KEY
typedef void * key;
#endif

#ifndef _FFREE
#define _FFREE
typedef void ( *FFREE ) ( key );
#endif

/* FEQU - functie generica de testare a egalitatii
 *1 = true; 0 = false
 */

#ifndef _FEQU
#define _FEQU
typedef int (*FEQU) (key, key);
#endif

struct nod_lista;
typedef struct nod_lista * List;
typedef List Nod;




/* Functions : */

/*Constructor lista ( creeaza un pointer la un nod santinela - un nod de tipul nod_lista,
 * dar cu date vide )
 */
List new_list();

/* Test lista vida */
int is_empty_list(List);

/* Cauta un element intr-o lista ( prima aparitie ) .
 * Returneaza null daca nu gaseste si adresa elementului gasit in caz contrar
 */
key find_nod_list(List, key, FEQU);

/* Adauga un element la inceputul listei
 */
void add_nod_list(List, key);

/*Extragere a primului element din lista cu returnarea adresei listei ce pleaca de la urmatorul element
 * Lista va fi modificata ( primul element sters ) */
key first_nod_list(List*);

/* Desc:
 * Returns a copy of the given list
 * Input:1: list to copy
 * Output:1: the copy list
 */
List copy_list ( List );

/* Desc:
 * Searches for an element within a list and removes it modifying the list
 * Input:4: Address to list , key to look for , fequ , ffree
 * Output:0
 */
void delete_elem_list ( List * , key , FEQU , FFREE );

/* Desc:
 * Searches for an element within a list and removes it returning the modified list
 * Input:4: Address to list , key to look for , fequ , ffree
 * Output:1: modified list
 */
List create_without_elem_list ( List, key , FEQU, FFREE);

/* Destructor Lista */
void free_list(List , FFREE );

#endif

