# Vector (String Vector for C)

A simple dynamic array (“vector”) implementation in C for storing **heap-allocated strings (`char*`)**.

This project is intended as a **learning-focused, minimal container library**, demonstrating:

* dynamic memory management
* capacity growth strategies
* ownership rules
* clean C APIs

---

## Features

* Dynamic resizing (capacity doubles when full)
* Push and pop from both front and back
* Safe string storage (strings are **deep-copied**)
* Explicit error handling via return codes
* Clean separation between header and implementation

---

## Data Structure

```c
typedef struct {
    size_t ObjectCount;  // number of stored strings
    char** Data;         // array of string pointers
    size_t capacity;     // allocated capacity
} vector;
```

---

## Ownership Rules (IMPORTANT)

* `push_back` / `push_front` **copy** the input string
  → the caller retains ownership of the original string
* The vector **owns all stored strings**
* `destroy()` must be called to free:

  * all stored strings
  * the internal array
  * the vector itself
* `at()` returns a pointer to internal storage
  → **do not free it**

---

## Public API

### Creation / Destruction

```c
vector* createVector(void);
void destroy(vector* v);
```

---

### Modification

```c
int push_back(vector* vec, const char* str);
int push_front(vector* vec, const char* str);
int pop_back(vector* vec);
int pop_front(vector* vec);
```

---

### Access

```c
char* at(vector* v, size_t index);
```

Returns `NULL` if:

* `v` is `NULL`
* `index` is out of bounds

---

## Error Codes

```c
typedef enum {
    Okay,
    AllocationError,
    NoData,
    Empty,
    NoArgument
} errors;
```

| Error             | Meaning                                   |
| ----------------- | ----------------------------------------- |
| `Okay`            | Operation successful                      |
| `AllocationError` | Memory allocation failed                  |
| `NoData`          | Operation requires data, but vector empty |
| `Empty`           | Invalid or empty vector                   |
| `NoArgument`      | Required argument was `NULL`              |

---

## Example Usage

```c
#include "vector.h"
#include <stdio.h>

int main(void) {
    vector* v = createVector();

    push_back(v, "hello");
    push_front(v, "world");

    for (size_t i = 0; i < v->ObjectCount; i++) {
        printf("%s\n", at(v, i));
    }

    pop_back(v);
    pop_front(v);

    destroy(v);
    return 0;
}
```

---

## Complexity Notes

| Operation    | Time Complexity |
| ------------ | --------------- |
| `push_back`  | Amortized O(1)  |
| `pop_back`   | O(1)            |
| `push_front` | O(n)            |
| `pop_front`  | O(n)            |
| `at`         | O(1)            |

Front operations are linear due to element shifting.

---

## Limitations

* Stores **strings only** (`char*`)
* Not thread-safe
* No iterator abstraction
* No shrink-to-fit
* Not a generic container

These are **intentional trade-offs** for clarity and learning value.

---

## Build Notes

This library uses only the C standard library.

Compile example:

```sh
gcc -Wall -Wextra -pedantic -std=c11 vector.c main.c -o example
```

Tested with `valgrind` (no leaks under correct usage).

---
