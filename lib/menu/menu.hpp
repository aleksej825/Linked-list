#ifndef __MENU_HPP__
#define __MENU_HPP__

#include "book.hpp"
#include "my_list.hpp"
#include "iostream"
#include <fstream>
#include "vector"

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
        std::cout << "sz - sort by size." << std::endl;
        std::cout << "sa - sort by author." << std::endl;
        std::cout << "sc - sort by created at." << std::endl;
        std::cout << "exit - close the book." << std::endl;
    }
    virtual void closeProgram() = 0;
    virtual void sortBySize() = 0;
    virtual void sortByAuthor() = 0;
    virtual void sortByCreatedAt() = 0;
};

class lib_menu: public generic_menu<Book>{
protected:
    std::ofstream backup_file;
    std::string file_path;

    void addBook(Book *new_book);
    void editBook(Book *new_book);
    void removeBook(Book *new_item);
public:
    lib_menu();
    ~lib_menu();

    void addElement() override;
    void editElement() override;
    void removeElement() override;
    void printList() override;
    void closeProgram() override;
    void userHelp() {generic_menu<Book>::userHelp();}; // wrapper for call the parrent method from the map
    void sortBySize() override;
    void sortByAuthor() override;
    void sortByCreatedAt() override;
    void addRecord(Book *item);
    void updateRecord(Book *item, int index);
    void removeRecord(int index);
    void updateBackup();
    void readBackupFile(std::string path);
    inline bool isFileEmpty(const std::string& filename) {
        std::ifstream file(filename);
        return file.peek() == std::ifstream::traits_type::eof();
    }
    void clearBackupFile();
    std::string getBookStr(Book *item);
    void fillBackupFile(std::vector<string> &new_data);
};

#endif // __MENU_HPP__