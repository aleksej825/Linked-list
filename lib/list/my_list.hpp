/**
 * @file my_list.hpp
 * @author Roman Yershov
 * @brief 
 * @version 0.1
 * @date 2024-03-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef __MY_LIST_HPP__
#define __MY_LIST_HPP__


#include <stdlib.h>

template <typename T>
struct list_element {
    struct list_element<T>*     next;
    struct list_element<T>*     prev;
    T*                          data;
};

template<typename T>
using compare_list_elements_fn = int (*) (struct list_element<T>*, struct list_element<T>*);

template <typename T>
struct bidir_list {
    struct list_element<T>*         head;
    struct list_element<T>*         tail;
    int                             count;
    compare_list_elements_fn<T>     criteria;
};


template <typename T>
class linkedList{
    private:
    bidir_list<T> *list;

    bool is_belonged_to_list(struct list_element<T>* le);
    void insert_empty_list(struct list_element<T>* new_elem);
    struct list_element<T>*find_element_in_list( struct list_element<T>* test );
    void add_to_sort_list( struct list_element<T>* new_element );
    void change_list_element_in_sort_list(
                            struct list_element<T>* what_to_find,
                            struct list_element<T>* what_to_change);
    void delete_all_from_list();
    // void resort_list(compare_list_elements_fn new_criteria );
    void insert_list_head(struct list_element<T>* new_elem);
    void insert_list_tail(struct list_element<T>* new_elem);
    void insert_list_between(   struct list_element<T>* pos,
                                struct list_element<T>* new_elem);

    struct list_element<T>* delete_form_list_head( bool need_free = true );
    struct list_element<T>* delete_form_list_tail( bool need_free = true );
    struct list_element<T>* delete_form_list_middle (
                                struct list_element<T>* element,
                                bool need_free = true );
    public:
    linkedList();
    linkedList(compare_list_elements_fn<T> cmp_f);
    ~linkedList();

    struct list_element<T>* create_list_element( void );
    struct list_element<T>* create_list_element( T* new_data);
    void delete_list_element( struct list_element<T>** del_element );
    struct bidir_list<T>* create_bidir_list( void );
    struct bidir_list<T>* create_bidir_list (compare_list_elements_fn<T> cmp_f);

    list_element<T>* get_list_element_at_pos(int pos);

    void insert_list(struct list_element<T>* pos,
                    struct list_element<T>* new_elem);

    struct list_element<T>* delete_from_list(  struct list_element<T>* pos,
                                            bool need_free = true);
    inline int get_elem_qty() { return list->count == 0 ? 0: list->count-1; }
};

#include "./my_list.cpp"

#endif // __MY_LIST_HPP__
