#include <iostream>

using namespace std;

// void test01(void);
// void test02(char *_str);

class Printer{
private:
    char *str;
public:
    void SetString(char *_str){
        str = _str;
    }

    void ShowString(void){
        cout << str << endl;
    }
};

int main()
{
    // test01();
    // test02("hello world");

    Printer pnt;
    pnt.SetString("Hello World!");
    pnt.ShowString();

    pnt.SetString("I love C++");
    pnt.ShowString();

    return 0;
}

void test01(void){
    char *str = "Hello";
    str = "Apple";
    cout << str;
}

void test02(char *_str){
    char *str = _str;
    cout << str << endl;
}

