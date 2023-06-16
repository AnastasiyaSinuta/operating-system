#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
#ifdef _WIN32 
    #include <Windows.h> 
#else 
    #include <sys/mman.h> 
#endif 
 
#define PAGE_SIZE 4096 // Размер страницы памяти (обычно 4 КБ) 
 
int main() { 
    void* memory = NULL; 
    size_t memorySize = 1024 * 1024; // Размер памяти, 1 МБ в данном примере 
 
    // Выделение памяти 
#ifdef _WIN32 
    memory = VirtualAlloc(NULL, memorySize, MEM_COMMIT, PAGE_READWRITE); 
#else 
    memory = mmap(NULL, memorySize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0); 
#endif 
 
    if (memory == NULL) { 
        fprintf(stderr, "Ошибка при выделении памяти\n"); 
        return 1; 
    } 
 
    // Заполнение памяти нулями с шагом, равным размеру страницы памяти 
    size_t pageSize = PAGE_SIZE; 
    size_t offset; 
    for (offset = 0; offset < memorySize; offset += pageSize) { 
        memset(memory + offset, 0, pageSize); 
    } 
 
    // Освобождение памяти 
#ifdef _WIN32 
    VirtualFree(memory, 0, MEM_RELEASE); 
#else 
    munmap(memory, memorySize); 
#endif 
 
    return 0; 
}
