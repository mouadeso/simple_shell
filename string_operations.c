#include "shell.h"

/**
 * copyString - copies a string with a specified length
 * @destination: the destination string to be copied to
 * @source: the source string
 * @length: the number of characters to be copied
 * Return: the concatenated string
 */
char *copyString(char *destination, char *source, int length)
{
    int i, j;
    char *result = destination;

    i = 0;
    while (source[i] != '\0' && i < length - 1)
    {
        destination[i] = source[i];
        i++;
    }
    if (i < length)
    {
        j = i;
        while (j < length)
        {
            destination[j] = '\0';
            j++;
        }
    }
    return result;
}

/**
 * concatenateStrings - concatenates two strings with a specified length
 * @destination: the first string
 * @source: the second string
 * @length: the maximum number of bytes to be used
 * Return: the concatenated string
 */
char *concatenateStrings(char *destination, char *source, int length)
{
    int i, j;
    char *result = destination;

    i = 0;
    j = 0;
    while (destination[i] != '\0')
        i++;
    while (source[j] != '\0' && j < length)
    {
        destination[i] = source[j];
        i++;
        j++;
    }
    if (j < length)
        destination[i] = '\0';
    return result;
}

/**
 * findCharacterInString - locates a character in a string
 * @string: the string to search
 * @character: the character to look for
 * Return: a pointer to the memory area containing the character
 */
char *findCharacterInString(char *string, char character)
{
    do {
        if (*string == character)
            return string;
    } while (*string++ != '\0');

    return NULL;
}

