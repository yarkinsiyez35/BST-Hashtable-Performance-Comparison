#include "DocumentWithItem.h"

#ifndef DOCUMENTCONTAINER_H
#define DOCUMENTCONTAINER_H

//this class stores a vector of DocumentWithItem, this class is used for showing the resulting query 
class DocumentContainer {
public:
    DocumentContainer();
    void addDocumentWithItem(const DocumentWithItem & documentWithItem);
    vector<DocumentWithItem> getContainer() const;
    int findDocumentWithItem(const DocumentWithItem& documentWithItem) const;
    void print() const;
    void showResults(const int & count) const;
private:
    vector<DocumentWithItem> container;

    void sort();
    void quicksort(int low, int high);
    int partition(int low, int high);
};






#endif //DOCUMENTCONTAINER_H
