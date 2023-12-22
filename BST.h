#include "Exception.h"

#ifndef BST_H
#define BST_H

template<class Obj>
struct Node                 //height is not necessary since this is a BST Node
{
    Node* left;
    Node* right;
    Obj object;             //this Obj must implement .update(Obj)

    Node(Obj obj)
    {
        left = nullptr;
        right = nullptr;
        object = obj;
    }
};


template<class Obj>
class BST
{
public:
    BST();
    ~BST();             //destructor

    void insert(Obj obj);
    Obj find(Obj obj);
    void remove(Obj obj);
    BST & operator=(const BST & rhs);
    void printTree() const;
    void printInfo() const;

private:
    Node<Obj>* root;

    //private functions
    void insert(Obj obj, Node<Obj>* & current);
    Node<Obj>* findMin(Node<Obj>* current) const;
    Node<Obj>* findMax(Node<Obj>* current) const;
    Node<Obj>* find(Obj, Node<Obj>* current) const;
    void remove(Obj, Node<Obj>*& current);
    void makeEmpty(Node<Obj>*& current);
    Node<Obj>* clone(Node<Obj>*rhs) const;
    void printNode(Node<Obj>* current) const;
    int min(const int & i1, const int & i2) const;
    int max(const int & i1, const int & i2) const;
    int getMaxHeight(Node<Obj>* current) const;
    int getMinHeight(Node<Obj>* current) const;
    int numberOfElements(Node<Obj>* current) const;
};










#endif //BST_H
