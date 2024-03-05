#include "string"

using namespace std;

class Book{
    private:
    string name;
    string author;
    string content;

    public:
    Book();
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

};