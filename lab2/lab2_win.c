#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    while (1) {
        long size = 1024*1024*1024;
        void* p = VirtualAlloc(0, size, MEM_COMMIT, PAGE_READWRITE);
        if (p != NULL) {
            char fullst[16];
            fgets(fullst, 16, stdin);
            for (int i=0; i < size; i += sysconf(_SC_PAGESIZE))
                ((char*)p)[i] = 0;
            fgets(fullst, 16, stdin);
        }
    }
    return 0;
}