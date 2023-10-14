#include "main.h" 
/**
 * bfree - Frees memory and sets the pointer to NULL
 * @ptr: A pointer to the memory to be freed
 *
 * This function frees the memory pointed to by
 * 'ptr' and sets 'ptr' to NULL.
 *
 * Return: 1 if successful, 0 if
 * 'ptr' is already NULL or uninitialized.
 */
int befreed(void **ptr)
{
    /*Check if 'ptr' is not NULL and it points to valid memory*/
    if (ptr && *ptr)
    {
        /*Free the memory pointed to by 'ptr'*/
        free(*ptr);
        
        /*Set 'ptr' to NULL to avoid accessing freed memory*/
        *ptr = NULL;
        
        return (1); /*Memory freed successfully*/
    }
    
    return 0; /*'ptr' was already NULL or uninitialized*/
}
