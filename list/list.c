/* Implements list with start santinel
 */

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct nod_lista {

	key data_list;
	struct nod_lista *next;

};

List new_list() {

	Nod santinela = (Nod) malloc(1 * sizeof(struct nod_lista));
	santinela -> next = NULL;
	santinela -> data_list = NULL;

	return santinela;
}

int is_empty_list(List L) {

	return L -> next == NULL;
}

key find_nod_list(List L, key content, FEQU fequ) {

	if (L -> next == NULL) {
		return NULL;
	}

	while (L -> next != NULL) {

		if (fequ(L -> next -> data_list, content))
			return L -> next -> data_list;

		L = L -> next;
	}

	return NULL;
}

void add_nod_list(List L, key content) {

	Nod new = (Nod) calloc(1, sizeof(struct nod_lista));
	new -> data_list = content;

	new -> next = L -> next;
	L -> next = new;
}

key first_nod_list(List* L) {

	if ((*L) -> next == NULL) { // daca lista vida
		return 0;
	}

	*L = (*L) -> next;

	return (*L) -> data_list;
}

List list_copy(List l, FALLOC falloc) {

	List new_l = new_list();
	key elem;

	for (elem = first_nod_list(&l); elem; elem = first_nod_list(&l))

		add_nod_list(new_l, falloc(elem));

	return new_l;
}

void delete_elem_list(List L, key k, FEQU fequ, FFREE ffree) {

	if (L -> next == NULL)
		return;

	List aux;

	while (L -> next != NULL) {

		if (fequ(L -> next -> data_list, k)) {

			aux = L -> next;
			L -> next = L -> next -> next;
			ffree(aux -> data_list);
			free(aux);
		}

		else
			L = L -> next;

	}
}

List create_without_elem_list(List L, key k, FEQU fequ, FFREE ffree,
		FALLOC falloc) {

	List l_cp = list_copy(L, falloc);

	delete_elem_list(l_cp, k, fequ, ffree);

	return l_cp;
}

void free_list(List L, FFREE fre) {

	List aux;
	while (L) {

		aux = L;
		L = L -> next;
		fre(aux -> data_list);
		free(aux);
	}
}

void print_list(List L) {

	if (L -> next == NULL) {
		printf("Lista vida");
		return;
	}

	while (L -> next != NULL) {
		printf("%d,", *(int*) L -> next -> data_list);
		L = L ->next;
	}
	printf("\n");

}
