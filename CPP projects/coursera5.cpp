#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

class Figure {
public:
   virtual string Name() const = 0;
   virtual double Perimeter() const = 0;
   virtual double Area() const = 0;
};

class Triangle : public Figure {
public:
   Triangle(int a, int b, int c) : _a(a), _b(b), _c(c) {}

   string Name() const override {
      return "TRIANGLE";
   }

   double Perimeter() const override {
      return _a + _b + _c;
   }

   double Area() const override {
      double p = (_a + _b + _c) / 2;
      return sqrt(p * (p - _a) * (p - _b) * (p - _c));
   }
private:
   const double _a, _b, _c;
};

class Rect : public Figure {
public:
   Rect(int width, int height) : _width(width), _height(height) {}

   string Name() const override {
      return "RECT";
   }

   double Perimeter() const override {
      return 2*(_width+_height);
   }

   double Area() const override {
      return _width * _height;
   }
private:
   const double _width, _height;
};

class Circle : public Figure {
public:
   Circle(int r) : _r(r) {}

   string Name() const override {
      return "CIRCLE";
   }

   double Perimeter() const override {
      return 2 * 3.14 * _r;
   }

   double Area() const override {
      return 3.14 * _r * _r;
   }
private:
   const double _r;
};

shared_ptr<Figure> CreateFigure(istringstream& line){
   string command;
   double a, b = -1, c = -1;
   line >> command >> a >> b >> c;
   if(b == -1 && c == -1){
      return make_shared<Circle>(a);
   } else if(c == -1){
      return make_shared<Rect>(a, b);
   } else {
      return make_shared<Triangle>(a, b, c);
   }
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}