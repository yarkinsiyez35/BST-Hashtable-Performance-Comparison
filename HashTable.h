#include <iostream>
#include <cstddef>
#include "Exception.h"
#include "LinkedList.h"
#include <cmath>

#ifndef HASHTABLE_H
#define HASHTABLE_H

using namespace std;

//this class is used for storing Obj in a HashTable, this class uses separate chaining
template<class Obj>
class HashTable{
public:
    HashTable();
    HashTable(double load= 0.5);
    ~HashTable();
    double getCurrentLoad() const;
    double getLoadFactor() const;
    int getCount() const ;
    void insert(Obj obj);
    void remove(Obj obj);
    bool exists(Obj obj) const;
    Obj find(Obj obj) const;
    bool needsRehash() const;

    void printTable() const;
    void printInfo() const;

private:
    long long unsigned int count;
    double loadFactor;
    unsigned int bucketSize;
    LinkedList<Obj>* buckets;

    size_t hashFunction(Obj obj) const;
    void rehash();
    int nextPrime(const int & currentNum) const;
    bool isPrime(const int & candidate) const;
    void resetTable();

};

#endif //HASHTABLE_H
