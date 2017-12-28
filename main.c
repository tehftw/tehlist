
#include "tehlist_tehstruct.h"


int main()
{
    size_t capacity_of_structuralist = 10;

    //
    tehlist structura_list;
    structura_list = tehlist_structura_createList(capacity_of_structuralist);
    printf("Sizeof structura = %d", sizeof(structura));




    structura temp_struct;
    structura* struc_ptr = structura_list.pointer_to_zero;
    struc_ptr ++;
    temp_struct.label[0] = 'T';
    temp_struct.label[1] = 'E';
    temp_struct.label[2] = 'H';
    temp_struct.label[3] = 'F';
    temp_struct.label[4] = 'T';
    temp_struct.label[5] = 'W';
    temp_struct.label[6] = 'V';
    temp_struct.label[7] = '@';
    temp_struct.val_integer = 74;
    temp_struct.val_double = 2.71;


    tehlist_generic_setValueAtIndex(&structura_list, -1, &temp_struct);
    tehlist_generic_setValueAtIndex(&structura_list, 5, &temp_struct);
    tehlist_generic_setValueAtIndex(&structura_list, 20, &temp_struct);
    tehlist_generic_setValueAtIndex(&structura_list, 25, &temp_struct);
    tehlist_generic_setValueAtIndex(&structura_list, 12, &temp_struct);

    printf("\n\n");
    tehlist_displayEverything(&structura_list);





    printf("\n\n\n\t - - -");
    return 0;
}
