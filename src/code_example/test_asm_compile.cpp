#include <stdint.h>
#include <iostream>
using namespace std;

typedef int32_t Atomic32;

inline Atomic32 NoBarrier_AtomicIncrement(volatile Atomic32* ptr,
                                          Atomic32 increment) {
  Atomic32 temp = increment;
  __asm__ __volatile__("lock; xaddl %0,%1"
                       : "+r" (temp), "+m" (*ptr)
                       : : "memory");
  // temp now holds the old value of *ptr
  return temp + increment;
}

int main() {
    Atomic32 a = 0;
    cout << NoBarrier_AtomicIncrement(&a, 2) << endl;
}