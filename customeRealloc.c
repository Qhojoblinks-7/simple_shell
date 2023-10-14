#include "main.h"

/**
 * memorySet - Fills memory with a constant byte
 * @s: The pointer to the memory area
 * @b: The byte to fill *s with
 * @n: The number of bytes to be filled
 *
 * Return: A pointer to the memory area s
 */
char *memorySet(char *str, char byte, unsigned int number)
{
    unsigned int i;

    for (i = 0; i < number; i++)
        str[i] = byte;

    return (str);
}

/**
 * freeStringArray - Frees a string array and its elements
 * @strArr: The string array to free
 */
void freeStringArray(char **strArr)
{
    char **temp = strArr;

    if (!strArr)
        return;

    while (*strArr)
    {
        free(*strArr);
        strArr++;
    }

    free(temp);
}

/**
 * customRealloc - Reallocates a block of memory
 * @ptr: Pointer to the previous malloc'ed block
 * @oldSize: Byte size of the previous block
 * @newSize: Byte size of the new block
 *
 * Return: Pointer to the reallocated block
 */
void *customRealloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
    char *newPtr;

    if (!ptr)
        return malloc(newSize);

    if (!newSize)
    {
        free(ptr);
        return NULL;
    }

    if (newSize == oldSize)
        return ptr;

    newPtr = malloc(newSize);

    if (!newPtr)
        return NULL;

    oldSize = oldSize < newSize ? oldSize : newSize;
    while (oldSize--)
    {
        newPtr[oldSize] = ((char *)ptr)[oldSize];
    }

    free(ptr);
    return newPtr;
}
