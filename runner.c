#include <ctdd/ctdd.h>
#include "list.h"

int list_free_node_test(){

	LIST* list = malloc(sizeof(LIST));
	memset(list, '\0', sizeof(LIST));

	list_free_node(list);

	list_free_node(NULL);

	return 0;
}

int list_create_test(){

	LIST* list = list_create(NULL, 0);

	ctdd_assert(list);
	ctdd_assert(!list->data && !list->data_len && !list->next);

	list_free_node(list);

	list = list_create(NULL, 4);

	ctdd_assert(list);
	ctdd_assert(!list->data && !list->data_len && !list->next);

	list_free_node(list);

	list = list_create("sup", 0);

	ctdd_assert(list);
	ctdd_assert(!list->data && !list->data_len && !list->next);

	list_free_node(list);

	list = list_create("sup", 4);

	ctdd_assert(list);
	ctdd_assert(!list->next);
	ctdd_assert(!strcmp(list->data, "sup"));
	ctdd_assert(list->data!="sup");
	ctdd_assert(list->data_len == 4);

	list_free_node(list);

	return 0;
}

int list_free_test(){

	LIST* list = list_create("hello", 6);

	list_free(list);

	list = list_create("ciao", 5);
	list->next = list_create("hey mate", 9);

	list_free(list);

	list_free(NULL);

	return 0;
}

int list_search_test(){

	LIST* list = list_create("hello", 6);
	list->next = list_create("ciao", 5);
	list->next->next = list_create("sup", 4);
	list->next->next->next = list_create(NULL, 0);

	ctdd_assert(list_search(list, "hello", 6) == list);

	ctdd_assert(list_search(list, "ciao", 5) == list->next);

	ctdd_assert(list_search(list, "sup", 4) == list->next->next);

	ctdd_assert(list_search(list, "heya", 5) == NULL);

	ctdd_assert(list_search(list, "sup", 5) == NULL);

	ctdd_assert(list_search(list, NULL, 4) == list->next->next->next);

	ctdd_assert(list_search(list, NULL, 0) == list->next->next->next);

	list_free(list);

	return 0;
}

int list_insert_node_test(){

	LIST* list = list_create("sup", 4);
	LIST* node = list_create("hey", 4);

	ctdd_assert(list == list_insert_node(list, node));
	ctdd_assert(list->next == node);

	ctdd_assert(list == list_insert_node(NULL, list));
	ctdd_assert(list == list_insert_node(list, NULL));

	ctdd_assert(NULL == list_insert_node(NULL, NULL));

	list_free(list);

	return 0;
}

int list_insert_test(){

	LIST* list = list_create("sup", 4);
	LIST* node = list_create(NULL, 0);
	list_insert_node(list, node);

	list = list_insert(list, "hello", 6);

	ctdd_assert(!strcmp(list->next->data, "hello"));

	ctdd_assert(list->next->next == node);

	LIST* node2 = list_insert(NULL, NULL, 0);

	ctdd_assert(node2);

	list_free(node2);

	list_free(list);

	return 0;
}

int list_remove_node_test(){

	LIST* list = list_create(NULL, 0);
	list_insert(list, NULL, 0);
	list_insert(list, NULL, 0);

	LIST* node1 = list->next;
	LIST* node2 = list->next->next;

	list = list_remove_node(list, node1);

	ctdd_assert(list->next != node1);
	ctdd_assert(list->next->next == NULL);

	LIST* ret = list_remove_node(list, list);
	ctdd_assert(ret == node2);
	ctdd_assert(!node2->next);

	ctdd_assert(list_remove_node(NULL, list) == NULL);
	ctdd_assert(list_remove_node(NULL, NULL) == NULL);
	ctdd_assert(list_remove_node(ret, NULL) == ret);

	list_free(ret);

	return 0;
}

int list_remove_test(){

	LIST* list = list_create(NULL, 0);
	list = list_insert(list, "sup", 4);
	list = list_insert(list, "hello", 6);

	LIST* node = list->next->next;

	list = list_remove(list, "hello", 6);

	ctdd_assert(list);
	ctdd_assert(!strcmp(list->next->data, "sup"));

	list = list_remove(list, NULL, 0);

	ctdd_assert(list);
	ctdd_assert(list == node);

	list_free(list);

	list = list_create("sup", 4);
	list = list_insert(list, "hello", 6);

	list = list_remove(list, "sup", 4);

	ctdd_assert( !strcmp(list->data, "hello") );
	ctdd_assert( !list->next );

	list_free(list);

	ctdd_assert( !list_remove(NULL, NULL, 0) );

	return 0;
}

int list_append_node_test(){

	LIST* list = list_create(NULL, 0);
	LIST* node1 = list_create("1", 2);
	LIST* node2 = list_create("2", 2);

	list = list_append_node(list, node1);

	ctdd_assert(list);
	ctdd_assert(list->next == node1);

	list = list_append_node(list, node2);

	ctdd_assert(list->next->next == node2);

	ctdd_assert( list_append_node(list, NULL) == list );

	ctdd_assert( list_append_node(NULL, list) == list );

	ctdd_assert( list_append_node(NULL, NULL) == NULL );

	list_free(list);

	return 0;
}

int list_append_test(){

	LIST* list = list_create(NULL, 0);

	list = list_append(list, "sup", 4);

	ctdd_assert(list);

	ctdd_assert( !strcmp(list->next->data, "sup") );

	list = list_append(list, NULL, 0);

	ctdd_assert( !list->next->next->data );

	LIST* node = list_append(NULL, NULL, 0);

	ctdd_assert(node);
	ctdd_assert( !node->data );

	list_free(list);
	list_free(node);

	return 0;
}

int list_size_test(){

	ctdd_assert( 0 == list_size(NULL) );

	LIST* list = list_create(NULL, 0);

	ctdd_assert( list_size(list) == 1 );

	list = list_append(list, NULL, 0);

	ctdd_assert(list_size(list) == 2);

	list_free(list);

	return 0;
}

int run_tests(){

	ctdd_verify(list_free_node_test);

	ctdd_verify(list_create_test);

	ctdd_verify(list_free_test);

	ctdd_verify(list_search_test);

	ctdd_verify(list_insert_node_test);

	ctdd_verify(list_insert_test);

	ctdd_verify(list_remove_node_test);

	ctdd_verify(list_remove_test);

	ctdd_verify(list_append_node_test);

	ctdd_verify(list_append_test);

	ctdd_verify(list_size_test);

	return 0;
}

int main(){

	ctdd_setup_signal_handler();

	return ctdd_test(run_tests);
}
