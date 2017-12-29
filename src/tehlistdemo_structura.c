

#include "tehlistdemo_structura.h"


tehlist tehlist_structura_createList(const size_t capacity__)
{
    tehlist initialized_tehlist;

    tehlist_generic_createListInPlace(&initialized_tehlist, sizeof(structura), capacity__);
    //
    initialized_tehlist.automatical_resize = true;
    initialized_tehlist.function_print_value_at_index = &tehlist_structura_printValueAtIndex;

    return initialized_tehlist;
}




void tehlist_structura_printValueAtIndex(const void* const list__, const size_t index__)
{
    printf("\n %3d. ", index__);
    const tehlist* list_ptr = list__;
    void* ptr_to_zero = (*list_ptr).pointer_to_zero;
    structura* ptr_to_value = ptr_to_zero;
    ptr_to_value = ptr_to_value + index__;

    for(int i =0; i<STRUCTURA_LABEL_LENGTH; i++)
    {
        printf("%c", (*ptr_to_value).label[i]);
    }
    printf(" integer %d ", (*ptr_to_value).val_integer);
    printf(" ; double %.2f ", (*ptr_to_value).val_double);
}
