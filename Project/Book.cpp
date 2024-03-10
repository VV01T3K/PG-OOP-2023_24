#include "Book.h"

#include <iostream>
#include <string>
using namespace std;

// konstruktor bezparametrowy
Book::Book() : title(""), author(""){};

// konstruktor, który przyjmuje autora i tytuł jako stałe l-referencje
Book::Book(const string& title, const string& author)
    : title(title), author(author){};

// konstruktor, który przyjmuje autora i tytuł jako r-referencje
Book::Book(string&& title, string&& author) : title(title), author(author){};

// dekonstruktor
Book::~Book(){};

// getery
string Book::GetTitle() const { return title; };
string Book::GetAuthor() const { return author; };

// setery z stałymi l-referencjami
void Book::SetTitle(const string& title) { this->title = title; };
void Book::SetAuthor(const string& author) { this->author = author; };

// setery z r-referencjami
void Book::SetTitle(string&& title) { this->title = title; };
void Book::SetAuthor(string&& author) { this->author = author; };

// operator << wypisania na strumień std::ostream
ostream& operator<<(ostream& out, const Book& book) {
    out << "Title: " << (book.title == "" ? "NONE" : book.title)
        << " Author: " << (book.author == "" ? "NONE" : book.author);
    return out;
}

// konstruktor kopiujący
Book::Book(const Book& book) : title(book.title), author(book.author){};

// konstruktor przenoszący
Book::Book(Book&& book) : title(move(book.title)), author(move(book.author)){};

// kopiujący operator przypisania
Book& Book::operator=(const Book& right) {
    Book tmp = right;
    swap(author, tmp.author);
    swap(title, tmp.title);
    return *this;
}

// przenoszący operator przypisania
Book& Book::operator=(Book&& right) {
    swap(author, right.author);
    swap(title, right.title);
    return *this;
}