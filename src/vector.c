#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vector* createVector(void)
{
    size_t ObjectCount = 0;
    char** Data = NULL;

    vector* vec = (vector*)malloc(sizeof(vector));
    if(!vec) return NULL;
    vec->Data = Data;
    vec->ObjectCount = ObjectCount;
    vec->capacity = 0;

    return vec;
}

void destroy(vector* v)
{
    if (!v) return;
    for (size_t i = 0; i < v->ObjectCount; i++)
        free(v->Data[i]);
    free(v->Data);
    free(v);
}

int pop_front(vector* oldV)
{
    if(!oldV) return Empty;
    if(!((oldV)->Data) || (oldV)->ObjectCount == 0) return NoData;
    
    free((oldV)->Data[0]);
    (oldV)->Data[0] = NULL;

    for(int i = 0; i < (oldV)->ObjectCount -1; i++)
    {
        (oldV)->Data[i] = (oldV)->Data[i+1];
    }
    (oldV)->Data[(oldV)->ObjectCount - 1] = NULL;
    (oldV)->ObjectCount--;

    return Okay;

}

int pop_back(vector* oldV)
{
    if(!oldV) return Empty;
    if(!((oldV)->Data) || (oldV)->ObjectCount == 0) return NoData;

    free((oldV)->Data[(oldV)->ObjectCount - 1]); 
    (oldV)->Data[(oldV)->ObjectCount - 1] = NULL;
    (oldV)->ObjectCount--;

    return Okay;
}

int push_back(vector* vec, const char* str)
{
    if(!vec) return Empty;
    if(!str) return NoArgument;


    if((vec)->ObjectCount == (vec)->capacity)
    {
        size_t new_capacity = (vec)->capacity == 0 ? 4 : (vec)->capacity *2;
        char** tmp = realloc((vec)->Data, new_capacity * sizeof(char*));
        if(!tmp) return AllocationError;
        (vec)->Data = tmp;
        (vec)->capacity = new_capacity;

    }

    (vec)->Data[(vec)->ObjectCount] = malloc(strlen(str) + 1);
    if(!(vec)->Data[(vec)->ObjectCount]) return AllocationError;
    strcpy((vec)->Data[(vec)->ObjectCount],str);
    (vec)->ObjectCount++;
    return Okay;
    
}

int push_front(vector* vec, const char* str)
{
    if(!vec || !str) return Empty;
    

    if((vec)->ObjectCount == (vec)->capacity)
    {
        size_t new_capacity = (vec)->capacity==0 ? 4 : (vec)->capacity *2;
        char** tmp = realloc((vec)->Data, new_capacity * sizeof(char*));
        if(!tmp) return AllocationError;
        (vec)->Data = tmp;
        (vec)->capacity = new_capacity;
    }


    for(int i = (vec)->ObjectCount; i > 0; i--)
    {
        (vec)->Data[i] = (vec)->Data[i-1]; 
    }

    (vec)->Data[0] = malloc(strlen(str)+1);
    if(!(vec)->Data[0]) return AllocationError;
    strcpy((vec)->Data[0], str);
    (vec)->ObjectCount++;
    

    


    return Okay;

}

char* at(vector* v, size_t index)
{
    if(!v) return NULL;
    if(index >= v->ObjectCount) return NULL;
    return v->Data[index];
}