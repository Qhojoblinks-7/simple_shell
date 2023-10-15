#include "main.h"

/**
 * mainShellLoop - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int mainShellLoop(info_t *info, char **av)
{
    ssize_t bytesRead = 0;
    int builtinResult = 0;

    while (bytesRead != -1 && builtinResult != -2) 
    {
        clearInfo(info);
        if (findBuiltin(info))
            printPrompt();
        printBufferFlush();

        bytesRead = getInput(info);
        if (bytesRead != -1)
        {
            setInfo(info, av);
            builtinResult = findBuiltin(info);
            if (builtinResult == -1)
                forkCommand(info);
        } else if (findBuiltin(info))
            printNewline();

        freeInfo(info, 0);
    }

    writeHistory(info);
    freeInfo(info, 1);
    if (!findBuiltin(info) && info->status)
        exit(info->status);
    if (builtinResult == -2)
    {
        if (info->errorNumber == -1)
            exit(info->status);
        exit(info->errorNumber);
    }
    return (builtinResult);
}

int findBuiltin(info_t *info)
{
    int i, builtinResult = -1;
    builtinTable builtinTable[] =
    {
        {"exit", exitShell},
        {"env", printEnvironment},
        {"help", displayHelp},
        {"history", displayHistory},
        {"setenv", setEnvironment},
        {"unsetenv", unsetEnvironment},
        {"cd", changeDirectory},
        {"alias", manageAliases},
        {NULL, NULL}
    };

    for (i = 0; builtinTable[i].type; i++)
    {
        if (stringsAreEqual(info->arguments[0], builtinTable[i].type) == 0)
        {
            info->lineCount++;
            builtinResult = builtinTable[i].func(info);
            break;
        }
    }
    return (builtinResult);
}

void forkCommand(info_t *info)
{
    char *path = NULL;
    int i, argumentCount = 0;

    info->path = info->arguments[0];
    if (info->lineCountFlag == 1)
    {
        info->lineCount++;
        info->lineCountFlag = 0;
    }
    for (i = 0; info->arguments[i]; i++)
    {
        if (!isDelimiter(info->arguments[i], " \t\n"))
        {
            argumentCount++;
        }
    }

    if (!argumentCount)
    {
        return;
    }

    path = findPath(info, setEnvironmentVariable(info, "PATH="), info->arguments[0]);
    if (path)
    {
        info->path = path;
        forkCommand(info);
    }
    else
    {
        if ((findBuiltin(info) || setEnvironmentVariable(info, "PATH=") ||
             info->arguments[0][0] == '/') && forkCommand(info, info->arguments[0]))
             {
            forkCommand(info);
        }
        else if (*(info->arguments) != '\n')
        {
            info->status = 127;
            printError(info, "not found\n");
        }
    }
}

/*void forkCommand(info_t *info)
{
    char *path = NULL;
    int i, argumentCount = 0;

    info->path = info->arguments[0];
    if (info->lineCountFlag == 1)
    {
        info->lineCount++;
        info->lineCountFlag = 0;
    }
    for (i = 0; info->arguments[i]; i++)
    {
        char *argument = info->arguments[i];
        for (int j = 0; argument[j]; j++) {
            if (!isDelimiter(argument[j], " \t\n"))
            {
                argumentCount++;
            }
        }
    }

    if (!argumentCount)
    {
        return;
    }
}*/

void clearInfo(info_t *info)
{
    if (info)
    {
        free(info->arg);
        freeList(info->env);
        freeList(info->history);
        freeList(info->alias);
        free(info->cmd_buf);

        info->arg = NULL;
        info->env = NULL;
        info->history = NULL;
        info->alias = NULL;
        info->cmd_buf = NULL;
        
        free(info);
    }
}