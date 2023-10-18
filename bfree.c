#include "shell.h"

/**
 * bfree - Frees a pointer and sets it to NULL.
 * @ptr: Address of the pointer to free.
 *
 * This function frees the memory pointed to by 'ptr' and sets 'ptr' to NULL
 * to prevent potential dangling pointers.
 *
 * Return: 1 if 'ptr' was freed, otherwise 0.
 */
int bfree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);   
        *ptr = NULL;   
        return 1;
    }
    return 0;
}
