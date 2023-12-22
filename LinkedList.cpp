#include "LinkedList.h"

using namespace std;

template<class Obj>
LinkedList<Obj>::LinkedList()   //default constructor
{
    head = nullptr;
}

template<class Obj>
LinkedList<Obj>::~LinkedList()  //destructor
{
    while(head != nullptr)  //deletes each Node
    {
        LinkedListNode<Obj>* temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
}


template<class Obj>
void LinkedList<Obj>::insert(Obj obj, long long unsigned int &count)    //inserts obj, if unique increase count
{
    if(head == nullptr) //obj becomes the first element
    {
        head = new LinkedListNode<Obj>(obj);
        count++;            //new obj is added
    }
    else
    {
        LinkedListNode<Obj>* temp = head;   //used in traversal
        while(temp->next != nullptr)    //goes to the last Node
        {
            if(temp->data == obj)   //same object is found, update it
            {
                temp->data.update(obj);
                return;
            }
            temp = temp->next;
        }
        if(temp->data == obj)   //list has one element, obj is the same with that element
        {
            temp->data.update(obj);
            return;
        }
        temp->next = new LinkedListNode<Obj>(obj);  //obj is added to the end of the list
        count++;        //new obj is added
    }
}

template<class Obj>
void LinkedList<Obj>::remove(Obj obj, long long unsigned int &count)    //removes obj if it exists, does nothing otherwise
{
    if(head == nullptr)             //list is empty
    {
        return;
    }
    else if (head->data == obj)                     //obj is at the head
    {

        LinkedListNode<Obj> *toBeDeleted = head;
        head = head->next;      //update the head
        delete toBeDeleted;     //delete previous head
        toBeDeleted = nullptr;  //good practice
        count--;                //decreases count
    }
    else
    {
        LinkedListNode<Obj>* temp = head;   //for traversal
        while(temp->next != nullptr && temp->next->data != obj)     //iterates until obj is at temp->next or end of the list is reached
        {
            temp = temp->next;
        }
        if(temp->next != nullptr && temp->next->data == obj)    //obj is found
        {
            LinkedListNode<Obj>* nodeToRemove = temp->next; //finds the Node to remove
            temp->next = temp->next->next;      //connects the Nodes
            delete nodeToRemove;        //deletes Node
            nodeToRemove = nullptr;     //good practice
            --count;                //decreases count
        }
    }
}

template <class Obj>
Obj LinkedList<Obj>::find(Obj obj) const    //returns obj if it exists, throws exception otherwise
{
    LinkedListNode<Obj>* temp = head;   //for traversal
    while(temp != nullptr)          //iteratively searches for obj
    {
        if(temp->data == obj)   //obj is found
        {
            return temp->data;
        }
        temp = temp->next;  //goes to the next Node
    }
    throw Exception("Element is not in LinkedList!");
}

template <class Obj>
bool LinkedList<Obj>::exists(Obj obj) const //returns true if obj exists
{
    LinkedListNode<Obj>* temp = head;
    while(temp != nullptr)          //iteratively searches for obj
    {
        if(temp->data == obj)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template<class Obj>
void LinkedList<Obj>::emptyList()   //deletes the list
{
    while(head != nullptr)              //iteratively deletes each node
    {
        LinkedListNode<Obj>* temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
    }
}

template<class Obj>
LinkedList<Obj> &LinkedList<Obj>::operator=(const LinkedList<Obj> &rhs) //allows assignment
{
    if(this != &rhs)        //prevention against self assignment
    {
        //empty the lhs
        emptyList();
        //get the head of rhs
        LinkedListNode<Obj>* rhsHead = rhs.getHead();
        //clone if rhs is not empty list
        if(rhsHead != nullptr)
        {
            head = clone(rhsHead);
        }
    }
    return *this;
}

template<class Obj>
LinkedListNode<Obj> *LinkedList<Obj>::getHead() const   //returns the head
{
    return head;
}

template<class Obj>
int LinkedList<Obj>::getCount() const   //returns the count
{
    int count = 0;
    LinkedListNode<Obj>* temp = head;
    while(temp != nullptr)
    {
        temp = temp->next;
        count++;
    }
    return count;
}

template<class Obj>
bool LinkedList<Obj>::isEmpty() const   //returns true if empty
{
    return head == nullptr;
}

template<class Obj>
void LinkedList<Obj>::printList() const //prints the list
{
    LinkedListNode<Obj>* temp = head;
    if(temp != nullptr)
    {
        while(temp->next != nullptr)                      //iteratively prints the list
        {
            cout << temp->data  << "---->";
            temp = temp->next;
        }
        cout << temp->data;
    }
    cout << endl;

}

template<class Obj>
LinkedListNode<Obj> *LinkedList<Obj>::clone(const LinkedListNode<Obj> *node)    //clones the node recursively
{
    if(node != nullptr)
    {
        LinkedListNode<Obj>* newNode = new LinkedListNode<Obj>(node->data);         //data is copied
        newNode->next = clone(node->next);          //recursively next nodes are connected
        return newNode;
    }
    return nullptr;
}