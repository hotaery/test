#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

union U1 {
    char c;
    int i;
};

template <typename T>
void printByte(T&& ptr) {
    char* p = reinterpret_cast<char*>(&ptr);
    for (int i = 0; i < sizeof(T); ++i) {
        cout << (int)*p << " ";
        ++p;
    }
    cout << endl;
}

class Foo {
public:
    Foo() {
        flag = 0x0;
        i = 0;
    }

    void setInt(int v) {
        flag = 0x0;
        i = v;
    }

    void setDouble(double v) {
        flag = 0x1;
        d = v;
    }

    bool getInt(int& v) {
        if (flag = 0x0) {
            v = i;
            return true;
        }
        return false;
    }

    bool getDouble(double& v) {
        if (flag & 0x1) {
            v = d;
            return true;
        }
        return false;
    }

    void describe(ostream& os) const {
        os << this << "[";
        if (flag == 0x0) {
            os << "int: " << i;
        } else {
            os << "double: " << d;
        }
        os << "]";
    }
private:
    uint8_t flag;
    union {
        int i;
        double d;
    };
};

ostream& operator<<(ostream& os, const Foo& foo) {
    foo.describe(os);
    return os;
}

int main() {
    cout << sizeof(U1) << endl;
    U1 u;
    memset(&u, 0, sizeof(u));
    u.c = 0x1;
    cout << hex;
    cout << (int)u.c << ", " << u.i << endl;
    printByte(u);

    Foo foo;
    cout << foo << endl;
    foo.setDouble(1.0);
    cout << foo << endl;
}