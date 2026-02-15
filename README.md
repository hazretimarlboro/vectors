# Generic Thread-Safe Vector API in C

A lightweight, **generic, thread-safe vector implementation** in C, designed for storing any data type with dynamic resizing, safe access, and optional reverse and iteration utilities. Ideal for multithreaded applications or high-performance code.

---

## Features

* **Generic**: works with any data type using `void*` and `elementSize`.
* **Thread-safe**: uses `pthread_mutex_t` internally to prevent race conditions.
* **Dynamic resizing**: automatically expands capacity when pushing elements.
* **Flexible operations**:

  * `push_back`, `push_front`
  * `pop_back`, `pop_front`
  * `reverse`
  * `at`, `begin`, `end` accessors
* **Safe destruction**: frees all memory and destroys internal locks.
* **Lightweight and readable**: minimal dependencies (POSIX threads only).

---

## Installation

Include the header and source in your project:

```c
#include "vector.h"
```

Compile with `-lpthread` to link pthreads:

```bash
gcc main.c vector.c -lpthread -o my_program
```

---

## API Reference

### Vector Creation

```c
vector* Vector(size_t elementSize);
```

* Allocates and returns a new vector for elements of size `elementSize`.
* Returns `NULL` on allocation failure.

---

### Adding Elements

```c
int vector_push_back(vector* v, const void* element);
int vector_push_front(vector* v, const void* element);
```

* Adds an element to the end or front of the vector.
* Automatically resizes if necessary.
* Returns an `errors` enum value:

  * `Okay` – success
  * `Empty` – vector pointer is NULL
  * `NoArgument` – element pointer is NULL
  * `AllocationError` – memory allocation failed

---

### Removing Elements

```c
int vector_pop_back(vector* v);
int vector_pop_front(vector* v);
```

* Removes the last or first element.
* Returns an `errors` enum value:

  * `Okay` – success
  * `Empty` – vector pointer is NULL
  * `NoData` – vector is empty

---

### Accessing Elements

```c
void* vector_at(vector* v, size_t index);
void* vector_begin(vector* v);
void* vector_end(vector* v);
```

* `vector_at`: returns a pointer to the element at `index`.
* `vector_begin`: pointer to the first element.
* `vector_end`: pointer one past the last element.
* ⚠️ **Note**: These pointers are valid only until the vector is modified by other threads.

---

### Reverse

```c
int vector_reverse(vector* v);
```

* Reverses the vector in-place.
* Returns `Okay` or `AllocationError` if internal memory allocation fails.

---

### Destruction

```c
void vector_destroy(vector* v);
```

* Frees all memory associated with the vector and destroys internal mutex locks.
* After this call, the vector pointer becomes invalid.

---

### Error Codes

```c
typedef enum {
    Okay,
    AllocationError,
    NoData,
    Empty,
    NoArgument
} errors;
```

Use these to handle errors gracefully.

---

## Usage Example

```c
#include <stdio.h>
#include "vector.h"

void print_ints(vector* v) {
    int* data = (int*)vector_begin(v);
    for(size_t i = 0; i < v->ObjectCount; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main() {
    vector* v = Vector(sizeof(int));
    int a = 10, b = 20, c = 30;

    vector_push_back(v, &a);
    vector_push_back(v, &b);
    vector_push_front(v, &c);

    print_ints(v); // Output: 30 10 20

    vector_reverse(v);
    print_ints(v); // Output: 20 10 30

    vector_destroy(v);
    return 0;
}
```

---

## Notes

* Thread-safety is **built-in**, but returning raw pointers (via `at`, `begin`, `end`) **can become invalid** if another thread modifies the vector.
* For safe multithreaded iteration, copy elements into a temporary buffer or lock the vector during the iteration.

---

## License

MIT License – free to use, modify, and distribute.

---
