#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------
// Create a new empty vector
// --------------------------------------
vector* Vector(size_t elemsize)
{
    vector* vec = malloc(sizeof(vector));
    if(!vec) return NULL;

    vec->Data = malloc(4 * elemsize);
    if(!vec->Data) { free(vec); return NULL; }

    vec->ObjectCount = 0;
    vec->capacity = 4;
    vec->elementSize = elemsize;

    pthread_mutex_init(&vec->lock, NULL);
    return vec;
}


// --------------------------------------
// Access element at a specific index
// --------------------------------------
void* vector_at(vector*v, size_t index)
{
    void* res = NULL;
    if(!v || !v->Data) return NULL;

    pthread_mutex_lock(&v->lock);
    if(index < v->ObjectCount)
        res = (char*)v->Data + index * v->elementSize;
    pthread_mutex_unlock(&v->lock);

    return res;
}


// --------------------------------------
// Return pointer to the first element
// --------------------------------------
void* vector_begin(vector* v)
{
    if(!v) return NULL;

    pthread_mutex_lock(&v->lock);
    void* result = NULL;
    

    if(v->Data && v->ObjectCount > 0)
        result = v->Data;

    pthread_mutex_unlock(&v->lock);
    return result;
}

// --------------------------------------
// Return pointer to one past the last element
// --------------------------------------
void* vector_end(vector* v)
{
    if(!v) return NULL;
    pthread_mutex_lock(&v->lock);
    void* result = NULL;
    

    if(v->Data)
        result = (char*)v->Data + v->ObjectCount * v->elementSize;

    pthread_mutex_unlock(&v->lock);
    return result;
}

// --------------------------------------
// Destroy vector and free all memory
// --------------------------------------
void vector_destroy(vector* v)
{
    if(!v) return;
    pthread_mutex_destroy(&v->lock);
    free(v->Data);
    free(v);
}

// --------------------------------------
// Remove the first element
// --------------------------------------
int vector_pop_front(vector* v)
{
    if(!v) return Empty;
    pthread_mutex_lock(&v->lock);
    if(!v->Data || v->ObjectCount == 0) return NoData;

    memmove((char*)v->Data, (char*)v->Data + v->elementSize * 1, (v->ObjectCount - 1) * v->elementSize);
    v->ObjectCount--;
    pthread_mutex_unlock(&v->lock);
    return Okay;
}

// --------------------------------------
// Remove the last element
// --------------------------------------
int vector_pop_back(vector* v)
{
    if(!v) return Empty;
    pthread_mutex_lock(&v->lock);
    if(!v->Data || v->ObjectCount == 0) return NoData;

    v->ObjectCount--;

    pthread_mutex_unlock(&v->lock);
    return Okay;
}

// --------------------------------------
// Add an element to the end
// --------------------------------------
int vector_push_back(vector* v, const void* element)
{
    if(!v) return Empty;
    pthread_mutex_lock(&v->lock);
    if(!element) {pthread_mutex_unlock(&v->lock);return NoArgument;}

    if(v->ObjectCount == v->capacity)
    {
        size_t newCap = v->capacity == 0 ? 4 : v->capacity *2;
        void* tmp = realloc(v->Data, newCap * v->elementSize);
        if(!tmp) return AllocationError;
        v->Data = tmp;
        v->capacity = newCap;
    }

    memmove((char*)v->Data + v->ObjectCount * v->elementSize, element, v->elementSize);
    v->ObjectCount++;
    pthread_mutex_unlock(&v->lock);
    return Okay;
}

// --------------------------------------
// Add an element to the front
// --------------------------------------
int vector_push_front(vector* v, const void* element)
{
    if(!v) return Empty;
    pthread_mutex_lock(&v->lock);
    if(!element) {pthread_mutex_unlock(&v->lock);return NoArgument;}

    if(v->ObjectCount == v->capacity)
    {
        size_t newCap = v->capacity == 0 ? 4 : v->capacity * 2;
        void* tmp = realloc(v->Data, newCap * v->elementSize);
        if(!tmp) return AllocationError;
        v->Data = tmp;
        v->capacity = newCap;
    }

    memmove((char*)v->Data + v->elementSize, v->Data, v->ObjectCount * v->elementSize);
    memcpy(v->Data, element, v->elementSize);

    pthread_mutex_unlock(&v->lock);
    v->ObjectCount++;
    return Okay;
}

//--------------------------------------
//Reverse a vector
//--------------------------------------
int vector_reverse(vector* v)
{
    if(!v) return Empty;
    pthread_mutex_lock(&v->lock);
    if(v->ObjectCount == 1) {pthread_mutex_unlock(&v->lock); return Okay;}  

    size_t n = v->ObjectCount;
    size_t sz = v->elementSize;


    void* tmp = malloc(sz);
    if(!tmp) {pthread_mutex_unlock(&v->lock); return AllocationError;}

    for(size_t i = 0; i < n / 2; i++)
    {
        void* a = (char*)v->Data + i * sz;
        void* b = (char*)v->Data + (n - i - 1) * sz;

        memcpy(tmp, a, sz);
        memcpy(a, b, sz);
        memcpy(b, tmp, sz);
    }

    free(tmp);
    pthread_mutex_unlock(&v->lock);
    return Okay;
}
