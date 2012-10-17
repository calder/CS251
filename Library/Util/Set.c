#include <stdlib.h>
#include <stdio.h>
#include "Util/Set.h"
#include "Util/spooky-c.h"


Set* set_create ()
{
    Set *toreturn = (Set*)malloc(sizeof(Set));
    toreturn->size = 0;
    toreturn->capacity = 20;
    toreturn->array = malloc(sizeof(void*)*20);
    for(int i = 0; i< 20; ++i)
    {
        toreturn->array[i] = NULL;
    }
    return toreturn;
}


void set_free (Set* set)
{
    set_clear(set);
    free(set->array);
    free(set);
}


void set_print (Set* set)
{
    printf("Set Contains %d items and has capacity %d (%0.2f load)\n", set->size, set->capacity, (float)set->size/(float)set->capacity);
}


int set_size (Set* set)
{
    return set->size;
}


bool set_empty (Set* set)
{
    return set->size==0;
}


void set_add (Set* set, void* item)
{
    int index = stupid_hash(&item, sizeof(void*), 0)%set->capacity;

    if(set->array[index] == NULL)
    {
        SetNode* toAdd = (SetNode*)malloc(sizeof(SetNode));
        toAdd->data = item;
        toAdd->next = NULL;

        set->array[index] = toAdd;
    }
    else
    {
        SetNode* curNode = set->array[index];
        while(curNode->next != NULL)
        {
            if(curNode->data == item)
            {
                return;
            }
            curNode = curNode->next;
        }
        SetNode* toAdd = (SetNode*)malloc(sizeof(SetNode));
        toAdd->data = item;
        toAdd->next = NULL;

        curNode->next = toAdd;
    }
    ++set->size;

}


void set_remove (Set* set, void* item)
{
    int index = stupid_hash(&item, sizeof(void*), 0)%set->capacity;
    SetNode* curNode = set->array[index];
    if (curNode != NULL)
    {
        SetNode** prevPointer = (SetNode**)&(set->array[index]);
        while (curNode->data != item )
        {
            if (curNode == NULL)
            {
                return;
            }
            prevPointer = &curNode->next;
            curNode = curNode->next;
        }
        *prevPointer = curNode->next;
        free(curNode);
        --set->size;
    }
}

void set_clear (Set* set)
{
    for (int i = 0; i<set->capacity; ++i)
    {
        SetNode* curNode = set->array[i];
        while (curNode != NULL)
        {
            SetNode* temp = curNode;
            curNode = curNode->next;
            free(temp);
            --set->size;
        }
        set->array[i] = NULL;
    }
}

bool set_contains (Set* set, void* item)
{
    if (set->size > 0)
    {
        int index = stupid_hash(&item, sizeof(void*), 0)%set->capacity;

        SetNode* curNode = set->array[index];

        while(curNode != NULL)
        {
            void* temp = curNode->data;
            if (curNode->data == item)
            {
                return 1;
            }
            curNode = curNode->next;
        }
    }   
    return 0;
}

uint32_t stupid_hash (const void* input, int length, int seed)
{
	return 1;
}