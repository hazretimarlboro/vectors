#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>

typedef enum
{
    Okay,
    AllocationError,
    NoData,
    Empty,
    NoArgument
} errors;

typedef struct 
{
    size_t ObjectCount;
    char** Data;
    size_t capacity;
} vector;

vector* createVector(void);
int     push_back (vector* vec, const char* str);
int     push_front(vector* vec, const char* str);
char*   at        (vector* v, size_t index);
int     pop_front (vector* oldV);
int     pop_back  (vector* oldV);
void    destroy   (vector* v);
char**  begin     (vector* v);
char**  end       (vector* v);

#endif