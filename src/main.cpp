#include <brpc/channel.h>
#include <iostream>
using namespace std;

struct Foo {
    Foo() {}

    bool _b;
};

int main() {
    Foo foo;
    cout << foo._b << endl;
}
