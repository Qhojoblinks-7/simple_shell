#include "main.h"

/**
 * stringCopy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to destination
 */
char *stringCopy(char *destination, const char *source) {
    int i = 0;

    if (destination == source || source == NULL)
        return destination;

    while (source[i]) {
        destination[i] = source[i];
        i++;
    }

    destination[i] = '\0';
    return destination;
}

/**
 * stringDuplicate - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *stringDuplicate(const char *str) {
    int length = 0;
    char *duplicate;

    if (str == NULL)
        return NULL;

    while (*str++) {
        length++;
    }

    duplicate = malloc(sizeof(char) * (length + 1));
    if (duplicate == NULL)
        return NULL;

    for (length++; length--;) {
        duplicate[length] = *--str;
    }

    return duplicate;
}

/**
 * printString - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void printString(char *str) {
    int i = 0;

    if (str == NULL)
        return;

    while (str[i] != '\0') {
        printCharacter(str[i]);
        i++;
    }
}

/**
 * printCharacter - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int printCharacter(char c) {
    static int index;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || index >= WRITE_BUF_SIZE) {
        write(1, buffer, index);
        index = 0;
    }

    if (c != BUF_FLUSH) {
        buffer[index++] = c;
    }

    return 1;
}
