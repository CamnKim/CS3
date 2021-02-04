
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout; using std::cerr; using std::endl;

int main(int argc, char* argv[]) {
    //Exits and sends error message if there is the wrong number of arguments
    if (argc < 3) {
        cerr << "Not enough arguments";
        exit(0);
    }
    else if (argc > 3) {
        cerr << "Too many arguments";
        exit(0);
    }


    //13 space characters which are the part of the output that dont change. used for spaceing the carrot
    const std::string LEADING_STRING = "             ";

    //Opens Files
    std::ifstream fileOne(argv[1]);
    std::ifstream fileTwo(argv[2]);

    std::string fStringOne = argv[1];
    std::string fStringTwo = argv[2];



    //Creates a vector for the contents of each file
    std::vector<std::string> fileVectorOne;
    std::vector<std::string> fileVectorTwo;
 
    std::string line = "";

    //Loops through files and adds each line to their vector
    while (std::getline(fileOne, line)) {
        fileVectorOne.push_back(line);
    }
    while (std::getline(fileTwo, line)) {
        fileVectorTwo.push_back(line);
    }

    int fileOneSize = fileVectorOne.size();
    int fileTwoSize = fileVectorTwo.size();
    int largestSize = 0;

    //Determines which file is larger and sets a varaible to that size and adds empty strings to the end of the smaller file
    //File one is bigger
    if (fileOneSize > fileTwoSize) {

        largestSize = fileOneSize;

        //Adds empty strings until both vectors are the same size
        while (fileVectorOne.size() != fileVectorTwo.size()) {
            fileVectorTwo.push_back("");
        }
    }
    //File two is bigger
    else if (fileOneSize < fileTwoSize) {

        largestSize = fileTwoSize;

        //Adds empty strings until both vectors are the same size
        while (fileVectorOne.size() != fileVectorTwo.size()) {
            fileVectorOne.push_back("");
        }
    }
    //Both files are the same size
    else { largestSize = fileOneSize; }

    fileTwo.close();
    fileOne.close();

    for (int i = 0; i < largestSize; i++) {
        //Creates the first part of the output strings
        std::string fileOneOut = fStringOne + ':' + ' ' + std::to_string(i + 1) + ':' + ' ';
        std::string fileTwoOut = fStringTwo + ':' + ' ' + std::to_string(i + 1) + ':' + ' ';

        //Checks if both lines are equal
        if (fileVectorOne[i].compare(fileVectorTwo[i]) != 0) {
            std::string strOne = fileVectorOne[i];
            std::string strTwo = fileVectorTwo[i];
            std::string carretStr = "";
            bool diffFlag = false;
            
            //sets the start of the carret line to be the right size before iterating through the characters
            for (int s = 0; s < fileOneOut.length(); s++) {
                carretStr += ' ';
            }
            //itterates through the characters and adds to the carret output line
            for (int j=0; j<strOne.length(); j++) {
                if (strOne[j] == strTwo[j]) {
                    carretStr += ' ';
                }
                else {
                    carretStr += '^';
                    diffFlag = true;
                    break;
                }
            }
            if (!diffFlag) { carretStr += '^'; }

            cout << fileOneOut << strOne << '\n';
            cout << fileTwoOut << strTwo << '\n';
            cout << carretStr << '\n';
        }
    }
    
}