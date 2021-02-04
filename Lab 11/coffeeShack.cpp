// Coffee Shack lab
// Cameron Kim
// 11/20/20

#include <string>
#include <iostream>
#include <set>
#include <math.h>
#include <stdlib.h>
// lab headers
#include "coffeeDecor.h"

using std::cout; using std::cin; using std::endl;
using std::string;
using std::set;

//////////////////////////////////////
//
// abstract classes describing the mechanism 
// of subscription and notification
// 

// class Subject; // forward class declaration

class Observer {
public:
    Observer(class Subject* s);
    virtual void notify() const = 0;
};


class Subject {
public:
    void registerObserver(Observer* o)
    {
        views_.insert(o);
    }
    void deregisterObserver(Observer* o)
    {
        views_.erase(o);
    }
    void notifyObservers() const {
        for (auto e : views_) e->notify();
    }
    bool isEmpty() {
        return views_.empty();
    }
private:
    set <Observer*> views_;
};


Observer::Observer(Subject* s) {
    s->registerObserver(this);
}


//
// concrete classes describing the content 
// of subject/observer
//

class ConcreteSubject;

class ConcreteObserver : public Observer {
public:
    ConcreteObserver(const string&, ConcreteSubject*);
    void notify() const override;
    void setOrder(Coffee* order) { order_ = order; }
private:
    string name_;
    ConcreteSubject* s_;
    Coffee* order_;
};

class ConcreteSubject : public Subject {
public:
    ConcreteSubject(const string& name) : name_(name) {}

    void setOrder(const string& order) {
        order_ = order;
        notifyObservers();
    }

    const string& getOrder() const { return order_; }
    const string& getName() const { return name_; }
private:
    string name_;
    string order_;
};

ConcreteObserver::ConcreteObserver(const string& name, ConcreteSubject* s) :
    name_(name), s_(s),
    Observer(static_cast<Subject*>(s)) {}

void ConcreteObserver::notify() const {
    cout << "Barista " << s_->getName() << " to " << name_ << ": " << s_->getOrder() << endl;
}


Coffee* newOrder(string& name) {
    Coffee* order = new Coffee("", DrinkType::small, 0.00);
    char size;
    string name = name;

    // asking for size
    cout << "Welcome to Coffee Shack, can I get you [l]arge, [m]edium, or [s]mall coffee?";
    cin >> size;
    cout << endl;

    /*// asking for name
    cout << "Can I get your name?";
    cin >> name;
    cout << endl;*/

    // determining correct size
    if (size == 's') {
        order = new Coffee(name, DrinkType::small, 1.00);
    }
    else if (size == 'm') {
        order = new Coffee(name, DrinkType::medium, 2.00);
    }
    else if (size == 'l') {
        order = new Coffee(name, DrinkType::large, 3.00);
    }

    // asking for toppings
    char topping = 'x';

    while (topping != 'n') {
        // getting input

        cout << "Would you like to add [s]prinkles, [c]aramel, milk [f]oam, [i]ce or [n]ot?";
        cin >> topping;
        cout << endl;

        // determining correct topping
        if (topping == 's') {
            Sprinkles sprinkle(order);
            order = new Coffee(sprinkle.getName(), order->getType(), sprinkle.getPrice());
        }
        else if (topping == 'c') {
            Caramel carmel(order);
            order = new Coffee(carmel.getName(), order->getType(), carmel.getPrice());
        }
        else if (topping == 'f') {
            MilkFoam foam(order);
            order = new Coffee(foam.getName(), order->getType(), foam.getPrice());
        }
        else if (topping == 'f') {
            MilkFoam foam(order);
            order = new Coffee(foam.getName(), order->getType(), foam.getPrice());
        }
        else if (topping == 'i') {
            Ice ice(order);
            order = new Coffee(ice.getName(), order->getType(), ice.getPrice());
        }
    }
    float price = roundf(order->getPrice() * 100) / 100;
    name = (order->getName() + "is ready. It will be $" + std::to_string(price) + ", please");
    order = new Coffee(name, order->getType(), price);
    return order;
}


// main
int main() {
    ConcreteSubject barista("Billy");
    ConcreteObserver obOne("Joe", &barista), obTwo("Jane", &barista);

    barista.registerObserver(&obOne);
    barista.registerObserver(&obTwo);


    while (!barista.isEmpty()) {

    }
} 