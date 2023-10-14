#include "main.h"

/**
 * getEnviron - Returns a string array copy of our environ
 * @info: The structure containing potential arguments
 *
 * Return: A pointer to the string array
 */
char **getEnviron(info_t *info)
{
    if (!info->environ || info->envChanged)
    {
        info->environ = listToStrings(info->env);
        info->envChanged = 0;
    }

    return (info->environ);
}

/**
 * unsetEnvironmentVariable - Removes an environment variable
 * @info: The parameter struct
 * @var: The string representing the environment variable
 *
 * Return: 1 if the variable is deleted, 0 otherwise
 */
int unsetEnvironmentVariable(info_t *info, char *var)
{
    list_t *currentNode = info->env;
    size_t currentIndex = 0;
    char *ptr;

    if (!currentNode || !var)
    {
        return (0);
    }

    while (currentNode)
    {
        ptr = startsWith(currentNode->str, var);

        if (ptr && *ptr == '=')
        {
            info->envChanged = deleteNodeAtIndex(&(info->env), currentIndex);
            currentIndex = 0;
            currentNode = info->env;
            continue;
        }

        currentNode = currentNode->next;
        currentIndex++;
    }

    return (info->envChanged);
}

/**
 * setEnvironmentVariable - Initializes a new environment variable
 * or modifies an existing one
 * @info: The parameter struct
 * @var: The string env var property
 * @value: The string env var value
 *
 * Return: 0 on success, 1 on failure
 */
int setEnvironmentVariable(info_t *info, char *var, char *value)
{
    char *envVarString = NULL;
    list_t *currentNode;
    char *ptr;

    if (!var || !value)
    {
        return (1);
    }

    envVarString = malloc(stringLength(var) + stringLength(value) + 2);

    if (!envVarString)
    {
        return (1);
    }

    stringCopy(envVarString, var);
    stringConcat(envVarString, "=");
    stringConcat(envVarString, value);

    currentNode = info->env;

    while (currentNode)
    {
        ptr = startsWith(currentNode->str, var);

        if (ptr && *ptr == '=')
        {
            free(currentNode->str);
            currentNode->str = envVarString;
            info->envChanged = 1;
            return 0;
        }

        envVarString = currentNode->next;
    }

    addNodeEnd(&(info->env), envVarString, 0);
    free(envVarString);
    info->envChanged = 1;

    return (0);
}
