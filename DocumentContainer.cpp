#include "DocumentContainer.h"

DocumentContainer::DocumentContainer()  //default constructor
{

}

void DocumentContainer::addDocumentWithItem(const DocumentWithItem &documentWithItem)
{
    int index = findDocumentWithItem(documentWithItem); //finds the index
    if(index == -1) //documentWithItem is not existing, add to the vector
    {
        container.push_back(documentWithItem);
    }
    else    //documentWithItem is existing, update the values
    {
        WordAndOccurrence first = documentWithItem.getWords()[0];
        container[index].addItem(first.occurrence, first.word);
    }
    sort(); //sort the vector
}

vector<DocumentWithItem> DocumentContainer::getContainer() const    //returns the container
{
    return container;
}

int DocumentContainer::findDocumentWithItem(const DocumentWithItem &documentWithItem) const
{
    for(int i = 0; i< container.size(); i++)    //for each element
    {
        if(container[i].getDocumentName() == documentWithItem.getDocumentName())    //documentWithItem exists
        {
            return i;
        }
    }
    return -1;
}

void DocumentContainer::print() const   //prints every value
{
    for(int i = 0; i< container.size(); i++)
    {
        container[i].print();
    }
}

void DocumentContainer::showResults(const int &count) const //prints only documentWithItem with size == count
{
    bool exists = false;
    for(int i =0; i< container.size(); i++)
    {
        if(container[i].getWordsSize() == count)
        {
            container[i].print();
            exists = true;  //there is at least one existing document
        }
    }
    if(!exists)
    {
        cout << "No document contains the given query\n";
    }
}


//--------------------------
//PRIVATE FUNCTIONS
//--------------------------




void DocumentContainer::sort()  //calls quicksort
{
    quicksort(0,container.size()-1);
}

void DocumentContainer::quicksort(int low, int high)    //quicksort
{
    if (low < high) {
        int pivotIndex = partition(low, high);
        quicksort(low, pivotIndex - 1);
        quicksort(pivotIndex + 1, high);
    }
}

int DocumentContainer::partition(int low, int high)     //used in quicksort
{
    DocumentWithItem pivot = container[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (container[j].getDocumentName() < pivot.getDocumentName()) {
            i++;
            std::swap(container[i], container[j]);
        }
    }
    std::swap(container[i + 1], container[high]);
    return i + 1;
}