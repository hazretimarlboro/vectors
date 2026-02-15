#ifndef VECTOR_H
#define VECTOR_H
#include <pthread.h>
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
    void* Data;
    size_t ObjectCount;
    size_t capacity;
    size_t elementSize;
    pthread_mutex_t lock;
} vector;

vector* Vector(size_t elemsize);
int     vector_push_back (vector* v, const void* elem);
int     vector_push_front(vector* v, const void* elem);
void*   vector_at        (vector* v, size_t index);
int     vector_pop_front (vector* v);
int     vector_pop_back  (vector* v);
void    vector_destroy   (vector* v);
void*   vector_begin     (vector* v);
void*   vector_end       (vector* v);
int     vector_reverse   (vector* v);

#endif