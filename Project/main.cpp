#include <iostream>
#include <string>
using namespace std;

#include "Book.h"
#include "Library.h"

int main() {
    // string a = "'Harry Potter'", t = "Rowling";
    // Book e;
    // cout << "e: " << e << endl;
    // Book b1 = {a, t};
    // cout << "b1: " << b1 << endl;
    // Book b2 = {"'To Kill a Mockingbird'", "Harper  Lee"};
    // cout << "b2: " << b2 << endl;
    // Book b3 = b1;
    // cout << "b3: " << b3 << " b1: " << b1 << endl;

    // e = move(b2);
    // cout << "e: " << e << " b2:" << b2 << endl;
    // e.SetAuthor("'Hobbit'");
    // cout << "e: " << e << endl;
    // e.SetTitle("Tolkien");
    // cout << "e: " << e << endl;

    //// !! ----------------------------------

    Library e;
    cout << "e: " << e << endl;
    // 3-5 książek
    Library l1 = {{"<?>", "<?>"}, {"<?>", "<?>"}, {"<?>", "<?>"}};
    cout << "l1: " << l1 << endl;
    Library l2;
    cout << "l2: " << l2 << endl;
    l2.push_back({"<?>", "<?>"});
    l2.push_back({"<?>", "<?>"});
    cout << "l2: " << l2 << endl;
    e = std::move(l2);
    cout << "e: " << e << " l2: " << l2 << endl;
    l1[0] = std::move(e[1]);
    cout << "l1: " << l1 << " e: " << e << endl;
}