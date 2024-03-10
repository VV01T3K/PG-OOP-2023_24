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

// operator[]
Book& Library::operator[](size_t index) {
    if (isEmpty()) throw out_of_range("Empty list - operator[]");
    if (index >= GetSize()) throw out_of_range("Index is out of range");
    Node<Book>* tmp = head;
    for (size_t i = 0; i < index; i++) tmp = tmp->next;
    return tmp->data;
};

// wersja const operatora []
const Book& Library::operator[](size_t index) const {
    if (isEmpty()) throw out_of_range("Empty list - operator[]");
    if (index >= GetSize()) throw out_of_range("Index is out of range");
    Node<Book>* tmp = head;
    for (size_t i = 0; i < index; i++) tmp = tmp->next;
    return tmp->data;
};

// operator << wypisania na strumień std::ostream
ostream& operator<<(ostream& out, const Library& library) {
    if (library.isEmpty()) cerr << "List is empty (<<)";
    for (int i = 0; i < library.GetSize(); i++) {
        if (i != 0)
            out << "    - ";
        else
            out << "- ";
        out << library[i];
        if (i != library.GetSize() - 1) out << "," << endl;
    }

    return out;
};

// gettery
std::size_t Library::GetSize() const { return size; };

// destruktor
Library::~Library() {
    while (!isEmpty()) pop_back();
}

// Tylko dla implementacji jako lista
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
    if (isEmpty()) throw out_of_range("Empty list - pop_back()");
    Node<Book>* tmp = tail;
    Book data = tmp->data;
    tail = tail->prev;
    delete tmp;
    size--;
    return data;
};