#include "menu.hpp"
#include "iostream"
#include <limits>
#include "rapidcsv.h"

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

    addBook(new_item);
    addRecord(new_item);
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

    Book *new_book = new Book(name, author, content);

    list_element<Book>* new_elem = list.create_list_element(new_book);

    list.insert_list(existing_elem, new_elem);
    list.delete_from_list(existing_elem);


    updateRecord(new_book, index);
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
    removeRecord(index);
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
    backup_file.close();
    exit(0);
}

void lib_menu::sortBySize(){
    
    auto compare_func = [](struct list_element<Book>* elem1, struct list_element<Book>* elem2){
        int elem1_size = elem1->data->length();
        int elem2_size = elem2->data->length();

        if(elem1_size > elem2_size)
            return true;

        return false;
    };
    
    list.resort_list(compare_func);
    updateBackup();
    std::cout << "List resorted!" << std::endl;
}

void lib_menu::addRecord(Book *item)
{
    backup_file << getBookStr(item);
    backup_file.flush();
}

void lib_menu::updateRecord(Book *item, int index)
{
    index++; // skip the first line
    std::ifstream in_stream;
    std::vector<std::string> buffer;
    in_stream.open(file_path, std::ifstream::in);
    for( std::string line; getline(in_stream, line ); )
    {
        buffer.push_back(line + "\n");
    }
    in_stream.close();
    buffer[index] = getBookStr(item);
    fillBackupFile(buffer);
}

void lib_menu::removeRecord(int index)
{
    index++; // skip the first line
    std::ifstream in_stream;
    std::vector<std::string> buffer;
    in_stream.open(file_path, std::ifstream::in);
    int counter = 0;
    for( std::string line; getline(in_stream, line ); )
    {
        if(counter != index) // skip the record
            buffer.push_back(line + "\n");
        counter++;
    }
    in_stream.close();
    fillBackupFile(buffer);
}

void lib_menu::readBackupFile(std::string path)
{
    file_path = path;
    backup_file.open(file_path, std::ios::app);
    rapidcsv::Document doc(file_path);

    std::cout << "Parse input file..." << path << std::endl;
    if(isFileEmpty(file_path)){
        std::cout << "The file is empty, initialization." << std::endl; 
        backup_file << "Created at" << ","
                    << "Author" << ","
                    << "Name" << ","
                    << "Content" << "\n";
        return;
    }

    try{
        // Parse backup file
        std::vector<std::string> created_at = doc.GetColumn<std::string>("Created at");
        std::vector<std::string> author = doc.GetColumn<std::string>("Author");
        std::vector<std::string> name = doc.GetColumn<std::string>("Name");
        std::vector<std::string> content = doc.GetColumn<std::string>("Content");

        int index = 0;
        for(auto item = created_at.begin(); item != created_at.end(); ++item){
            /// Add items to the list
            Book *new_item = new Book(name[index], author[index], content[index]);
            new_item->parseDateTime(created_at[index].c_str());
            addBook(new_item);
            index++;
        }
        std::cout << "Done!" << std::endl;
    }catch(...){
        std::cout << "File parsing error." << std::endl;
    }
}

void lib_menu::addBook(Book *new_book)
{
    list_element<Book>* new_elem = list.create_list_element(new_book);
    int elem_qty = list.get_elem_qty();
    list_element<Book>* existing_elem = list.get_list_element_at_pos(elem_qty-1);
    list.insert_list(existing_elem, new_elem);
}

void lib_menu::editBook(Book *new_book)
{

}

void lib_menu::removeBook(Book *new_item)
{

}

void lib_menu::clearBackupFile()
{
    backup_file.close();
    backup_file.open(file_path); // automaticly clear file when open
}

std::string lib_menu::getBookStr(Book *item)
{
    std::string out;
    out =   item->getTimeCreate() + ","
            + item->getAuthor() + ","
            + item->getName() + ","
            + item->getContent() + "\n";
    return out;
}

void lib_menu::fillBackupFile(std::vector<string> &new_data)
{
    clearBackupFile();
    for(auto const &elem: new_data ){
        backup_file << elem;
    }
    backup_file.flush();
}

void lib_menu::updateBackup()
{
    std::ifstream in_stream;
    std::vector<std::string> buffer;
    std::string header = "Created at,Author,Name,Content\n";

    buffer.push_back(header);
    for(int index = 0; index < list.get_elem_qty(); index++)
    {
        struct list_element<Book>* item = list.get_list_element_at_pos(index);
        buffer.push_back(getBookStr(item->data));
    }
    in_stream.close();
    fillBackupFile(buffer);
}