#include "main.h"

/**
 * isShellInteractive - Check if the shell is running in interactive mode.
 *
 * @param: info Pointer to the struct address.
 * Return: 1 if interactive mode, 0 otherwise.
 */
int isShellInteractive(info_t *info)
{
	int stdinFileDescriptor = STDIN_FILENO;
	int isStandardInputTerminal = isatty(stdinFileDescriptor);
	int isReadFdValid = (info->readfd >= 0 && info->readfd <= 2);

	return (isStandardInputTerminal && isReadFdValid);
}

/**
 * isDelimiter - Checks if a character is a delimiter.
 *
 * @character: The character to check.
 * @delim: The delimiter string.
 * Return: 1 if the character is a delimiter, 0 if it is not.
 */
int isDelimiter(char character, const char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == character)
		{
			return (1);
		}
		delim++;
	}
	return (0);
}

/**
 * isAlpha - Checks if a character is an alphabetic character.
 *
 * @character: The character to check.
 * Return: 1 if c is an alphabetic character, 0 otherwise.
 */
int isAlpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0;
}

#include <stdio.h>

/**
 * stringToInt - Converts a string to an integer.
 *
 * @s: The string to be converted.
 * Return: The converted number or 0 if no numbers are found in the string.
 */
int stringToInt(const char *s)
{
	int result = 0;
	int sign = 1;
	int foundNumber = 0;

	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
		{
			sign = -1;
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			result = result * 10 + (s[i] - '0');
			foundNumber = 1;
		}
		else if (foundNumber)
		{
			/*Stop processing if non-numeric characters are encountered after digits*/
			break;
		}
	}

	return (result * sign);
}
