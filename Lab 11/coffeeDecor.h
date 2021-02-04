// Coffee Shack Decorator
// Cameron Kim
// 11/20/20
#include <string>
#include <iostream>

using std::cout; using std::cin; using std::endl;
using std::string;

// drink component class

enum class DrinkType { small, medium, large };

// used for getting strings from enum for output
const string drinkToString(DrinkType drink) {
    if (drink == DrinkType::small) { return "small"; }
    else if (drink == DrinkType::medium) { return "medium"; }
    else if (drink == DrinkType::large) { return "large"; }
}

class Drink {
public:
    virtual double getPrice() const = 0;
    virtual string getName() const = 0;
};

// Coffee concrete component
class Coffee : public Drink {
public:
    Coffee(string name = "", DrinkType type = DrinkType::small, double price = 0) :
        name_(name),
        price_(price),
        type_(type)
    {}

    double getPrice() const override { return price_; }
    string getName() const override { return (name_ + ", your " + drinkToString(type_) + " coffee with "); }
    DrinkType getType() const { return type_; }

private:
    string name_;
    double price_;
    DrinkType type_;
};

// sprinkle decorator
class Sprinkles : public Drink {
public:
    Sprinkles(const Drink* drink) : drink_(drink) {}

    double getPrice() const override { return (drink_->getPrice() + 0.50); }
    string getName() const override { return (drink_->getName() + "sprinkles, "); }
private:
    const Drink* drink_;
};

// caramel decorator
class Caramel : public Drink {
public:
    Caramel(const Drink* drink) : drink_(drink) {}

    double getPrice() const override { return (drink_->getPrice() + 0.20); }
    string getName() const override { return (drink_->getName() + "caramel, "); }
private:
    const Drink* drink_;
};

// milk foam decorator
class MilkFoam : public Drink {
public:
    MilkFoam(const Drink* drink) : drink_(drink) {}

    double getPrice() const override { return (drink_->getPrice() + 0.40); }
    string getName() const override { return (drink_->getName() + "milk foam, "); }
private:
    const Drink* drink_;
};

// ice decorator
class Ice : public Drink {
public:
    Ice(const Drink* drink) : drink_(drink) {}

    double getPrice() const override { return (drink_->getPrice() + 0.10); }
    string getName() const override { return (drink_->getName() + "ice, "); }
private:
    const Drink* drink_;
};