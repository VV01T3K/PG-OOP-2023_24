#include <iostream>
#include <string>
using namespace std;

#include "Book.h"

int main() {
    string a = "Harry Potter", t = "Rowling";
    Book e;
    cout << "e: " << e << endl;
    Book b1 = {a, t};
    cout << "b1: " << b1 << endl;
    Book b2 = {"To Kill a Mockingbird ", "Harper  Lee"};
    cout << "b2: " << b2 << endl;
    Book b3 = b1;
    cout << "b3: " << b3 << " b1: " << b1 << endl;

    e = move(b2);
    cout << "e: " << e << " b2:" << b2 << endl;
    e.SetAuthor("Hobbit");
    cout << "e: " << e << endl;
    e.SetTitle("Tolkien");
    cout << "e: " << e << endl;
}