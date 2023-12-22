#include <iostream>
#include "Exception.h"


#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class Obj>
struct LinkedListNode{
    LinkedListNode* next;
    Obj data;

    LinkedListNode(Obj object) : next(nullptr), data(object){}
};

template<class Obj>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void insert(Obj obj, long long unsigned int & count);
    void remove(Obj obj, long long unsigned int & count);
    Obj find(Obj obj) const ;
    bool exists(Obj obj) const;
    void emptyList();
    LinkedList & operator=(const LinkedList & rhs);
    LinkedListNode<Obj>* getHead() const;
    int getCount() const;
    bool isEmpty() const;

    void printList() const;

private:
    LinkedListNode<Obj> * head;


    LinkedListNode<Obj>* clone(const LinkedListNode<Obj>* node);
};

#endif //LINKEDLIST_H
