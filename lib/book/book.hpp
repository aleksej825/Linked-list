#ifndef __BOOK_HPP__
#define __BOOK_HPP__

#include "string"
#include "iostream"
#include <ctime>

using namespace std;

class Book{
    private:
    string name;
    string author;
    string content;
    std::time_t created_at;

    public:
    Book();
    Book(string new_name, string new_author, string new_content);
    ~Book();

    inline void setName(string new_val){
        name = new_val;
    }

    inline void setAuthor(string new_val){
        author = new_val;
    }

    inline void setContent(string new_val){
        content = new_val;
    }

    inline string getName(){
        return name;
    }

    inline string getAuthor(){
        return author;
    }

    inline string getContent(){
        return content;
    }

    inline string getTimeCreateAsString(){
        string temp = std::asctime(std::localtime(&created_at));
        temp.erase(temp.end()-1);
        return temp;
    }

    inline std::time_t getTimeCreateAsTimeFormat(){
        return created_at;
    }

    friend ostream& operator<<(ostream& os, const Book& bk)
    {
        os << "Book name - " << bk.name << endl;
        os << "Author - " << bk.author << endl;
        os << "Created - " << std::asctime(std::localtime(&bk.created_at));
        os << "Content - " << bk.content << endl;

        return os;
    }

    friend ostream& operator<<(ostream& os, const Book* bk)
    {
        os << "Book name - " << bk->name << endl;
        os << "Author - " << bk->author << endl;
        os << "Created - " << std::asctime(std::localtime(&bk->created_at));
        os << "Content - " << bk->content << endl;

        return os;
    }

    inline int length(){
        return name.length() + author.length() + content.length();
    }

    inline void parseDateTime(const char* datetimeString)
    {
        struct tm tmStruct;
        strptime(datetimeString, "%c", &tmStruct);
        created_at = mktime(&tmStruct);
    }

};

#endif //__BOOK_HPP__