#ifndef __MENU_HPP__
#define __MENU_HPP__

#include "book.hpp"
#include "my_list.hpp"
#include "iostream"
#include <fstream>

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
    virtual void sortBySize() = 0;
};

class lib_menu: public generic_menu<Book>{
protected:
    std::ofstream backup_file;
    std::string file_path;
public:
    lib_menu();
    ~lib_menu();

    void addElement() override;
    void editElement() override;
    void removeElement() override;
    void printList() override;
    void closeProgram() override;
    void userHelp() {this->userHelp();}; // wrapper for call the parrent method from the map
    void sortBySize() override; // TODO: don't work
    void addRecord(Book *item);
    void updateRecord();
    void readBackupFile(std::string path);
    inline bool isFileEmpty(const std::string& filename) {
        std::ifstream file(filename);
        return file.peek() == std::ifstream::traits_type::eof();
    }
};

#endif // __MENU_HPP__