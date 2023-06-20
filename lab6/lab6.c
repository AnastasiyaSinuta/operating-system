#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/time.h> 

#define FILENAME "allocation_times.txt"
#define NUM_TESTS 10 
 
long long get_current_time() { 
    struct timeval tv; 
    gettimeofday(&tv, NULL); 
    return tv.tv_sec * 1000000 + tv.tv_usec; 
} 
 
long long test_malloc(size_t size) { 
    void* ptr; 
    long long start_time, end_time, total_time = 0; 
 
    for (int i = 0; i < NUM_TESTS; i++) { 
        start_time = get_current_time(); 
        ptr = malloc(size); 
        free(ptr); 
        end_time = get_current_time(); 
        total_time += end_time - start_time;
    } 
 
    return total_time / NUM_TESTS;
} 
 
long long test_calloc(size_t size) { 
    void* ptr; 
    long long start_time, end_time, total_time = 0; 
 
    for (int i = 0; i < NUM_TESTS; i++) { 
        start_time = get_current_time(); 
        ptr = calloc(1, size); 
        free(ptr); 
        end_time = get_current_time(); 
        total_time += end_time - start_time;
    } 
 
    return total_time / NUM_TESTS;
} 
 
long long test_realloc(size_t size) { 
    void* ptr; 
    long long start_time, end_time, total_time = 0; 
 
    for (int i = 0; i < NUM_TESTS; i++) { 
        ptr = malloc(size / 2);
        start_time = get_current_time(); 
        ptr = realloc(ptr, size);
        free(ptr);
        end_time = get_current_time(); 
        total_time += end_time - start_time; 
    } 
 
    return total_time / NUM_TESTS;
} 
 
int main() { 
    FILE* file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return 1;
    }
    fprintf(file, "size;malloc;calloc;realloc\n");
    
    size_t min_size = 1;  // Minimum size of memory to allocate 
    size_t max_size = 100000000;  // Maximum size of memory to allocate 
    size_t step_size = 100000;  // Size increment 
 
    for (size_t size = min_size; size <= max_size; size += step_size) { 
        long long m = test_malloc(size); 
        long long c = test_calloc(size); 
        long long r = test_realloc(size); 
        fprintf(file, "%zu;%lld;%lld;%lld\n", size, m, c, r);
    } 
    fclose(file);
    printf("Results saved to file %s\n", FILENAME);
    return 0; 
}