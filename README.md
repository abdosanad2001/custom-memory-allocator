![C CI](https://github.com/abdosanad2001/custom-memory-allocator/actions/workflows/ci.yml/badge.svg)

# Custom Memory Allocator

A thread-safe, explicit free-list memory allocator implemented in pure C. 
This project serves as an educational replacement for standard malloc and free, directly utilizing the sbrk system call to manage heap memory.

## Features
- **Custom malloc & free**: Implemented using a First-Fit search strategy.
- **Thread-Safety**: Utilizes pthread_mutex to handle concurrent allocation requests safely.
- **Memory Coalescing**: Forward coalescing logic to merge contiguous free blocks and reduce memory fragmentation.
- **Alignment**: Ensures 8-byte memory alignment for CPU efficiency.

## Getting Started

### Prerequisites
- GCC Compiler
- Make
- Valgrind (for memory leak checks)

### Build and Run
```bash
make
./test_runner
valgrind --leak-check=full ./test_runner
