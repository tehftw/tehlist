#ifndef TEHLIST_H
#define TEHLIST_H


#include <stdlib.h>     // malloc, free
#include <stdio.h>      // printf
#include <stdbool.h>    // boolean
#include <string.h>     // memcpy(copying memory)

/*
    List specification
 Needed operations:
DONE 1. constructor for creating an empty list;
 2. operation for testing whether or not a list is empty;
 3. operation for prepending an entity to a list
 4. operation for appending an entity to a list
 5. operation for determining the first component (or the "head") of a list
 6. operation for referring to the list consisting of all the components of a list except for its first (this is called the "tail" of the list.)
*/


typedef struct TEHLIST_
{
    // All of those values must be initialized in the function that creates the list
//  Technical stuff(memory)
    size_t size_of_value;      // this will be set depending on the desired size of held content's structure
    size_t list_capacity;      // memory allocated for the list
    bool automatical_resize;          //
//  About values themself:
    size_t list_size;          // number of records(highest defined index)
    void* pointer_to_zero;     // address of the content
//  Functions needed by tehlist interface:
    void  (* function_print_value_at_index)(const void* const list__, const size_t index__);
} tehlist;

// tehlist_generic_func     generally shouldn't be invoked by user
// tehlist_func             can be used as-is


void tehlist_generic_createListInPlace (tehlist* list_to_initialize__,
                                        const size_t value_size__,
                                        const size_t capacity__,
                                        void  (*function_print_value_at_index__)(const void* const list__, const size_t index__) );
//
//

// Operating on list's content
void* tehlist_generic_getPointerToIndex(const tehlist* list__, const int index__);
void  tehlist_generic_setValueAtIndex  (tehlist* list__, int index__, void* value__);
void  tehlist_generic_appendValue      (tehlist* list__, void* value__); // should employ setValueAtIndex



//
void tehlist_displayEverything           (const tehlist* displayed_list__);
void tehlist_displayContent              (const tehlist* displayed_list__);
void tehlist_displayInformation          (const tehlist* displayed_list__);
void tehlist_displayInformation_functions(const tehlist* displayed_list__);





#endif // TEHLIST_H
