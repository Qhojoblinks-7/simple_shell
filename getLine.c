#include "main.h"

/**
 * input_buf - Buffers input for chained commands
 * @info: The parameter struct
 * @buf: A pointer to the buffer
 * @len: A pointer to the length variable
 *
 * Return: The number of bytes read
 */
ssize_t inputBuffer(info_t *info, char **buf, size_t *len)
{
    ssize_t bytesRead = 0;
    size_t bufferLength = 0;

    if (!*len) /* If there's nothing left in the buffer, fill it */
    {
        /* Free any existing buffer */
        free(*buf);
        *buf = NULL;
        signal(SIGINT, sigintHandler);

        #if USE_GETLINE
            bytesRead = _getline(buf, &bufferLength, stdin);
        #else
            bytesRead = _getline(info, buf, &bufferLength);
        #endif

        if (bytesRead > 0)
        {
            if ((*buf)[bytesRead - 1] == '\n')
            {
                (*buf)[bytesRead - 1] = '\0'; /* Remove trailing newline */
                bytesRead--;
            }

            info->lineCountFlag = 1;
            removeComments(*buf);
            buildHistoryList(info, *buf, info->histcounter++);

            /* Check if this is a command chain */
            /* if (stringLocateChar(*buf, ';')) */

            *len = bytesRead;
            info->cmd_buf = buf;
        }
    }

    return (bytesRead);
}

/**
 * getInput - Gets a line of input without the newline character
 * @info: The parameter struct
 *
 * Return: The number of bytes read
 */
ssize_t getInput(info_t *info)
{
    static char *commandChainBuffer; /* The ';' command chain buffer */
    static size_t currentPos, nextCommandPos, bufferLength;
    ssize_t bytesRead = 0;
    char **bufferPtr = &(info->arg), *commandStart;

    printCharacter(BUF_FLUSH);

    bytesRead = inputBuffer(info, &commandChainBuffer, &bufferLength);

    if (bytesRead == -1) /* EOF */
    {
        return (-1);
    }

    if (bufferLength) /* There are commands left in the chain buffer */
    {
        nextCommandPos = currentPos; /* Initialize new iterator to the current buffer position */
        commandStart = commandChainBuffer + currentPos; /* Get a pointer for return */

        checkCommandChain(info, commandChainBuffer, &nextCommandPos, currentPos, bufferLength);

        while (nextCommandPos < bufferLength) /* Iterate to semicolon or end */
        {
            if (isCommandChain(info, commandChainBuffer, &nextCommandPos))
            {
                break;
            }
            nextCommandPos++;
        }

        currentPos = nextCommandPos + 1; /* Increment past the nullified ';' */

        if (currentPos >= bufferLength) /* Reached the end of the buffer? */
        {
            currentPos = bufferLength = 0; /* Reset the position and length */
            info->cmd_buf_type = CMD_NORM;
        }

        *bufferPtr = commandStart; /* Pass back a pointer to the current command position */
        return (stringLength(commandStart)); /* Return the length of the current command */
    }

    *bufferPtr = commandChainBuffer; /* Not a chain; pass back the buffer from _getline() */
    return (bytesRead); /* Return the length of the buffer from _getline() */
}

/**
 * read_buf - Reads data into a buffer
 * @info: The parameter struct
 * @buf: The buffer to read into
 * @i: The size of the buffer
 *
 * Return: The number of bytes read
 */
ssize_t readBuffer(info_t *info, char *buf, size_t *bufferSize)
{
    ssize_t bytesRead = 0;

    if (*bufferSize)
    {
        return (0);
    }

    bytesRead = read(info->readfd, buf, READ_BUF_SIZE);

    if (bytesRead >= 0)
    {
        *bufferSize = bytesRead;
    }

    return (bytesRead);
}

/**
 * _getline - Reads the next line of input from STDIN
 * @info: The parameter struct
 * @ptr: A pointer to the buffer, either preallocated or NULL
 * @length: The size of the preallocated ptr buffer if not NULL
 *
 * Return: The number of characters read
 */
int getlineFromStdin(info_t *info, char **ptr, size_t *length)
{
    static char buffer[READ_BUF_SIZE];
    static size_t currentIndex = 0, bufferLength = 0;
    size_t charactersRead = 0;
    ssize_t bytesRead = 0;
    char *currentPointer = NULL, *newPointer = NULL, *newlinePosition = NULL;

    currentPointer = *ptr;

    if (currentPointer && length)
    {
        charactersRead = *length;
    }

    if (currentIndex == bufferLength)
    {
        currentIndex = bufferLength = 0;
    }

    bytesRead = readBuffer(info, buffer, &bufferLength);

    if (bytesRead == -1 || (bytesRead == 0 && bufferLength == 0))
    {
        return (-1);
    }

    newlinePosition = stringLocatechar(buffer + currentIndex, '\n');
    size_t charactersToCopy = newlinePosition ? (1 + (unsigned int)(newlinePosition - (buffer + currentIndex))) : bufferLength;

    newPointer = customRealloc(currentPointer, charactersRead, charactersRead ? (charactersRead + charactersToCopy) : (charactersToCopy + 1));

    if (!newPointer) /* MALLOC FAILURE! */
    {
        if (currentPointer)
        {
            free(currentPointer);
        }
        return (-1);
    }

    if (charactersRead)
    {
        stringConcat(newPointer, buffer + currentIndex, charactersToCopy - currentIndex);
    }
    else
    {
        stringCopy(newPointer, buffer + currentIndex, charactersToCopy - currentIndex + 1);
    }

    charactersRead += charactersToCopy - currentIndex;
    currentIndex = charactersToCopy;
    currentPointer = newPointer;

    if (length)
    {
        *length = charactersRead;
    }

    *ptr = currentPointer;

    return (charactersRead);
}

/**
 * sigintHandler - Handles the Ctrl-C signal by printing a newline and prompt
 * @sig_num: The signal number (unused, but required by the signal handler)
 *
 * Return: void
 */
void handleCtrlC(__attribute__((unused))int sig_num)
{
    printString("\n");  /* Print a newline to separate lines */
    printString("$ ");   /* Print the shell prompt */
    printCharacter(BUF_FLUSH);  /* Flush the buffer */
}

