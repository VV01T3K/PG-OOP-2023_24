_Pragma("once");
#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "DoublyLinkedList_Template.h"
template <typename T>
class Stack {
    DoublyLinkedList<T> list;
    Node<T> *top;

   public:
    Stack();
    ~Stack();
    void push(T data);
    T pop();
    void print() const;

    T peek() { return list.getAtBeginning(); }
    const;
    size_t getSize() { return list.getSize(); }
    const;
    bool isEmpty() { return list.isEmpty(); }
    const;
    void clear() { list.clear(); };
};

template <typename T>
Stack<T>::~Stack() {
    list.clear();
    top = nullptr;
};

template <typename T>
void Stack<T>::print() const {
    cout << "Stack: (";
    while (top != nullptr) {
        cout << top->data << " ";
        top = top->next;
    }
    cout << ")" << endl;
};

template <typename T>
void Stack<T>::push(T data) {
    list.insertAtBeginning(data);
    top = list.getHead();
};

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) throw std::out_of_range("Stack is empty");
    T data = list.removeAtBeginning();
    top = list.getHead();
    return data;
};