#include "main.h"

/**
 * exitShell - Exits the shell with a given exit status.
 *
 * @info: Structure containing potential arguments.
 * Return: the exit status
 * -2 if info->arguments[0] is "exit" and an argument is provided.
 * 1 if there is an argument, but it's not a valid number.
 * 0 if info->arguments[0] is not "exit" or no argument is provided.
 */
int exitShell(info_t *info)
{
    if (strcmp(info->arguments[0], "exit") == 0)
    {
        if (info->arguments[1])
        {
            int exitCode = convertStringToInteger(info->arguments[1]);
            if (exitCode == -1)
            {
                info->status = 2;
                printError(info, "Illegal number: ");
                printString(info->arguments[1]);
                writeCharacterToStdErr('\n');
                return (1);
            }
            info->errorNumber = exitCode;
            return (-2);
        }
        else
        {
            info->errorNumber = -1;
            return (-2);
        }
    }
    else
    {
        return (0);
    }
}


/**
 * changeDirectory - Changes the current directory of the process.
 *
 * info: Structure containing potential arguments.
 * Return: Always 0.
 */
int changeDirectory(info_t *info)
{
    char *currentDir, *newDir, buffer[1024];
    int chdirRet;

    currentDir = getcwd(buffer, 1024);
    if (!currentDir)
    {
        printString("TODO: >>getcwd failure emsg here<<\n");
    }
    
    if (!info->arguments[1])
    {
        newDir = getEnvironment(info, "HOME=");
        if (!newDir)
        {
            chdirRet = chdir((newDir = getEnvironment(info, "PWD=")) ? newDir : "/");
        }
        else
        {
            chdirRet = chdir(newDir);
        }
    }
    else if (stringCompare(info->arguments[1], "-") == 0)
    {
        if (!getEnvironment(info, "OLDPWD="))
        {
            printString(currentDir);
            printCharacter('\n');
            return 1;
        }
        printString(getEnvironment(info, "OLDPWD="));
        printCharacter('\n');
        chdirRet = chdir((newDir = getEnvironment(info, "OLDPWD=")) ? newDir : "/");
    }
    else
    {
        chdirRet = chdir(info->arguments[1]);
    }

    if (chdirRet == -1) {
        printError(info, "can't cd to ");
        printString(info->arguments[1]);
        writeCharacterToStdErr('\n');
    } else {
        setEnvironmentVariable(info, "OLDPWD", getEnvironment(info, "PWD="));
        setEnvironmentVariable(info, "PWD", getcwd(buffer, 1024));
    }

    return (0);
}


/**
 * Displays a help message for the shell.
 *
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int displayHelp(info_t *info)
{
    if (info)
    {
        printString("Welcome to YourShell Help\n");
        printString("Available commands:\n");
        printString("  help - Display this help message\n");
        printString("  cd - Change the current directory\n");
        printString("  exit - Exit the shell\n");
        return (0);
    }
    else
    {
        printString("Error: 'info' parameter is NULL\n");
        return 1; 
    }
}
