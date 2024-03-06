_Pragma("once");
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
   public:
    T data;
    Node<T> *next;
    Node<T> *prev;
    Node(T data) : data(data), next(nullptr), prev(nullptr) {}
};

template <typename T>
class DoublyLinkedList {
    Node<T> *head;
    Node<T> *tail;
    size_t size;

   public:
    // T getHead();
    // T getTail();
    DoublyLinkedList();
    ~DoublyLinkedList();
    void insertAtPos(size_t pos, T data);
    void removeAtPos(size_t pos);
    void insertAtBeginning(T data);
    void removeAtBeginning();
    void insertAtEnd(T data);
    void removeAtEnd();
    void print() const;
    size_t getSize() const;
    bool isEmpty() const;
    T getAtPos(size_t pos);
    T getAtBeginning();
    T getAtEnd();
    void clear();
    void destroy();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : size(0), head(nullptr), tail(nullptr) {}

template <typename T>
void DoublyLinkedList<T>::insertAtBeginning(T data) {
    Node<T> *newNode = new Node<T>(data);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    size++;
};

template <typename T>
void DoublyLinkedList<T>::insertAtEnd(T data) {
    Node<T> *newNode = new Node<T>(data);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
};

template <typename T>
void DoublyLinkedList<T>::removeAtBeginning() {
    if (isEmpty()) throw std::out_of_range("List is empty");
    Node<T> *tmp = head;
    head = head->next;
    delete tmp;
    size--;
};

template <typename T>
void DoublyLinkedList<T>::removeAtEnd() {
    if (isEmpty()) throw std::out_of_range("List is empty");
    Node<T> *tmp = tail;
    tail = tail->prev;
    delete tmp;
    size--;
};

template <typename T>
void DoublyLinkedList<T>::insertAtPos(size_t pos, T data) {
    Node<T> *newNode = new Node<T>(data);
    if (isEmpty()) {
        head = tail = newNode;
        size++;
    } else if (pos == 0) {
        insertAtBeginning(data);
    } else if (pos >= getSize()) {
        insertAtEnd(data);
    } else if (pos >= getSize() / 2) {
        Node<T> *tmp = tail;
        for (size_t i = getSize() - 1; i > pos; i--) tmp = tmp->prev;
        newNode->next = tmp->next;
        newNode->prev = tmp;
        tmp->next = newNode;
        newNode->next->prev = newNode;
        size++;
    } else {
        Node<T> *tmp = head;
        for (size_t i = 0; i < pos; i++) tmp = tmp->next;
        newNode->next = tmp;
        newNode->prev = tmp->prev;
        tmp->prev = newNode;
        newNode->prev->next = newNode;
        size++;
    }
};

template <typename T>
void DoublyLinkedList<T>::removeAtPos(size_t pos) {
    if (isEmpty()) throw std::out_of_range("List is empty");
    if (pos >= getSize()) throw std::out_of_range("Index is out of range");

    if (pos == 0) {
        removeAtBeginning();
    } else if (pos == getSize() - 1) {
        removeAtEnd();
    } else if (pos >= getSize() / 2) {
        Node<T> *tmp = tail;
        for (size_t i = getSize() - 1; i > pos; i--) tmp = tmp->prev;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        delete tmp;
        size--;
    } else {
        Node<T> *tmp = head;
        for (size_t i = 0; i < pos; i++) tmp = tmp->next;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        delete tmp;
        size--;
    }
};

template <typename T>
void DoublyLinkedList<T>::print() const {
    if (isEmpty()) throw std::out_of_range("List is empty");
    Node<T> *tmp = head;
    std::cout << "List: (";
    while (tmp != nullptr) {
        std::cout << tmp->data << ",";
        tmp = tmp->next;
    }
    std::cout << "\b)" << std::endl;
};

template <typename T>
size_t DoublyLinkedList<T>::getSize() const {
    return size;
};

template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return size == 0;
};

template <typename T>
T DoublyLinkedList<T>::getAtPos(size_t pos) {
    if (isEmpty()) throw std::out_of_range("List is empty");
    if (pos >= getSize()) throw std::out_of_range("Index is out of range");
    Node<T> *tmp = head;
    for (size_t i = 0; i < pos; i++) tmp = tmp->next;
    return tmp->data;
};

template <typename T>
T DoublyLinkedList<T>::getAtBeginning() {
    if (isEmpty()) throw std::out_of_range("List is empty");
    return head->data;
};

template <typename T>
T DoublyLinkedList<T>::getAtEnd() {
    if (isEmpty()) throw std::out_of_range("List is empty");
    return tail->data;
};

template <typename T>
void DoublyLinkedList<T>::clear() {
    if (isEmpty()) throw std::out_of_range("List is already empty");
    while (!isEmpty()) removeAtBeginning();
};

template <typename T>
void DoublyLinkedList<T>::destroy() {
    clear();
    head = nullptr;
    tail = nullptr;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    destroy();
};