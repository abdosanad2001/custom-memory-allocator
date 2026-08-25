#include "allocator.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(void) {
    // Test 1: Simple integer array allocation
    int *arr = (int *)custom_malloc(100 * sizeof(int));
    assert(arr != NULL);

    for (int i = 0; i < 100; i++) {
        arr[i] = i;
    }
    assert(arr[50] == 50);

    // Test 2: String allocation and memory write
    char *str = (char *)custom_malloc(256);
    assert(str != NULL);
    strcpy(str, "Allocation test");
    assert(strcmp(str, "Allocation test") == 0);

    // Test 3: Memory deallocation (trigger coalescing)
    custom_free(arr);
    custom_free(str);

    // Re-allocation after free
    int *new_arr = (int *)custom_malloc(50 * sizeof(int));
    assert(new_arr != NULL);
    custom_free(new_arr);

    printf("All memory tests passed successfully.\n");
    return 0;
}
