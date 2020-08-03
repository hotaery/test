#include <iostream>
#include <stdlib.h>
using namespace std;

#define BUFLEN 64

struct Foo {
public:
    Foo() {
        cout << "Foo[" << this << "]" << endl;
    }
};

int main() {
    unsigned char* buf = (unsigned char*)malloc(BUFLEN);
    Foo* fp = new(buf) Foo();
    cout << (void*)buf << ", " << fp << endl;
}