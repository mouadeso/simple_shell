#include "shell.h"

/**
 * custom_memset - fills memory with a specified byte
 * @s: pointer to the memory area
 * @b: byte to fill *s with
 * @n: number of bytes to be filled
 * Return: pointer to the memory area s
 */
char *custom_memset(char *s, char b, unsigned int n)
{
    unsigned int i;

    for (i = 0; i < n; i++)
        s[i] = b;
    return s;
}

/**
 * free_string_array - frees a string array
 * @str_array: string array to be freed
 */
void free_string_array(char **str_array)
{
    char **temp = str_array;

    if (!str_array)
        return;
    while (*str_array)
        free(*str_array++);
    free(temp);
}

/**
 * custom_realloc - reallocates a block of memory
 * @ptr: pointer to the previous memory block
 * @old_size: size of the previous block
 * @new_size: size of the new block
 * Return: pointer to the reallocated memory block
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    char *p;

    if (!ptr)
        return malloc(new_size);
    if (!new_size)
        return (free(ptr), NULL);
    if (new_size == old_size)
        return ptr;

    p = malloc(new_size);
    if (!p)
        return NULL;

    old_size = old_size < new_size ? old_size : new_size;
    while (old_size--)
        p[old_size] = ((char *)ptr)[old_size];
    free(ptr);
    return p;
}

