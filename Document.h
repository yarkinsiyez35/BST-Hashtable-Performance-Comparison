#include <string>
#include <ostream>

using namespace std;


#ifndef DOCUMENT_H
#define DOCUMENT_H

//this class holds the name of the document and the number of occurrences of that document
class Document{
public:
    Document();
    Document(const string & doc, const int & occurrence = 0);

    int getCount() const;
    string getDocumentName() const;
    void setCount(const int & newCount);
    void setDocumentName(const string & newDocumentName);

    bool operator==(const Document & rhs) const ;

    string toString() const;

private:
    int count;
    string documentName;

};

ostream & operator<<(ostream& os, const Document & document);


#endif //DOCUMENT_H
