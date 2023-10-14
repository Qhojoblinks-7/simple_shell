#include "main.h"

/**
 * convertStringToInteger - Converts a string to an integer.
 *
 * @str: The string to be converted.
 * Return: The converted number, 0 if no numbers in the string, -1 on error.
 */
int convertStringToInteger(char *str) 
{
    int index = 0;
    unsigned long int result = 0;

    if (*str == '+') {
        str++; /*Skip leading '+'*/
    }

    for (index = 0; str[index] != '\0'; index++)
    {
        if (str[index] >= '0' && str[index] <= '9')
        {
            result *= 10;
            result += (str[index] - '0');

            if (result > INT_MAX)
            {
                return (-1); /*Integer overflow error*/
            }
        }
        else
        {
            return (-1); /*Error if non-numeric character found*/
        }
    }

    return ((int)result);
}

/**
 * Prints an error message.
 *
 * @info: The parameter and return info struct.
 * @errorString: String containing the specified error type.
 */
void printErrorMessage(info_t *info, char *errorString)
{
    printString(info->fname);
    printString(": ");
    printToStdErr(info->lineCount, STDERR_FILENO);
    printString(": ");
    printString(info->arguments[0]);
    printString(": ");
    printString(errorString);
}

/**
 * printDecimal - Prints a decimal (integer) number (base 10).
 *
 * @input: The input number.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int printDecimal(int input, int fd)
{
    int (*outputChar)(char) = (fd == STDERR_FILENO) ? writeCharacterToStdErr : printCharacter;
    int i, count = 0;
    unsigned int absoluteValue, current;

    if (input < 0)
    {
        absoluteValue = -input;
        outputChar('-');
        count++;
    }
    else
    {
        absoluteValue = input;
    }

    current = absoluteValue;

    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absoluteValue / i)
        {
            outputChar('0' + current / i);
            count++;
        }
        current %= i;
    }

    outputChar('0' + current);
    count++;

    return (count);
}

/**
 * convertNumberToString - Converts a number to a string using the
 * specified base.
 *
 * @num: The number to be converted.
 * @base: The base for conversion.
 * @flags: Argument flags.
 * Return: The converted string.
 */
char *convertNumberToString(long int num, int base, int flags)
{
    static char *charArray;
    static char stringBuffer[50];
    char sign = 0;
    char *stringPtr;
    unsigned long absoluteValue = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        absoluteValue = -num;
        sign = '-';
    }

    charArray = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    stringPtr = &stringBuffer[49];
    *stringPtr = '\0';

    do
    
    {
        *--stringPtr = charArray[absoluteValue % base];
        absoluteValue /= base;
    } while (absoluteValue != 0);

    if (sign)
    {
        *--stringPtr = sign;
    }

    return (stringPtr);
}

/**
 * removeComments - Replaces the first instance of '#' with '\0' to remove comments from the string.
 *
 * @buf: The address of the string to modify.
 */
void removeComments(char *buf)
{
    int index;

    for (index = 0; buf[index] != '\0'; index++)
    {
        if (buf[index] == '#' && (!index || buf[index - 1] == ' '))
        {
            buf[index] = '\0';
            break;
        }
    }
}
