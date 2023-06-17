#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <windows.h>

int main() {
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    size_t pageSize = systemInfo.dwPageSize;
    
    while (1) {
        LPVOID p = VirtualAlloc(NULL, pageSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        if (p == NULL) {
            printf("Memory allocation failed!\n");
            break;
        }

        for (size_t i = 0; i < pageSize; i++) {
            *((volatile uint8_t*)(p + i)) = 0;
        }
    }

    return 0;
}
