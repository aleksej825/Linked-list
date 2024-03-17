#include "book.hpp"


Book::Book(){
    name = "";
    author = "";
    content = "";
    created_at = std::time(nullptr);
}

Book::Book(string new_name, string new_author, string new_content){
    name = new_name;
    author = new_author;
    content = new_content;
    created_at = std::time(nullptr);
}

Book::~Book(){
    name = "";
    author = "";
    content = "";
}