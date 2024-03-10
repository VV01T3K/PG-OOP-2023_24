#include <initializer_list>
#include <string>

#include "Book.h"

using namespace std;

template <typename T>
class Node {
   public:
    T data;
    Node<T>* next;
    Node<T>* prev;
};

class Library {
   private:
    /* data */
   public:
    Library();
    Library(std::initializer_list<Book> list);
    Library(const Library& orig);
    Library(Library&& orig);
    Library& operator=(const Library& right);
    Library& operator=(Library&& right);
    Book& operator[](std::size_t index);
    const Book& operator[](std::size_t index) const;
    std::size_t GetSize() const;
    ~Library();
    // Tylko dla implementacji jako lista
    void push_back(const Book&);
    void push_back(Book&&);
    Book pop_back();
};

Library::Library(/* args */) {}

Library::~Library() {}
