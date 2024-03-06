#include <cassert>

#include "./LinkedList/DoublyLinkedList_Template.h"

int main() {
    // Test on an empty list
    DoublyLinkedList<int>* list1 = new DoublyLinkedList<int>();
    assert(list1->isEmpty());
    assert(list1->getSize() == 0);
    delete list1;

    // Test on a single element list
    DoublyLinkedList<int>* list2 = new DoublyLinkedList<int>();
    list2->insertAtBeginning(10);
    assert(!list2->isEmpty());
    assert(list2->getSize() == 1);
    assert(list2->getAtBeginning() == 10);
    assert(list2->getAtEnd() == 10);
    delete list2;

    // Test on a list with multiple elements
    DoublyLinkedList<int>* list3 = new DoublyLinkedList<int>();
    list3->insertAtBeginning(10);
    list3->insertAtEnd(20);
    assert(!list3->isEmpty());
    assert(list3->getSize() == 2);
    assert(list3->getAtBeginning() == 10);
    assert(list3->getAtEnd() == 20);
    delete list3;

    // Test on removing elements
    DoublyLinkedList<int>* list4 = new DoublyLinkedList<int>();
    list4->insertAtBeginning(10);
    list4->insertAtEnd(20);
    list4->removeAtBeginning();
    assert(!list4->isEmpty());
    assert(list4->getSize() == 1);
    assert(list4->getAtBeginning() == 20);
    assert(list4->getAtEnd() == 20);
    list4->removeAtEnd();
    assert(list4->isEmpty());
    assert(list4->getSize() == 0);
    delete list4;

    // Test on inserting at specific positions
    DoublyLinkedList<int>* list5 = new DoublyLinkedList<int>();
    list5->insertAtPos(0, 10);  // Inserting at the beginning
    list5->insertAtPos(1, 20);  // Inserting at the end
    list5->insertAtPos(1, 15);  // Inserting in the middle
    assert(!list5->isEmpty());
    assert(list5->getSize() == 3);
    assert(list5->getAtPos(0) == 10);
    assert(list5->getAtPos(1) == 15);
    assert(list5->getAtPos(2) == 20);
    delete list5;

    // Test on removing at specific positions
    DoublyLinkedList<int>* list6 = new DoublyLinkedList<int>();
    list6->insertAtBeginning(10);
    list6->insertAtEnd(20);
    list6->insertAtEnd(30);
    list6->removeAtPos(1);  // Removing from the middle
    assert(!list6->isEmpty());
    assert(list6->getSize() == 2);
    assert(list6->getAtPos(0) == 10);
    assert(list6->getAtPos(1) == 30);
    delete list6;

    return 0;
}
