#include "../include/vector.h"
#include <stdio.h>

int main()
{
    vector* Vec = Vector(1);

    

    push_back(&Vec,"hello");
    push_back(&Vec,"world");
    push_back(&Vec,"happy");
    push_front(&Vec,"make");

    pop_front(&Vec);
    pop_back(&Vec);

    for(int i = 0; i < Vec->ObjectCount; i++)
    {
        printf("%s\n", at(Vec,i));
    }

    return 0;
}