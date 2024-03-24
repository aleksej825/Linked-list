/**
 * @file main.cpp
 * @author Oleksii Tkachenko (lyoshatkachenko@gmail.com)
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

#include "book.hpp"
#include "menu.hpp"
#include <functional>

lib_menu my_library;

int main(int argc, char *argv[]){

    std::string default_path = "./my_list_backup.csv";
    std::string backup_path;

    if(argc < 2){
        std::cout << "Backup file path not passed, used default path - " << default_path << std::endl;
        backup_path = default_path;
    }else{
        std::cout << "Backup file path found - " <<  argv[1] << std::endl;
        backup_path = argv[1];
    }

    my_library.readBackupFile(backup_path);

    std::cout << "Welcome to the library!" << std::endl;

    std::string command;
    using handler_ptr_type = std::function<void()>;
    std::map<std::string, handler_ptr_type> handlers_map = {
        {"add", std::bind(&lib_menu::addElement, &my_library)},
        {"edit", std::bind(&lib_menu::editElement, &my_library)},
        {"ls", std::bind(&lib_menu::printList, &my_library)},
        {"rm", std::bind(&lib_menu::removeElement, &my_library)},
        {"sz", std::bind(&lib_menu::sortBySize, &my_library)},
        {"help", std::bind(&lib_menu::userHelp, &my_library)},
        {"exit", std::bind(&lib_menu::closeProgram, &my_library)},
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
