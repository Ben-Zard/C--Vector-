/*******************************************************************
Creating a lite vector that will be initialized by pointers that point to a type
of data. This program will have operations to cleanup the vector, clear the vectors
values it has been pointed to, a way to get the length of the amount of elements stored
in a vector, a way to get an element from the vector and a way to add an element to the vector.
I have used the class slides to understand the knowledge as well as:
ttps://www.cs.cmu.edu/~ab/15-123N09/lectures/Lecture%2005%20-%20Advanced%20pointers.pdf - was used
for the understanding of creating pointers and arrays in C, also helped me understand the use of
using pointers as input parameters and that it is value addresses rather than element value
https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/ -
Helped me to understand the basic elements of coding a lite vector and helped me to
understand the use of malloc, this site also helped me write the code for lv_append.
This site also helped me to better understand the use of pointers being static and
how to properly compile with this in mind

@author Ben Zardus 
@version CIS 343 Winter 2022
*****************************************************************/

#include "lite_vector.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
  
/*****************************************************************
    create a new lite_vector that allocating a memory of single element 
    of type "type_size" and using malloc to create a pointer value for 
    allocating memory to lite_vector initializing the length to 0 as start a
    nd the max capacity to 1, as for now the vector can only hold 1 element
    @param type_size number of bytes for a single element of the type
                     to be stored in the vector.
    @return the vector, or null if fails 
*****************************************************************/
lite_vector* lv_new_vec(size_t type_size){
    lite_vector* lv= (lite_vector*)malloc(sizeof (lite_vector));  
    lv->length = 0;  
    lv->data = (void*) malloc(sizeof (type_size)); 
    lv->max_capacity = 1;  
    lv->type_size = type_size;
    return lv;
}

/*****************************************************************
   Free the memory that is being used by the vector.
   first clearing up the memory used by lite_vector data. Then
   clearing the memory of the vector itself
   @param vec The address of the vector we wish to clear
   @return Sends true on success, or false otherwise.
*****************************************************************/
void lv_cleanup(lite_vector* vec){
    free(vec->data);  
    vec->length=0;
    vec->max_capacity=1;
    free(vec); 
}

/*****************************************************************
    getting the current number of elements in the vector by the 
    length of the vector, which is the number of elements stored inside the vector
    @param vec The address of the vector we want to know the length of.
    @return The vector length, or 0 if the operation fails.
*****************************************************************/
size_t lv_get_length(lite_vector* vec){
    return vec->length;  
}

/*****************************************************************
   clearing data of the vector where elements are stored and setting its values
   back to its initialized state, this is done by initializing the data with a
   memory of single element of type "type_size" if memory is allocated correctly
   it will returns True else False
   @param vec The address of the vector we want to know the length of.
   @return The vector length, or 0 if the operation fails.
*****************************************************************/
bool lv_clear(lite_vector* vec){
    free(vec->data);  
    vec->length = 0;
    vec->max_capacity= 1;
    vec->data = (void*) malloc(sizeof vec->type_size); 
    if(vec->data!=NULL)
        return true;  
    return false;
}

/*****************************************************************
   returning the element at a specific index if the index is in the 
   vector and is checked by using the pointer values length 
   @param vec The address of the vector we wish to retrieve from.
   @param index The index we wish to retrieve from.
   @return An element from the vector.  NULL if doesn't exist or
      the function cannot complete.
*****************************************************************/
void* lv_get(lite_vector* vec, size_t index){
    if(index < lv_get_length(vec)){
        return vec->data[index];  
    }
    else
        return NULL;
}

/*****************************************************************
   First, doubling the capacity of the vector. Then use realloc
   to reinitialize the data with memory of double the capacity.
   @param vec The address of the vector we wish to retrieve from.
   @return True if successful and false if not
*****************************************************************/
static bool lv_resize(lite_vector* vec){
    vec->max_capacity = 2*vec->max_capacity;   
    vec->data = realloc(vec->data,vec->max_capacity*(sizeof (vec->type_size)));
    return true;
}

/*****************************************************************
    First check if there is enough capacity to store the element
    and if there is add element to the vector that was given as a parameter 
    If there is space then capacity is added by when lv_resize is called
    this allows to be able to recursive call to the lv_append function
    @param vec The address of the vector we wish to add to.
    @param element The element we wish to add.
    @return Will return true if successful, false otherwise.
*****************************************************************/
bool lv_append(lite_vector* vec, void* element){
    if(vec->length<vec->max_capacity){  
        vec->data[vec->length] = element;
        vec->length++;
        return true;
    }
    else
    {
        lv_resize(vec);
        lv_append(vec,element); 
        return false;
    }
}


