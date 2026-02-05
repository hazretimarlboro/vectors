#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------------------
// Access element at a specific index
// --------------------------------------
char* at(vector* v, size_t index)
{
    if(!v) return NULL;                   // check for NULL vector
    if(index >= v->ObjectCount) return NULL; // check index bounds
    return v->Data[index];                // return pointer to string
}

// --------------------------------------
// Return pointer to the first element
// --------------------------------------
char** begin(vector* v)
{
    if(!v) return NULL;                   // check for NULL vector
    
    return v->Data;                       // return pointer to first element
}

// --------------------------------------
// Return pointer to one past the last element
// --------------------------------------
char** end(vector* v)
{
    if(!v || !v->Data) return NULL;       // check for NULL vector or empty data

    return v->Data + v->ObjectCount;      // pointer arithmetic: points one past last element
}

// --------------------------------------
// Create a new empty vector
// --------------------------------------
vector* createVector(void)
{
    size_t ObjectCount = 0;               // initialize object count
    char** Data = NULL;                    // initialize data pointer to NULL

    vector* vec = (vector*)malloc(sizeof(vector)); // allocate vector struct
    if(!vec) return NULL;                  // check allocation

    vec->Data = Data;                      // set initial data pointer
    vec->ObjectCount = ObjectCount;        // set initial object count
    vec->capacity = 0;                     // capacity is zero initially

    return vec;                            // return the new vector
}

// --------------------------------------
// Destroy vector and free all memory
// --------------------------------------
void destroy(vector* v)
{
    if (!v) return;                        // check for NULL

    // free each string individually
    for (size_t i = 0; i < v->ObjectCount; i++)
        free(v->Data[i]);

    // clear all pointers in the array (optional safety)
    for (char** it = begin(v); it != end(v); it++)
    {
        free(*it);                         // free again? careful: redundant if already freed
        *it = NULL;                         // nullify pointer
    }

    free(v->Data);                          // free the array of pointers
    free(v);                                // free the struct itself
}

// --------------------------------------
// Remove the first element
// --------------------------------------
int pop_front(vector* oldV)
{
    if(!oldV) return Empty;                // check for NULL
    if(!((oldV)->Data) || (oldV)->ObjectCount == 0) return NoData; // empty vector

    free((oldV)->Data[0]);                 // free memory of first string
    (oldV)->Data[0] = NULL;                // optional: set pointer to NULL

    // shift all elements one position to the front
    memmove(oldV->Data, oldV->Data + 1, (oldV)->ObjectCount - 1 * sizeof(char*));

    (oldV)->Data[(oldV)->ObjectCount - 1] = NULL; // clear last pointer
    (oldV)->ObjectCount--;                  // decrease count

    return Okay;                             // operation successful
}

// --------------------------------------
// Remove the last element
// --------------------------------------
int pop_back(vector* oldV)
{
    if(!oldV) return Empty;                // check for NULL
    if(!((oldV)->Data) || (oldV)->ObjectCount == 0) return NoData; // empty vector

    free((oldV)->Data[(oldV)->ObjectCount - 1]); // free last string
    (oldV)->Data[(oldV)->ObjectCount - 1] = NULL; // nullify pointer
    (oldV)->ObjectCount--;                  // decrease count

    return Okay;                             // operation successful
}

// --------------------------------------
// Add an element to the end
// --------------------------------------
int push_back(vector* vec, const char* str)
{
    if(!vec) return Empty;                  // check vector pointer
    if(!str) return NoArgument;             // check string pointer

    // If vector is full, increase capacity
    if((vec)->ObjectCount == (vec)->capacity)
    {
        size_t new_capacity = (vec)->capacity == 0 ? 4 : (vec)->capacity * 2; // double capacity or set to 4
        char** tmp = realloc((vec)->Data, new_capacity * sizeof(char*));     // realloc array
        if(!tmp) return AllocationError;     // check allocation
        (vec)->Data = tmp;                   // update vector's data pointer
        (vec)->capacity = new_capacity;      // update capacity
    }

    // Allocate memory for new string and copy it
    (vec)->Data[(vec)->ObjectCount] = malloc(strlen(str) + 1); // +1 for null terminator
    if(!(vec)->Data[(vec)->ObjectCount]) return AllocationError; // check allocation
    strcpy((vec)->Data[(vec)->ObjectCount], str);               // copy string
    (vec)->ObjectCount++;                                        // increment count
    return Okay;                                                 // success
}

// --------------------------------------
// Add an element to the front
// --------------------------------------
int push_front(vector* vec, const char* str)
{
    if(!vec || !str) return Empty;          // check vector and string pointers

    // If vector is full, increase capacity
    if((vec)->ObjectCount == (vec)->capacity)
    {
        size_t new_capacity = (vec)->capacity == 0 ? 4 : (vec)->capacity * 2; // double capacity or set to 4
        char** tmp = realloc((vec)->Data, new_capacity * sizeof(char*));     // realloc array
        if(!tmp) return AllocationError;     // check allocation
        (vec)->Data = tmp;                   // update vector's data pointer
        (vec)->capacity = new_capacity;      // update capacity
    }

    // Shift all elements one position back to make space at front
    for (char** it = end(vec); it != begin(vec); it--)
    {
        *it = *(it - 1);                     // move element backwards
    }

    // Allocate memory for new string and copy it
    (vec)->Data[0] = malloc(strlen(str) + 1); // +1 for null terminator
    if(!(vec)->Data[0]) return AllocationError; // check allocation
    strcpy((vec)->Data[0], str);               // copy string
    (vec)->ObjectCount++;                       // increment count

    return Okay;                                // success
}