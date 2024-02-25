#include "my_list.hpp"
#include "iostream"
#include "map"

using namespace std;

void addElement();
void editElement();
void removeElement();
void printList();
void userHelp();

int main(){

    cout << "Welcome to the data store!" << endl;
    linkedList my_list;

    string command;
    using handler_ptr_type = void (*)(void);
    map<string, handler_ptr_type> handlers_map = {
        {"add", &addElement},
        {"edit", &editElement},
        {"ls", &printList},
        {"rm", &removeElement},
        {"help", &userHelp}
    };
 
    while(1){
        cout << "Enter the command:" << endl;
        cin >> command;
        auto handler = handlers_map.find(command);
        if(handler == handlers_map.end()){
            cout << "Unknown command, if you need help, write 'help' command" << endl;
        } else {
            handler->second();
        }
    }

    return 0;
}

void addElement(){
    cout << "Element added" << endl;
    cout << "*********************" << endl;
}

void editElement(){
    cout << "Element edited" << endl;
    cout << "*********************" << endl;
}

void removeElement(){
    cout << "Element removed" << endl;
    cout << "*********************" << endl;
}

void printList(){
    cout << "List printed" << endl;
    cout << "*********************" << endl;
}

void userHelp(){
    cout << "For working with list you can use the following commands:" << endl;
    cout << "add - add a new element;" << endl;
    cout << "edit - edit existing element;" << endl;
    cout << "ls - get list of all elements;" << endl;
    cout << "rm - remove element." << endl;
}