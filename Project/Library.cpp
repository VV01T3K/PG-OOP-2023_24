#include "Library.h"

#include <initializer_list>
#include <iostream>
#include <string>

#include "Book.h"

using namespace std;

// konstruktor bezparametrowy
Library::Library() : head(nullptr), tail(nullptr), size(0) {}

// konstruktor z listą inicjalizacyjną
Library::Library(initializer_list<Book> list)
    : head(nullptr), tail(nullptr), size(0) {
    for (const Book& book : list) push_back(book);
}

// konstruktor kopiujący
Library::Library(const Library& orig) : head(nullptr), tail(nullptr), size(0) {
    for (size_t i = 0; i < orig.size; i++) push_back(orig[i]);
}

// konstruktor przenoszący
Library::Library(Library&& orig)
    : head(std::move(orig.head)),
      tail(std::move(orig.tail)),
      size(std::move(orig.size)) {
    orig.head = nullptr;
    orig.tail = nullptr;
    orig.size = 0;
}

// kopiujący operator przypisania
Library& Library::operator=(const Library& right) {
    Library tmp = right;
    swap(head, tmp.head);
    swap(tail, tmp.tail);
    swap(size, tmp.size);
    return *this;
};

// przenoszący operator przypisania
Library& Library::operator=(Library&& right) {
    swap(head, right.head);
    swap(tail, right.tail);
    swap(size, right.size);
    return *this;
};

// Book& Library::operator[](size_t index){};

bool Library::isEmpty() const { return size == 0; };
void Library::push_back(const Book& book) {
    Node<Book>* newNode = new Node<Book>(book);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
    size++;
};
void Library::push_back(Book&& book) {
    Node<Book>* newNode = new Node<Book>(move(book));
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
};

Book Library::pop_back() {
    if (isEmpty()) throw std::out_of_range("List is empty - pop_back()");
    Node<Book>* tmp = tail;
    Book data = tmp->data;
    tail = tail->prev;
    delete tmp;
    size--;
    return data;
};