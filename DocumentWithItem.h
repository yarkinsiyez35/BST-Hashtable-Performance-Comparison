#include "Item.h"
#include <iostream>

#ifndef DOCUMENTWITHITEM_H
#define DOCUMENTWITHITEM_H




struct WordAndOccurrence
{
    string word;
    int occurrence;
    WordAndOccurrence(string s, int o)
    {
        word = s;
        occurrence = o;
    }
};


class DocumentWithItem{
public:
    DocumentWithItem(string docName);

    string getDocumentName() const;
    vector<WordAndOccurrence> getWords() const;
    int getWordsSize() const;
    void addItem(int count,  string word);

    void print()const;


private:
    string documentName;
    vector<WordAndOccurrence> words;
};


#endif //DOCUMENTWITHITEM_H
