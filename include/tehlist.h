#ifndef TEHLIST_H
#define TEHLIST_H


#include <stdlib.h>     // malloc, free
#include <stdio.h>      // printf
#include <stdbool.h>    // boolean
#include <string.h>     // memcpy (copying memory)
#include <stddef.h>     // NULL

/** List specification
*
*   Potential issues/problems/shortcomings
*
*   1. This only works with a struct that has constant size. Using a flexible array member would kill it, due to having to allocate the memory.
*   Memory allocated is: [size_of_structure] * [list_capacity]
*       NOTE: This could be fairly easily fixed by creating a struct which holds pointers instead of having a flexible block of data.
*   Thus a potentially fatal bug: trying to use a structure of non-constant size causes massive problems: crashes, deaths, grievous injuries
*
*
*   2. The tehlist functions don't check for type(and they shouldn't, really),
*   and they can't really do so(the tehlist can only know the size of structure)
*       NOTE: All the needed functions have to be encapsulated
*
*
*
*
*      # Needed operations(stolen from wikipedo):
*
*       1. constructor for creating an empty list:
*            tehlist listCreate(tehlist, capacity, value_size)
*   DONE :void tehlist_generic_createListInPlace
*
*
*     2. operation for testing whether or not a list is empty:
*            bool listIsEmpty(tehlist)
*   DONE  tehlist.list_size         (stored in the list's metainfo. Size 0 means list is empty)
*
*
*    3. operation for prepending an entity to a list
*            void listPrepend(tehlist, value)
*
*
*    4. operation for appending an entity to a list
*            void tehlistAppend(tehlist, value)
*   DONE  void tehlist_generic_appendValue()
*
*
*    DONE 5. operation for determining the first component (or the "head") of a list
*            void* tehlistGetFirst(tehlist)
* tehlist.pointer_to_zero   (stored in the list's metainfo)
*
*
*    ?DONE 6. operation for referring to the list consisting of all the components of a list except for its first
* I don't understand that xD I believe it simply means random access.
* Though, it could also mean requiring an operation that cuts the list.
* I want to add operations which allow concatenating and splitting lists, so finally, it should sort itself out either way.
*
*           Other operations I want :
*
*        7. Inserting a value into any place(which pushes other values forward when needed)
*            void tehlistInsert(tehlist, value, position)
*
*        8. Delete a value from any place(which pushes other values back, to fill the gap)
*            void tehlistDeleteValue(tehlist, position)
*
*        9. Remove a value from a tehlist and receive it
*            void* tehlistPullValue(tehlist, position)
*
*        10. Extension of: 7, 8, 9. With a range of values(inserting a tehlist into a tehlist, or popping a tehlist from a list):
*           void tehlistInsertTehlist(tehlist, tehlist_to_insert, position)
*           void tehlistRemoveValues(tehlist, first_position, last_position)
*           tehlist tehlistPullValues(tehlist, first_position, last_position)
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
*
 */


typedef struct TEHLIST_
{
    // All of those values must be initialized in the function that creates the list
//  Technical stuff(memory)
    size_t size_of_value;      // this will be set depending on the desired size of held content's structure
    size_t list_capacity;      // memory allocated for this many values(size can't be larger than this)
    bool automatical_resize;
//  About values themself:
    size_t list_size;          // number of records: highest record + 1
    void* pointer_to_zero;     // address of the content
//  Functions needed by tehlist interface:
    void  (* function_print_value_at_index)(const void* const list__, const size_t index__);
} tehlist;


// tehlist_generic_func     generally shouldn't be invoked by user, but can be used as-is
// tehlist_func             can be used as-is


// 1. the barest initialization, only what is absolutely necessary to have it work
void tehlist_generic_createListInPlace (tehlist* const list_to_initialize__,
                                        const size_t value_size__,
                                        const size_t capacity__);
// Operations on memory
void tehlist_generic_resizeList(tehlist* const list_to_resize__, const size_t desired_capacity___);
void tehlist_generic_destroyList(tehlist* const list_to_destroy__);


// Content
void* tehlist_generic_getPointerToIndex(const tehlist* list__, const int index__);
void tehlist_generic_setValueAtIndex(tehlist* const list__, const size_t index__, const void* const value__);
void tehlist_generic_appendValue(tehlist* const list__, const void* const value__);
void tehlist_generic_prependValue(tehlist* const list__, const void* const value__);


// Display
void tehlist_displayEverything(const tehlist* const displayed_list__);
void tehlist_displayInformation(const tehlist* const displayed_list__);
void tehlist_displayInformation_functions(const tehlist* const displayed_list__);
void tehlist_displayContent(const tehlist* const displayed_list__);





#endif // TEHLIST_H
