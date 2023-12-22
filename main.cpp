#include <iostream>
#include "Item.h"
#include "BST.cpp"
#include "LinkedList.cpp"
#include "HashTable.cpp"
#include <fstream>
#include "Util.h"
#include <sstream>
#include "DocumentContainer.h"

using namespace std;

int main() {

    /*Get number of files*/
    cout << "Enter the number of files: ";
    int numberOfFiles;
    cin >> numberOfFiles;

    string* fileNames = new string[numberOfFiles];              //this array will hold the filenames

    /*Get names of the files*/
    for(int i = 0; i< numberOfFiles; i++)                       //every filename is received
    {
        cout << "Enter " << i+1 << ". file name: ";
        string fileName;
        cin >> fileName;
        fileNames[i] = fileName;
    }

    BST<Item> bst;

    /*Process Files with bst */
    for(int i = 0; i< numberOfFiles ; i++)          //for each file
    {
        ifstream inputFile(fileNames[i]);
        if (inputFile.is_open())                    //opens the file
        {
            Document document(fileNames[i]);            //creates a document with the name of fileName
            string currentWord;                                        //word for iterating the file
            while (inputFile >> currentWord)
            {
                vector<Item> items = processWord(currentWord,document.getDocumentName());   //processes word and returns vector<Item>
                for(int j = 0; j< items.size(); j++)
                {
                    bst.insert(items[j]);
                }
            }
        }
    }

    /*Process Files with hashTable */
    HashTable<Item> hashTable(0.55);    //load factor is 0.55
    for(int i = 0; i< numberOfFiles ; i++)          //for each file
    {
        ifstream inputFile(fileNames[i]);
        if (inputFile.is_open())                    //opens the file
        {
            Document document(fileNames[i]);            //creates a document with the name of fileName
            string currentWord;                                        //word for iterating the file
            while (inputFile >> currentWord)
            {
                vector<Item> items = processWord(currentWord,document.getDocumentName()); //processes word and returns vector<Item>
                for(int j = 0; j< items.size(); j++)
                {
                    hashTable.insert(items[j]);
                }
            }
        }
    }

    cout << "\nAfter preprocessing, the unique word count is " << hashTable.getCount() <<". Current load ratio is " << hashTable.getCurrentLoad() << endl;

    /*Getting query */
    cout << "Enter queried words in one line: ";
    cin.ignore();
    string query;
    getline(cin,query);
    /*Process query*/
    stringstream stream(query);
    string queriedWord;
    vector<Item> queriedItems;
    while(stream >> queriedWord)
    {
        vector<Item> queryVec = processWord(queriedWord,"default.txt");    //documentName does not matter
        for(int i = 0; i< queryVec.size(); i++)
        {
            queriedItems.push_back(queryVec[i]);
        }
    }

    //SEARCH WITH BST
    bool continueSearchBst = true;
    DocumentContainer containerBst;
    for(int i = 0; i< queriedItems.size(); i++)
    {
        try
        {
            Item searchedItem = bst.find(queriedItems[i]);
            vector<Document> documents = searchedItem.getDocuments();
            for(int j = 0; j< documents.size(); j++)
            {
                DocumentWithItem documentWithItem(documents[j].getDocumentName());
                documentWithItem.addItem(documents[j].getCount(), searchedItem.getWord());
                containerBst.addDocumentWithItem(documentWithItem);
            }
        }
        catch( Exception e)
        {
            continueSearchBst = false;
        }
    }
    containerBst.showResults(queriedItems.size());


    //SEARCH WITH HASHTABLE
    bool continueSearchHt = true;
    DocumentContainer containerHt;
    for(int i = 0; i< queriedItems.size(); i++)
    {
        try
        {
            Item searchedItem = hashTable.find(queriedItems[i]);
            //process the item and add it to the DocumentWithItem
            vector<Document> documents = searchedItem.getDocuments();
            for(int j = 0; j< documents.size(); j++)
            {
                DocumentWithItem documentWithItem(documents[j].getDocumentName());
                documentWithItem.addItem(documents[j].getCount(), searchedItem.getWord());     //documentWithItem : {documentName}, {word, count}
                containerHt.addDocumentWithItem(documentWithItem);
            }
        }
        catch(Exception e)
        {
            continueSearchHt = false;
        }
    }

    containerHt.showResults(queriedItems.size());


    //TIMING BST
    int k = 100;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        /*search queried items with BST */
        for(int j = 0; j< queriedItems.size(); j++)     //for each queried item
        {
            try
            {
                Item searchedItem = bst.find(queriedItems[j]);
            }
            catch (Exception e)
            {

            }
        }
    }
    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);
    cout << "\nTime: " << BSTTime.count() / k << "\n";

    //TIMING HASHTABLE
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
        for(int j = 0; j< queriedItems.size(); j++)
        {
            try
            {
                Item searchedItem = hashTable.find(queriedItems[j]);
            }
            catch(Exception e)
            {

            }
        }
    }
    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);
    cout << "\nTime: " << HTTime.count() / k << "\n";

    cout << "Speed Up: " << (double) BSTTime.count() / HTTime.count() << "\n";


#ifdef INFO
    bst.printInfo();
    hashTable.printInfo();
#endif

    return 0;
}
