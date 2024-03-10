#include "book.hpp"


Book::Book(){
    name = "";
    author = "";
    content = "";
}

Book::Book(string new_name, string new_author, string new_content){
    name = new_name;
    author = new_author;
    content = new_content;
}

Book::~Book(){
    name = "";
    author = "";
    content = "";
}