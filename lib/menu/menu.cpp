#include "menu.hpp"
#include "iostream"
#include <limits>

lib_menu::lib_menu(){

}

lib_menu::~lib_menu(){

}

void lib_menu::addElement(){
    std::string name;
    std::string author;
    std::string content;
    std::cout << "Enter the new book name: ";
    std::getline(std::cin>>ws, name);
    std::cout << "Enter the author: ";
    std::getline(std::cin>>ws, author);
    std::cout << "Enter the book content: ";
    std::getline(std::cin>>ws, content);

    Book *new_item = new Book(name, author, content);

    list_element<Book>* new_elem = list.create_list_element(new_item);
    
    int elem_qty = list.get_elem_qty();
    list_element<Book>* existing_elem = list.get_list_element_at_pos(elem_qty);
    list.insert_list(existing_elem, new_elem);

    std::cout << "New Book has been added" << std::endl;
    std::cout << "*********************" << std::endl;
}

void lib_menu::editElement(){
    std::string new_data;
    int index = 0; 

    std::cout << "Enter the element index: ";
    std::cin >> index;

    if(!std::cin){
        std::cout  << "Error: wrong input index" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    list_element<Book>* existing_elem = list.get_list_element_at_pos(--index);
    if(existing_elem == NULL){
        std::cout << "Error: element not found" << std::endl;
        return;
    }

    std::string name;
    std::string author;
    std::string content;
    std::cout << "Enter the new book name: ";
    std::cin >> name;
    std::cout << "Enter the author: ";
    std::cin >> author;
    std::cout << "Enter the book content: ";
    std::cin >> content;

    Book *new_item = new Book(name, author, content);

    list_element<Book>* new_elem = list.create_list_element(new_item);

    list.insert_list(existing_elem, new_elem);
    list.delete_from_list(existing_elem);

    std::cout << "New Book has been edited" << std::endl;
    std::cout << "*********************" << std::endl;
}

void lib_menu::removeElement(){
    int index = 0; 

    std::cout << "Enter the element index: ";
    std::cin >> index;

    if(!std::cin){
        std::cout  << "Error: wrong input index" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    list_element<Book>* existing_elem = list.get_list_element_at_pos(--index);
    if(existing_elem == NULL){
        std::cout << "Error: element not found" << std::endl;
        return;
    }
    list.delete_from_list(existing_elem);

    std::cout << "Element has been removed" << std::endl;
    std::cout << "*********************" << std::endl;
}

void lib_menu::printList(){
   std::cout << "List of elements:" << std::endl;
    int counter = 0;
    list_element<Book> *item = list.get_list_element_at_pos(counter++);
    while(item != NULL){
        Book* data = item->data;
        std::cout << counter << ":" << std::endl;
        std::cout << data << std::endl;
        item = list.get_list_element_at_pos(counter++);
    }

    std::cout << "*********************" << std::endl;
}


void lib_menu::closeProgram(){
    exit(0);
}
