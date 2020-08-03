#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

#define BUFLEN 64

pthread_key_t key;
pthread_once_t once = PTHREAD_ONCE_INIT;

void initPthreadKey() {
    pthread_key_create(&key, free);
}

const char* getPthreadId() {
    pthread_once(&once, initPthreadKey);
    pthread_t id = pthread_self();
    void* buf = pthread_getspecific(key);
    if (!buf) {
        buf = malloc(BUFLEN); 
    }
    pthread_setspecific(key, buf);
    snprintf((char*)buf, BUFLEN, "%ld", id);
    return (const char*)buf;     
}

void* thFun(void*) {
    printf("%s\n", getPthreadId());
    return nullptr;
}

void exitFn() {
    pthread_key_delete(key);
}

int main() {
    pthread_t id1, id2;
    atexit(exitFn);
    pthread_create(&id1, NULL, thFun, NULL);
    pthread_create(&id2, NULL, thFun, NULL);
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
}