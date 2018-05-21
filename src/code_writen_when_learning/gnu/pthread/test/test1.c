#include <pthread.h>
int main(int argc, char** argv) {
#ifndef pthread_create
    return ((int*)(&pthread_create))[argc];
#else
    return 0;
#endif
}

