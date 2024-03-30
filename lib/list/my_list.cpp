/**
 * @file my_list.cpp
 * @author Roman Yershov
 * @brief 
 * @version 0.1
 * @date 2024-03-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __MY_LIST_CPP__
#define __MY_LIST_CPP__


#include "my_list.hpp"

#include <stdio.h>
#include <cstring>

template <typename T>
linkedList<T>::linkedList(){
    list = NULL;
    list = new bidir_list<T>();
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    list->criteria = NULL;
}

template <typename T>
linkedList<T>::linkedList(compare_list_elements_fn<T> cmp_f){
    list = NULL;
    list = new bidir_list<T>();
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    list->criteria = cmp_f;
}

template <typename T>
linkedList<T>::~linkedList(){

}

// list_element* xxx = create_list_element();

template <typename T>
 list_element<T>* linkedList<T>::create_list_element( void )
{
    list_element<T>* temp_element = NULL;
    temp_element = new list_element<T>();   

    return temp_element;
}

/* Default constructor
template <class T>
list_element<T> :: list_element()
{
	this->next = NULL; 
	this->prev = NULL; 	
	this->data = NULL; 	
}*/

// list_element<double>* xxx = new list_element;

/*
template <class T >
list_element* list_element<T> :: operator new()
{
//	list_element<T>* temp = NULL;
	
	this->next = NULL; 
	this->prev = NULL; 	
	this->data = NULL; 	
	
//	return tep;	
}
*/

template <typename T>
 list_element<T>* linkedList<T>::create_list_element( T* new_data)
{
     list_element<T>* temp_element = NULL;
    temp_element = new list_element<T>(new_data);

    return temp_element;
}
#include "iostream"
template <typename T>
void linkedList<T>::delete_list_element(  list_element<T>** del_element )
{
    delete *del_element;
    *del_element = NULL;
}

template <typename T>
bidir_list<T>* linkedList<T>::create_bidir_list( void )
{
    bidir_list<T>* temp_list = NULL;
    temp_list = new bidir_list<T>();
    temp_list->head = NULL;
    temp_list->tail = NULL;
    temp_list->count = 0;
    temp_list->criteria = NULL;

    return temp_list;
}

template <typename T>
bidir_list<T>* linkedList<T>::create_bidir_list( compare_list_elements_fn<T> cmp_f )
{
    bidir_list<T>* temp_list = NULL;
    temp_list = new bidir_list<T>();
    temp_list->head = NULL;
    temp_list->tail = NULL;
    temp_list->count = 0;
    temp_list->criteria = cmp_f;

    return temp_list;
}


template <typename T>
bool linkedList<T>::is_belonged_to_list( list_element<T>* le)
{
   bool presence_flag = false;

    list_element<T>* wp = list->head;
   // create and set 'work pointer' to the list beginning

   while( wp != NULL ){ // while the end of list is not reached
       if( wp == le ) {
            presence_flag = true;
            break;
       }
       wp = wp->next; // switching to the next list element
   }

   return presence_flag;
}

template <typename T>
void linkedList<T>::insert_empty_list( list_element<T>* new_elem)
{
    if( new_elem == NULL ) return;

    if( list->head == NULL && list->tail == NULL )
    {// check if the list is empty
        list->head = new_elem;
        list->tail = new_elem;
        list->count = 1;
    }
}

template <typename T>
void linkedList<T>::insert_list_head( list_element<T>* new_elem)
{
    if( list->head == NULL || list->tail == NULL) return;

    new_elem->next = list->head;  /* 1 */
    list->head->prev  = new_elem; /* 2 */
    list->head = new_elem;        /* 3 */

    list->count++;
}

template <typename T>
void linkedList<T>::insert_list_tail( list_element<T>* new_elem)
{
    if( list->head == NULL || list->tail == NULL) return;

    new_elem->prev = list->tail;  /* 1 */
    list->tail->next  = new_elem; /* 2 */
    list->tail =new_elem;         /* 3 */

    list->count++;
}

template <typename T>
void linkedList<T>::insert_list_between(    list_element<T>* pos,
                                        // position AFTER which will be inserted
                                         list_element<T>* new_elem)
{
    if( list->head == NULL || list->tail == NULL) return;

    if ( ! is_belonged_to_list(pos)) return;
    // firstly, agree connections from element to list
    new_elem->next = pos->next;      /* 1 */
    new_elem->prev = pos;            /* 2 */

    pos->next = new_elem;            /* 3 */
    new_elem->next->prev = new_elem; /* 4 */

    /* Alternative:
        pos->next->prev = new_elem;
        pos->next = new_elem;
    */

    list->count++;
}

template <typename T>
void linkedList<T>::insert_list(    list_element<T>* pos,
                                 list_element<T>* new_elem)
{
    if( new_elem == NULL ) return;

    if( list->head == NULL && list->tail == NULL ) {
        insert_empty_list(new_elem );
        printf("Insert into EMPTY list \n");
    } else if( pos == NULL ) {
        insert_list_head(new_elem );
        printf("Insert into list HEAD \n");
    } else if ( pos == list->tail ) {
        insert_list_tail(new_elem );
        printf("Insert into list TAIL \n");
    } else {
        insert_list_between(pos, new_elem);
        printf("Insert into list BETWEEN \n");
    }
}

template <typename T>
list_element<T>* linkedList<T>::get_list_element_at_pos(int pos)
{
     list_element<T>* wp = NULL;
    if( (pos < 0) || (pos >= list->count) ) return NULL;

    wp = list->head;
    for( int i = 0; i < pos ; i++ )
        wp = wp->next;

    return wp;
}

template <typename T>
 list_element<T>* linkedList<T>::delete_form_list_head(bool need_free )
{
    if(     (list->head == NULL) ||
            (list->tail == NULL) ||
            (list == NULL ))
        return NULL;

     list_element<T>* del_pos = list->head;

    if( list->head != list->tail ) {
        // check if list has more than element
        list->head = list->head->next;
        list->head->prev = NULL;
    } else {
        // list has only one element, so, after
        // deleting list will become empty
        list->head = NULL;
        list->tail = NULL;
    }

    list->count--;

    if( need_free == true ) {
        delete_list_element( & del_pos );
        return NULL;
    } else {
        return del_pos;
    }
}

template <typename T>
 list_element<T>* linkedList<T>::delete_form_list_tail(bool need_free )
{
    if(     (list->head == NULL) ||
            (list->tail == NULL) ||
            (list == NULL ))
        return NULL;

     list_element<T>* del_pos = list->tail;

    if( list->head != list->tail ) {
        // check if list has more than element
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    } else {
        // list has only one element, so, after
        // deleting list will become empty
        list->head = NULL;
        list->tail = NULL;
    }

    list->count--;

    if( need_free == true ) {
        delete_list_element( & del_pos );
        return NULL;
    } else {
        return del_pos;
    }
}

template <typename T>
 list_element<T>* linkedList<T>::delete_form_list_middle (
         list_element<T>* element,
        bool need_free )
{
    if( element == NULL ) return NULL;

    if( !is_belonged_to_list(element)) return NULL;

    if(list->head != list->tail ) {
        // check if list has more than element
        element->prev->next = element->next;
        element->next->prev = element->prev;
    } else {
        list->head = NULL;
        list->tail = NULL;
    }


    list->count--;
    if( need_free == true ) {
        delete_list_element( & element );
        return NULL;
    } else {
        return element;
    }
}

template <typename T>
 list_element<T>*linkedList<T>::delete_from_list(    list_element<T>* pos,
                                                    bool need_free )
{
     list_element<T>* temp_element = NULL;
    if( list->head == NULL && list->tail == NULL ) // empty list
    {
        return NULL;
    } else if( pos == list->head ) {
        temp_element = delete_form_list_head(need_free);
    } else if ( pos == list->tail ) {
        temp_element = delete_form_list_tail(need_free);
    } else {
        temp_element = delete_form_list_middle(pos, need_free);
    }
    return temp_element;
}

template <typename T>
 list_element<T>* linkedList<T>::find_element_in_list(  list_element<T>* test )
{
     list_element<T>* wp = list->head;

    while( wp != NULL )
    {
        if( list->criteria( test, wp ) == 0 )
            break;
        else
            wp = wp->next;
    }
    return wp;
}

template <typename T>
void linkedList<T>::add_to_sort_list(  list_element<T>* new_element )
{

 list_element<T>* wp = list->head;
int compare_prev = 0;
int compare_curr = 0;

    while( wp != NULL )
    {
        compare_prev = compare_curr;
        compare_curr = list->criteria( new_element, wp );

        if( compare_prev != compare_curr )
            break;
        else
            wp = wp->next;
    }

    // insertion is performed before the element on
    // which the search cycle is broke

    insert_list(wp->prev, new_element);
}

/**
 *  @WARNING: pointers onto list elements: what_to_find, what_to_change
 *  need to be free in high-level code after this function call have
 *  been executed due to fact that there are only temporarycontainers
 *  for end-data
**/
template <typename T>
void linkedList<T>::change_list_element_in_sort_list(
         list_element<T>* what_to_find,
         list_element<T>* what_to_change)
{
    /* STAGE 1: find element that is need to be changed */
     list_element<T>* fp = find_element_in_list(what_to_find);

    if (fp != NULL ) { // If element for changing is existed in the list

    /* STAGE 2: remove element from list */
     list_element<T>* cp = delete_from_list(fp, false);

    /* STAGE 3: perform changes with data */
    // free( cp->data );    
    delete cp->data;
    cp->data = what_to_change->data; // VERY COARSE CHANGING METHOD !!!

    /* STAGE 4: add changed element to list again */
    add_to_sort_list(cp);
    }
}

// (*A).x   <==>    A->x
// Why arrow operator is neccesary ?
// (*(*(*head).next).next).data
// IS EQUAL TO:
// head->next->next->data

template <typename T>
void linkedList<T>::delete_all_from_list()
{
    if( list->head == NULL ) return;

     list_element<T>* dp = list->head;


    while( dp != NULL )
    {
        dp =  dp -> next;
     //   remove_list_element( dp -> prev);
    }

    // remove_list_element( list->tail );

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;

}

template <typename T>
void linkedList<T>::resort_list(compare_list_elements_fn<T> new_criteria )
{
    if( new_criteria == NULL ) return;

    list->criteria = new_criteria;

    // Start from the head of the list
     list_element<T>* i = list->head;
	// Loop over each element in the list
    while (i != nullptr) {
		// Assume the current element is the smallest
         list_element<T>* min = i;
		// Look for a smaller element in the rest of the list
         list_element<T>* j = i->next;
        while (j != nullptr) {
			// If a smaller element is found, update min
            if (list->criteria(j, min) == 1) {
                min = j;
            }
            j = j->next;
        }
		// If a smaller element was found, swap the data of the current element and the smallest element
        if (min != i) {
            // Swap the data of i and min
            T* temp = i->data;
            i->data = min->data;
            min->data = temp;
        }
		// Move on to the next element
        i = i->next;
    }

}

#endif // __MY_LIST_CPP__