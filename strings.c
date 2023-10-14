#include "main.h"

/**
 * stringNumCopy - Copies a string up to a specified number of characters
 * @dest: The destination string to be copied to
 * @src: The source string
 * @n: The maximum number of characters to be copied
 *
 * Return: A pointer to the concatenated string
 */
char *stringNumCopy(char *dest, const char *src, int n)
{
    int src_index = 0, dest_index = 0;
    char *result = dest;

    while (src[src_index] != '\0' && dest_index < n)
    {
        dest[dest_index] = src[src_index];
        src_index++;
        dest_index++;
    }

    while (dest_index < n)
    {
        dest[dest_index] = '\0';
        dest_index++;
    }

    return (result);
}

/**
 * stringNumConcat - Concatenates two strings, limiting the number of bytes to be used
 * @dest: The destination string (the first string)
 * @src: The source string (the second string)
 * @n: The maximum number of bytes to be used
 *
 * Return: A pointer to the concatenated string
 */
char *stringNumConcat(char *dest, const char *src, int n)
{
    int dest_index = 0, src_index = 0;
    char *result = dest;

    while (dest[dest_index] != '\0')
    {
        dest_index++;
    }

    while (src[src_index] != '\0' && src_index < n)
    {
        dest[dest_index] = src[src_index];
        dest_index++;
        src_index++;
    }

    if (src_index < n)
    {
        dest[dest_index] = '\0';
    }

    return (result);
}

/**
 * stringLocateChar - Locates a character in a string
 * @s: The string to be searched
 * @c: The character to find
 *
 * Return: A pointer to the first occurrence of the character in the string, or NULL if not found.
 */
char *stringLocateChar(const char *str, char character)
{
    while (*str != '\0')
    {
        if (*str == character)
        {
            return ((char *)str);
        }
        str++;
    }

    return (NULL);
}
