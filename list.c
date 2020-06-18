#include "list.h"

uint8 _list_cmp_data(LIST* list, void* data, long unsigned data_len){

	return list->data_len == data_len && !memcmp(list->data, data, data_len);
}

uint8 _list_data_is_null(LIST* list, void* data, long unsigned data_len){

	return !list->data;
}

typedef uint8 (*list_if_search)(LIST* list, void* data, long unsigned data_len);

LIST* _list_search(LIST* list, void* data, long unsigned data_len, list_if_search if_func ){

	for(; list ; list = list->next )
	
		if( if_func(list, data, data_len) )

			return list;

	return list;
}

LIST* list_search(LIST* list, void* data, long unsigned data_len){

	if( data )
		return _list_search(list, data, data_len, _list_cmp_data);
	else
		return _list_search(list, data, data_len, _list_data_is_null);
}

LIST* _list_return_valid(LIST* list, LIST* to_insert){

	return list ?: to_insert;
}

LIST* _list_insert_next(LIST* list, LIST* to_insert){

	to_insert->next = list->next;
	list->next = to_insert;
	return list;
}

LIST* list_insert_node(LIST* list, LIST* to_insert){

	if( !list || !to_insert )
		return _list_return_valid(list, to_insert);

	return _list_insert_next(list, to_insert);
}

LIST* list_insert(LIST* list, void* data, long unsigned data_len){

	LIST* new = list_create(data, data_len);
	return list_insert_node(list, new);
}

LIST* _list_remove_node_return_next(LIST* list){

	LIST* node = list->next;
	list_free_node(list);
	return node;
}

LIST* _list_find_previous(LIST* list, LIST* find){

	for(; list && list->next != find; list = list->next);

	return list;
}

void _list_remove_node(LIST* previous){

	if(!previous) return;

	LIST* to_remove = previous->next;
	previous->next = to_remove->next;
	list_free_node(to_remove);
}

void _list_find_and_remove_node(LIST* list, LIST* to_remove){

	
	_list_remove_node( _list_find_previous(list, to_remove) );
}

LIST* list_remove_node(LIST* list, LIST* to_remove){

	if( !to_remove )

		return list;

	if( list == to_remove )

		return _list_remove_node_return_next(list);

	_list_find_and_remove_node(list, to_remove);

	return list;
}

uint8 _list_previous_data(LIST* list, void* data, long unsigned data_len){

	return list->next && _list_cmp_data(list->next, data, data_len);
}

uint8 _list_previous_data_is_null(LIST* list, void* data, long unsigned data_len){

	return list->next && _list_data_is_null(list->next, data, data_len);
}

LIST* _list_previous_search(LIST* list, void* data, long unsigned data_len, list_if_search if_func){

	if( data )
		return _list_search(list, data, data_len, _list_previous_data);
	else
		return _list_search(list, data, data_len, _list_previous_data_is_null);
}

void _list_find_remove(LIST* list, void* data, long unsigned data_len){

	_list_remove_node( _list_previous_search(list, data, data_len, _list_previous_data) );
}

uint8 _list_cmp_data_null(LIST* list, void* data, long unsigned data_len){

	return list && ( ( !data && list->data == data ) || ( _list_cmp_data( list, data, data_len ) ) );
}

LIST* list_remove(LIST* list, void* data, long unsigned data_len){
	
	_list_find_remove(list, data, data_len);

	if( _list_cmp_data_null(list, data, data_len) )

		return _list_remove_node_return_next(list);

	return list;
}

uint8 _list_is_last(LIST* list, void* data, long unsigned data_len){

	return !list->next;
}

LIST* list_append_node(LIST* list, LIST* to_append){

	LIST* last = _list_search(list, NULL, 0, _list_is_last);

	if( last ) list_insert_node(last, to_append);

	return _list_return_valid(list, to_append);
}

LIST* list_append(LIST* list, void* data, long unsigned data_len){

	LIST* new = list_create(data, data_len);
	return list_append_node(list, new);
}

long unsigned list_size(LIST* list){

	long unsigned size=0;
	for(; list ; list = list->next, size++);
	return size;
}
void list_free_node(LIST* list){

	if( !list ) return;

	free(list->data);
	free(list);
}

void _list_copy_data(LIST* list, void* data, long unsigned data_len){

	list->data = memcpy( malloc(data_len), data, data_len);
	list->data_len = data_len;
}

void _list_unset(LIST* list){

	list->data = NULL;
	list->data_len = 0;
}

void _list_set(LIST* list, void* data, long unsigned data_len){

	if( data && data_len )

		_list_copy_data(list, data, data_len);
	else

		_list_unset(list);
}

LIST* list_create(void* data, long unsigned data_len){

	LIST* list = malloc(sizeof(LIST));

	list->next = NULL;

	if( list ) _list_set(list, data, data_len);

	return list;
}

LIST* _list_free_current_return_next(LIST* list){

	LIST* tmp = list->next;
	list_free_node( list );
	return tmp;
}

void list_free(LIST* list){

	while( list )

		list = _list_free_current_return_next(list);
}

