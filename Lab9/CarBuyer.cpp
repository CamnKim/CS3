// needed for lab
// Cameron Kim
// 11/6/20

#include <iostream>
#include <vector>
#include <list>
#include <cstdlib>
#include "CarFactory.hpp"
#include <time.h>
#include <string>

using std::vector; using std::list; using std::string;
using std::cout; using std::endl;

class CarLot{
public:
   CarLot();
   Car *testDriveCar(){return car4sale_;}
   
   void nextCar();
   int lotSize() { return size_; };
   void print();

   // if a car is bought, requests a new one
   Car *buyCar(){ 
      Car *bought = car4sale_;
      lot_[pos] = factories_[rand()%factories_.size()]->requestCar();
      car4sale_ = lot_[pos];
      return bought;
   }
		     
private:
   Car *car4sale_; // single car for sale at the lot
   vector<CarFactory *> factories_;
   const int size_ = 10;
   vector<Car*> lot_;
   int pos = 0;
};


CarLot::CarLot(){
   // creates 2 Ford factories and 2 Toyota factories 
   factories_.push_back(new FordFactory());   
   factories_.push_back(new ToyotaFactory());
   factories_.push_back(new FordFactory());
   factories_.push_back(new ToyotaFactory());


   // fills lot with 10 random cars
   for (int i = 0; i < 10; ++i) {
       Car* temp = factories_[rand() % factories_.size()]->requestCar();
       lot_.push_back(temp);
   }

   // gets the first car for sale
   car4sale_ = lot_[0];
}

 void CarLot::nextCar() {
     if (pos != 9) {
         pos += 1;
         car4sale_ = lot_[pos];
     }
     else {
         pos = 0;
     }
}


CarLot* carLotPtr = nullptr; // global pointer instantiation


void buyer(int id) {
    if (carLotPtr == nullptr) {
        carLotPtr = new CarLot();
    }

    // creating factory vector for random car generation
    vector<CarFactory*> factories;
    factories.push_back(new ToyotaFactory());
    factories.push_back(new FordFactory());

    // randomly generating car that buyer wants
    Car* carWant = factories[rand() % factories.size()]->requestCar();


    cout << "Buyer " << id << endl; 
    cout << "Wants " << carWant->getMake() << " " << carWant->getModel() << endl << endl;

    for (int i = 0; i < carLotPtr->lotSize(); ++i) {
        Car* toBuy = carLotPtr->testDriveCar();

        cout << "test driving "
            << toBuy->getMake() << " "
            << toBuy->getModel() << endl;

        if ((toBuy->getMake() == carWant->getMake()) && (toBuy->getModel() == carWant->getModel())) {
            cout << " love it! buying it!" << endl;
            carLotPtr->buyCar();
            break;
        }
        else
            cout << " did not like it!" << endl;
        carLotPtr->nextCar();
    }
    cout << "================================================" << endl;

}

int main() {
   srand(time(nullptr));
   const int numBuyers = 10;
   for (int i = 0; i < numBuyers; ++i) {
       buyer(i);
   }
}
