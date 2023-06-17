#include <unistd.h> 
#include <sys/mman.h> 
#include <stdio.h> 
 
int main() { 
    while (1) { 
        long size = sysconf(_SC_PAGESIZE); 
        void* p = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0); 
        if (p == MAP_FAILED) { 
            perror("Memory allocation failed"); 
            break; 
        } 
 
        for (int i = 0; i < size; i++) 
            ((char*)p)[i] = 0; 
    } 
 
    return 0; 
}
