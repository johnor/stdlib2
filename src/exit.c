#include "stdlib.h"

#define HANDLERS 32
static void (*_exit_handlers[HANDLERS])(void);

void exit(int exit_code) {
    for (int i = 0; i < HANDLERS; ++i) {
        if (_exit_handlers[i]) {
            _exit_handlers[i]();
        }
    }

#if _WIN64 || __CYGWIN__
    volatile register int rdi asm("%rcx") = exit_code;
    asm("call ExitProcess");
#else
    asm("movq $60, %rax");
    volatile register int rdi asm("%rdi") = exit_code;
    asm("syscall");
#endif
    while (1) {}
}

int atexit(void (*func)(void)) {
    static int i = HANDLERS - 1;

    if (i < 0) {
        return 1;
    }

    _exit_handlers[i--] = func;
    return 0;
}
