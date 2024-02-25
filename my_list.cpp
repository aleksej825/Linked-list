
#include "my_list.hpp"

#include <stdio.h>

linkedList::linkedList(){
    list = NULL;
    list = (struct bidir_list*) malloc( sizeof(struct bidir_list));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    list->criteria = NULL;
}

linkedList::linkedList(compare_list_elements_fn cmp_f){
    list = NULL;
    list = (struct bidir_list*) malloc( sizeof(struct bidir_list));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    list->criteria = cmp_f;
}

linkedList::~linkedList(){

}

// list_element* xxx = create_list_element();

struct list_element* linkedList::create_list_element( void )
{
    struct list_element* temp_element = NULL;
    temp_element = (struct list_element*) 
	                malloc( sizeof(struct list_element));
    /* (*temp_element).next = NULL; */  temp_element->next = NULL;
    /* (*temp_element).prev = NULL; */  temp_element->prev = NULL;
    /* (*temp_element).data = NULL; */  temp_element->data = NULL;

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


struct list_element* linkedList::create_list_element( void* new_data )
{
    struct list_element* temp_element = NULL;
    temp_element = (struct list_element*) malloc( sizeof(struct list_element));
    temp_element->next = NULL;
    temp_element->prev = NULL;
    temp_element->data = new_data;

    return temp_element;
}

void linkedList::delete_list_element( struct list_element** del_element )
{
    (*del_element)->next = NULL; // paranoic assignment
    (*del_element)->prev = NULL; // paranoic assignment

    if( (*del_element)->data != NULL)
        free( (*del_element)->data ); // free connected data first of all
    (*del_element)->data = NULL; // paranoic assignment

    free( *del_element );
    *del_element = NULL;
}

// struct bidir_list* linkedList::create_bidir_list( void )
// {
//     struct bidir_list* temp_list = NULL;
//     temp_list = (struct bidir_list*) malloc( sizeof(struct bidir_list));
//     temp_list->head = NULL;
//     temp_list->tail = NULL;
//     temp_list->count = 0;
//     temp_list->criteria = NULL;

//     return temp_list;
// }

// struct bidir_list* linkedList::create_bidir_list( compare_list_elements_fn cmp_f )
// {
//     struct bidir_list* temp_list = NULL;
//     temp_list = (struct bidir_list*) malloc( sizeof(struct bidir_list));
//     temp_list->head = NULL;
//     temp_list->tail = NULL;
//     temp_list->count = 0;
//     temp_list->criteria = cmp_f;

//     return temp_list;
// }



bool linkedList::is_belonged_to_list(struct list_element* le)
{
   bool presence_flag = false;

   struct list_element* wp = list->head;
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

void linkedList::insert_empty_list(struct list_element* new_elem)
{
    if( new_elem == NULL ) return;

    if( list->head == NULL && list->tail == NULL )
    {// check if the list is empty
        list->head = new_elem;
        list->tail = new_elem;
        list->count = 1;
    }
}

void linkedList::insert_list_head(struct list_element* new_elem)
{
    if( list->head == NULL || list->tail == NULL) return;

    new_elem->next = list->head;  /* 1 */
    list->head->prev  = new_elem; /* 2 */
    list->head = new_elem;        /* 3 */

    list->count++;
}

void linkedList::insert_list_tail(struct list_element* new_elem)
{
    if( list->head == NULL || list->tail == NULL) return;

    new_elem->prev = list->tail;  /* 1 */
    list->tail->next  = new_elem; /* 2 */
    list->tail =new_elem;         /* 3 */

    list->count++;
}

void linkedList::insert_list_between(   struct list_element* pos,
                                        // position AFTER which will be inserted
                                        struct list_element* new_elem)
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

void linkedList::insert_list(   struct list_element* pos,
                                struct list_element* new_elem)
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

struct list_element* linkedList::get_list_element_at_pos(int pos)
{
    struct list_element* wp = NULL;
    if( (pos < 0) || (pos >= list->count) ) return NULL;

    wp = list->head;
    for( int i = 0; i < pos ; i++ )
        wp = wp->next;

    return wp;
}



struct list_element*
linkedList::delete_form_list_head(bool need_free )
{
    if(     (list->head == NULL) ||
            (list->tail == NULL) ||
            (list == NULL ))
        return NULL;

    struct list_element* del_pos = list->head;

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

struct list_element*
linkedList::delete_form_list_tail(bool need_free )
{
    if(     (list->head == NULL) ||
            (list->tail == NULL) ||
            (list == NULL ))
        return NULL;

    struct list_element* del_pos = list->tail;

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

struct list_element* linkedList::delete_form_list_middle (
        struct list_element* element,
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

struct list_element*
linkedList::delete_from_list(   struct list_element* pos,
                                bool need_free )
{
    struct list_element* temp_element = NULL;
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

struct list_element*
linkedList::find_element_in_list( struct list_element* test )
{
    struct list_element* wp = list->head;

    while( wp != NULL )
    {
        if( list->criteria( test, wp ) == 0 )
            break;
        else
            wp = wp->next;
    }
    return wp;
}


void linkedList::add_to_sort_list( struct list_element* new_element )
{

struct list_element* wp = list->head;
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
void linkedList::change_list_element_in_sort_list(
        struct list_element* what_to_find,
        struct list_element* what_to_change)
{
    /* STAGE 1: find element that is need to be changed */
    struct list_element* fp = find_element_in_list(what_to_find);

    if (fp != NULL ) { // If element for changing is existed in the list

    /* STAGE 2: remove element from list */
    struct list_element* cp = delete_from_list(fp, false);

    /* STAGE 3: perform changes with data */
    free( cp->data );    
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

void linkedList::delete_all_from_list()
{
    if( list->head == NULL ) return;

    struct list_element* dp = list->head;


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

void linkedList::resort_list(compare_list_elements_fn new_criteria )
{
    if( new_criteria == NULL ) return;

    struct list_element* old_list = list->head;

    list->head = list->tail = NULL;
    list->count = 0;

    list->criteria = new_criteria;

    while( old_list != NULL)
    {
        old_list = old_list->next; // move to the next element

        old_list->prev->next = NULL; // perform insertion for previous element
        old_list->prev->prev = NULL;

        add_to_sort_list(old_list->prev);
        // add old elemnt to the list with new sorting criteria !
    }

}













