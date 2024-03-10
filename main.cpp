/**
 * @file main.cpp
 * @author Oleksii Tnachenko (lyoshatkachenko@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "my_list.hpp"
#include "iostream"
#include "map"
#include <limits>

void addElement();
void editElement();
void removeElement();
void printList();
void userHelp();
void closeProgram();

linkedList<char*> my_library;


int main(){

    std::cout << "Welcome to the data store!" << std::endl;

    std::string command;
    using handler_ptr_type = void (*)(void);
    std::map<std::string, handler_ptr_type> handlers_map = {
        {"add", &addElement},
        {"edit", &editElement},
        {"ls", &printList},
        {"rm", &removeElement},
        {"help", &userHelp},
        {"exit", &closeProgram},
    };
 
    while(1){
        std::cout << "Enter the command:" << std::endl;
        std::cin >> command;
        auto handler = handlers_map.find(command);
        if(handler == handlers_map.end()){
            std::cout << "Unknown command, if you need help, write the command 'help'" << std::endl;
        } else {
            handler->second();
        }
    }

    return 0;
}

void addElement(){
    std::string new_data;
    std::cout << "Enter the new data: ";
    std::cin >> new_data;

    list_element<char*>* new_elem = my_library.create_list_element(   (void*) new_data.c_str(),
                                                            new_data.length());
    
    int elem_qty = my_library.get_elem_qty();
    list_element<char*>* existing_elem = my_library.get_list_element_at_pos(elem_qty);
    my_library.insert_list(existing_elem, new_elem);

    std::cout << "Element has been added" << std::endl;
    std::cout << "*********************" << std::endl;
}

void editElement(){
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

    list_element<char*>* existing_elem = my_library.get_list_element_at_pos(--index);
    if(existing_elem == NULL){
        std::cout << "Error: element not found" << std::endl;
        return;
    }

    std::cout << "Enter the new data: ";
    std::cin >> new_data;

    list_element<char*>* new_elem = my_library.create_list_element(   (void*) new_data.c_str(),
                                                            new_data.length());
    my_library.insert_list(existing_elem, new_elem);
    my_library.delete_from_list(existing_elem);

    std::cout << "Element has been edited" << std::endl;
    std::cout << "*********************" << std::endl;
}

void removeElement(){
    int index = 0; 

    std::cout << "Enter the element index: ";
    std::cin >> index;

    if(!std::cin){
        std::cout  << "Error: wrong input index" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    list_element<char*>* existing_elem = my_library.get_list_element_at_pos(--index);
    if(existing_elem == NULL){
        std::cout << "Error: element not found" << std::endl;
        return;
    }
    my_library.delete_from_list(existing_elem);

    std::cout << "Element has been removed" << std::endl;
    std::cout << "*********************" << std::endl;
}

void printList(){
    std::cout << "List of elements:" << std::endl;
    int counter = 0;
    list_element<char*> *item = my_library.get_list_element_at_pos(counter++);
    while(item != NULL){
        char* array = (char*)item->data;
        std::cout << counter << ": " << array << std::endl;
        item = my_library.get_list_element_at_pos(counter++);
    }

    std::cout << "*********************" << std::endl;
}

void userHelp(){
    std::cout << "For working with library you can use the following commands:" << std::endl;
    std::cout << "add - add a new book;" << std::endl;
    std::cout << "edit - edit existing book;" << std::endl;
    std::cout << "ls - get list of all book;" << std::endl;
    std::cout << "rm - remove book." << std::endl;
    std::cout << "exit - close the book." << std::endl;
}

void closeProgram(){
    exit(0);
}