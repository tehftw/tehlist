#include "tehlist.h"



void tehlist_generic_createListInPlace (tehlist* list_to_initialize__,
                                        const size_t value_size__,
                                        const size_t capacity__,
                                        void  (*function_print_value_at_index__)(const void* const list__, const size_t index__)
) {
    // capacity = number of potential values
    size_t memory_size_for_values = value_size__*capacity__;


    void* address_of_values = calloc(capacity__, value_size__);
    printf("\n Allocated memory for content: %d [bytes]", memory_size_for_values );
    printf("\n at address: %p \n", address_of_values );


    // Storing information in the structure
    (*list_to_initialize__).size_of_value   = value_size__;
    (*list_to_initialize__).list_capacity   = capacity__;
    (*list_to_initialize__).list_size       = 0;
    (*list_to_initialize__).pointer_to_zero = address_of_values;
    (*list_to_initialize__).automatical_resize = true;
    //
    (*list_to_initialize__).function_print_value_at_index = function_print_value_at_index__;
}

// Operations on memory
void tehlist_generic_resizeList(tehlist *list_to_resize__, const size_t desired_size___)
{
    void* pointer_to_zero = (*list_to_resize__).pointer_to_zero;
    printf("\n Reallocating the list. Capacity before: %d | Pointer before: %p", (*list_to_resize__).list_capacity, pointer_to_zero );

    void* reallocated_pointer_to_zero = realloc( pointer_to_zero, desired_size___);
    printf("\n                       Capacity after: %d | Pointer after: %p", (*list_to_resize__).list_capacity, pointer_to_zero  );

    (*list_to_resize__).list_capacity = desired_size___;
    (*list_to_resize__).pointer_to_zero = reallocated_pointer_to_zero ;
}


void tehlist_generic_destroyList(const tehlist* list_to_destroy__)  {
    free( (*list_to_destroy__).pointer_to_zero );
}



//
void* tehlist_generic_getPointerToIndex(const tehlist* list__, const int index__) {
    //printf("\n tehlist_generic_getPointerToIndex. index = %d", index__);
    int capacity =  (*list__).list_capacity;
    if( index__ >= 0 && index__ < capacity )
    {
        void* pointer_to_index = (*list__).pointer_to_zero;
        size_t bytes_forward = (*list__).size_of_value*index__;
        // Move pointer forward by a given amount of bytes
        pointer_to_index = (char*)(pointer_to_index) + ( bytes_forward );
        return pointer_to_index;
    }
    return 0;   // null pointer means out of bounds
}


void tehlist_generic_setValueAtIndex(tehlist* list__, int index__, void* value__) {

    printf("\n setValueAtIndex %d. ", index__);

    size_t list_size = (*list__).list_size;
    size_t list_capacity = (*list__).list_capacity;
    bool can_move_data = false;


    if( index__ >= 0)
    {
        if( index__ < list_capacity )
        {
            can_move_data = true;
        }
        else if( (*list__).automatical_resize )
        {
            can_move_data = true;
            tehlist_generic_resizeList(list__, index__);
        }
    }
    //
    if( can_move_data )   // only allowed to work when can't be out of bounds
    {
        printf(" Asking for destination. ");
        void* destination = tehlist_generic_getPointerToIndex(list__, index__);
        printf(" Destination: %p", destination );
        //
        if(destination != 0)
        {
            // Copy from @value__ to @destination
            memcpy(destination, value__, (*list__).size_of_value );   // void * memcpy ( void * destination, const void * source, size_t num );

            // List size has to be no less than highest index that was set for the sake of other functions
            if( list_size < index__)
            {
                printf("List's size = %d", list_size );
                (*list__).list_size = index__;
            }
        }
        else
        {
            printf(" Null destination.");
        }
    }
}


void tehlist_generic_appendValue(tehlist* list__, void* value__)    {
    size_t needed_index = (*list__).list_size + 1;
    tehlist_generic_setValueAtIndex(list__, needed_index, value__);
}







// Display
void tehlist_displayEverything(const tehlist* displayed_list__)
{
    tehlist_displayInformation(displayed_list__);
    tehlist_displayInformation_functions(displayed_list__);
    tehlist_displayContent(displayed_list__);
}


void tehlist_displayInformation(const tehlist* displayed_list__)
{
    printf("\n\t\t\t Displaying information about the list: ");
    printf("\n\t Memory taken by the list's metainformation: %d ", sizeof(*displayed_list__) );
    printf("\n\t Size of stored values: %d (Memory taken by each value)", (*displayed_list__).size_of_value);
    printf("\n\t List capacity: %d (Memory for storing values)", (*displayed_list__).list_capacity);
    printf("\n\t Size of list: %d (Highest index of stored value)", (*displayed_list__).list_size);
    printf("\n\t Memory prepared for content: %d ", ( (*displayed_list__).list_capacity * (*displayed_list__).size_of_value) );
    printf("\n\t Adres of content: %p", (*displayed_list__).pointer_to_zero);
    printf("\n\t Automatical resize: %d", (*displayed_list__).automatical_resize);
}


void tehlist_displayInformation_functions(const tehlist* displayed_list__)
{
    printf("\n\t Addresses of list's functions:");
    printf("\n\t\t printValue %p", (*displayed_list__).function_print_value_at_index);
}


void tehlist_displayContent(const tehlist* displayed_list__)
{
    printf("\n Contents of list: ");
    for(size_t i = 0; i < (*displayed_list__).list_size; i++)
    {
        (*displayed_list__).function_print_value_at_index(displayed_list__, i);
    }
}
