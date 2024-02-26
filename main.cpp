#include "my_list.hpp"
#include "iostream"
#include "map"

using namespace std;

void addElement();
void editElement();
void removeElement();
void printList();
void userHelp();

linkedList my_list;

int main(){

    cout << "Welcome to the data store!" << endl;

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
            cout << "Unknown command, if you need help, write the command 'help'" << endl;
        } else {
            handler->second();
        }
    }

    return 0;
}

void addElement(){
    string new_data;
    cout << "Enter the new data: ";
    cin >> new_data;

    list_element* new_elem = my_list.create_list_element(   (void*) new_data.c_str(),
                                                            new_data.length());
    
    int elem_qty = my_list.get_elem_qty();
    list_element* existing_elem = my_list.get_list_element_at_pos(elem_qty);
    my_list.insert_list(existing_elem, new_elem);

    cout << "Element has been added" << endl;
    cout << "*********************" << endl;
}

void editElement(){
    string new_data;
    int index = 0; 

    cout << "Enter the element index: ";
    cin >> index;

    list_element* existing_elem = my_list.get_list_element_at_pos(--index);
    if(existing_elem == NULL){
        cout << "Error: element not found" << endl;
        return;
    }

    cout << "Enter the new data: ";
    cin >> new_data;

    list_element* new_elem = my_list.create_list_element(   (void*) new_data.c_str(),
                                                            new_data.length());
    my_list.insert_list(existing_elem, new_elem);
    my_list.delete_from_list(existing_elem);

    cout << "Element has been edited" << endl;
    cout << "*********************" << endl;
}

void removeElement(){
    int index = 0; 

    cout << "Enter the element index: ";
    cin >> index;

    list_element* existing_elem = my_list.get_list_element_at_pos(--index);
    if(existing_elem == NULL){
        cout << "Error: element not found" << endl;
        return;
    }
    my_list.delete_from_list(existing_elem);

    cout << "Element has been removed" << endl;
    cout << "*********************" << endl;
}

void printList(){
    cout << "List of elements:" << endl;
    int counter = 0;
    list_element *item = my_list.get_list_element_at_pos(counter++);
    while(item != NULL){
        char *array = (char*)item->data;
        cout << counter << ": " << array << endl;
        item = my_list.get_list_element_at_pos(counter++);
    }

    cout << "*********************" << endl;
}

void userHelp(){
    cout << "For working with list you can use the following commands:" << endl;
    cout << "add - add a new element;" << endl;
    cout << "edit - edit existing element;" << endl;
    cout << "ls - get list of all elements;" << endl;
    cout << "rm - remove element." << endl;
}