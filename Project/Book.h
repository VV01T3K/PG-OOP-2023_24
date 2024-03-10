#pragma once
#include <string>

using namespace std;
class Book {
   private:
    string title;
    string author;

   public:
    Book();
    Book(const string& title, const string& author);
    Book(string&& title, string&& author);
    ~Book();
    string GetTitle() const;
    string GetAuthor() const;
    void SetTitle(const string& title);
    void SetAuthor(const string& author);
    void SetTitle(string&& title);
    void SetAuthor(string&& author);
    friend ostream& operator<<(ostream& out, const Book& book);

    Book(const Book& book);
    Book(Book&& book);
    Book& operator=(const Book& right);
    Book& operator=(Book&& right);
};
