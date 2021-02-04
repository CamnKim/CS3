// vector and list algorithms
// Mikhail Nesterenko
// 3/11/2014

#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>

using std::ifstream;
using std::string; using std::getline;
using std::list; using std::vector;
using std::cout; using std::endl;
using std::move;

// reading a list from a fileName
void readRoster(vector <list<string>>& studentEntries, string fileName);

// printing a list out
void printRoster(const vector <list<string>>& studentEntries);

int main(int argc, char* argv[]){

   if (argc <= 1){ 
      cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" 
      << endl; exit(1);
   }

   // vector of courses of students
   vector <list<string>> studentEntries;

   for(int i=1; i < argc-1; ++i){
      
      readRoster(studentEntries, argv[i]);
   }

   printRoster(studentEntries);

   /*
   // reading in dropouts
   list<string> dropouts; 
   readRoster(dropouts, argv[argc-1]); 
   cout << "\n\n dropouts \n"; printRoster(dropouts);

   // master list of students
   list<string> allStudents;  
 
   for(auto& lst : courseStudents) 
     allStudents.splice(allStudents.end(), lst);

   cout << "\n\n all students unsorted \n"; 
           printRoster(allStudents);

   // sorting master list
   allStudents.sort();
   cout << "\n\n all students sorted \n"; 
   printRoster(allStudents);

   // eliminating duplicates
   allStudents.unique(); 
   cout << "\n\n all students, duplicates removed \n"; 
   printRoster(allStudents);

   // removing individual dropouts
   for (const auto& str : dropouts)  
      allStudents.remove(str);

   cout << "\n\n all students, dropouts removed \n"; 
   printRoster(allStudents);
   */
}

// reading in a file of names into a list of strings
void readRoster(vector <list<string>>& studentEntries, string fileName){
   ifstream course(fileName);    
   string first, last;

   // removing .txt ending
   string className = fileName.erase(fileName.length() - 4, 4);

   // looping through file
   while (course >> first >> last) {
       string name = first + ' ' + last + ':';
       bool exists = false;
       
       // looping through studentEntries to see if the student already exists
       for (auto& student : studentEntries) {
           // if the student already exists, push the class name to the back of list and break from loop
           if (name == student.front()) {
               student.push_back(className);
               exists = true;
               break;
           }

       }

       // if the student doesnt exist, create new student and push back the name and class
       if (!exists) {
           list<string> student;
           student.push_back(name);
           student.push_back(className);

           // add to vector
           studentEntries.push_back(student);
       }

   }
   course.close();
}

// printing a list out
void printRoster(const vector <list<string>>& studentEntries){
    for (const auto& student : studentEntries) {
        for (const auto& str : student) {
            cout << str << ' ';
        }
        cout << '\n';
   }
}
