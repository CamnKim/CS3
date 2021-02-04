// sorting oranges
// converting vectors to multimaps
// Cameron Kim
// 10/6/2020


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

/*struct Fruit{
   Variety v;
   string color; // red, green or orange
};
*/

int main(){
   srand(time(nullptr));

   multimap<Variety, string> tree;
   //vector <Fruit> tree(rand()%100+1);
   int size = rand() % 100 + 1;
   //cout << size << endl;

   for (int i = 0; i < size; ++i) {
      Variety fruit = static_cast<Variety>(rand() % 3);
      string color = colors[rand()%3];

      tree.insert(std::make_pair(fruit, color));
   }
 
   cout << "Colors of the oranges: ";
   for (auto i = tree.lower_bound(Variety::orange); i != tree.upper_bound(Variety::orange); ++i) {
       if (i->first == Variety::orange) {
           cout << i->second << ", ";
       }
   }
   cout << endl;

}

