#include "allocator.h"
#include <unistd.h>
#include <pthread.h>

// Global head of the memory block linked list
static block_meta *head = NULL;
// Mutex to ensure thread-safety across concurrent allocations
static pthread_mutex_t global_malloc_lock = PTHREAD_MUTEX_INITIALIZER;

// Search for an existing free block using First-Fit strategy
static block_meta *find_free_block(block_meta **last, size_t size) {
    block_meta *current = head;
    while (current && !(current->is_free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

// Request additional heap space from OS using sbrk system call
static block_meta *request_space(block_meta *last, size_t size) {
    block_meta *block = (block_meta *)sbrk(0);
    void *request = sbrk(size + META_SIZE);
    
    // Check if sbrk failed
    if (request == (void *)-1) {
        return NULL;
    }

    if (last) {
        last->next = block;
    }

    block->size = size;
    block->next = NULL;
    block->is_free = 0;
    return block;
}

// Dynamic memory allocation implementation
void *custom_malloc(size_t size) {
    if (size <= 0) {
        return NULL;
    }

    // Align allocation size to 8-byte boundary
    size = (size + 7) & ~7;

    pthread_mutex_lock(&global_malloc_lock);
    block_meta *block;

    if (!head) {
        // First allocation request
        block = request_space(NULL, size);
        if (!block) {
            pthread_mutex_unlock(&global_malloc_lock);
            return NULL;
        }
        head = block;
    } else {
        block_meta *last = head;
        block = find_free_block(&last, size);
        if (!block) {
            // No suitable block found, extend heap
            block = request_space(last, size);
            if (!block) {
                pthread_mutex_unlock(&global_malloc_lock);
                return NULL;
            }
        } else {
            // Reusing existing free block
            block->is_free = 0;
        }
    }

    pthread_mutex_unlock(&global_malloc_lock);
    // Return pointer to payload right after the metadata header
    return (block + 1);
}
