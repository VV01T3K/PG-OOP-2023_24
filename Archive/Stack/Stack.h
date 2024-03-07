_Pragma("once");
#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "DoublyLinkedList_Template.h"
template <typename T>
class Stack {
    DoublyLinkedList<T> list;
    Node<T>* top;

   public:
    Stack();
    ~Stack();
    void push(T data);
    T pop();
    void print() const;
    T peek() const {
        if (isEmpty()) throw std::out_of_range("Stack is empty");
        return top->data;
    };
    size_t getSize() const { return list.getSize(); };
    bool isEmpty() const { return list.isEmpty(); };
    void clear() { list.clear(); };
};

template <typename T>
Stack<T>::Stack() : top(nullptr) {}

template <typename T>
Stack<T>::~Stack() {
    list.clear();
    top = nullptr;
};

template <typename T>
void Stack<T>::print() const {
    std::cout << "Stack: ";
    list.print();
}

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