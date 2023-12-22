#include <string>

using namespace std;

#ifndef EXCEPTION_H
#define EXCEPTION_H

//this class will be used when searched object is not found in BST or HashTable or LinkedList
class Exception {
public:
    Exception();
    Exception(const string& msg);
    const string & getMessage();
    void setMessage(const string & msg);

private:
    string message;
};


#endif //EXCEPTION_H
