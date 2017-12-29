#include "tehlist.h"

#define DISPLAY_MORE_DEBUG_STUFF false
#define TEHLIST_DEFAULT_AUTORESIZE_MODE false

void tehlist_generic_createListInPlace (tehlist* const list_to_initialize__,
                                        const size_t value_size__,
                                        const size_t capacity__)
{

    void* address_of_values = calloc(capacity__, value_size__);
    if(DISPLAY_MORE_DEBUG_STUFF)
    {
        printf("\n Allocated memory for content: %d [bytes]", value_size__*capacity__ );
        printf("\n at address: %p \n", address_of_values );
    }


    // Storing information in the structure
    (*list_to_initialize__).size_of_value   = value_size__;
    (*list_to_initialize__).list_capacity   = capacity__;
    (*list_to_initialize__).list_size       = 0;
    (*list_to_initialize__).pointer_to_zero = address_of_values;
    (*list_to_initialize__).automatical_resize = TEHLIST_DEFAULT_AUTORESIZE_MODE;
    //  functions:
    (*list_to_initialize__).function_print_value_at_index = 0;
}




// Operations on memory
void tehlist_generic_resizeList(tehlist* list_to_resize__, const size_t desired_capacity___)
{
    void* const pointer_to_zero = (*list_to_resize__).pointer_to_zero;
    const size_t needed_memory = desired_capacity___* (*list_to_resize__).size_of_value;

    if(DISPLAY_MORE_DEBUG_STUFF)
    {
        printf("\n Reallocating the list. Capacity before: %d | Pointer before: %p", (*list_to_resize__).list_capacity, pointer_to_zero );
        printf("| Needed memory: %d ", needed_memory );
    }

    void* reallocated_pointer_to_zero = realloc( pointer_to_zero, needed_memory);
    (*list_to_resize__).list_capacity = desired_capacity___;
    (*list_to_resize__).pointer_to_zero = reallocated_pointer_to_zero ;

    if(DISPLAY_MORE_DEBUG_STUFF)
    {
        printf("\n Capacity after: %d | Pointer after: %p", (*list_to_resize__).list_capacity, pointer_to_zero  );
    }
}

void tehlist_generic_destroyList(tehlist* const list_to_destroy__)
{
    free( (*list_to_destroy__).pointer_to_zero );
    (*list_to_destroy__).pointer_to_zero = 0;
}




// Content

// tehlist_generic_getPointerToIndex needs revision - don't know whether it's legal to do pointer arithmetics like that
void* tehlist_generic_getPointerToIndex(const tehlist* list__, const int index__) {
    //printf("\n tehlist_generic_getPointerToIndex. index = %d", index__);
    const int capacity =  (*list__).list_capacity;
    if( index__ >= 0 && index__ < capacity )
    {
        // Move pointer forward by a given amount of bytes, through casting the void* to a char*
        // Because:
        // 1. Can't do pointer arithmetic on void*, but can on char*
        // 2. char* is defined as 1[unit or byte],
        // thus moving char* forward by N, causes it to move as if we were moving through a pointer that was of size N
        void* pointer_to_index = (*list__).pointer_to_zero;

        const size_t bytes_forward = (*list__).size_of_value*index__;
        pointer_to_index = (char*)(pointer_to_index) + ( bytes_forward );

        return pointer_to_index;
    }
    return 0;   // null pointer means out of bounds
}


void tehlist_generic_setValueAtIndex(tehlist* const list__, const size_t index__, const void* const value__)
{
    if(DISPLAY_MORE_DEBUG_STUFF)
    {
        printf("\n setValueAtIndex %d. ", index__);
    }

    const size_t list_size = (*list__).list_size;
    const size_t list_capacity = (*list__).list_capacity;
    bool can_move_data = false;



    if( index__ < list_capacity )
    {
        can_move_data = true;
    }
    else if( (*list__).automatical_resize )
    {
        tehlist_generic_resizeList(list__, index__+1);
        can_move_data = true;
    }
    else if(DISPLAY_MORE_DEBUG_STUFF)
    {
        printf(" No resize. ");
    }



    if( can_move_data )   // only allowed to work when it's allowed to work
    {
        if(DISPLAY_MORE_DEBUG_STUFF)
        {
            printf(" Asking for destination. ");
        }

        void* destination = tehlist_generic_getPointerToIndex(list__, index__);

        if(DISPLAY_MORE_DEBUG_STUFF)
        {
            printf(" Destination: %p", destination );
        }
        //
        if  ( destination ) // non-null only allowed. Ideally, this shouldn't be needed, though I keep it for some reason.
        {
            memcpy(destination, value__, (*list__).size_of_value );             // Copy from @value__ to @destination
            // List size has to be no less than highest index that was set for the sake of other functions
            if( list_size <= index__)
            {
                (*list__).list_size = index__+1;
                if(DISPLAY_MORE_DEBUG_STUFF)
                {
                    printf(" List's size = %d ", (*list__).list_size );
                }
                //
            }
        }
    }
    else if(DISPLAY_MORE_DEBUG_STUFF)
    {
        printf(" Didn't set the value.");
    }
}


void tehlist_generic_appendValue(tehlist* const list__, const void* const value__)
{
    const size_t needed_index = (*list__).list_size;
    tehlist_generic_setValueAtIndex(list__, needed_index, value__);
}

void tehlist_generic_prependValue(tehlist* const list__, const void* const value__)
{
    // First, push all the stored values one index forward
    const size_t needed_index = (*list__).list_size;
    tehlist_generic_setValueAtIndex(list__, needed_index, value__);
}




// Display
void tehlist_displayEverything(const tehlist* const displayed_list__)
{
    tehlist_displayInformation(displayed_list__);


    if(DISPLAY_MORE_DEBUG_STUFF)
    {
        tehlist_displayInformation_functions(displayed_list__);
    }

    printf("\n Contents of list: ");
    tehlist_displayContent(displayed_list__);
}


void tehlist_displayInformation(const tehlist* const displayed_list__)
{
    printf("\n Displaying information about the list: ");
    if(DISPLAY_MORE_DEBUG_STUFF)
    {
        printf("\n\t Memory taken by the list's metainformation: %d ", sizeof(*displayed_list__) );
        printf("\n\t Memory needed by each value: %d", (*displayed_list__).size_of_value);
        printf("\n\t Memory prepared for content: %d ", ( (*displayed_list__).list_capacity * (*displayed_list__).size_of_value) );
    }
    printf("\n\t List capacity: %d (Memory allocated for storing values)", (*displayed_list__).list_capacity);
    printf("\n\t Size of list: %d (Number of stored values)", (*displayed_list__).list_size);
    printf("\n\t Automatical resize: %d (whether it will resize upon trying to access a place that wasn't prepared earlier)", (*displayed_list__).automatical_resize);
    if(DISPLAY_MORE_DEBUG_STUFF)
    {
        printf("\n\t Adres of content: %p", (*displayed_list__).pointer_to_zero);
    }
}


void tehlist_displayInformation_functions(const tehlist* const displayed_list__)
{
    printf("\n\t Addresses of list's functions:");
    printf("\n\t\t printValue %p", (*displayed_list__).function_print_value_at_index);
}


void tehlist_displayContent(const tehlist* const displayed_list__)
{
    for(size_t i = 0; i < (*displayed_list__).list_size; i++)
    {
        (*displayed_list__).function_print_value_at_index(displayed_list__, i);
    }
}
