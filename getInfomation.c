#include "main.h"

/**
 * initializeInfoStruct - Initializes an info_t structure
 * @info: A pointer to the info_t structure to be initialized
 */
void initializeInfoStruct(info_t *info)
{
    info->arg = NULL;
    info->arguments = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * initializeInfoFromCommandLine - Initializes an info_t structure with command line arguments
 * @info: A pointer to the info_t structure to be initialized
 * @commandLineArgs: The command line arguments (argument vector)
 */
void initializeInfoFromCommandLine(info_t *info, char **commandLineArgs)
{
    int argumentCount = 0;
    int i = 0;

    info->fname = commandLineArgs[0];

    if (info->arg)
    {
        info->arguments = splitString(info->arg, " \t");

        if (!info->arguments)
        {
            info->arguments = malloc(sizeof(char *) * 2);

            if (info->arguments)
            {
                info->arguments[0] = stringDuplicate(info->arg);
                info->arguments[1] = NULL;
            }
        }

        for (i = 0; info->arguments && info->arguments[i]; i++)
        {
            argumentCount++;
        }

        info->argc = argumentCount;

        replaceAliases(info);
        replaceVariables(info);
    }
}

/**
 * freeInfoStructure - Frees the memory associated with an info_t structure
 * @info: A pointer to the info_t structure
 * @freeAllFields: If true, free all fields; otherwise, only free specific fields
 */
void freeInfoStructure(info_t *info, int freeAllFields)
{
    freeStringArray(info->arguments);
    info->arguments = NULL;
    info->path = NULL;

    if (freeAllFields)
    {
        if (!info->cmd_buf)
            free(info->arg);

        if (info->env)
            freeList(&(info->env));

        if (info->history)
            freeList(&(info->history));

        if (info->alias)
            freeList(&(info->alias));

        freeStringArray(info->environ);
        info->environ = NULL;

        befreed((void **)info->cmd_buf);

        if (info->readfd > 2)
            close(info->readfd);

        printCharacter(BUF_FLUSH);
    }
}

