#pragma once


#include <stdio.h>
#include "tehlist.h"

#define STRUCTURA_LABEL_LENGTH 8

typedef struct STRUCTURA
{
    int val_integer;
    double val_double;
    char label[STRUCTURA_LABEL_LENGTH];
} structura;

tehlist tehlist_structura_createList(const size_t capacity__);


void  tehlist_structura_printValueAtIndex(const void* const list__, const size_t index__);
