// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Cameron Kim
// 10/06/2020


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <iterator>
#include <algorithm>
#include <numeric>


using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};

// used to generate random apples
class appleFunctor {
public:
    appleFunctor(int min, int max) { min_ = min; max_ = max; };

    Apples operator() () {
        Apples apple;
        apple.weight = min_ + static_cast<double>(rand()) / RAND_MAX * (max_ - min_);
        apple.color = rand() % 2 == 1 ? "green" : "red";
        return apple;
    }
private:
    int min_;
    int max_;
};



int main(){
   srand(time(nullptr));
   const double minWeight = 8.;
   const double maxWeight = 3.;

   // initilizing functor
   appleFunctor genNew(minWeight, maxWeight);

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   // assign random weight and color to apples in the crate
   // replace with generate()
   std::generate(crate.begin(), crate.end(), genNew);
 
   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;

   // count_if()
   int cnt = std::count_if(crate.cbegin(), crate.cend(), [toFind](Apples apple) { return apple.weight > toFind; });


   cout << "There are " << cnt << " apples heavier than " 
	<< toFind << " oz" <<  endl;

   // find_if()
   cout << "at positions ";
   auto it = std::find_if(crate.begin(), crate.end(), [toFind](Apples apple) { return apple.weight > toFind; });
   while (it != crate.end()) {
       cout << (std::distance(crate.begin(), it)) << ", ";
       it = std::find_if(++it, crate.end(), [toFind](Apples apple) { return apple.weight > toFind; });
   }


   // max_element()
   auto heaviest = std::max_element(crate.begin(), crate.end(), [](Apples appleOne, Apples appleTwo) { return appleOne.weight < appleTwo.weight; }); 
   cout << "Heaviest apple weighs: " << heaviest->weight << " oz" << endl;


   // for_each() or accumulate()
   double sum = std::accumulate(crate.cbegin(), crate.cend(), 0., [](double i, Apples apple) { return i + apple.weight; });
   cout << "Total apple weight is: " << sum << " oz" << endl;


   // transform();
   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;

   std::transform(crate.begin(), crate.end(), crate.begin(), [toGrow](Apples apple) { apple.weight += toGrow; return apple; });


   // remove_if()
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;
   
   auto pend = std::remove_if(crate.begin(), crate.end(), [minAccept](Apples apple) { return apple.weight < minAccept; });
   crate.resize(std::distance(crate.begin(), pend));


   // bubble sort, replace with sort()
   std::sort(crate.begin(), crate.end(), [](Apples appleOne, Apples appleTwo) { return appleOne.weight < appleTwo.weight; });


   // moving all red apples from crate to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Apples> peck;

   std::remove_copy_if(crate.begin(), crate.end(), std::back_inserter(peck), [](Apples apple) { return apple.color == "green"; });
   pend = std::remove_if(crate.begin(), crate.end(), [](Apples apple) { return apple.color == "red"; });
   crate.resize(std::distance(crate.begin(), pend));


   // for_each() possibly
   cout << "apples in the create" << endl;
   std::for_each(crate.begin(), crate.end(), [](Apples apple) { apple.print(); });
   cout << endl;
   cout << "apples in the peck" << endl;
   std::for_each(peck.begin(), peck.end(), [](Apples apple) { apple.print(); });
   
}

