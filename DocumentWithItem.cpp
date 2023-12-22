#include "DocumentWithItem.h"

using namespace std;

DocumentWithItem::DocumentWithItem(std::string docName) //constructor
{
    documentName = docName;
}

string DocumentWithItem::getDocumentName() const    //returns the documentName
{
    return documentName;
}

vector<WordAndOccurrence> DocumentWithItem::getWords() const    //returns the words and their occurrences in a vector
{
    return words;
}

int DocumentWithItem::getWordsSize() const  //returns the number of words
{
    return words.size();
}

void DocumentWithItem::addItem(int count, std::string word) //adds a given word with the given count to the vector
{
    WordAndOccurrence wordAndOccurrence(word,count);
    words.push_back(wordAndOccurrence);
}

void DocumentWithItem::print() const    //printing format
{
    cout << "in Document " << documentName <<", ";
    for(int i = 0; i < words.size()-1; i++)
    {
        cout << words[i].word << " found " << words[i].occurrence << " times, ";
    }
    cout << words[words.size()-1].word << " found " << words[words.size()-1].occurrence << " times." << endl;

}
