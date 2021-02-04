#include "WordList.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>


//////////////////////////////////////
// WordOccurrence

//Constructor
WordOccurrence::WordOccurrence(const std::string& word, int num) {
	word_ = word;
	num_ = num;
}

WordOccurrence& WordOccurrence::operator= (WordOccurrence rhs) {
	word_ = rhs.word_;
	num_ = rhs.num_;

	return *this;
}

//Returns true if passed word equals the stored word
bool WordOccurrence::matchWord(const std::string& word) {
	if (word_.compare(word) == 0) {
		return true;
	}
	else {
		return false;
	}
}

//Increments the word count
void WordOccurrence::increment() {
	num_++;
}

//Word getter
std::string WordOccurrence::getWord() const {
	return word_;
}

//Num getter
int WordOccurrence::getNum() const {
	return num_;
}


//////////////////////////////////////
// WordList


WordList::WordList() {
	size_ = 0;
	wordArray_ = new WordOccurrence[size_];
}
//Copy constructor
WordList::WordList(const WordList& actual) {
	size_ = actual.size_; //Sets this size equal to the passed array size
	wordArray_ = new WordOccurrence[size_]; //Creates a new array of size size_

	//Loops through and assigns each space in wordArray to the passed wordArray
	for (int i = 0; i < size_; ++i) {
		wordArray_[i] = actual.wordArray_[i];
	}
}

//Destructor
WordList::~WordList() {
	delete[] wordArray_;
}

//Overloaded assignment using constant time swap
WordList& WordList::operator= (WordList rhs) {
	swap(rhs);
	return *this;
}

//Constant time swap
void WordList::swap(WordList& rhs) {
	WordOccurrence* tempWL = wordArray_;
	wordArray_ = rhs.wordArray_;
	rhs.wordArray_ = tempWL;

	int tempSize = size_;
	size_ = rhs.size_;
	rhs.size_ = tempSize;
}

//Returns true if the two WordLists are equal
bool equal(const WordList& lhs, const WordList& rhs) {
	if (lhs.size_ == rhs.size_){
		for (int i = 0; i < lhs.size_; ++i) {
			if (lhs.wordArray_[i].getWord().compare(rhs.wordArray_[i].getWord()) != 0) {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

//Adds new word to wordList
void WordList::addWord(const std::string& word) {
	
	bool matched = false;

	//Checks to see if the word matches any existing words and incriments if it does
	for (int i = 0; i < size_; ++i) {
		if (wordArray_[i].matchWord(word)) {
			wordArray_[i].increment();
			matched = true;
		}
	}

	//If it was not matched then it adds the word to the list
	if (!matched) {
		//Creates new wordOccurrence of word
		WordOccurrence newWord = WordOccurrence(word);
		newWord.increment();

		//Temp array of size 1 greater than current size
		WordOccurrence* tempArray = new WordOccurrence[size_ + 1];

		//Loops through and copys over all words from current array to temp
		for (int i = 0; i < size_; i++) {
			tempArray[i] = wordArray_[i];
		}

		//Sets the last spot in temp to the newWOrd
		tempArray[size_] = newWord;

		//Increments size to match
		size_++;
		delete[] wordArray_;
		wordArray_ = tempArray;
	}
		
}

void WordList::print() {
	for (int i = 0; i < size_; ++i) {
		std::cout << wordArray_[i].getWord() << ": " << wordArray_[i].getNum() << '\n';
	}
}

void WordList::sortSwap(WordOccurrence wordOne, WordOccurrence wordTwo) {
	WordOccurrence temp = wordOne;
	wordOne = wordTwo;
	wordTwo = temp;
}

void WordList::sort() {
	for (int i = 0; i < size_ - 1; i++) {
		for (int j = 0; j < size_ - i - 1; j++) {
			if (wordArray_[j].getNum() > wordArray_[j + 1].getNum()) {
				WordOccurrence temp = wordArray_[j];
				wordArray_[j] = wordArray_[j + 1];
				wordArray_[j + 1] = temp;
			}
		}
	}	
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MAIN
int main(int argc, char* argv[]) {
	//Exits and sends error message if there is the wrong number of arguments
	if (argc < 2) {
		std::cerr << "Not enough arguments";
		exit(0);
	}
	else if (argc > 2) {
		std::cerr << "Too many arguments";
		exit(0);
	}

	//Open file
	std::ifstream file(argv[1]);

	std::string line;
	WordList list;

	//Loops through lines of file
	while (std::getline(file, line)) {
		int i = 0;
		std::string word;
		//Loops characters in the line
		while (line[i] != '\0') {
			//Checks if the character is a space
			if (line[i] != ' ') {
				//Checks if the character is alphanumeric
				if (isalnum(line[i]) != 0) {
					word.push_back(line[i]);
				}
			}
			else {
				list.addWord(word);

				//Resets the word to an empty string
				std::string blank;
				word = blank;
			}
			++i;
		}
		list.addWord(word);

	}
	list.sort();
	list.print();

	file.close();



}