#ifndef __MENU_HPP__
#define __MENU_HPP__

#include "book.hpp"
#include "my_list.hpp"
#include "iostream"

template<typename T>
class generic_menu{
protected:

    linkedList<T> list;
public:
    generic_menu(){

    }
    ~generic_menu(){

    }

    virtual void addElement() = 0;
    virtual void editElement() = 0;
    virtual void removeElement() = 0;
    virtual void printList() = 0;
    void userHelp(){
        std::cout << "For working with library you can use the following commands:" << std::endl;
        std::cout << "add - add a new book;" << std::endl;
        std::cout << "edit - edit existing book;" << std::endl;
        std::cout << "ls - get list of all book;" << std::endl;
        std::cout << "rm - remove book." << std::endl;
        std::cout << "exit - close the book." << std::endl;
    }
    virtual void closeProgram() = 0;
};

class lib_menu: public generic_menu<Book>{

public:
    lib_menu();
    ~lib_menu();

    void addElement() override;
    void editElement() override;
    void removeElement() override;
    void printList() override;
    void closeProgram() override;
    void userHelp() {this->userHelp();}; // wrapper for call the parrent method from the map
};

#endif // __MENU_HPP__