#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

int main() {
    while (1) {
        long size = 1024*1024*1024;
        void* p = mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
        if (p != NULL) {
            char fullst[16];
            fgets(fullst, 16, stdin);
            for (int i = 0; i < size; i += sysconf(_SC_PAGESIZE))
                ((char*)p)[i] = 0;
            fgets(fullst, 16, stdin);
        }
    }
    return 0;
}