#include "stdbool.h"
#include "stdlib.h"

void do_thing() {
    volatile int a = 1;
    (void)a;
}

void do_more() {
    volatile int *b = 0;
    (void)b;
}

int main2() {
    bool a = false;
    bool b = !a;
    (void)b;

    atexit(do_more);
    atexit(do_thing);

    exit(100);
    return 50;
}
