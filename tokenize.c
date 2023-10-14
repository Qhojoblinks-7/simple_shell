#include "main.h"

/**
 * splitString - Splits a string into words using specified delimiters. Repeated delimiters are ignored.
 * @str: The input string to be split
 * @delimiters: A string containing delimiter characters
 * Return: A pointer to an array of strings (words), or NULL on failure
 */
char **splitString(char *str, char *delimiters) 
{
    int index, wordCount, wordLength, charIndex, wordIndex;
    char **wordsArray;

    if (str == NULL || str[0] == '\0')
    {
        return (NULL);
    }

    if (!delimiters)
    {
        delimiters = " ";
    }

    wordCount = countWords(str, delimiters);
    if (wordCount == 0)
    {
        return (NULL);
    }

    wordsArray = (char **)malloc((1 + wordCount) * sizeof(char *));
    if (!wordsArray)
    {
        return (NULL);
    }

    wordIndex = 0;
    for (index = 0; index < wordCount; index++)
    {
        while (isDelimiter(str[wordIndex], delimiters)) {
            wordIndex++;
        }

        wordLength = 0;
        while (!isDelimiter(str[wordIndex + wordLength], delimiters) && str[wordIndex + wordLength])
        {
            wordLength++;
        }

        wordsArray[index] = (char *)malloc((wordLength + 1) * sizeof(char));
        if (!wordsArray[index])
        {
            for (charIndex = 0; charIndex < index; charIndex++) {
                free(wordsArray[charIndex]);
            }
            free(wordsArray);
            return (NULL);
        }

        for (charIndex = 0; charIndex < wordLength; charIndex++)
        {
            wordsArray[index][charIndex] = str[wordIndex++];
        }
        wordsArray[index][charIndex] = '\0';
    }

    wordsArray[index] = NULL;
    return (wordsArray);
}

/**
 * splitStringBySingleDelimiter - Splits a string into words using a single delimiter character.
 * @str: The input string to be split
 * @delimiter: The delimiter character used for splitting
 * Return: A pointer to an array of strings (words), or NULL on failure
 */
char **splitStringBySingleDelimiter(char *str, char delimiter)
{
    int index, wordCount, wordLength, charIndex, wordIndex;
    char **wordsArray;

    if (str == NULL || str[0] == '\0')
    {
        return (NULL);
    }

    wordCount = countWordsBySingleDelimiter(str, delimiter);
    if (wordCount == 0)
    {
        return (NULL);
    }

    wordsArray = (char **)malloc((1 + wordCount) * sizeof(char *));
    if (!wordsArray)
    {
        return (NULL);
    }

    wordIndex = 0;
    for (index = 0; index < wordCount; index++)
    {
        while (str[wordIndex] == delimiter && str[wordIndex] != delimiter)
        {
            wordIndex++;
        }

        wordLength = 0;
        // Count the length of the current word
        while (str[wordIndex + wordLength] != delimiter && str[wordIndex + wordLength] && str[wordIndex + wordLength] != delimiter)
        {
            wordLength++;
        }

        wordsArray[index] = (char *)malloc((wordLength + 1) * sizeof(char));
        if (!wordsArray[index])
        {
            for (charIndex = 0; charIndex < index; charIndex++)
            {
                free(wordsArray[charIndex]);
            }
            free(wordsArray);
            return (NULL);
        }

        for (charIndex = 0; charIndex < wordLength; charIndex++)
        {
            wordsArray[index][charIndex] = str[wordIndex++];
        }
        wordsArray[index][charIndex] = '\0';
    }

    wordsArray[index] = NULL;
    return (wordsArray);
}

/**
 * countWords - Counts the number of words in a string using specified delimiters.
 * @str: The input string
 * @delimiters: A string containing delimiter characters
 * Return: The number of words
 */
int countWords(char *str, char *delimiters)
{
    int index, wordCount = 0;
    int len = strlen(str);

    for (index = 0; index < len; index++)
    {
        if (!isDelimiter(str[index], delimiters) &&
            (isDelimiter(str[index + 1], delimiters) || !str[index + 1]))
            {
            wordCount++;
        }
    }

    return (wordCount);
}

/**
 * countWordsBySingleDelimiter - Counts the number of words in a string using a single delimiter character.
 * @str: The input string
 * @delimiter: The delimiter character
 * Return: The number of words
 */
int countWordsBySingleDelimiter(char *str, char delimiter)
{
    int index, wordCount = 0;
    int len = strlen(str);

    for (index = 0; index < len; index++)
    {
        if ((str[index] != delimiter && str[index + 1] == delimiter) ||
            (str[index] != delimiter && !str[index + 1]) || str[index + 1] == delimiter)
            {
            wordCount++;
        }
    }

    return (wordCount);
}