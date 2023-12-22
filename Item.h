#include "Document.h"
#include <vector>
#include <ostream>
#ifndef ITEM_H
#define ITEM_H

class Item{
public:
    Item();
    Item(const string & w);

    string getWord() const;
    vector<Document> getDocuments() const;
    void setWord(const string & newWord);
    void addDocument(const Document & newDocument);                //this function will call insertDocument() if document does not exist, else it will call updateDocument()
    int findIndex(const Document & searchedDocument) const;   //iterates documents to find searchedDocument
    void insertDocument(const Document & newDocument);          //inserts a new Document to the documents vector
    void updateDocument(const Document & newDocument, const int & index);          //updates an existing Document in documents vector
    Document getFirstDocument() const;          //returns the first document
    void update(Item newItem);                                  //it will insertDocument() or updateDocument()

    bool operator<(const Item & rhs) const;                 //less than operator
    bool operator>(const Item & rhs) const;                 //greater than operator
    bool operator==(const Item & rhs) const;                //equivalence operator
    bool operator!=(const Item & rhs) const;

    size_t customHash() const;      //hashing function for Item
    string toString() const;
private:
    string word;
    vector<Document> documents;


};

ostream& operator<<(ostream& os, const Item & item);


#endif //ITEM_H
