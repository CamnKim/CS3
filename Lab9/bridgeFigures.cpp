// filled/hollow figures demonstrates Bridge Design Pattern,
// square is either hollow or square and is painted with a particular character,
// it is bridged over Figure --> Fill abstract body/handle
// Cameron Kim
// 11/6/20

#include <iostream>

using std::cout; using std::endl; using std::cin;

// abstract body
class Fill{
public:
   Fill(char fillChar, char borderFill):fillChar_(fillChar), borderFill_(borderFill) {}
   virtual char getBorder()=0;
   virtual char getInternal()=0;
   virtual ~Fill() {}
protected:
   char fillChar_;
   char borderFill_;
};

// concrete body
class Hollow: public Fill{
public:
   Hollow(char borderFill):Fill(' ', borderFill) {}
   char getBorder() override {return borderFill_;}
   char getInternal() override {return fillChar_;}
   ~Hollow(){}
};



// another concrete body
class Filled: public Fill {
public:
   Filled(char fillChar):Fill(fillChar, fillChar){}
   char getBorder() override {return fillChar_;}
   char getInternal() override {return fillChar_;}
   ~Filled(){}
};

class EnhancedFilled : public Filled {
public:
    EnhancedFilled(char internalFill, char borderFill) :Filled(internalFill) { borderFill_ = borderFill; }
    char getBorder() override { return borderFill_; };
    ~EnhancedFilled() {};
};

// abstract handle
class Figure {
public:
    Figure(int size, Fill* fill) : size_(size), fill_(fill) {}

    // change fill
    void changeFill(const Fill* fill) {
        fill_ = const_cast<Fill*>(fill);
    }

    virtual void draw() =0;
    virtual ~Figure(){}
protected:
   int size_;
   Fill *fill_;
};



// concrete handle
class Square: public Figure{
public:
   Square(int size, Fill* fill): Figure(size, fill){}
   void draw() override;

};


void Square::draw(){
   for(int i=0; i < size_; ++i){
      for(int j=0; j < size_; ++j)
	 if(i==0 || j==0 || i==size_-1 || j==size_-1 )
	    cout << fill_ -> getBorder();
	 else
	    cout << fill_ -> getInternal();
      cout << endl;
   }
}


int main(){

    // part one
    int size = 9;
    char fillChar = '#';

    Figure* filledSquare = new Square(size, new Filled(fillChar));
    cout << "filled square before changeFill" << endl;
    filledSquare->draw();
    cout << endl;

    filledSquare->changeFill(new Hollow(fillChar));
    cout << "filled square after changing fill to hollow" << endl;
    filledSquare->draw();
    cout << endl;


    fillChar = '@';
    Figure* hollowSquare = new Square(size, new Hollow(fillChar));
    cout << "hollow square before changeFill" << endl;
    hollowSquare->draw();
    cout << endl;

    hollowSquare->changeFill(new Filled(fillChar));
    cout << "hollow square after changing fill to filled" << endl;
    hollowSquare->draw();


    cout << endl << "========================================================" << endl;
    /////////////////////////////////////////////////////////////////////////////////////


    fillChar = '#';

    Figure* hollowSqr = new Square(size, new Hollow(fillChar));
    Figure* filledSqr = new Square(size, new Filled(fillChar));
    Figure* enhancedSqr = new Square(size, new EnhancedFilled('@', fillChar));

    cout << "hollow square:" << endl;
    hollowSqr->draw();
    cout << endl;

    cout << "filled square:" << endl;
    filledSqr->draw();
    cout << endl;

    cout << "enhanced square:" << endl;
    enhancedSqr->draw();
    cout << endl;



}
