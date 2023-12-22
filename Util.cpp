#include "Util.h"

bool isLetter(char c)
{
    //A -> 65
    //Z -> 90
    //a ->97
    //z -> 122
    return (c>64 && c <91 || (c > 96 && c<123));
}

bool isWord(string word)
{
    for(int i = 0; i< word.size(); i++)
    {
        if(!isLetter(word[i]))  //non letter character
        {
            return false;
        }
    }
    return true;
}

string separateWord(string word)    //returns the leftmost word
{
    //find the index of first nonalphabetic character
    int index = notLetterIndex(word);
    if(index == 0)      //first index is problematic
    {
        word = word.substr(1);  //remove the first index
        return separateWord(word);  //return the result of this
    }
    else if (index == -1)   //word is correct
    {
        return word;
    }
    else    //another index is problematic
    {
        string newWord = word.substr(0,index);  //find the correct word
        return newWord;
    }
}

int notLetterIndex(string word)         //returns first occurrence of nonalphabetic character, returns -1 if it does not exist
{
    for (int i = 0; i< word.size(); i++)    //for each character
    {
        if(!isLetter(word[i]))  //that character is nonalphabetic
        {
            return i;
        }
    }
    return -1;
}

vector<Item> processWord(string word, string documentName)
{
    vector<Item> items;
    Document newDocument(documentName,1);
    bool remainingWord = true;
    while(!isWord(word))        //while there are nonalphabetic characters
    {
        //get the leftMostWord
        string leftMostWord = separateWord(word);
        //create Item from leftMostWord
        if(leftMostWord != "")      //word is not empty
        {
            Item newItem(lowercase(leftMostWord));
            newItem.addDocument(newDocument);
            items.push_back(newItem);
            //update the word
            int wordIndex = word.find(leftMostWord);
            int wordLength = leftMostWord.length();
            word = word.substr(wordIndex + wordLength);
        }
        else        //there are no more remaining words
        {
            remainingWord = false;
            break;
        }
    }
    if(word != "" && remainingWord)     //if there is a remaining word and it does not contain nonalphabetic characters
    {
        Item newItem(lowercase(word));
        newItem.addDocument(newDocument);
        items.push_back(newItem);
    }
    return items;
}

string lowercase(string word)
{
    string result = "";
    for(char c: word)
    {
        result += tolower(c);
    }
    return result;
}
