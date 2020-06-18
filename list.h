#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>

typedef char uint8;

typedef struct LIST {

	void* data;
	long unsigned data_len;
	struct LIST* next;
} LIST;

// CREATE, FREE, REMOVE, INNSERT, APPEND

void list_free_node(LIST* list);

LIST* list_create(void* data, long unsigned data_len);

void list_free(LIST* list);

LIST* list_search(LIST* list, void* data, long unsigned data_len);

LIST* list_insert_node(LIST* list, LIST* to_insert);

LIST* list_insert(LIST* list, void* data, unsigned long data_len);

LIST* list_remove_node(LIST* list, LIST* to_remove);

LIST* list_remove(LIST* list, void* data, long unsigned data_len);

LIST* list_append_node(LIST* list, LIST* to_append);

LIST* list_append(LIST* list, void* data, long unsigned data_len);

long unsigned list_size(LIST*);

// ORDER

#endif
