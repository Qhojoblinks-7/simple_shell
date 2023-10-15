#include "main.h"

/**
 * isExecutable - Checks if a file is an executable command.
 * @info: The info struct.
 * @path: Path to the file.
 *
 * Return: 1 if it's an executable, 0 otherwise.
 */
int isExecutable(info_t *info, char *path)
{
    struct stat fileStat;

    (void)info;
    if (!path || stat(path, &fileStat))
        return (0);

    if (fileStat.st_mode & S_IFREG)
    {
        return (1);
    }
    return (0);
}

/**
 * extractSubstring - Extracts characters from a string within a specified range.
 * @source: The source string.
 * @start: Starting index.
 * @end: Ending index.
 *
 * Return: Pointer to a new buffer containing the extracted substring.
 */
char *extractSubstring(char *source, int start, int end)
{
    static char buffer[1024];
    int bufferIndex = 0, sourceIndex;

    for (sourceIndex = start; sourceIndex < end; sourceIndex++)
    {
        if (source[sourceIndex] != ':')
        {
            buffer[bufferIndex++] = source[sourceIndex];
        }
    }

    buffer[bufferIndex] = '\0';
    return (buffer);
}

/**
 * find_executable_path - Finds the full path of a command in the PATH string.
 * @info: The info struct.
 * @path_string: The PATH string.
 * @command: The command to find.
 *
 * Return: Full path of the command if found, or NULL if not found.
 */
char *findExecutablePath(info_t *info, char *pathString, char *command)
{
    int pathStart = 0;
    char *fullPath;
    int pathIndex = 0;


    if (!pathString)
    {
        return (NULL);
    }

    if ((stringLength(command) > 2) && stringStartsWith(command, "./"))
    {
        if (isExecutable(info, command))
        {
            return (command);
        }
    }

    while (1)
    {
        if (!pathString[pathIndex] || pathString[pathIndex] == ':')
        {
            fullPath = extractSubstring(pathString, pathStart, pathIndex);

            if (!*fullPath)
            {
                stringConcat(fullPath, command);
            }
            else
            {
                stringConcat(fullPath, "/");
                stringConcat(fullPath, command);
            }

            if (isExecutable(info, fullPath))
            {
                return (fullPath);
            }

            if (!pathString[pathIndex])
            {
                break;
            }

            pathStart = pathIndex;
        }
        pathIndex++;
    }

    return (NULL);
}
