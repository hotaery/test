#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

typedef void(*DELETER)(void*);

struct UserDelete {
    DELETER del;
};

struct Foo {
    int i;
    char c;
    char* data;

    Foo() : i(0), c(0), data(NULL) {}
};

void fn(void* data) {
    cout << "fn(" << data << ")" << endl;
    free(data);
}

int main() {
    char* p = (char*)malloc(16);
    memset(p, 0, 16);
    cout << (void*)p << endl;
    Foo foo;
    char* fp = (char*)&foo;
    cout << &foo << ", " << (void*)fp << endl;
    foo.c = 'A';
    foo.i = 42;
    char* cp = fp + offsetof(Foo, c);
    cout << *cp << endl;
    char* ip = fp + offsetof(Foo, i);
    cout << *((int*)ip) << endl;

    foo.data = p;
    cout << sizeof(foo) << ", " << offsetof(Foo, data) << endl;
}

