// vector and list algorithms with objects in containers
// Cameron Kim
// 9/22/2020

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


class Student{
public:
   Student(string firstName, string lastName): 
      firstName_(firstName), lastName_(lastName) {}
 
   // move constructor, not really needed, generated automatically
   Student(Student && org):
      firstName_(move(org.firstName_)),
      lastName_(move(org.lastName_))
   {}
  
   // force generation of default copy constructor
   Student(const Student & org) = default;
   
   string print() const {
       string output = firstName_ + ' ' + lastName_ + ": ";
       for (const auto& className : classNames_) {
           output += (className + ' ');
       }
       return output;
   }

   void addClass(string className) {
        classNames_.push_back(className);
   }

    // needed for unique() and for remove()
   friend bool operator== (Student left, Student right){
      return left.lastName_ == right.lastName_ &&
	     left.firstName_ == right.firstName_;
   }

   // needed for sort()
   friend bool operator< (Student left, Student right){
      return left.lastName_ < right.lastName_ ||
	     (left.lastName_ == right.lastName_ && 
	      left.firstName_ < right.firstName_);
   }
private:
   string firstName_;
   string lastName_;
   list<string> classNames_;
};




// reading a list from a fileName
void readRoster(vector<Student>& studentEntries, string fileName);
// printing a list out
void printRoster(const vector<Student>& studentEntries);

int main(int argc, char* argv[]){

   if (argc <= 1){ cout << "usage: " << argv[0] 
      << " list of courses, dropouts last" << endl; exit(1);}

   // vector of courses of students
   vector <Student> studentEntries;

   for(int i=1; i < argc-1; ++i){
      readRoster(studentEntries, argv[i]);
       
   }

   printRoster(studentEntries);
}


void readRoster(vector<Student>& studentEntries, string fileName){
   ifstream course(fileName);
   string first, last;

   string className = fileName.erase(fileName.length() - 4, 4);

   while (course >> first >> last) {
       bool exists = false;
       Student temp(first, last);

       // looping through studentEntries to see if the student already exists
       for (auto& student : studentEntries) {
           // if the student already exists, push the class name to the back of list and break from loop
           if (temp == student) {
               student.addClass(className);
               exists = true;
               break;
           }
       }

       // if the student doesnt exist, create new student and push back the name and class
       if (!exists) {
           temp.addClass(className);

           // add to vector
           studentEntries.push_back(temp);
       }
   }
   course.close();
}

// printing a list out
void printRoster(const vector<Student>& studentEntries){
   for(const auto& student : studentEntries)
      cout << student.print() << endl;
}
