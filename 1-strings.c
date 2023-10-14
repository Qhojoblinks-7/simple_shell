#include "main.h"

/**
 * stringLength - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of the string
 */
int stringLength(char *str) {
    int length = 0;

    if (!str) {
        return 0;
    }

    while (*str++) {
        length++;
    }

    return length;
}

/**
 * stringCompare - performs lexicographic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, positive if str1 > str2, zero if str1 == str2
 */
int stringCompare(char *str1, char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return (*str1 - *str2);
        }
        str1++;
        str2++;
    }

    if (*str1 == *str2) {
        return 0;
    } else {
        return (*str1 < *str2 ? -1 : 1);
    }
}

/**
 * stringStartsWith - checks if the haystack starts with the needle
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of the next character in haystack or NULL
 */
char *stringStartsWith(const char *haystack, const char *needle) {
    while (*needle) {
        if (*needle++ != *haystack++) {
            return NULL;
        }
    }
    return (char *)haystack;
}

/**
 * stringConcatenate - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to the destination buffer
 */
char *stringConcat(char *destination, char *source) {
    char *result = destination;

    while (*destination) {
        destination++;
    }

    while (*source) {
        *destination++ = *source++;
    }

    *destination = *source;
    
    return result;
}
