template <typename T>
class Queue {
    DoublyLinkedList<T> list;

   public:
    Queue(){};
    ~Queue();
    void put(T data) { list.insertAtEnd(data); };
    T get() {
        if (isEmpty()) throw std::out_of_range("Queue is empty");
        return list.removeAtBeginning();
    };
    void print(const char *separator) const;
    size_t getSize() const { return list.getSize(); };
    bool isEmpty() const { return list.isEmpty(); };
    void clear() { list.clear(); };
    template <typename T2>
    friend std::ostream &operator<<(std::ostream &out, const Queue<T2> &queue);
};

template <typename T>
void Queue<T>::print(const char *separator) const {
    list.print(separator);
};

template <typename T>
Queue<T>::~Queue() {
    list.clear();
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const Queue<T> &Queue) {
    out << Queue.list;
    return out;
};