#include <iostream>
#include <string>
#include <limits>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
using namespace std;

ostream& operator<<(ostream& os, const struct timespec& ts) {
    os << "[" << ts.tv_sec << ", " << ts.tv_nsec << "]";
    return os;
}

int main() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    cout << ts << "\n=====================\n";
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts);
    cout << ts << "\n=====================\n";
    clock_gettime(CLOCK_MONOTONIC, &ts);
    cout << ts << "\n=====================\n";
}
