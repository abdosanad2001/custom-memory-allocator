#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

// Structure representing the metadata of each memory block
typedef struct block_meta {
    size_t size;               // Size of the allocated user data
    struct block_meta *next;   // Pointer to the next memory block
    int is_free;               // Flag: 1 if block is free, 0 if occupied
} block_meta;

#define META_SIZE sizeof(block_meta)

// Function prototypes for allocation and deallocation
void *custom_malloc(size_t size);
void custom_free(void *ptr);

#endif
