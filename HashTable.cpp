#include "HashTable.h"

using namespace std;

template<class Obj>
HashTable<Obj>::HashTable() //default constructor
{
    loadFactor = 0.5;
    count = 0;
    bucketSize = 17;
    buckets = new LinkedList<Obj>[bucketSize];
}

template<class Obj>
HashTable<Obj>::HashTable(double load)  //parametric constructor
{
    loadFactor = load;
    count = 0;
    bucketSize = 53;
    buckets = new LinkedList<Obj>[bucketSize];
}

template<class Obj>
HashTable<Obj>::~HashTable()
{
    if(buckets != nullptr)      //prevention against deleting an already cleared table
    {
        delete [] buckets;
        buckets = nullptr;
    }
}

template<class Obj>
double HashTable<Obj>::getCurrentLoad() const   //returns the current load
{
    return (double) count / bucketSize;
}

template<class Obj>
double HashTable<Obj>::getLoadFactor() const    //returns the load factor
{
    return loadFactor;
}

template<class Obj>
int HashTable<Obj>::getCount() const    //returns the number of elements
{
    return count;
}

template<class Obj>
void HashTable<Obj>::insert(Obj obj)    //inserts obj
{
    size_t index = hashFunction(obj) % bucketSize;  //finds the index
    buckets[index].insert(obj, count);  //inserts to the corresponding LinkedList

    if(needsRehash())
    {
        cout << "rehashed...\n";
        rehash();
    }
}

template<class Obj>
void HashTable<Obj>::remove(Obj obj)    //removes obj if it exists, does nothing otherwise
{
    size_t index = hashFunction(obj) % bucketSize;  //finds the index
    buckets[index].remove(obj,count);   //removes from the corresponding LinkedList
}

template<class Obj>
bool HashTable<Obj>::exists(Obj obj) const  //returns true if obj exists
{
    size_t index = hashFunction(obj) % bucketSize;  //finds the index
    return buckets[index].exists(obj);  //searches for the obj in the corresponding LinkedList
}

template<class Obj>
Obj HashTable<Obj>::find(Obj obj) const //returns obj if it exists, throws exception otherwise
{
    try
    {
        size_t index = hashFunction(obj) % bucketSize;  //finds the index
        Obj searchedObj = buckets[index].find(obj); //this part can throw the exception
        return searchedObj;
    }
    catch (Exception e)
    {
        throw Exception("Element is not in HashTable!");
    }
}

template<class Obj>
bool HashTable<Obj>::needsRehash() const    //returns true if currentLoad >= loadFactor
{
    return getCurrentLoad() >= loadFactor;
}

template<class Obj>
void HashTable<Obj>::printTable() const //prints each bucket
{
    for(int i = 0; i< bucketSize; i++)
    {
        cout << i << ": ";
        buckets[i].printList();
    }
}

template<class Obj>
void HashTable<Obj>::printInfo() const
{
    cout << "Hashtable:\n";
    unordered_map<int,int> chains;  //key is number of Nodes, value is number of occurrences
    int sum = 0;    //this will hold the number of elements
    int active = 0; //this will hold the number of nonempty buckets
    for(int i = 0; i< bucketSize; i++)  //for each bucket
    {
        int numberOfElements = buckets[i].getCount();   //gets the number of elements in buckets[i]
        sum += numberOfElements;    //updates the sum
        chains[numberOfElements]++; //updates the map
        if(numberOfElements != 0)   //updates the number of active buckets
        {
            active++;
        }
    }
    for (const auto & pair: chains)
    {   //this shows the probability of the new Item being added to a chain with the given length

        cout << "chain length: " << pair.first << ", count: " << pair.second << ", probability: " << (double) 100 *pair.second/bucketSize << endl;


    }
    //other useful statistics
    cout << "average length: " << (double) sum/bucketSize << endl;
    cout << "average active length: " << (double) sum/active << endl;
    cout << "number of elements: " << count << endl << endl;
}



//-------------------------------
//PRIVATE FUNCTIONS
//-------------------------------

template<class Obj>
size_t HashTable<Obj>::hashFunction(Obj obj) const
{
    return obj.customHash();        //returns the custom hash of the object
}

template<class Obj>
void HashTable<Obj>::rehash()
{
    int newSize = nextPrime(bucketSize);    //newSize becomes the next prime number
    LinkedList<Obj>* newList = new LinkedList<Obj>[newSize];    //creates a new LinkedList with updated size
    long long unsigned int newCount = 0;
    for(int i =0; i< bucketSize; i++)       //for each bucket
    {
        LinkedListNode<Obj>* currentNode = buckets[i].getHead();
        while(currentNode != nullptr)           //for each element in each bucket
        {
            size_t newIndex = hashFunction(currentNode->data) % newSize;   //rehashes the element
            newList[newIndex].insert(currentNode->data, newCount);  //inserts the element to the newList
            currentNode = currentNode->next;    //updates
        }
    }
    delete [] buckets;  //deletes the old LinkedList
    buckets = newList;  //assigns buckets to the rehashed LinkedList
    cout << "previous table size:" << bucketSize << ", new table size:" << newSize << " current unique word count " << newCount <<",";
    bucketSize = newSize;   //updates the size
    count = newCount;   //updates the count
    cout << " current load factor: " << getCurrentLoad() << endl;
}

template <class Obj>
int HashTable<Obj>::nextPrime(const int & currentNum) const
{
    int next = currentNum *2 + 1;  //next should be at least twice the size of currentNum
    //next is always odd
    while(!isPrime(next))   //checks the number
    {
        next += 2;      //skips the even numbers
    }
    return next;
}

template<class Obj>
bool HashTable<Obj>::isPrime(const int & candidate) const
{
    int sqrtCandidate = static_cast<int>(sqrt(candidate));  //finds the square root of the candidate
    for (int i = 3; i <= sqrtCandidate; i += 2)         //candidate will always be odd number, no need to check if it is divisible by even numbers
    {
        if (candidate % i == 0)     //not a prime
        {
            return false;
        }
    }
    return true;
}

template <class Obj>
void HashTable<Obj>::resetTable()   //empties the table and creates a new table
{
    delete [] buckets;
    bucketSize = 17;
    buckets = new LinkedList<Obj>[bucketSize];
    count = 0;
}