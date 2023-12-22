#include "Document.h"

Document::Document()    //default constructor
{
    documentName = "default name";
    count = 0;
}

Document::Document(const std::string &doc, const int &occurrence)   //parametric constructor
{
    documentName = doc;
    count = occurrence;
}

int Document::getCount() const  //returns the count
{
    return count;
}

string Document::getDocumentName() const    //returns the documentName
{
    return documentName;
}

void Document::setCount(const int &newCount)    //sets the count
{
    count = newCount;
}

void Document::setDocumentName(const std::string &newDocumentName)  //sets the documentName
{
    documentName = newDocumentName;
}

bool Document::operator==(const Document &rhs) const    //allows equality checks
{
    return documentName == rhs.getDocumentName();
}

string Document::toString() const   //creates a string representation of Document object
{
    string result =  "("+documentName + "," + to_string(count)+ ")";
    return result;
}

ostream & operator<<(ostream& os, const Document & document)    //allows cout << Document
{
    os << document.toString();
    return os;
}