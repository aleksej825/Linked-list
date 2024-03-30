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
class list_element {
    public:
    list_element<T>*     next;
    list_element<T>*     prev;
    T*                         data;
    
    list_element(){
        next = NULL;
        prev = NULL;
        data = NULL;
    }
    list_element(T* new_data){
        next = NULL;
        prev = NULL;
        data = new_data;
    }
    ~list_element(){
        if(data != NULL)
            delete data;
    }

};

template<typename T>
using compare_list_elements_fn = int (*) (list_element<T>*, list_element<T>*);

template <typename T>
class bidir_list {
    public:
    list_element<T>*         head;
    list_element<T>*         tail;
    int                             count;
    compare_list_elements_fn<T>     criteria;

    bidir_list(){
        head = NULL;
        tail = NULL;
        count = 0;
        criteria = NULL;
    }

    ~bidir_list(){

    }
};


template <typename T>
class linkedList{
    private:
    bidir_list<T> *list;

    bool is_belonged_to_list(list_element<T>* le);
    void insert_empty_list(list_element<T>* new_elem);
    list_element<T>*find_element_in_list( list_element<T>* test );
    void add_to_sort_list( list_element<T>* new_element );
    void change_list_element_in_sort_list(
                            list_element<T>* what_to_find,
                            list_element<T>* what_to_change);
    void delete_all_from_list();
    void insert_list_head(list_element<T>* new_elem);
    void insert_list_tail(list_element<T>* new_elem);
    void insert_list_between(   list_element<T>* pos,
                                list_element<T>* new_elem);

    list_element<T>* delete_form_list_head( bool need_free = true );
    list_element<T>* delete_form_list_tail( bool need_free = true );
    list_element<T>* delete_form_list_middle (
                                list_element<T>* element,
                                bool need_free = true );
    public:
    linkedList();
    linkedList(compare_list_elements_fn<T> cmp_f);
    ~linkedList();

    void resort_list(compare_list_elements_fn<T> new_criteria );
    list_element<T>* create_list_element( void );
    list_element<T>* create_list_element( T* new_data);
    void delete_list_element( list_element<T>** del_element );
    bidir_list<T>* create_bidir_list( void );
    bidir_list<T>* create_bidir_list (compare_list_elements_fn<T> cmp_f);

    list_element<T>* get_list_element_at_pos(int pos);

    void insert_list(list_element<T>* pos,
                    list_element<T>* new_elem);

    list_element<T>* delete_from_list(  list_element<T>* pos,
                                        bool need_free = true);
    inline int get_elem_qty() { return list->count; }
};

#include "./my_list.cpp"

#endif // __MY_LIST_HPP__
