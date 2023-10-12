#include "main.h"

/**
 * exitShell - Exits the shell with a given exit status.
 *
 * @info: Structure containing potential arguments.
 * Return: the exit status
 * -2 if info->argv[0] is "exit" and an argument is provided.
 * 1 if there is an argument, but it's not a valid number.
 * 0 if info->argv[0] is not "exit" or no argument is provided.
 */
int exitShell(info_t *info)
{
    if (strcmp(info->argv[0], "exit") == 0)
    {
        if (info->argv[1])
        {
            int exitCode = _erratoi(info->argv[1]);
            if (exitCode == -1)
            {
                info->status = 2;
                print_error(info, "Illegal number: ");
                _eputs(info->argv[1]);
                _eputchar('\n');
                return (1);
            }
            info->err_num = exitCode;
            return (-2);
        }
        else
        {
            info->err_num = -1;
            return (-2);
        }
    }
    else
    {
        return 0;
    }
}

#include <unistd.h>
#include <stdlib.h>

/**
 * changeDirectory - Changes the current directory of the process.
 *
 * info: Structure containing potential arguments.
 * Return: Always 0.
 */
int changeDirectory(info_t *info)
{
    char *currentDir, *newDir;
    int chdirResult;

    currentDir = getcwd(NULL, 0); /*Get the current directory*/

    if (!currentDir)
    {
        _puts("Error: Unable to retrieve current directory\n");
        return (0);
    }

    if (!info->argv[1])
    {
        newDir = _getenv(info, "HOME=");
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        newDir = _getenv(info, "OLDPWD=");
        if (!newDir)
        {
            _puts(currentDir);
            _putchar('\n');
            free(currentDir);
            return (1);
        }
    }
    else
    {
        newDir = info->argv[1];
    }
    chdirResult = chdir(newDir);

    if (chdirResult == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", currentDir);
        _setenv(info, "PWD", getcwd(NULL, 0));
    }


    free(currentDir);
    return 0;
}

/**
 * Displays a help message for the shell.
 *
 * @param info Structure containing potential arguments.
 * @return Always 0.
 */
int displayHelp(info_t *info)
{
    _puts("Welcome to YourShell Help\n");
    _puts("Available commands:\n");
    _puts("  help - Display this help message\n");
    _puts("  cd - Change the current directory\n");
    _puts("  exit - Exit the shell\n");

    return 0;
}
