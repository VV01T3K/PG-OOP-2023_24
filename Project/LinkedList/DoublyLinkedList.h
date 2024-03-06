_Pragma("once");
#include <cstddef>

template <typename T>
class Node {
    T data;
    Node<T> *next;
    Node<T> *prev;

   public:
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