
#include "tehlistdemo_structura.h"


#include <math.h> // For some vanity maths functions because I like maths and numbers

int main()
{
    size_t capacity_of_structuralist = 3;

    //
    tehlist structura_list;
    structura_list = tehlist_structura_createList(capacity_of_structuralist);
    tehlist_displayEverything(&structura_list);

    printf("\nSizeof structura = %d", sizeof(structura));

    structura temp_struct;
    printf("\nSizeof temp_struct = %d", sizeof(temp_struct));


    temp_struct.label[5] = 'A';
    temp_struct.val_integer = 1;
    temp_struct.val_double  = sqrt(2) ;

    tehlist_generic_appendValue(&structura_list, &temp_struct);




    printf("\n\n FINISHED DOING STUFF ON THE LIST \n\n");
    tehlist_displayEverything(&structura_list);



    printf("\n\n\n\t - - -");
    return 0;
}
