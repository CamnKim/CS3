#ifndef CS3_WORDLIST_HPP
#define CS3_WORDLIST_HPP

#include <string>

class WordOccurrence {
public:
    WordOccurrence(const std::string& word = "", int num = 0);
    WordOccurrence& operator= (WordOccurrence);
    bool matchWord(const std::string&); // returns true if word matches stored
    void increment(); // increments number of occurrences
    std::string getWord() const;
    int getNum() const;

private:
    std::string word_;
    int num_;
};

class WordList {
public:
    WordList();
    WordList(const WordList&); //Copy constructor
    ~WordList(); //Destructor
    WordList& operator= (WordList); //Overloaded assignment
    void swap(WordList&); //Constant time swap
    void sortSwap(WordOccurrence, WordOccurrence); //Swaps places of items for sorting
    void sort();

    // implement comparison as friend
    friend bool equal(const WordList&, const WordList&);

    void addWord(const std::string&);
    void print();
private:
    WordOccurrence* wordArray_; // a dynamically allocated array of WordOccurrences
                                // may or may not be sorted
    int size_;
};

#endif