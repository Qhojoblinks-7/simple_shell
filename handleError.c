#include "main.h"

/**
 * printString - Prints an input string.
 *
 * @str: The string to be printed.
 */
void printString(char *str)
{
    int index = 0;

    if (!str) {
        return;
    }

    while (str[index] != '\0')
    {
        writeCharacterToStdErr(str[index]);
        index++;
    }
}

/**
 * writeCharacterToStdErr - Writes a character to stderr.
 *
 * @c: The character to print.
 * Return: 1 on success, -1 on error.
 */
int writeCharacterToStdErr(char character)
{
    static int bufferIndex;
    static char charBuffer[WRITE_BUF_SIZE];

    if (character == BUF_FLUSH || bufferIndex >= WRITE_BUF_SIZE)
    {
        write(2, charBuffer, bufferIndex);
        bufferIndex = 0;
    }

    if (character != BUF_FLUSH)
    {
        charBuffer[bufferIndex++] = character;
    }
}

/**
 * charToFileDescriptor - Writes the character c to the given file descriptor.
 *
 * @character: The character to print.
 * @fd: The file descriptor to write to.
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int charToFileDescriptor(char character, int fd)
{
    static int bufferIndex;
    static char charBuffer[WRITE_BUF_SIZE];

    if (character == BUF_FLUSH || bufferIndex >= WRITE_BUF_SIZE)
    {
        /*If buffer is full or flush character is encountered, write to the file descriptor*/
        write(fd, charBuffer, bufferIndex);
        bufferIndex = 0;
    }

    if (character != BUF_FLUSH)
    {
        /*Store character in the buffer (except for the flush character)*/
        charBuffer[bufferIndex++] = character;
    }

    return (1);
}

/**
 * Prints an input string to the given file descriptor.
 *
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters written.
 */
int printStringToFileDescriptor(char *str, int fd)
{
    int charCount = 0;

    if (!str)
    {
        return 0; /* Return 0 if the string is NULL*/
    }

    while (*str)
    {
        charCount += charToFileDescriptor(*str++, fd);
    }

    return charCount;
}
