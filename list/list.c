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

key find_nod_list(List L, key content, FEQU compare_key) {

	if (L -> next == NULL) {
		return NULL;
	}

	L = L -> next;
	while (L -> next != NULL) {
				if (compare_key(L -> data_list, content) == 1) {
			return L->data_list;
		}
		L = L -> next;

	}



	if (compare_key(L -> data_list, content) == 1) {
		return L -> data_list;
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

	if ( (*L) -> next == NULL) { // daca lista vida
		return 0;
	}

	(*L) = (*L) -> next;

	return (*L) -> data_list;
}

void free_list(List L , FFREE fre ) {

	if ( L == 0 ) return;
	List aux;
	if(L->next == NULL){
		fre ( L-> data_list );
		free(L); return;
	}
	L = L -> next;

	while(L != NULL){

		aux = L;
		L = L -> next;
		fre(aux -> data_list );
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
