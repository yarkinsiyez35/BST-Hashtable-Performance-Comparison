#include "Item.h"

Item::Item()    //default constructor
{
    word = "default word";
}

Item::Item(const std::string &w)    //parametric constructor
{
    word = w;
}

string Item::getWord() const    //returns the word
{
    return word;
}

vector<Document> Item::getDocuments() const //returns the vector of documents
{
    return documents;
}

void Item::setWord(const std::string &newWord)  //sets the word
{
    word = newWord;
}

void Item::addDocument(const Document &newDocument) //adds a Document to the vector of Documents
{
    int index = findIndex(newDocument); //finds the index of newDocument
    if(index != -1) //document exists
    {
        updateDocument(newDocument, index);
    }
    else    //document is unique
    {
        insertDocument(newDocument);
    }
}

int Item::findIndex(const Document &searchedDocument) const     //returns the index of the Document
{
    for (int i = 0; i< documents.size(); i++)
    {
        if(documents[i] == searchedDocument)    //searchedDocument exists
        {
            return i;
        }
    }
    return -1;  //does not exist
}

void Item::insertDocument(const Document &newDocument)  //inserts newDocument to the vector of Documents
{
    documents.push_back(newDocument);       //adds a new Document
}

void Item::updateDocument(const Document &newDocument, const int & index)   //updates the Document at index by incrementing the count with newDocument's count
{
    documents[index].setCount(documents[index].getCount() + newDocument.getCount());    //updates document[index]'s count with adding newDocument's count which will be usually 1
}

Document Item::getFirstDocument() const //returns the first document, it is guaranteed that this will not be called if Item has 0 Documents
{
    return documents[0];
}


void Item::update(Item newItem)
{
    Document documentToAdd = newItem.getFirstDocument();        //finds the document to add, it is guaranteed that newItem will have only 1 document
    addDocument(documentToAdd);     //adds the document
}

bool Item::operator<(const Item &rhs) const //allows less than check
{
    return word < rhs.getWord();
}

bool Item::operator>(const Item &rhs) const //allows greater than check
{
    return word > rhs.getWord();
}

bool Item::operator==(const Item &rhs) const    //allows equality check
{
    return word == rhs.getWord();
}

bool Item::operator!=(const Item &rhs) const    //allows inequality check
{
    return word != rhs.getWord();
}

string Item::toString() const   //returns a string representation of Item
{
    string result ="{" + word + ":" ;
    for (int i = 0; i< documents.size(); i++)
    {
        result += documents[i].toString();
    }
    result += "}";
    return result;
}

ostream& operator<<(ostream& os, const Item & item) //allows cout << Item
{
    os << item.toString();
    return os;
}

size_t Item::customHash() const         //should be fast no normal multiplications
{
    size_t value = 0;
    for(int i = 0; i<word.length(); i++)
    {
        value = ((value << 4)) ^ word[i];                   //best performing
        //value = ((value << 4)-value) ^ word[i];             //multiply the value by 15 and xor with word[i], slightly worse than the first one
        //value = ((value << 5) + value) + word[i];               //multiply the value by 33 and add word[i]
        //value = (value << 6) + (value<<16) - value + word[i];       //multiply the value by 65599 and add word[i] good distribution
    }
    return value;
}