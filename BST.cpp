#include "BST.h"
#include <iostream>

using namespace std;

template<class Obj>
BST<Obj>::BST()
{
    root = nullptr;
}

template<class Obj>
BST<Obj>::~BST()
{
    makeEmpty(root);    //deletes every node recursively starting from the root
}

template<class Obj>
void BST<Obj>::insert(Obj obj)  //inserts obj
{
    insert(obj, root);
}

template<class Obj>
Obj BST<Obj>::find(Obj obj)     //returns obj if it exists, throws exception otherwise
{
    Node<Obj> * node = find(obj, root);     //finds the Node
    if(node != nullptr)                     //if Node exists
    {
        return node->object;
    }
    else
    {
        throw Exception("Element is not in BST!");
    }
}

template<class Obj>
void BST<Obj>::remove(Obj obj)      //removes obj if it exists, does nothing otherwise
{
    remove(obj,root);
}

template<class Obj>
BST<Obj> &BST<Obj>::operator=(const BST<Obj> &rhs)  //allows for assignment
{
    if(this != &rhs)        //prevention against self assignment
    {
        makeEmpty(root);                //empties the lhs
        root = clone(rhs.root);        //copies the elements
    }
    return *this;
}


template<class Obj>
void BST<Obj>::printTree() const    //prints the tree in order
{
    printNode(root);
}

template <class Obj>
void BST<Obj>::printInfo() const    //gives info about the tree
{
    cout << "BST:\n";
    if(root != nullptr)
    {
        int minLeftHeight = getMinHeight(root->left);
        int maxLeftHeight = getMaxHeight(root->left);
        int minRightHeight = getMinHeight(root->right);
        int maxRightHeight = getMaxHeight(root->right);
        int totalCount = numberOfElements(root);
        cout << "min left height: " << minLeftHeight << endl;
        cout << "max left height: " << maxLeftHeight << endl;
        cout << "min right height: " << minRightHeight << endl;
        cout << "max right height: " << maxRightHeight << endl ;
        cout << "number of elements: " <<totalCount << endl << endl;
    }
    else
    {
        cout << "Tree is empty!\n\n";
    }
}


//------------------------------------------------------------------------------
//PRIVATE FUNCTIONS
//------------------------------------------------------------------------------



template<class Obj>
void BST<Obj>::insert(Obj obj, Node<Obj> *&current) //tries to insert obj at the given Node
{
    if(current == nullptr)      //inserts obj
    {
        Node<Obj>* newNode = new Node<Obj>(obj);
        current = newNode;
    }
    else if (obj < current->object)     //inserts obj in left subtree
    {
        insert(obj,current->left);
    }
    else if (obj> current->object)       //inserts obj in right subtree
    {
        insert(obj, current->right);
    }
    else    //obj is found
    {
        current->object.update(obj);
    }
}


template<class Obj>
void BST<Obj>::makeEmpty(Node<Obj> *&current)   //recursively deletes every node
{
    if(current != nullptr)
    {
        makeEmpty(current->left);
        makeEmpty(current->right);
        delete current;
        current = nullptr;
    }
}

template<class Obj>
void BST<Obj>::remove(Obj obj, Node<Obj> *&current)
{
    if(current == nullptr)              //obj is not found
    {
        return;
    }
    else if (obj < current->object)     //search the obj in left subtree
    {
        remove(obj, current->left);
    }
    else if(obj> current->object)       //search the obj in right subtree
    {
        remove(obj, current->right);
    }
    else        //obj is found
    {
        if(current->right == nullptr && current->left == nullptr)               //leaf node
        {
            delete current;
            current = nullptr;
        }
        else if (current->right != nullptr && current->left == nullptr)         //has right child
        {
            Node<Obj>* replacement = findMin(current->right);           //find the min value from the right subtree
            current->object = replacement->object;                              //assignment
            remove(replacement->object, current->right);                        //recursively delete the replacement node
        }
        else if (current->right == nullptr && current->left != nullptr)        //has left child
        {
            Node<Obj>* replacement = findMax(current->left);        //find the max value from left subtree
            current->object = replacement->object;                          //assignment
            remove(replacement->object, current->left);                     //recursively delete the replacement node
        }
        else                                                                    //has two children
        {
            Node<Obj>* replacement = findMin(current->right);           //find the min value from right subtree
            current->object = replacement->object;                              //assignment
            remove(replacement->object, current->right);                        //recursively delete the replacement node
        }
    }
}

template<class Obj>
Node<Obj>* BST<Obj>::findMin(Node<Obj> *current) const
{
    if(current != nullptr)
    {
        while(current->left != nullptr)     //finds the min Node by going left
        {
            current = current->left;        //updates the Node
        }
    }
    return current;
}

template<class Obj>
Node<Obj> *BST<Obj>::findMax(Node<Obj> *current) const
{
    if(current != nullptr)
    {
        while(current->right != nullptr)    //finds the max Node by going right
        {
            current = current->right;       //updates the Node
        }
    }
    return current;
}

template<class Obj>
Node<Obj> *BST<Obj>::find(Obj obj, Node<Obj> *current) const
{
    if(current == nullptr)  //obj is not found
    {
        return nullptr;
    }
    else if (obj < current->object) //find the obj in left subtree
    {
        return find(obj, current->left);
    }
    else if (obj > current->object) //find the obj in right subtree
    {
        return find(obj,current->right);
    }
    else    //obj is found
    {
        return current;
    }
}


template<class Obj>
Node<Obj> *BST<Obj>::clone(Node<Obj> *node) const
{
    if(node == nullptr)
    {
        return nullptr;
    }
    else
    {
        Node<Obj>* newNode = new Node(node->object);    //create a new Node with same object value
        newNode->left = clone(node->left);          //copy left subtree recursively
        newNode->right = clone(node->right);        //copy right subtree recursively
        return newNode;
    }
}

template<class Obj>
void BST<Obj>::printNode(Node<Obj> *current) const  //prints the Node in order
{
    if(current != nullptr)
    {
        printNode(current->left);
        cout << current->object << endl;
        printNode(current->right);
    }
}

template <class Obj>
int BST<Obj>::min(const int &i1, const int &i2) const   //returns min int
{
    if(i1 < i2)
    {
        return i1;
    }
    else
    {
        return i2;
    }
}

template <class Obj>
int BST<Obj>::max(const int &i1, const int &i2) const   //returns max int
{
    if(i1<i2)
    {
        return i2;
    }
    else
    {
        return i1;
    }
}

template <class Obj>
int BST<Obj>::getMaxHeight(Node<Obj> *current) const    //returns max Height
{
    if(current == nullptr)
    {
        return 0;
    }
    else
    {
        return max(getMaxHeight(current->left), getMaxHeight(current->right)) + 1;
    }
}

template <class Obj>
int BST<Obj>::getMinHeight(Node<Obj> *current) const    //returns min height
{
    if(current == nullptr)
    {
        return 0;
    }
    else
    {
        return min(getMinHeight(current->left), getMinHeight(current->right)) + 1;
    }
}

template<class Obj>
int BST<Obj>::numberOfElements(Node<Obj> *current) const    //returns number of elements in the tree with root as current
{
    if(current == nullptr)
    {
        return 0;
    }
    else
    {
        return numberOfElements(current->left) + numberOfElements(current->right) + 1;
    }
}
