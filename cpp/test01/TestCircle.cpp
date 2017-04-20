#include <iostream>

using namespace std;

class Circle{
    public:
        double radius;

        Circle(){
            radius = 1;
        }

        Circle(double newRadius){
            radius = newRadius;
        }

        double getArea(){
            return radius * radius * 3.14159;
        }
};

int main(){
    Circle circle1;
    Circle circle2(5.0);

    cout << "The Area of the Circle of Radius" << circle1.radius << " is " << circle1.getArea() << endl;
    cout << "The Area of the Circle of Radius" << circle2.radius << " is " << circle2.getArea() << endl;

    circle2.radius = 100;
    cout << "The Area of the Circle of Radius" << circle2.radius << " is " << circle2.getArea() << endl;

    return 0;
}
