#pragma once
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
    Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
};

class Library {
   private:
    Node<Book>* head;
    Node<Book>* tail;
    size_t size;

   public:
    Library();
    Library(initializer_list<Book> list);
    Library(const Library& orig);
    Library(Library&& orig);
    Library& operator=(const Library& right);
    Library& operator=(Library&& right);
    Book& operator[](size_t index);
    const Book& operator[](size_t index) const;
    friend ostream& operator<<(ostream& out, const Library& library);
    size_t GetSize() const;
    ~Library();

    bool isEmpty() const;
    void push_back(const Book& book);
    void push_back(Book&& book);
    Book pop_back();
};