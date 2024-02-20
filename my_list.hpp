#ifndef __MY_LIST_H__
#define __MY_LIST_H__


#include <stdlib.h>


struct list_element {
    struct list_element*    next;
    struct list_element*    prev;
    void*                   data;
};

typedef int (*compare_list_elements_fn) (struct list_element*, struct list_element*);

struct bidir_list {
    struct list_element*        head;
    struct list_element*        tail;
    int                         count;
    compare_list_elements_fn    criteria;
};

class linkedList{


    private:
    bool is_belonged_to_list(   struct bidir_list* l,
                                            struct list_element* le );
    void insert_empty_list( struct bidir_list* l,
                            struct list_element* new_elem);
    struct list_element*find_element_in_list(   struct bidir_list* l,
                                                struct list_element* test );
    void add_to_sort_list(  struct bidir_list* l,
                            struct list_element* new_element );
    void change_list_element_in_sort_list(
                            struct bidir_list* l,
                            struct list_element* what_to_find,
                            struct list_element* what_to_change);
    void delete_all_from_list( struct bidir_list* l );
    void resort_list( struct bidir_list* l, compare_list_elements_fn new_criteria );

    public:
    linkedList();
    linkedList(compare_list_elements_fn cmp_f);
    ~linkedList();

    struct list_element* create_list_element( void );
    struct list_element* create_list_element( void* new_data );
    void delete_list_element( struct list_element** del_element );
    struct bidir_list* create_bidir_list( void );
    struct bidir_list* create_bidir_list( compare_list_elements_fn cmp_f );

    struct list_element* get_list_element_at_pos( struct bidir_list* l, int pos);


    void insert_list_head(struct bidir_list* l, struct list_element* new_elem);
    void insert_list_tail(struct bidir_list* l, struct list_element* new_elem);
    void insert_list_between(struct bidir_list* l,
                            struct list_element* pos,
                            struct list_element* new_elem);

    void insert_list(struct bidir_list* l,
                    struct list_element* pos,
                    struct list_element* new_elem);


    struct list_element* delete_form_list_head( struct bidir_list* l, bool need_free );
    struct list_element* delete_form_list_tail( struct bidir_list* l, bool need_free );
    struct list_element* delete_form_list_middle (
                                struct bidir_list* l,
                                struct list_element* element,
                                bool need_free );
    struct list_element* delete_from_list( struct bidir_list* l,
                                    struct list_element* pos,
                                    bool need_free);
};

#endif // __MY_LIST_H__
