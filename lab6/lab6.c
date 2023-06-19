#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "allocation_times.txt"

int main() {
    double time_spent = 0.0;
    FILE* file = fopen(FILENAME, "w");
    
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return 1;
    }

    fprintf(file, "size;time\n");
    
    for (int i = 0; i < 10000; i++) {
        clock_t begin = clock();
        void* memory = malloc(i);
        free(memory);
        clock_t end = clock();
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        fprintf(file, "%d;%f\n", i, time_spent);
    }
    fclose(file);
    printf("Results saved to file %s\n", FILENAME);
    return 0;
}
