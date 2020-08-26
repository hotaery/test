#include <linux/futex.h>
#include <syscall.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>
#include <iostream>
#include <atomic>
#include <queue>
#include <random>
#include <thread>
#include <chrono>
using namespace std;

//http://locklessinc.com/articles/futex_cheat_sheet/
//http://locklessinc.com/articles/mutex_cv_futex/
//https://developer.aliyun.com/article/6043

int futex(void* uaddr, int futex_op, int val, const timespec* timeout, 
          void* uaddr2, int val3) {
    return syscall(SYS_futex, uaddr, futex_op, val, timeout, uaddr2, val3); }

int futex_wait(void* uaddr, int val, const timespec* timeout) {
    //futex_wait和val比较的原因是因为：
    //如果在调用futex_wait和线程实际阻塞的时间窗内，有其他线程改变uaddr的值并且唤醒
    //如果不比较那么当前线程可能永远不会被唤醒
    return futex(uaddr, FUTEX_WAIT_PRIVATE, val, timeout, NULL, 0);
}

int futex_wake(void* uaddr, int nwake) {
    return futex(uaddr, FUTEX_WAKE_PRIVATE, nwake, NULL, NULL, 0);
}

int futex_requeue(void* uaddr, int nwake, uint32_t val2, void* uaddr2) {
    return futex(uaddr, FUTEX_REQUEUE_PRIVATE, nwake, (const timespec*)val2, uaddr2, 0);
}

int futex_cmp_requeue(void* uaddr, int nwake, uint32_t val2, void* uaddr2, int val3) {
    //futex_requeue和futex_cmp_requeue的区别是会比较uaddr和val3的值，如果不等直接返回
    //原因和futex_wait类似，如果不比较的话直接将uaddr的等待队列直接移到uaddr2的等待队列，
    //那么可能丢失唤醒，有其他线程唤醒uaddr，但是已经requeue了
    return futex(uaddr, FUTEX_CMP_REQUEUE_PRIVATE, nwake, (const timespec*)val2, uaddr2, val3);
}

int uaddr1 = 0;
int uaddr2 = 0;
int q[4] = {0};
int head = 0;
int tail = 0;
atomic<int> len(0);
#define LOOP 16

void producer() {
    for (int i = 0; i < LOOP; ++i) {
        if (len.load() == 4) {
            futex_wait(&uaddr2, uaddr2, NULL);
        }
        q[tail] = i + 1;
        tail = (tail + 1) % 4;
        len.fetch_add(1);
        uaddr1 += 1;
        futex_wake(&uaddr1, 1);
    }
}

void consumer() {
    for (int i = 0; i < LOOP; ++i) {
        if (len.load() == 0) {
            futex_wait(&uaddr1, uaddr1, NULL);
        }
        int val = q[head];
        head = (head + 1) % 4;
        len.fetch_sub(1);
        uaddr2 += 1;
        futex_wake(&uaddr2, 1);
        cout << val << ", ";
    }
}


int main() {
    thread t1(producer), t2(consumer);
    t1.join();
    t2.join();
}