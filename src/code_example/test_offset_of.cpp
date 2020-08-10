#include <stddef.h>
#include <iostream>
using namespace std;

class Base {
public:
    virtual ~Base() {}
    int _i = 0;
};

class Derived : public Base {
public:
    char _c = 'a';
};

int main() {
    cout << sizeof(Base) << endl;
    cout << sizeof(Derived) << endl;
    cout << offsetof(Base, _i) << endl;
    cout << offsetof(Derived, _c) << endl;
    Base b;
    b._i = 42;
    char* pb = reinterpret_cast<char*>(&b);
    int* pb_i = reinterpret_cast<int*>(pb + offsetof(Base, _i));
    cout << *pb_i << endl;
}