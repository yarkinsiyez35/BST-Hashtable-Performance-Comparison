#include <string>
#include <vector>
#include "Item.h"

#ifndef UTIL_H
#define UTIL_H
    bool isLetter(char c);      //returns true if c is a letter
    bool isWord(string word);   //returns true if input is a word
    string separateWord(string word);   //creates words by separating the input string from unrecognized characters
    int notLetterIndex(string word);    //returns the first occurrence index of unrecognized character
    vector<Item> processWord(string word, string documentName);     //processes each word and returns an vector<Item>
    string lowercase(string word);  //converts the word to lowercase
#endif //UTIL_H
