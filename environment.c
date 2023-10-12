#include "main.h"

/**
 * printEnvironment - Prints the current environment variables.
 *
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int printEnvironment(info_t *info)
{
    /*Call a function (print_list_str) to display the environment variables*/
    print_list_str(info->env);
    return 0;
}

/**
 * getEnvironment - Gets the value of an environment variable.
 *
 * @info: Structure containing potential arguments.
 * @name: The name of the environment variable.
 * Return: The value of the environment variable, or NULL if not found.
 */
char *getEnvironment(info_t *info, const char *name)
{
    list_t *currentNode = info->env;
    char *value;

    while (currentNode)
    {
        char *variableName = starts_with(currentNode->str, name);

        if (variableName && *variableName)
        {
            /*if a match is found, return the value*/
            value = variableName;
            return (value);
        }

        currentNode = currentNode->next;
    }

    /*Return NULL if the environment variable is not found*/
    return (NULL);
}

/**
 * setEnvironment - Initialize a new environment variable or modify an
 * existing one.
 *
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on incorrect number of arguments.
 */
int setEnvironment(info_t *info)
{
    if (info->argc != 3)
    {
        printString("Incorrect number of arguments\n");
        return (1);
    }

    if (_setenv(info, info->argv[1], info->argv[2]))
    {
        return (0);
    }

    return (1);
}

/**
 * unsetEnvironment - Remove environment variables.
 *
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on incorrect number of arguments.
 */
int unsetEnvironment(info_t *info)
{
    int count;

    if (info->argc == 1)
    {
        printString("Too few arguments.\n");
        return (1);
    }

    for (count = 1; count < info->argc; i++)
    {
        _unsetenv(info, info->argv[i]);
    }

    return (0);
}

/**
 * populateEnvironmentList - Populates the environment linked list.
 *
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int populateEnvironmentList(info_t *info) 
{
    list_t *currentNode = NULL;
    size_t i;

    /*Loop through the environ array and add nodes to the environment linked list*/
    for (i = 0; environ[i]; i++)
    {
        add_node_end(&currentNode, environ[i], 0);
    }

    /*Assign the populated linked list to the info structure*/
    info->env = currentNode;

    return (0);
}
